
/*
########		Classe UART - Header	  ########
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

#ifndef F_CPU
#define F_CPU 8000000UL
#endif

#ifndef UART_HPP
#define UART_HPP

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

class UART {

public:
	UART();

	~UART() = default;

	uint8_t receive();


	void transmit(uint8_t data);

	void initialiser();
	
	
private:
};

#endif
