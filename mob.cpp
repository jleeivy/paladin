#include "mob.h"
//default constructor
void mob::setStats() {
    speed=1500;
    speedCD=0;
    damage=100000;
    lvl=110;
}
//setters
void mob::setSpeed(int x) {
    speed=x;
}
void mob::attack() {
    speedCD=speed;
}
void mob::setDamage(int x) {
    damage=x;
}
void mob::setLvl(int x) {
    lvl=x;
}
void mob::milliSec() {
    if (speedCD>speed) {
        speedCD=0;
    } else {
        speedCD++;
    }
}
//getters
int mob::getDamage() {
    return damage;
}
int mob::getLvl() {
    return lvl;
}
bool mob::swing() {
    if (speedCD==0) {
        return true;
    } else {
        return false;
    }
}
