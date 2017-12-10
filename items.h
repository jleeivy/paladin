#include <iostream>
#include <string>

#ifndef ITEMS_H_INCLUDED
#define ITEMS_H_INCLUDED

class items {
public:
    class armor {
    private:
        int str;
        int stam;
        int haste;
        int mast;
        int crit;
        int vers;
        int arm;
    public:
        int getStr();
        int getStam();
        int getHaste();
        int getMast();
        int getCrit();
        int getVers();
        int getArm();

        void setStats(int, int, int, int, int, int, int);

        void setStats();
    };
    class weapon {
    private:
        int str;
        int stam;
        int haste;
        int mast;
        int crit;
        int vers;
        int minDam;
        int maxDam;
    public:
        int getStr();
        int getStam();
        int getHaste();
        int getMast();
        int getCrit();
        int getVers();
        int getMinDam();
        int getMaxDam();

        void setStats(int, int, int, int, int, int, int, int);

        void setStats();
    };
};
#endif // ITEMS_H_INCLUDED
