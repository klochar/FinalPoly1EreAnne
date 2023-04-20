
/*
########   Classe UART - Impl�mentation   ########
#####                                        #####
#####      Classe produite et ecrite par     #####
#####         Nkondog Yvan Aristide			 #####
#####            Ghobrial Mina Y             #####
#####        Piquant Pierre Olivier          #####
#####             Hemissi Omar               #####
#####         INF1900 Mars 2023              #####
#####                                        #####
#####										 #####
#####										 #####
##################################################

# Description :

Cette classe permet au robot de communiquer du robot au PC via
un RS232.
Ci-dessous la description des methodes de cette
classe :
	* Le constructeur par d�faut initialise les registres.
	* * La m�thode receive permet de recevoir des donn�es.
	* La m�thode transmit prend une donn�e en parametre, attends que le tampon 
	soit vide, ensuite transmet la donn�e par communication serielle.
	
*/


#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "UART.hpp"


UART::UART() {			 
}


uint8_t UART::receive() {
	// Attendre que de nouvelles donn�es deviennent disponibles.
	do {
		//
	} while (!(UCSR0A & (1 << RXC0)));

	// Revoyer les donn�es re�ues.
	return UDR0;
}


void UART::transmit(uint8_t data) {
	// Attendre que le tampon devienne vide.
	while(!(UCSR0A) & (1<<UDRE0)){

    }
    UDR0 = data; 
}

void UART::initialiser()
{
    // 2400 bauds. Nous vous donnons la valeur des deux

    // premiers registres pour vous éviter des complications.
	UBRR0H = 0;
	UBRR0L = 0xCF;
	// Activer la transmission et la reception (Page 186)
	UCSR0A = 0;
	UCSR0B =  1 << RXEN0 | 1 << TXEN0;  
	// Format des trames: 8 bits, 1 bit d'arr�t, pas de bit de parit� (p.188)
	UCSR0C = 1 << UCSZ01 | 1 << UCSZ00;  
}