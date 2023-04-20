
/*
######	    Classe PWM - Implementation   ########
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

Cette classe permet la creation et le controle d'un PWM materiel
Ci-dessous la description des methodes de cette
classe :
    * Le constructeur initialise les registres et les ports.
    * La methode getPinDirection permet d'acc�der � la direction du pin.
    * La m�thode getPwmDirection permet d'acc�der � la direction du PWM.
    * La m�thode getPwmPercentage permet d'acc�der au pourcentage du PWM.
    * La m�thode setPwmDirection permet de changer la direction du pin.
    * La m�thode changePwmDirection permet de changer la direction du pin.
    * La m�thode setPwmDirection permet de modifier la direction du PWM.
    * La m�thode setPwmDirection permet de modifier la direction du PWM.
    * La m�thode increasePwmPercentage permet d'augmenter le porcentage du PWM
      d'une quantit� cible pass�e en argument.
    * La m�thode decreasePwmPercentage permet diminuer le porcentage du PWM
      d'une quantit� cible pass�e en argument.
    * La methode startWithoutInterrupt permet de compter sans activer les
      les interruptions.

*/

#ifndef F_CPU
#define F_CPU 8000000UL
#endif

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "PWM.hpp"


PWM::PWM(PinPwm pinPWM, uint8_t pinDirection) :
    pwmDirection_(0),
    percentage_(0),
    pinDirection_(pinDirection) 
{

    switch (pinPWM) {
    case PinPwm::B3:
        OCRnx_ = &OCR0A;
        COMnxn_ = COM0A0;
        break;

    case PinPwm::B4:
        OCRnx_ = &OCR0B;
        COMnxn_ = COM0B0;
        break;
    }

    TCCR0A |= (0b10 << COMnxn_) | (1 << WGM10);

    TCCR0B |= (1 << CS11);

    uint32_t avoidOverflowConstant = (MAX_PWM * percentage_) / 100;
    *OCRnx_ = uint8_t(avoidOverflowConstant);

    PORTB |= (pwmDirection_ << pinDirection_);
}


// Methodes d'acces
uint8_t PWM::getPinDirection() const { return pinDirection_; }


bool PWM::getPwmDirection() const { return pwmDirection_; }


uint8_t PWM::getPwmPercentage() const { return percentage_; }


void PWM::setPwmDirection(bool PwmDirection) {
    pwmDirection_ = PwmDirection;
    if (pwmDirection_ == true)
        PORTB |= (1 << pinDirection_);
    else if (pwmDirection_ == false)
        PORTB &= ~(1 << pinDirection_);
}


void PWM::changePwmDirection() {
    pwmDirection_ = !pwmDirection_;
    PORTB ^= (1 << pinDirection_);
}


// Methodes de modification
void PWM::setPwmPercentage(uint8_t percentage) {
    percentage_ = percentage;
    uint32_t avoidOverflowConstant = (MAX_PWM * percentage_) / 100;
    *OCRnx_ = uint8_t(avoidOverflowConstant);
}


void PWM::increasePwmPercentage(uint8_t percentage) {
    percentage_ += percentage;
    if (percentage_ > 100) {
        percentage_ = 100;
    }
    uint32_t avoidOverflowConstant = (MAX_PWM * percentage_) / 100;
    *OCRnx_ = uint8_t(avoidOverflowConstant);
}


void PWM::decreasePwmPercentage(uint8_t percentage) {
    if (percentage_ < percentage) {
        percentage_ = 0;
    }
    else
        percentage_ -= percentage;
    uint32_t avoidOverflowConstant = (MAX_PWM * percentage_) / 100;
    *OCRnx_ = uint8_t(avoidOverflowConstant);
}
