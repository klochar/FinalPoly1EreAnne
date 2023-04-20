

/*
######	    Classe LED - Implementation    ########
#####                                        #####
#####      Classe produite et ecrite par     #####
#####         Nkondog Yvan Aristide			 #####
#####            Ghobrial Mina Y             #####
#####        Piquant Pierre Olivier          #####
#####             Hemissi Omar               #####
#####                                        #####
#####                                        #####
#####		    INF1900 Mars 2023            #####
#####										 #####
##################################################

# Description :

Cette classe permettra le fonctionnement de la LED 
par quelque methode qui se trouve ci desssou:
    -constructeur dans lequel on passera le port (passage par reference)
    -onLED avec un parametre qui sera la couleur, 
        pour allumer la Led en cette couleur predefini 
    -flashLED, cette methode permettra a la led de flasher dans un 
        temps total que l utilisateur aura choisi ainsi que la couleur
	-OffLED, celle ci permettra d eteindre la LED
    -amber, permettra d allumer la led avec un couleur ambre 
        pendant un temps choisi passe en parametre

*/
#define F_CPU 8000000UL
#include "LED.hpp"
#include <avr/io.h>
#include <util/delay.h>



void LED::onLED(uint8_t couleur){
    this->port = couleur;

}

void LED::flashLED(uint8_t color, uint16_t totalTime)
{ // tempsTotal en ms


    uint16_t offLED = 0x00;
    int TotalTimeConversionInt = totalTime;
    for (int i = 0; i < (TotalTimeConversionInt / 1000); i++)
    { // tempstotal

        this->port = color;
        _delay_ms(500);
        this->port = offLED;
        _delay_ms(500);
    }
}

void LED::offLED()
{
    uint8_t offLED = 0x00;
    this->port = offLED;
}

void LED::amber(uint16_t time)
{
    uint8_t red, green, off;
    red = 0x02;
    green = 0x01;
    off = 0x00;
    int timeConversionInt = time;
    for (int i = 0; i < (timeConversionInt / 20); i++)
    { // temps Total
        this->port = red;
        _delay_ms(20);
        this->port = green;
        _delay_ms(20);
    }
    this->port = off;
}
