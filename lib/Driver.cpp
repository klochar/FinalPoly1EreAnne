

/*
######	Classe Driver - Implementation    ########
#####                                        #####
#####      Classe produite et ecrite par     #####
#####         Nkondog Yvan Aristide			     #####
#####            Ghobrial Mina Y             #####
#####        Piquant Pierre Olivier          #####
#####             Hemissi Omar               #####
#####                                        #####
#####                                        #####
#####		    INF1900 Mars 2023                #####
#####										                     #####
##################################################

# Description :

Cette classe utilise la clase Pwm afin de controler le movement
des roues du robot.
Ci-dessous la description des methodes de cette
classe :
    * Le constructeur initialise les moteurs de gauche et de droite.
    * La méthode moveForward(uint8_t percentage) permet de faire avancer
      le robot à une vitesse qui correstpond au pourcentage passé en
      argument.
    * La méthode moveBack(uint8_t percentage) permet de faire reculer
      le robot à une vitesse qui correstpond au pourcentage passé en
      argument.

    * La méthode turnLeft90() permet de faire tourner le robot à
      90 dégrés vers la gauche.
    * La méthode turnRight90() permet de faire tourner le robot à
      90 dégrés vers la droite.
    * La méthode void turn180() permet de faire tourner le robot à
      180 dégrés.

*/


#define F_CPU 8000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "PWM.hpp"
#include "Driver.hpp"


Driver::Driver(PWM& leftMotor, PWM& rightMotor) : 
    leftMotor_(&leftMotor), 
    rightMotor_(&rightMotor) 
{
  
}

//on veut qu il avance tant qu il detecte et 
//arrete lorsqu il devie de sa trajectoire
// void Driver::moveForwardWhileInRange(uint8_t percentage){
//     leftMotor_->setPwmDirection(PwmDirection::Forward);
//     rightMotor_->setPwmDirection(PwmDirection::Forward);

//     leftMotor_->setPwmPercentage(percentage);
//     rightMotor_->setPwmPercentage(percentage);

//     uint16_t valeur; 
//     valeur = this->capteur.lectureCapteur();
//     //tant que le robot se trouve en chemin 
//     //valeur vaut quoi : 
//     while(true){
//       _delay_ms(3);
//       //on upgrade la valeur pour la prochaine boucle
//       valeur = this->capteur.lectureCapteur();
//     }
//     //quand il arrete ca veut dire que il a devie, on arrete les moteur
//     stop();


// }

void Driver::moveForward10Cm(uint8_t percentage) {
    leftMotor_->setPwmDirection(PwmDirection::Forward);
    rightMotor_->setPwmDirection(PwmDirection::Forward);

    leftMotor_->setPwmPercentage(percentage);
    rightMotor_->setPwmPercentage(percentage);

    uint16_t valeur;
    
    //a ne pas modifier
    // for (int i = 0;i<5000;i++){
    //   _delay_ms(1);
    //   valeur = this->capteur.lectureCapteur();
    //   if (this->capteur.detection10Cm(valeur)){
    //     break;
    //   }
    // }
    // stop();


    //a ne pas modifier, avec les deviations
    // for (int i = 0;i<5000;i++){
    //   _delay_ms(1);
    //   valeur = this->capteur.lectureCapteur();
    //   if (this->capteur.detection10Cm(valeur)){
    //     break;
    //   }else if (valeur<10){
    //     stop();
    //     //detection pou rreprendre
    //     moveForward10Cm(70);
    //     while(!this->capteur.detection10Cm(valeur)){
    //       //tourneGauche faudrai faire tourner gauche comme la droite
    //       valeur = this->capteur.lectureCapteur();
    //     }
    //     break;
    //   }
    // }
    //stop();

    //retry
    
    while(true){
      _delay_ms(3);
      this->derniereValeurCapte = valeur;
      valeur = this->capteur.lectureCapteur();
      //si il rentre dans la boucle c qu il a devie du chemin
      if (this->capteur.detectionVide(valeur)){
        //on peut sortir avec une bool pour faire un changement d etat
        
        break;
      }
      if (this->capteur.detection10Cm(valeur)){
        break;
      }
    }
    //valeur = this->capteur.lectureCapteur();
    
    //stop();



    //stop();
}

void Driver::moveForward(uint8_t percentage) {
    leftMotor_->setPwmDirection(PwmDirection::Forward);
    rightMotor_->setPwmDirection(PwmDirection::Forward);

    leftMotor_->setPwmPercentage(percentage);
    rightMotor_->setPwmPercentage(percentage);
}

void Driver::moveBack(uint8_t percentage) {
    leftMotor_->setPwmDirection(PwmDirection::Back); 
    rightMotor_->setPwmDirection(PwmDirection::Back);   

    leftMotor_->setPwmPercentage(percentage);
    rightMotor_->setPwmPercentage(percentage);
}

void Driver::stop(){
  leftMotor_->setPwmPercentage(0);
  rightMotor_->setPwmPercentage(0);
}

void Driver::moveBackLeftWheel(uint8_t percentage){
   leftMotor_->setPwmDirection(PwmDirection::Back); 
   leftMotor_->setPwmPercentage(percentage);
}

void Driver::moveBackRighWheel(uint8_t percentage){
    rightMotor_->setPwmDirection(PwmDirection::Back);  
    rightMotor_->setPwmPercentage(percentage);
}

void Driver::turnLeft90() {
    uint8_t previousPercent = rightMotor_->getPwmPercentage();
    rightMotor_->setPwmPercentage(50);

    // La fonction _delay_ms(ms) prend en argument une valeur dont l'unit� est la milliseconde.
    // _delay_ms(2000) fournit donc un d�lai de deux secondes avant de red�marrer la minuterie et de tourner.
    _delay_ms(1670);

    rightMotor_->setPwmPercentage(previousPercent);
}
void Driver::turnLeft45() {
    // uint8_t previousPercent = rightMotor_->getPwmPercentage();
    // rightMotor_->setPwmPercentage(69);

    // // La fonction _delay_ms(ms) prend en argument une valeur dont l'unit� est la milliseconde.
    // // _delay_ms(2000) fournit donc un d�lai de deux secondes avant de red�marrer la minuterie et de tourner.
    // _delay_ms(720);

    // rightMotor_->setPwmPercentage(previousPercent);
}


//tourner a gauche de 5 degre 1 fois 
//et arrete ensuite et reprend la fonction 10Cm
void Driver::turnLeft5UntilGetPost(){
  
  //uint8_t previousPercent = rightMotor_->getPwmPercentage();
  rightMotor_->setPwmPercentage(69);
  moveBackRighWheel(62);
  _delay_ms(1000);

  //rightMotor_->setPwmPercentage(previousPercent);

  stop();
}

void Driver::turnRight5(){
    
    uint8_t previousPercent = leftMotor_->getPwmPercentage();
    leftMotor_->setPwmDirection(PwmDirection::Forward);
    leftMotor_->setPwmPercentage(58);
    moveBackRighWheel(62);
    // La fonction _delay_ms(ms) prend en argument une valeur dont l'unit� est la milliseconde.
    // _delay_ms(2000) fournit donc un d�lai de deux secondes avant de red�marrer la minuterie et de tourner.
    uint16_t valeur;
    for (int i =0 ; i<33;i++){
      valeur = this->capteur.lectureCapteur();
      _delay_ms(3);
      if (capteur.detection1Point(valeur)||capteur.detection1PointDiagonale(valeur)||capteur.detection2Point(valeur)||capteur.detection2PointDiagonale(valeur)) {
          
          _delay_ms(35);
          break;
      }
    }
    //_delay_ms(100);
    stop();

    //leftMotor_->setPwmPercentage(previousPercent);
}


void Driver::turnLeft5(bool& tournerGauche){
    
    uint8_t previousPercent = rightMotor_->getPwmPercentage();
    rightMotor_->setPwmDirection(PwmDirection::Forward);
    rightMotor_->setPwmPercentage(65);
    moveBackLeftWheel(62);
    // La fonction _delay_ms(ms) prend en argument une valeur dont l'unit� est la milliseconde.
    // _delay_ms(2000) fournit donc un d�lai de deux secondes avant de red�marrer la minuterie et de tourner.
    uint16_t valeur;
    for (int i =0 ; i<33;i++){
      valeur = this->capteur.lectureCapteur();
      _delay_ms(3);
      if (capteur.detection1Point(valeur)||capteur.detection1PointDiagonale(valeur)||capteur.detection2Point(valeur)||capteur.detection2PointDiagonale(valeur)) {
          _delay_ms(23);
          tournerGauche = false;
          break;
      }
      
    }
    
    stop();

    rightMotor_->setPwmPercentage(previousPercent);
}

void Driver::moveForwardDoucement(uint8_t percentage,uint16_t& valeur,bool& dixCm,bool& tournerGauchePetitCoup){
    
    rightMotor_->setPwmDirection(PwmDirection::Forward);
    leftMotor_->setPwmDirection(PwmDirection::Forward);
    rightMotor_->setPwmPercentage(percentage-2);
    leftMotor_->setPwmPercentage(percentage+15);

    
    for (int i =0 ; i<22;i++){
      valeur = this->capteur.lectureCapteur();
      _delay_ms(3);
      if (capteur.detectionVide(valeur)) {
          //on le fait tourner a gauche un peu
          compteur++;
          if(compteur==2){
            compteur =0;
            tournerGauchePetitCoup = true;
          }
      } else {
        tournerGauchePetitCoup = false;
      }
      if(capteur.detection10Cm(valeur)){
        dixCm = true;
      }
    }
    
    stop();

    
}


void Driver::turnRight90() {
    uint8_t previousPercent = leftMotor_->getPwmPercentage();
    leftMotor_->setPwmPercentage(50);

    // La fonction _delay_ms(ms) prend en argument une valeur dont l'unit� est la milliseconde.
    // _delay_ms(2000) fournit donc un d�lai de deux secondes avant de red�marrer la minuterie et de tourner.
    _delay_ms(1670);

    leftMotor_->setPwmPercentage(previousPercent);
}




void Driver::turn180() {
    uint8_t previousLeftPwmPercentage = leftMotor_->getPwmPercentage();
    uint8_t previousRightPwmPercentage = rightMotor_->getPwmPercentage();

    bool previousLeftPwmDirection = leftMotor_->getPwmDirection();
    bool previousRightPwmDirection = rightMotor_->getPwmDirection();

    leftMotor_->setPwmDirection(PwmDirection::Forward);
    rightMotor_->setPwmDirection(PwmDirection::Back); 

    leftMotor_->setPwmPercentage(50);
    rightMotor_->setPwmPercentage(50);

    // La fonction _delay_ms(ms) prend en argument une valeur dont l'unit� est la milliseconde.
    // _delay_ms(2500) fournit donc un d�lai de deux secondes et demi avant de red�marrer la minuterie et de tourner.
    _delay_ms(2500);

    leftMotor_->setPwmDirection(previousLeftPwmDirection);
    rightMotor_->setPwmDirection(previousRightPwmDirection);

    leftMotor_->setPwmPercentage(previousLeftPwmPercentage);
    rightMotor_->setPwmPercentage(previousRightPwmPercentage);
}
