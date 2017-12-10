#include "spells.h"
//Active spells
void spells::active::def() {
    CD=0;
    baseCD=0;
    coef=0.0;
    coefAlt=0.0;
    charge=1;
    chargeCap=1;
}
void spells::active::setChargeCap(int x) {
    chargeCap=x;
    charge=x;
}
void spells::active::setCoef(double x) {
    coef=x;
}
void spells::active::setCoefAlt(double x) {
    coefAlt=x;
}
void spells::active::setBaseCD(int sec) {
    CD=0;
    baseCD=sec;
}
void spells::active::milliSec() {
    if (charge<chargeCap) {
        CD++;
    }
    if (CD>=baseCD) {
        CD=CD-baseCD;
        charge++;
    }
}
void spells::active::cast() {
    charge--;
}
bool spells::active::usable() {
    if (charge>0) {
        return true;
    } else {
        return false;
    }
}
void spells::active::addCharge() {
    if (charge<chargeCap) {
        charge++;
    }
}
void spells::active::redCD(int sec) {
    CD=CD+sec;
}
double spells::active::getCoef() {
    return coef;
}
double spells::active::getCoefAlt() {
    return coefAlt;
}
//Passive spells
void spells::passive::def() {
    coef1=0;
    coef2=0;
    coef3=0;
}
void spells::passive::setCoef1(double x) {
    coef1=x;
}
void spells::passive::setCoef2(double x) {
    coef2=x;
}
void spells::passive::setCoef3(double x) {
    coef3=x;
}
double spells::passive::getCoef1() {
    return coef1;
}
double spells::passive::getCoef2() {
    return coef2;
}
double spells::passive::getCoef3() {
    return coef3;
}
