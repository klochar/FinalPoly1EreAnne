/*
######	       Classe PWM - Header		  ########
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

#ifndef PWM_HPP
#define PWM_HPP

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>


const uint8_t MAX_PWM = 255;


enum class PinPwm { B3, B4 };

class PWM {
public:
	PWM(PinPwm pinPWM, uint8_t pinDirection);

	// M�thodes d'acces
	uint8_t getPinDirection() const;

	bool getPwmDirection() const;

	uint8_t getPwmPercentage() const;
	

	// M�thodes de modification
	void setPwmDirection(bool PwmDirection);

	void changePwmDirection();

	void stopTimer();

	void setPwmPercentage(uint8_t percentage);

	void increasePwmPercentage(uint8_t percentage);

	void decreasePwmPercentage(uint8_t percentage);


private:
	bool pwmDirection_;
	uint8_t percentage_;
	uint8_t pinDirection_;

	// Registres
	volatile uint8_t* OCRnx_;
	uint8_t COMnxn_;
};

#endif
