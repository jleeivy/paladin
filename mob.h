#ifndef MOB_H_INCLUDED
#define MOB_H_INCLUDED

class mob {
    private:
        int speed;
        int speedCD;
        int damage;
        int lvl;
    public:
        void setStats();
        void setSpeed(int);
        void attack();
        void setDamage(int);
        void setLvl(int);
        void milliSec();
        int getDamage();
        int getLvl();
        bool swing();
};
#endif // MOB_H_INCLUDED
