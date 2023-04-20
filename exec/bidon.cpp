#define F_CPU 8000000UL



#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "Driver.hpp"
#include "can.h"

#include "PWM.hpp"
#include "PwmFrequency.hpp"
#include "memoire_24.h"
#include "UART.hpp"
#include <stdio.h>
#include <string.h>

void transmissionValeur(uint8_t &indexX, uint8_t &indexY, UART uart)
    {
        char buffer1[90];
        uint16_t valY= indexX * 110 + 123;
        uint16_t valX = indexY * 110 + 191;
        sprintf(buffer1, "<circle cx=\"%d\" cy=\"%d\" r=\"10\" ", valX, valY);
        //sprintf(buffer1, "<circle cx=\"%d\" cy=\"%d\" r=\"10\" ", valX, valY);
        for (size_t i = 0; i < strlen(buffer1); i++)
            {uart.transmit(buffer1[i]);
                _delay_ms(5);
            }
    }
    //Méthode 2
    void transmissionValeur1(uint8_t &indexX,uint8_t &indexY, UART uart, char buffer[90])
    {
        uint16_t valX;
        uint16_t valY;

        if (indexX == 0)
            valX = 203;
        
        if (indexX == 1)
            valX = 307;

        if (indexX == 2)
            valX = 410;

        if (indexX == 3)
            valX = 513;

        if (indexX == 4)
            valX = 617;

        if (indexX == 5)
            valX = 720;

        if (indexX == 6)
            valX = 823;

        if (indexX == 7)
            valX = 928;

        if (indexY == 0)
            valY = 144;
        if (indexY == 1)
            valY = 240;
        if (indexY == 2)
            valY = 336;
        if (indexY == 3)
            valY = 432;
        
        sprintf(buffer, "<circle cx=  +\"%d\" + cy=std::to_string(valeurY) r=\"%d\" ", valX, valY);
        for (uint16_t i = 0; i < sizeof(buffer)-1; i++)
            uart.transmit(i);
        //uart.transmit(buffer);
        uart.transmit(0x03);
    }

    uint32_t generate_crc32 (uint32_t crc, unsigned char *data, int length) { 
    int i, j; 
    for (i=0; i<length; i++) { 
        crc = crc ^ *(data++); 
        for (j=0; j<8; j++) { 
            if ((crc & 1) != 0) {
                crc = (crc>>1) ^ 0xEDB88320 ; 
                }
            else 
                crc = crc >>1 ; 
        } 
    } 
    return crc;}

int main () {
    UART uart = UART();
    Memoire24CXXX memoire = Memoire24CXXX();
    // uint8_t nombrePoteaux = 0;
    // uint8_t arrayX[8];
    // uint8_t arrayY[8];
     uint8_t adresseMemoire = 0;
    // //Memoire24CXXX memoire;
    // char buffer[580];
    // uint16_t valeurX;
    // uint16_t valeurY;
    // char abc[] = "</svg>";
    // uart.initialiser();

    // uart.transmit(0x02);
    // _delay_ms(5);


//led.flashLED(0x01,1000);
                uint8_t nombrePoteaux = 0;
                uint8_t arrayX[8];
                uint8_t arrayY[8];
                //uint16_t adresseMemoire = 0;
                //Memoire24CXXX memoire;
                char buffer[580];
                uint16_t valeurX;
                uint16_t valeurY;
                char abc[] = "</svg>";
                uart.initialiser();

                uart.transmit(0x02);
                _delay_ms(5);

                uint8_t arrayNombres[] = {1, 1, 2, 2, 2, 3, 3, 3, 0xff};

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
                for (size_t i = 0; i < textDebut_length; i++)
                {
                    _delay_ms(5);
                    uart.transmit(textDebut[i]);
                }

                for (uint16_t i = 0; i < 8; i++)
                {
                    valeurX = i * 110 + 191;
                    for (uint8_t j = 0; j < 4; j++)
                    {
                        valeurY = j * 110 + 123;
                        sprintf(buffer, "<rect x=\"%d\" y=\"%d\" width=\"5\" height=\"5\"/>\n", valeurX, valeurY);
                        //sprintf(buffer, "<rect x=\"50\" y=\"50\" width=\"5\" height=\"5\"/>\n");
                        for (size_t index = 0; index < strlen(buffer); index++)
                        {
                            uart.transmit(buffer[index]);
                            _delay_ms(5);
                        }
                    }
                }

                
                
                char rectangleRouge[] = "<rect x=\"191\" y=\"453\" width=\"5\" height=\"5\" fill=\"red\"/>\n";
                for (size_t i = 0; i < strlen(rectangleRouge); i++)
                {
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

                // do
                // {
                    
                for (uint16_t i = 0; i < 9; i++)
                {
                    arrayX[nombrePoteaux] = arrayNombres[adresseMemoire++];
                        _delay_ms(5);
                    arrayY[nombrePoteaux] = arrayNombres[adresseMemoire++];
                    _delay_ms(5);
                    nombrePoteaux++;
                    if (arrayX[i] == 0xff)
                    {
                        break;
                        }
                   
                }
 
                // } while (arrayX[nombrePoteaux] != 0xff);
                
                // while(arrayX[nombrePoteaux] != 0xff)
                // {
                //     memoire.lecture(adresseMemoire++, &arrayX[nombrePoteaux]);
                //     nombrePoteaux++;
                //     memoire.lecture(adresseMemoire++, &arrayY[nombrePoteaux]);
                
                // }
                    

                    for (uint16_t index= 0; index < nombrePoteaux; index++)
                {
                    transmissionValeur(arrayX[index], arrayY[index], uart);
                    char ligne2[] = "stroke=\"black\" stroke-width=\"2\" fill=\"gray\" />\n";
                    sprintf (buffer, ligne2);
                    for (size_t i = 0; i < strlen(buffer); i++)
                        {
                        uart.transmit(buffer[i]);
                        _delay_ms(5);
                        }
                }

                for (uint8_t i = 0; i < 6; i++)
                    {
                        
                        uart.transmit(abc[i]);
                        _delay_ms(5);
                        }


                uart.transmit(0x03);
                uart.transmit(0x04);
        

}