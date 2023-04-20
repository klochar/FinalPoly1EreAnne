#include "Capteur.hpp"


Capteur::Capteur(){
    //mettre en entree la lecture du capteur PA0
    DDRA &= ~(1<<PA0);
    //capteur.lecture(PA0);
}

uint16_t Capteur::lectureCapteur(){
    uint16_t valeur = this->capteur.lecture(PA0);
    valeur = valeur>>2;
    return valeur;
}

bool Capteur::detection1Point(uint16_t& valeur){
    if(valeur >= 107 && valeur <= 215) {
        return true;
    }
    return false;
}

bool Capteur::detection2Point(uint16_t& valeur){
     if (valeur >= 40 && valeur <= 47) {//40 a 47 valeur >= 40 && valeur <= 54
        return true;
    }
     return false;
}

bool Capteur::detection2PointDiagonale(uint16_t& valeur){
    if(valeur>=24 && valeur <= 33){ // 24 a 33, quand 9,1 volt
        return true;
    }
    return false;
}

bool Capteur::detection10Cm(uint16_t& valeur){
    if(valeur>=88 && valeur <= 500){
        return true;
    }
    return false;
}

bool Capteur::detection1PointDiagonale(uint16_t& valeur){
    if (valeur >= 52 && valeur <= 83) {
        return true;
    }
     return false;
}

bool Capteur::detectionVide(uint16_t& valeur){
    if(valeur<=17){
        return true;
    }
    
    // if (10<=valeur &&valeur <= 18  ){//14 
    //     return true;
    // }
    return false;

}
