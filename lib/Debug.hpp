
/*
########	   Class DEBUG - Header	      ########
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

Cette classe permet de transmettre, caract�re par caract�re, une chaine de caract�re au PC.
Aucune m�thode pour cette classe.

*/


#ifndef F_CPU
#define F_CPU 8000000UL
#endif


#include "UART.hpp"
#include <string.h>

// Si DEBUG est defini, le string pass� en param�tre est transmis caract�re par caract�re au PC. 


#ifdef DEBUG
//UART uart;
#define DEBUG_PRINT(str) for (uint8_t i = 0; i < strlen(str); i++) {uart.transmit(str[i]);}

#else

// Sinon, ne rien faire.
#define DEBUG_PRINT(str) do {} while (0)


#endif
