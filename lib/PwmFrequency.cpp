
/*
######  Classe PwmFrequency - Implementation #####
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

#define F_CPU 8000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include "PwmFrequency.hpp"


PwmFrequency::PwmFrequency(uint16_t frequency): 
    frequency_(frequency) 
{
    

}


uint8_t PwmFrequency::getFrequency() {
    return frequency_;
}


void PwmFrequency::setFrequency(uint16_t frequency) {
    frequency_ = frequency;
    OCR2A = frequency_;
}

void PwmFrequency::musicNote(uint8_t note) {
    this->setFrequency(notes_[note - 45]);
    this->start();
}


void PwmFrequency::start() {
    cli();
    TCNT2 = 0; 
    OCR2A = frequency_;
    TCCR2A = (1<<WGM21);              
    TCCR2B = (1 << WGM22) |(1 << CS22);  
    TIMSK2 |= (1<<OCIE2A);
    sei();   
}


void PwmFrequency::stop() {
    //TCCR1A &= ~(1 << COM1A0);
    TCCR2B &= (0 << WGM22) | ~(1 << CS22);
}
