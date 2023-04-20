/*
########   Class Robot - Implementation	  ########
#####                                        #####
#####      Classe produite et ecrite par     #####
#####            Ghobrial Mina Y             #####
#####        Piquant Pierre Olivier          #####
#####             Hemissi Omar               #####
#####         INF1900 Avril 2023             #####
#####                                        #####
#####										 #####
#####										 #####
##################################################

*/
#define F_CPU 8000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "Driver.hpp"
#include "can.h"
#include "memoire_24.h"
#include "UART.hpp"
#include "Capteur.hpp"
#include "LED.hpp"
#include <stdio.h>
#include <string.h>
//#include "Debug.hpp"

#include "PWM.hpp"
#include "PwmFrequency.hpp"

// void initialisationCapteurPort(){
//     //mettre en entree la lecture du capteur PA0
//     DDRA &= ~(1<<PA1);
// }

void initialisationMoteurPort(){
     //mettre en sortie les ports PB2-PB3-PB4-PB5, pour le moteur
    DDRB |= (1<<PB2) | (1<<PB3) | (1<<PB4) | (1<<PB5);   
}

void initialisationLEDPort(){
    //mettre en sortie les Ports PB0 et PB1 pour la LED
    DDRB |= (1<<PB0)| (1<<PB1);
}

enum class Etat {
    debut,
    debutDetection,
    detectionDroite,
    detectionGauche,
    tournerGauchePetitCoup,
    rouler,
    fin,
    attente,
    transmission,

};



volatile bool gBoutonPoussoirInt0=false;
volatile bool gBoutonPoussoirInt1=false;


ISR (INT1_vect){
    uint8_t tempsRebond=30; 
    _delay_ms(tempsRebond);

    gBoutonPoussoirInt1 = true;
    EIFR |= (1 << INTF1) ;
}

ISR (INT0_vect){
    uint8_t tempsRebond=30; 
    _delay_ms(tempsRebond);

    //gBoutonpoussoirInt0 = ! gBoutonpoussoirInt0;
    gBoutonPoussoirInt0 = true;
    EIFR |= (1 << INTF0) ;
}

// uint32_t generate_crc32(uint32_t crc, uint8_t data) {
//     crc = crc ^ ((uint32_t)data);
//     for (uint8_t j = 0; j < 8; j++) {
//         if ((crc & 1) != 0) {
//             crc = (crc >> 1) ^ 0xEDB88320;
//         } else {
//             crc = crc >> 1;
//         }
//     }
//     return crc;
// }


void initialisationUartFlag(){
    // 2400 bauds. Nous vous donnons la valeur des deux

    // premiers registres pour vous éviter des complications.

    UBRR0H = 0;

    UBRR0L = 0xCF;

    // permettre la réception et la transmission par le UART0

    UCSR0A |= (1<<UDR0) ;

    UCSR0B |=(1<<TXEN0) | (1<<RXEN0)  ;

    // Format des trames: 8 bits, 1 stop bits, sans parité

    UCSR0C =  (0<<UCSZ02) | (1<<UCSZ01)|(1<<UCSZ00); 
}


void initInterrupt0(){//interruption 0 
    cli();
    EICRA = (1 << ISC00) | (1<<ISC10);
    EIMSK = (1 << INT0) | (1<<INT1);
    DDRD &= ~(1<<PD3) | ~(1<<PD2); //PD2->INT0,PD3->INT1
    sei();
}

void transmissionValeur(uint8_t &indexX, uint8_t &indexY, UART uart)
    {
        char buffer1[90];
        // uint16_t valY= indexY * 110 + 123;
        // uint16_t valX = indexX * 110 + 191;


        uint16_t valX;
        uint16_t valY;

        if (indexX == 0)
            valX = 191;
        
        if (indexX == 1)
            valX = 301;

        if (indexX == 2)
            valX = 411;

        if (indexX == 3)
            valX = 521;

        if (indexX == 4)
            valX = 631;

        if (indexX == 5)
            valX = 741;

        if (indexX == 6)
            valX = 851;

        if (indexX == 7)
            valX = 961;

        if (indexY == 0)
            valY = 123;
        if (indexY == 1)
            valY = 233;
        if (indexY == 2)
            valY = 343;
        if (indexY == 3)
            valY = 453;


        sprintf(buffer1, "<circle cx=\"%d\" cy=\"%d\" r=\"10\" ", valX, valY);
        //sprintf(buffer1, "<circle cx=\"%d\" cy=\"%d\" r=\"10\" ", valX, valY);
        for (size_t i = 0; i < strlen(buffer1); i++)
            {uart.transmit(buffer1[i]);
                _delay_ms(5);
            }

    }
 



int main (){
    //initialisationCapteurPort();
    initialisationMoteurPort();
    initialisationLEDPort();
    initInterrupt0();
    
    
    //creation du capteur
    Capteur capteur = Capteur();


    //creation de la led
    LED led = LED(PORTB);

    //reglage des PWM qui seront utilise pour le moteur
    PWM pwmDroite = PWM(PinPwm::B3,PB5);
    PWM pwmGauche = PWM(PinPwm::B4,PB2);

   
    uint8_t arrayX[]={0,0,0,0,0,0,0,0};
    uint8_t arrayY[]={0,0,0,0,0,0,0,0};
    uint8_t adresseMemoire = 0;
    
    uint16_t adresse = 0;

    //UART
    initialisationUartFlag();
    UART uart = UART();
    //initialiser la memoire
    Memoire24CXXX memoire = Memoire24CXXX();

    uint8_t nombrePoteaux = 0;
    
    //uint16_t adresseMemoire = 0;

    
    uint8_t indexI,indexJ;
    indexI=3;
    indexJ=0;
    memoire.ecriture(adresse++,indexJ);
    _delay_ms(5);
    memoire.ecriture(adresse++,indexI);
    _delay_ms(5);
    bool premiereFois=true;

    //soit au debut de 0 degree ou 90 degre,
    //on va la mettre a 0 juste pour initialiser
    int angle=0;
    
    bool loin = false;
    
    //bool detectionPoint = false;

    bool tournerPetitGauchePetitCoup = false;
    
    uint16_t valeurCercleVide = 0 ;

    //_delay_ms(5000);
    //uart.transmit(indexI);

    
    //creation du moteur avec les deux PWM 
    Driver drive = Driver(pwmGauche,pwmDroite);
    uint16_t valeur = capteur.lectureCapteur();
    Etat etatActuel = Etat::debut;
    bool dixCm = false;
    uint16_t compteur = 0;
    bool loinUneFois = true;
    bool once = true;
    while(true){
        switch (etatActuel) {//debug spam les boutons
            case Etat::debut:
                //debogage
                // valeur =(capteur.lectureCapteur()>>2);
                
                // _delay_ms(20);
                // uart.transmit(valeur);
                //fin debogage
                if(gBoutonPoussoirInt0){
                    etatActuel = Etat::debutDetection;
                    _delay_ms(200);
                    gBoutonPoussoirInt0 = false;
                } else if(gBoutonPoussoirInt1){
                    etatActuel = Etat::transmission;
                    _delay_ms(200);
                    gBoutonPoussoirInt1=false;

                }
                break;

            case Etat::debutDetection:
                //faudra le faire ambre pendant
                led.amber(100);
                //bouton interrupt
                if(gBoutonPoussoirInt0){////il regarde vers le haut donc tourner a droite
                    led.onLED(0x01);
                    _delay_ms(2000);
                    led.offLED();
                    etatActuel = Etat::detectionDroite;
                    _delay_ms(200);
                    gBoutonPoussoirInt0 = false;
                    angle = 90;
                    
                //bouton blanc    
                } else if (gBoutonPoussoirInt1){//il regarde vers la droite donc tourner a gauche
                    led.onLED(0x02);
                    _delay_ms(2000);
                    led.offLED();
                    etatActuel = Etat::detectionGauche;
                    _delay_ms(200);
                    gBoutonPoussoirInt1 = false;
                    angle = 0;
                    
                }

                break;

            case Etat::tournerGauchePetitCoup:
                if(tournerPetitGauchePetitCoup){
                    drive.turnLeft5(tournerPetitGauchePetitCoup);
                    _delay_ms(220);
                } else {
                    etatActuel = Etat::rouler;
                }
                
                break;


            case Etat::detectionDroite:
                //gBoutonPoussoirInt0 = false;
                valeur = capteur.lectureCapteur();
                
                if (capteur.detection1Point(valeur)) {
                    etatActuel = Etat::rouler;
                    if(loinUneFois){
                        loin = false;
                        loinUneFois = false;
                    }
                    //1point
                } 
                if (capteur.detection1PointDiagonale(valeur)){
                    
                    etatActuel = Etat::rouler;
                    if(loinUneFois){
                        loinUneFois = false;
                        loin=false;//1point
                    }
                    
                } 
                if(capteur.detection2Point(valeur)){
                    etatActuel = Etat::rouler;
                    if(loinUneFois){
                        loinUneFois = false;
                        loin=true;//2point
                    }
                    
                } 
                if(capteur.detection2PointDiagonale(valeur)){
                    etatActuel = Etat::rouler;
                    if(loinUneFois){
                        loinUneFois = false;
                        loin=true;//2point
                    }
                    
                }
                
                drive.turnRight5();
                //uart.transmit(angle);
                compteur++;
                if (compteur == 4){//on veut 2,25 degree, donc moyenne
                    angle -=3;
                    compteur = 0;//ne pas depasser 255
                    valeurCercleVide+=3;

                } else {
                    angle -=2;
                    valeurCercleVide+=2;
                }

                if(valeurCercleVide> 360){
                    etatActuel = Etat::fin;
                    
                }
                
                
                _delay_ms(180);
                break;

            case Etat::detectionGauche:
                valeur = capteur.lectureCapteur();
                
                if (capteur.detection1Point(valeur)) {
                    etatActuel = Etat::rouler;
                }
                if (capteur.detection1PointDiagonale(valeur)){
                    etatActuel = Etat::rouler;
                }
                if(capteur.detection2Point(valeur)){
                    etatActuel = Etat::rouler;
                }
                if(capteur.detection2PointDiagonale(valeur)){
                    etatActuel = Etat::rouler;
                }

                drive.turnLeft5(tournerPetitGauchePetitCoup);
                
                tournerPetitGauchePetitCoup = false;
                compteur++;
                if (compteur == 4){
                    angle +=3;
                    compteur = 0;//ne pas depasser 255

                } else {
                    angle +=2;
                }

                _delay_ms(300);
                
                break;
            
            case Etat::rouler:
                //avant de modifier la matrice il faudra changer le 2 a 1 des anciens index
                //faudra faire qqch pour les negatif 
                
                while(angle< 0 ){
                    angle +=360;
                }


                if(once){

                    if( (337<=angle&&angle<=360) || (0<=angle&&angle<=22)){//a droite
                        if(loin){
                            indexJ+=2;
                        } else {
                            indexJ++;
                        }
                    }
                    if(23<=angle && angle<=67){//droite haut
                        if(loin){
                            indexI-=2;
                            indexJ+=2;
                        } else {
                            indexI--;
                            indexJ++;
                        }
                    }
                    if((68<=angle) && (angle<=112)){//vers le haut
                        if(loin){
                            indexI-=2;
                        } else {
                            indexI--;
                        }
                    }
                    if(113<=angle && angle<=157){//haut gauche
                        if(loin){
                            indexI-=2;
                            indexJ-=2;
                        } else {
                            indexI--;
                            indexJ--;
                        }
                    }
                    if(158<=angle && angle<=202){//gauche
                        if(loin){
                            indexJ-=2;
                        } else {
                            indexJ--;
                        }
                    }
                    if(203<=angle && angle<=247){//en bas a gauche
                        if(loin){
                            indexI+=2;
                            indexJ-=2;
                        } else {
                            indexI++;
                            indexJ--;
                        }
                    }
                    if(248<=angle && angle<=292){//en bas
                        if(loin){
                            indexI+=2;
                        } else {
                            indexI++;
                        }
                    }
                    if(293<=angle && angle<=336){//en bas a droite
                        if(loin){
                            indexI+=2;
                            indexJ+=2;
                        } else {
                            indexI++;
                            indexJ++;
                        }
                    }
                    once = false;
                    //memoire ecrire les index
                    memoire.ecriture(adresse++,indexJ);//x
                    _delay_ms(5);
                    memoire.ecriture(adresse++,indexI);//y
                    _delay_ms(5);
                }


                // _delay_ms(50);
                // uart.transmit(indexI);
                // _delay_ms(20);
                // uart.transmit(indexJ);
                // _delay_ms(20);
                

                



                

                valeur = capteur.lectureCapteur();
                drive.moveForwardDoucement(60,valeur,dixCm,tournerPetitGauchePetitCoup);
                if(tournerPetitGauchePetitCoup){
                    etatActuel = Etat::tournerGauchePetitCoup;
                    
                }
                _delay_ms(50);
                if(dixCm){
                    etatActuel = Etat::attente;
                    _delay_ms(20);
                    
                }
                break;


            case Etat::attente:
                while(!gBoutonPoussoirInt0){
                    led.amber(100);
                }
                //_delay_ms(200);
                gBoutonPoussoirInt0 = false;
                valeurCercleVide =0 ;
                angle = 90;
                tournerPetitGauchePetitCoup = false;
                once = true;
                loinUneFois = true;
                loin = false;
                dixCm = false;
                etatActuel = Etat::detectionDroite;
                break;

            case Etat::fin:
                //led.flashLED(0x01,1000);
                memoire.ecriture(adresse++,0xff);
                _delay_ms(5);
                break;

            case Etat::transmission:
                led.onLED(0x01);
                _delay_ms(2000);
                led.offLED();
                _delay_ms(500);
                led.onLED(0x02);
                
                
                //Memoire24CXXX memoire;
                char buffer[580];
                uint16_t valeurX;
                uint16_t valeurY;
                char abc[] = "</svg>";
                uart.initialiser();
                // uint8_t dataBuffer [1024];
                // size_t dataBufferIndex = 0;
                // uint32_t crc32 = 0xFFFFFFFF;
                uart.transmit(0x02);
                _delay_ms(5);


                char textDebut[] = "<svg xmlns=\"http://www.w3.org/2000/svg\" width=\"100%\" height=\"100%\" viewBox=\"0 0 1152 576\">\n"
                    "<text x=\"76\" y=\"36\" font-family=\"arial\" font-size=\"25\" fill=\"blue\"> Section 03 -- Equipe 7178 -- Bot101</text>\n"
                    "<text x=\"96\" y=\"564\" font-family=\"arial\" font-size=\"20\" fill=\"blue\">AIRE : 0 pouces carres</text>\n"
                    "<rect x=\"96\" y=\"48\" width=\"960\" height=\"480\" stroke=\"black\" stroke-width=\"1\" fill=\"white\"/>\n";

                // for (uint16_t i = 0; i < sizeof(buffer); i++)
                // {
                //     _delay_ms(5);
                //     uart.transmit(textDebut[i]);
                    
                // }
                size_t textDebut_length = strlen(textDebut);
                for (size_t i = 0; i < textDebut_length; i++) {
                    _delay_ms(5);
                    uart.transmit(textDebut[i]);
                }

                for (uint16_t i = 0; i < 8; i++) {
                    valeurX = i * 110 + 191;
                    for (uint8_t j = 0; j < 4; j++) {
                        valeurY = j * 110 + 123;
                        sprintf(buffer, "<rect x=\"%d\" y=\"%d\" width=\"5\" height=\"5\"/>\n", valeurX, valeurY);
                        //sprintf(buffer, "<rect x=\"50\" y=\"50\" width=\"5\" height=\"5\"/>\n");
                        for (size_t index = 0; index < strlen(buffer); index++) {
                            uart.transmit(buffer[index]);
                            _delay_ms(5);
                        }
                    }
                }

                
                
                char rectangleRouge[] = "<rect x=\"191\" y=\"453\" width=\"5\" height=\"5\" fill=\"red\"/>\n";
                for (size_t i = 0; i < strlen(rectangleRouge); i++) {
                    uart.transmit(rectangleRouge[i]);
                    _delay_ms(5);
                }

                
                    //memoire.lecture(adresseMemoire++, &arrayX[nombrePoteaux]);
                // do
                // {
                //     memoire.lecture(adresseMemoire++, &arrayX[nombrePoteaux]);
                    
                //     memoire.lecture(adresseMemoire++, &arrayY[nombrePoteaux]);
                //     nombrePoteaux++;
                // } while (arrayX[nombrePoteaux] != 0xff);

                for (uint8_t i = 0; i < 9; i++) {
                    memoire.lecture(adresseMemoire++, &(arrayX[nombrePoteaux]));
                    _delay_ms(5);
                    if (arrayX[i] == 0xff) {
                        break;
                    }
                    memoire.lecture(adresseMemoire++, &(arrayY[nombrePoteaux]));
                    _delay_ms(5);
                    nombrePoteaux++;

                    
                    
                }

                
                // while(arrayX[nombrePoteaux] != 0xff)
                // {
                //     memoire.lecture(adresseMemoire++, &arrayX[nombrePoteaux]);
                //     nombrePoteaux++;
                //     memoire.lecture(adresseMemoire++, &arrayY[nombrePoteaux]);
                
                // }
                    

                    for (uint8_t index= 0; index < nombrePoteaux; index++) {
                    // if(arrayX[index]>1000 || arrayY[index]>500){
                    //     continue;
                    // }
                    transmissionValeur(arrayX[index], arrayY[index], uart);
                    char ligne2[] = "stroke=\"black\" stroke-width=\"2\" fill=\"gray\" />\n";
                    sprintf (buffer, ligne2);
                    for (size_t i = 0; i < strlen(buffer); i++) {
                        uart.transmit(buffer[i]);
                        _delay_ms(5);
                        }
                }

                for (uint8_t i = 0; i < 6; i++) {
                        
                        uart.transmit(abc[i]);
                        _delay_ms(5);
                }

                _delay_ms(10);
                led.offLED();



                uart.transmit(0x03);
                //crc entre 0x03 et 0x04
                

                
                // for (size_t i = 0; i < dataBufferIndex; i++) {
                //     crc32 = generate_crc32(crc32, dataBuffer[i]);
                // }

                // crc32 = crc32 ^ 0xFFFFFFFF; 

                // for (int i = 0; i < 4; i++) {
                //      uint8_t crc_byte = (crc32 >> (8 * i)) & 0xFF;
                //      uart.transmit(crc_byte);
                //      _delay_ms(5);
                // }
                
                uart.transmit(0x04);
        


                break;

        
        }//fin switch
    }//fin while
}//fin main


