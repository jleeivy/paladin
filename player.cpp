#include "player.h"

void player::def(){
    life=0;
    maxLife=0;
}
void player::maxHealth(int x){
    maxLife=x;
}
void player::heal(int x){
    if (life+x>maxLife) {
        life=maxLife;
    } else {
        life=life+x;
    }
}
void player::damage(int x){
    if (life<x) {
        life=0;
    } else {
        life=life-x;
    }
}
int player::getHealth(){
    return life;
}
int player::getMaxHealth() {
    return maxLife;
}
