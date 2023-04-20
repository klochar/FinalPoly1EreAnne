
/*
######      Classe PwmFrequency - Header     #####
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

Cette classe utilise la minuterie Timer1 afin de faire varier les fr�quences Pwm.
Configuration : Mode CTC du timer1.

*/

#ifndef F_CPU
#define F_CPU 8000000UL
#endif

#ifndef PWMFREQUENCY_HPP
#define PWMFREQUENCY_HPP

#include <avr/io.h>
#include <avr/interrupt.h>

class PwmFrequency {
public:
    PwmFrequency(uint16_t frequency = 0);
    uint8_t getFrequency();
    void setFrequency(uint16_t frequency);
    void start();
    void stop();
    void musicNote(uint8_t note);

private:
    uint16_t notes_ [37] = {141, 133, 126, 118, 112, 105, 99, 94, 88, 83, 79, 74, 70,
	   66, 62, 59, 55, 52, 49, 46, 44, 41, 39, 37, 35, 33, 31, 29, 27, 26, 24, 23, 21, 20, 19, 18, 17};
    uint16_t frequency_;
};

#endif
