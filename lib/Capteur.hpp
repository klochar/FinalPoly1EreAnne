#ifndef CAPTEUR_HPP
#define CAPTEUR_HPP
#define F_CPU 8000000UL
#include "can.h"



class Capteur {
public : 
    Capteur();
    ~Capteur() = default;
    uint16_t lectureCapteur();
    bool detection1Point(uint16_t& valeur);
    bool detection2Point(uint16_t& valeur);
    bool detection1PointDiagonale(uint16_t& valeur);
    bool detection2PointDiagonale(uint16_t& valeur);
    bool detection10Cm(uint16_t& valeur);//a mettre const
    bool detectionVide(uint16_t& valeur);

    

private :
    can capteur = can();


};

#endif