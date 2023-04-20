
/*
######		Classe Driver - Header        ########
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

Cette classe utilise la clase Pwm afin de controler le movement
des roues du robot.
Ci-dessous la description des methodes de cette
classe :
	* Le constructeur initialise les moteurs de gauche et de droite.
	* La m�thode moveForward(uint8_t percentage) permet de faire avancer
	  le robot � une vitesse qui correstpond au pourcentage pass� en 
	  argument.
	* La m�thode moveBack(uint8_t percentage) permet de faire reculer
	  le robot � une vitesse qui correstpond au pourcentage pass� en 
	  argument.

	* La m�thode turnLeft90() permet de faire tourner le robot �
	  90 d�gr�s vers la gauche.
	* La m�thode turnRight90() permet de faire tourner le robot �
	  90 d�gr�s vers la droite.
	* La m�thode void turn180() permet de faire tourner le robot �
	  180 d�gr�s.

*/


#ifndef F_CPU
#define F_CPU 8000000UL
#endif

#ifndef DRIVER_HPP
#define DRIVER_HPP


#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "PWM.hpp"
#include "Capteur.hpp"

enum PwmDirection { Forward = 0, Back = 1 };

class Driver {
public:
	Driver(PWM& leftMotor, PWM& rightMotor);


	void moveForward(uint8_t percentage);
	void moveForwardDoucement(uint8_t percentage,uint16_t&, bool&,bool&);
	void moveForward10Cm(uint8_t percentage);
	void moveForwardWhileInRange(uint8_t percentage);
	void moveBack(uint8_t percentage);

	void turnLeft90();
	void turnLeft45();

	void turnRight90();
	void turnRight5();
	void turnLeft5(bool&);

	 
	void turnLeft5UntilGetPost();

	void moveBackRighWheel(uint8_t percentage);
	void moveBackLeftWheel(uint8_t percentage);

	void turn180();
	void stop();

private:
	bool deviation =false;
	PWM* leftMotor_;
	PWM* rightMotor_;
	Capteur capteur = Capteur();
	uint16_t derniereValeurCapte;
	uint8_t compteur=0;
};

#endif