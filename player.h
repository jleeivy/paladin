#include <iostream>
#include <string>

#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

class player {
private:
    int life;
    int maxLife;
public:
    void def();
    void maxHealth(int);
    void heal(int);
    void damage(int);
    int getHealth();
    int getMaxHealth();
};

#endif // PLAYER_H_INCLUDED
