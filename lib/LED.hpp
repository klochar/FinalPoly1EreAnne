/*
######	        Classe LED - Header       ########
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

#ifndef DEL_HPP
#define DEL_HPP 
#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>

// enum class Temps{low,med,high};

class LED
{
public:

    LED(volatile uint8_t &port) : port(port){}

    void onLED(uint8_t color);
    void flashLED(uint8_t color, uint16_t totalTime);
    void offLED();
    void amber(uint16_t time);

private:
    volatile uint8_t &port;
};

#endif