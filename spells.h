#include <string>

#ifndef SPELLS_H_INCLUDED
#define SPELLS_H_INCLUDED

class spells {
    public:
    class active {
    private:
        int CD;
        int baseCD;
        int charge;
        int chargeCap;
        double coef;
        double coefAlt;
    public:
        void def();
        void setChargeCap(int);
        void setCoef(double);
        void setCoefAlt(double);
        void setBaseCD(int);
        void redCD(int);
        void milliSec();
        void cast();
        void addCharge();
        double getCoef();
        double getCoefAlt();
        bool usable();
    };
    class passive {
    private:
        double coef1;
        double coef2;
        double coef3;
    public:
        void def();
        void setCoef1(double);
        void setCoef2(double);
        void setCoef3(double);
        double getCoef1();
        double getCoef2();
        double getCoef3();
    };
};
#endif // SPELLS_H_INCLUDED
