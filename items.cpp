#include "items.h"
//armor
//default constructors
void items::armor::setStats() {
    arm=0;
    str=0;
    stam=0;
    haste=0;
    mast=0;
    crit=0;
    vers=0;
}
//setters
void items::armor::setStats(int a, int b, int c, int d, int e, int f, int g) {
    arm=a;
    str=b;
    stam=c;
    haste=d;
    mast=e;
    crit=f;
    vers=g;
}
//getters
int items::armor::getStr() {
    return str;
}
int items::armor::getStam() {
    return stam;
}
int items::armor::getHaste() {
    return haste;
}
int items::armor::getMast() {
    return mast;
}
int items::armor::getCrit() {
    return crit;
}
int items::armor::getVers() {
    return vers;
}
int items::armor::getArm() {
    return arm;
}
//weapons
//default constructors
void items::weapon::setStats() {
    minDam=0;
    maxDam=0;
    str=0;
    stam=0;
    haste=0;
    mast=0;
    crit=0;
    vers=0;
}
//setters
void items::weapon::setStats(int a, int b, int c, int d, int e, int f, int g, int h) {
    minDam=a;
    maxDam=b;
    str=c;
    stam=d;
    haste=e;
    mast=f;
    crit=g;
    vers=h;
}
//getters
int items::weapon::getStr() {
    return str;
}
int items::weapon::getStam() {
    return stam;
}
int items::weapon::getHaste() {
    return haste;
}
int items::weapon::getMast() {
    return mast;
}
int items::weapon::getCrit() {
    return crit;
}
int items::weapon::getVers() {
    return vers;
}
int items::weapon::getMinDam() {
    return minDam;
}
int items::weapon::getMaxDam() {
    return maxDam;
}
