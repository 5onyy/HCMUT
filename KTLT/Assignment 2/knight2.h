#ifndef __KNIGHT2_H__
#define __KNIGHT2_H__

#include "main.h"

// #define DEBUG

enum ItemType {/* TODO: */};

class BaseBag {
public:
    virtual bool insertFirst(BaseItem * item);
    virtual BaseItem * get(ItemType itemType);
    virtual string toString() const;
};

class BaseOpponent;

enum KnightType { PALADIN = 0, LANCELOT, DRAGON, NORMAL };
class BaseKnight {
protected:
    int id;
    int hp;
    int maxhp;
    int level;
    int gil;
    int antidote;
    BaseBag * bag;
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
        int a=hp%10, b=(hp%100)/10, c=hp/100;
        if ((hp<=999 && hp >=100)  &&  (a*a=b*b+c*c || b*b=a*a+c*c || c*c=a*a+b*b))
            return DRAGON;
        return NORMAL;       
    };

public:
    static BaseKnight * create(int id, int maxhp, int level, int gil, int antidote, int phoenixdownI){
        int *a=new int [6];
        a[0]=id, a[1]=maxhp, a[2]=level, a[3]=gil, a[4]=antidote, a[5]=phoenixdownI;
        return a;
    }
    string toString() const;
};

class ArmyKnights {
public:
    int n;

    ArmyKnights (const string & file_armyknights);
    ~ArmyKnights();
    bool fight(BaseOpponent * opponent);
    bool adventure (Events * events);
    int count() const;
    BaseKnight * lastKnight() const;
    BaseKnight **knight;
    bool hasPaladinShield() const;
    bool hasLancelotSpear() const;
    bool hasGuinevereHair() const;
    bool hasExcaliburSword() const;

    void printInfo() const;
    void printResult(bool win) const;
};

class BaseItem {
public:
    virtual bool canUse ( BaseKnight * knight ) = 0;
    virtual void use ( BaseKnight * knight ) = 0;
};

class Events {
public:
    int n_ev;
    int count() const;
    int get(int i) const;
    int *ev=new int[count()];
    Events (const string & file_events){
        ifstream ife(file_events);
        
    }
};

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