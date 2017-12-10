//main program for paladin simulation
#include <iostream>
#include <iomanip>
#include <string>
#include <time.h>
#include "items.h"
#include "spells.h"
#include "player.h"
#include "mob.h"

using namespace std;

//GCD spells
int castJudgment(int,int,double);
int castAvShld(int,int,double);
int castHotR(int,int,double);
int damageConsec(int, int, double);

//non-GCD spells
int castSotR(int,int,double);
int castLotP(int,int,double);

//PROC effects
bool grandCrusader(int);

//mechanics
double randRange();
double SotRMitigation(int,bool);
string attackTable(int,int,int,int);


int main()
{
    srand(time(NULL));

    items::armor cloak;
    cloak.setStats(137,880,1321,302,0,0,512);
    items::armor chest;
    chest.setStats(706,1566,2349,0,445,1004,0);
    items::armor feet;
    feet.setStats(485,1174,1762,0,753,0,333);
    items::armor hands;
    hands.setStats(441,1174,1762,450,0,637,0);
    items::armor head;
    head.setStats(573,1566,2349,476,0,973,0);
    items::armor legs;
    legs.setStats(617,1566,2349,0,569,0,880);
    items::armor shoulders;
    shoulders.setStats(529,1174,1762,683,0,0,404);
    items::armor waist;
    waist.setStats(397,1174,1764,637,450,0,0);
    items::armor wrist;
    wrist.setStats(309,880,1321,494,0,0,320);
    items::armor offHand;
    offHand.setStats(1154,880,1321,0,397,414,0);
    items::weapon mainHand;
    mainHand.setStats(4059,6766,671,1006,0,303,315,0);

    const int armorSlots=10;
    const int itemSlots=11;

    int armor[armorSlots]={cloak.getArm(),chest.getArm(),feet.getArm(),hands.getArm(),head.getArm(),legs.getArm(),shoulders.getArm(),waist.getArm(),wrist.getArm(),offHand.getArm()};
    int str[itemSlots]={cloak.getStr(),chest.getStr(),feet.getStr(),hands.getStr(),head.getStr(),legs.getStr(),shoulders.getStr(),waist.getStr(),wrist.getStr(),offHand.getStr(),mainHand.getStr()};
    int stam[itemSlots]={cloak.getStam(),chest.getStam(),feet.getStam(),hands.getStam(),head.getStam(),legs.getStam(),shoulders.getStam(),waist.getStam(),wrist.getStam(),offHand.getStam(),mainHand.getStam()};
    int haste[itemSlots]={cloak.getHaste(),chest.getHaste(),feet.getHaste(),hands.getHaste(),head.getHaste(),legs.getHaste(),shoulders.getHaste(),waist.getHaste(),wrist.getHaste(),offHand.getHaste(),mainHand.getHaste()};
    int mast[itemSlots]={cloak.getMast(),chest.getMast(),feet.getMast(),hands.getMast(),head.getMast(),legs.getMast(),shoulders.getMast(),waist.getMast(),wrist.getMast(),offHand.getMast(),mainHand.getMast()};
    int crit[itemSlots]={cloak.getCrit(),chest.getCrit(),feet.getCrit(),hands.getCrit(),head.getCrit(),legs.getCrit(),shoulders.getCrit(),waist.getCrit(),wrist.getCrit(),offHand.getCrit(),mainHand.getCrit()};
    int vers[itemSlots]={cloak.getVers(),chest.getVers(),feet.getVers(),hands.getVers(),head.getVers(),legs.getVers(),shoulders.getVers(),waist.getVers(),wrist.getVers(),offHand.getVers(),mainHand.getVers()};

    const double statHaste=375.0;
    const double statMast=400.0;
    const double statCrit=400.0;
    const double statVers=475.0;
    const double statParryStr=786.0711197;
    const double statParryCrit=130.0;

    int damage;
    int heal;

    double totalArmor=0;
    int totalStr=0;
    int totalStam=0;
    int totalHaste=0;
    int totalMast=0;
    int totalCrit=0;
    int totalVers=0;

    //total armor
    for (int i=0; i<armorSlots; i++) {
        totalArmor=totalArmor+armor[i];
    }
    //total strength
    for (int i=0; i<itemSlots; i++) {
        totalStr=totalStr+str[i];
    }
    //total stamina
    for (int i=0; i<itemSlots; i++) {
        totalStam=totalStam+stam[i];
    }
    //total haste
    for (int i=0; i<itemSlots; i++) {
        totalHaste=totalHaste+haste[i];
    }
    //total mastery
    for (int i=0; i<itemSlots; i++) {
        totalMast=totalMast+mast[i];
    }
    //total critical strike
    for (int i=0; i<itemSlots; i++) {
        totalCrit=totalCrit+crit[i];
    }
    //total versatility
    for (int i=0; i<itemSlots; i++) {
        totalVers=totalVers+vers[i];
    }

    totalStr=totalStr*1.05;     //plate armor bonus
    int ap=totalStr*(108+totalMast/statMast)/100;
    int critChance=500+totalCrit/statCrit*100;
    double hasteCoef=(100+totalHaste/statHaste)/100;
    double versCoef=(100+totalVers/statVers)/100;
    double redVersCoef=(200-totalVers/statVers)/200;
    const int gcdBase=1500/hasteCoef;
    int gcd=0;
    int weaponDamage;

//spell object(s) creation
//Consecration
    spells::active consec;
    consec.def();
    consec.setBaseCD(9000/hasteCoef);
    consec.setCoef(.3);
    consec.setCoefAlt(9000/hasteCoef);
//Judgment
    spells::active judgment;
    judgment.def();
    judgment.setBaseCD(12000/hasteCoef);
    judgment.setCoef(2.5);
//Avenger's Shield
    spells::active avShld;
    avShld.def();
    avShld.setBaseCD(15000/hasteCoef);
    avShld.setCoef(3.915);
//Hammer of the Righteous
    spells::active HotR;
    HotR.def();
    HotR.setBaseCD(4500/hasteCoef);
    HotR.setCoef(1.12);
    HotR.setCoefAlt(.67);
    HotR.setChargeCap(2);
//Light of the Protector
    spells::active LotP;
    LotP.def();
    LotP.setBaseCD(15000/hasteCoef);
    LotP.setCoef(.3);
//Shield of the Righteous
    spells::active SotR;
    SotR.def();
    SotR.setBaseCD(16000/hasteCoef);
    SotR.setCoef(3.6);
    SotR.setCoefAlt(4500);
    SotR.setChargeCap(3);

//Passives
//Guarded by the Light
    spells::passive GbtL;
    GbtL.setCoef1(1.4);             //stamina modifier
    GbtL.setCoef2(5000);            //%block increase: effect currently in dispute, taken as literal interpretation
//Sanctuary
    spells::passive Sanctuary;
    Sanctuary.setCoef1(.9);         //damage reduction coefficient
    Sanctuary.setCoef2(200);        //%dodge increase
//Grand Crusader
    spells::passive GCrusader;
    GCrusader.setCoef1(1500);       //%chance to proc Grand Crusader

//Enemies
    mob enemy1;
    enemy1.setStats();
    enemy1.setSpeed(1500);
    enemy1.setDamage(100000);
    enemy1.setLvl(110);

//More variables
    int hp=totalStam*GbtL.getCoef1()*60;
    player player;
    player.maxHealth(hp);
    player.heal(hp);

    double coefConsec;
    int durConsec=0;
    int tickConsec=0;
    bool consecUp;
    int ICDSotR=0;
    int durSotR=0;
    double SotRCoef;


    //math to determine internal values. all values base on information as given by lead of dev team "Celestalon"
    double paladinBlockCoef=.6;
    int miss=500;

    const double kValueArmor=7390;
    double armorCoef=1.0-(totalArmor/(totalArmor+kValueArmor));

    double dodge=300+Sanctuary.getCoef2();

    const double kValueParry=.94;
    const double paladinParryConstant=.018;
    double totalParry=totalStr/statParryStr+totalCrit/statParryCrit;
    int parry=300+totalParry/(totalParry*paladinParryConstant+1/kValueParry)*100;

    const double kValueblock=150.3759;
    const double paladinBlockConstant=.886;
    double totalBlock=8+totalMast/statMast;
    int block=500+(totalBlock*kValueblock)/(totalBlock+kValueblock*paladinBlockConstant)*100;
    //end of calculations

    string result;

    //core of program: time measured in milliseconds
    for (double i=0; i<120000; i++) {
        double tick=i/1000;
        //Consecration Active Check
        if (durConsec>0) {
            consecUp=true;
        } else {
            consecUp=false;
        }

        //Enemy Attack
        if (enemy1.swing()) {
            result=attackTable(miss,dodge,parry,block);
            if (result=="Misses") {
                cout<<setw(7)<<left<<tick<<" Melee "<<result<<" player."<<endl;
            } else if (result=="Dodges") {
                cout<<setw(7)<<left<<tick<<" Player "<<result<<" Melee"<<endl;
            } else if (result=="Parries") {
                cout<<setw(7)<<left<<tick<<" Player "<<result<<" Melee"<<endl;
            } else if (result=="Blocks") {
                damage=enemy1.getDamage()*randRange();
                if (durSotR>0) {
                    SotRCoef=SotRMitigation(totalBlock,consecUp);
                } else {
                    SotRCoef=1.0;
                }
                damage=damage*redVersCoef*armorCoef*Sanctuary.getCoef1()*SotRCoef*paladinBlockCoef;  //Versatility and armor damage reduction applied
                player.damage(damage);
                cout<<setw(7)<<left<<tick<<" Melee "<<result<<" Player for "<<damage<<" damage"<<endl;
            } else if (result=="Hits") {
                if (durSotR>0) {
                    SotRCoef=SotRMitigation(totalBlock,consecUp);
                } else {
                    SotRCoef=1.0;
                }
                damage=enemy1.getDamage()*randRange();
                damage=damage*redVersCoef*armorCoef*Sanctuary.getCoef1()*SotRCoef;  //Versatility and armor damage reduction applied
                player.damage(damage);
                cout<<setw(7)<<left<<tick<<" Melee "<<result<<" Player for "<<damage<<" damage"<<endl;
            }
        }

        //non-GCD
        //Light of the Protector
        if (LotP.usable() && durConsec>0) {
            if (durConsec>0) {
                coefConsec=1.2;
            } else {
                coefConsec=1.0;
            }
            heal=castLotP(player.getMaxHealth(),player.getHealth(),LotP.getCoef()*coefConsec);
            heal=heal*versCoef;  //Versatility healing multiplier
            cout<<setw(7)<<left<<tick<<" Player's Light of the Protector healed for "<<heal<<" health"<<endl;
            LotP.cast();
            player.heal(heal);
        //Shield of the Righteous
        }
        if (SotR.usable() && ICDSotR==0) {
            damage=castSotR(ap,critChance,avShld.getCoef());
            damage=damage*versCoef;  //Versatility damage multiplier
            cout<<setw(7)<<left<<tick<<" Player's Shield of the Righteous dealt "<<damage<<" damage"<<endl;
            SotR.cast();
            ICDSotR=1000;
            durSotR=SotR.getCoefAlt();
        }
        //GCD
        if (gcd>0) {
        //Buffers time to generate GCD: does nothing other than stop GCD spells from activating

        //Consecration
        } else if (consec.usable()) {
            cout<<setw(7)<<left<<tick<<" Player casts Consecration"<<endl;
            consec.cast();
            durConsec=consec.getCoefAlt();
            gcd=gcdBase;

        //Judgment
        } else if (judgment.usable()) {
            int critical=1;
            int range=rand();
            if (range<=critChance) {
                critical=2;
            }
            damage=castJudgment(ap,critical,judgment.getCoef());
            damage=damage*versCoef;  //Versatility damage multiplier
            cout<<setw(7)<<left<<tick<<" Player's Judgment dealt "<<damage<<" damage"<<endl;
            judgment.cast();
            if (critical==2) {
                SotR.redCD(4000);
            } else {
                SotR.redCD(2000);
            }
            gcd=gcdBase;

        //Avenger's Shield
        } else if (avShld.usable()) {
            damage=castAvShld(ap,critChance,avShld.getCoef());
            damage=damage*versCoef;  //Versatility damage multiplier
            cout<<setw(7)<<left<<tick<<" Player's Avenger's Shield dealt "<<damage<<" damage"<<endl;
            avShld.cast();
            gcd=gcdBase;

        //Hammer of the Righteous
        } else if (HotR.usable()) {
            weaponDamage=mainHand.getMinDam()+rand() %mainHand.getMaxDam()+ap*2.4/3.5;     //weapon damage calculation
            damage=castHotR(weaponDamage,critChance,HotR.getCoef());
            damage=damage*versCoef;  //Versatility damage multiplier
            cout<<setw(7)<<left<<tick<<" Player's Hammer of the Righteous dealt "<<damage<<" damage"<<endl;
            HotR.cast();
            if (grandCrusader(GCrusader.getCoef1())) {
                    avShld.addCharge();
            }
            gcd=gcdBase;
        }
        enemy1.milliSec();
        LotP.milliSec();
        SotR.milliSec();
        judgment.milliSec();
        avShld.milliSec();
        HotR.milliSec();
        consec.milliSec();

        //Shield of the Righteous buff tracker
        if (durSotR>0) {
            durSotR--;
        } else {
            durSotR=0;
        }
        //consecration buff tracker
        if (durConsec>0) {
            durConsec--;
            tickConsec++;
        } else {
            durConsec=0;
            tickConsec=0;
        }
        if (tickConsec>consec.getCoefAlt()/9-1) { //the minus 1 is to fix a double floating rounding error preventing me from evenly dividing time into 9 equal segments
            tickConsec=0;
            damage=damageConsec(ap,critChance,consec.getCoef());
            damage=damage*versCoef;  //Versatility damage multiplier
            cout<<setw(7)<<left<<tick<<" Player's Consecration dealt "<<damage<<" damage"<<endl;
        }
        //SotR ICD tracker
        if (ICDSotR>0) {
            ICDSotR--;
        } else {
            ICDSotR=0;
        }
        //global cooldown tracker
        if (gcd>0) {
            gcd--;
        } else {
            gcd=0;
        }
    }
    return 0;
}

//functions for casting spells
int damageConsec(int ap, int critChance, double coef) {
    double critical=1.0;
    int range=rand() %10000;
    if (critChance>=range) {              //checks to see if skill scored critical
        critical=2.0;
    }
    int damage=ap*coef*randRange()*critical;
    return damage;
}
int castJudgment(int ap, int critical, double coef) {
    int damage=ap*coef*randRange()*critical;
    return damage;
}
int castAvShld(int ap, int critChance, double coef) {
    double critical=1.0;
    int range=rand() %10000;
    if (critChance>=range) {              //checks to see if skill scored critical
        critical=2.0;
    }
    int damage=ap*coef*randRange()*critical;
    return damage;
}
int castHotR(int weaponDamage, int critChance, double coef) {
    double critical=1.0;
    int range=rand() %10000;
    if (critChance>=range) {              //checks to see if skill scored critical
        critical=2.0;
    }
    int damage=weaponDamage*coef*critical;
    return damage;
}
int castSotR(int ap, int critChance, double coef) {
    double critical=1.0;
    int range=rand() %10000;
    if (critChance>=range) {              //checks to see if skill scored critical
        critical=2.0;
    }
    int damage=ap*coef*randRange()*critical;
    return damage;
}
int castLotP(int maxHP, int curHP, double coef) {
    int heal;
    heal=(maxHP-curHP)*coef;
    return heal;
}
bool grandCrusader(int chance) {
    bool proc=false;
    int range=rand() %10000;
    if (range<=chance) {
        proc=true;
    }
    return proc;
}
double randRange() {
    double var=825+rand() %351;
    var=var/1000;
    return var;
}
string attackTable(int miss, int dodge, int parry, int block) {
    int range=rand() %10000;
    string reply;
    if (range<=miss) {
        reply="Misses";
    } else if (range<=miss+dodge) {
        reply="Dodges";
    } else if (range<=miss+dodge+parry) {
        reply="Parries";
    } else if (range<=miss+dodge+parry+block) {
        reply="Blocks";
    } else {
        reply="Hits";
    }
    return reply;
}
double SotRMitigation(int mastery, bool consec) {
    double mitiCoef=(25+mastery/2)/100;
    if (consec==true) {
        mitiCoef=mitiCoef*1.2;
    }
    mitiCoef=1-mitiCoef;
    return mitiCoef;
}

