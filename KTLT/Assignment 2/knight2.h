#ifndef __KNIGHT2_H__
#define __KNIGHT2_H__

#include "main.h"

// #define DEBUG

//enum ItemType {/* TODO: */};

/* class BaseBag {
public:
    virtual bool insertFirst(BaseItem * item);
    virtual BaseItem * get(ItemType itemType);
    virtual string toString() const;
}; */

class Events {
public:
    int n_ev;
    int *ev=NULL;
    Events (const string & file_events);
    ~Events();
    int count() const;
    int get(int i) const;
};

class BaseOpponent{
    public:
    int i;
    int id;
    int levelO(){
        return ((i+id)%10+1);
    };
    int g[6]={0,100,150,450,750,800};
    int base[6]={0,10,15,45,75,95};
    int base_damage(){
        return base[id];
    } 
    int gil(){
        return g[id];
    }
    BaseOpponent(int pos, int _id){
        i=pos;
        id=_id;
    }
};

class normalType : public BaseOpponent{
    public:
/*         normalType(int pos, int _id){
            i=pos;
            id=_id;
        } */
        using BaseOpponent :: BaseOpponent;
};

class Tornbery : public BaseOpponent{
    public:
/*         Tornbery(int pos, int _id){
            i=pos;
            id=_id;
        } */
        using BaseOpponent :: BaseOpponent;
};

class Queen : public BaseOpponent{
    public:
        using BaseOpponent :: BaseOpponent;
};

enum KnightType { PALADIN = 0, LANCELOT, DRAGON, NORMAL };

class BaseKnight {
public:
    int id;
    int maxhp;
    int hp;
    int level;
    int gil;
    int antidote;
    int phoenixdownI;
    bool poison=0;
    //BaseBag * bag;
    bool prime (int hp){
        if (hp<2)   
            return 0;
        for (int i=2;i*i<=hp;i++)
            if (hp%i==0)
                return 0;
        return 1;
    }
    KnightType knight_Type(){
        if (prime(hp))
            return PALADIN;
        if (hp==888)
            return LANCELOT;
        int a=hp%10;
        int b=(hp%100)/10;
        int c=hp/100;
        if ((hp<=999 && hp >=100)  &&  (a*a==b*b+c*c || b*b==a*a+c*c || c*c==a*a+b*b))
            return DRAGON;
        return NORMAL;       
    };
    double knightBaseDamage[3]={0.06,0.05,0.075};
    static BaseKnight * create(int _id, int _maxhp, int _level, int _phoenixdownI, int _gil, int _antidote){
        BaseKnight *a=new BaseKnight [6];
        a->id=_id; a->maxhp=_maxhp; a->level=_level; a->gil=_gil; a->antidote=_antidote; a->phoenixdownI=_phoenixdownI; a->hp=a->maxhp;
        return a;
    }
    string toString() ;
};

class ArmyKnights {
public:
    int n;
    int cur;
    BaseKnight **knight=NULL;
    ArmyKnights (const string & file_armyknights);
    ~ArmyKnights(){
        delete knight;
    };
    bool met_omega;
    bool met_hades;
    bool fight(BaseOpponent * target);
    bool adventure (Events * events);
    int count() const;
    BaseKnight * lastKnight() const;
    bool can_revive(BaseKnight * lknight);
    bool hasPaladinShield;
    bool hasLancelotSpear;
    bool hasGuinevereHair;
    bool hasExcaliburSword;
    bool win_Ultimecia;
    void printInfo() const;
    void printResult(bool win) const;
};

/* class BaseItem {
public:
    virtual bool canUse ( BaseKnight * knight ) = 0;
    virtual void use ( BaseKnight * knight ) = 0;
}; */



class KnightAdventure {
private:
    ArmyKnights * armyKnights;
    Events * events;

public:
    KnightAdventure();
    ~KnightAdventure(); // TODO:

    void loadArmyKnights(const string &file_armyknights);
    void loadEvents(const string &file_events);
    void run();
};

#endif // __KNIGHT2_H__