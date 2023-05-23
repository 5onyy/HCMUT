#ifndef __KNIGHT2_H__
#define __KNIGHT2_H__

#include "main.h"

// #define DEBUG

enum ItemType {antidote=0,phoenixdownI,phoenixdownII,phoenixdownIII,phoenixdownIV};
enum KnightType { PALADIN = 0, LANCELOT, DRAGON, NORMAL };

class BaseKnight;
class _BaseItem;
class Events;
class BaseOpponent;
class node;
class ArmyKnights;

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
        using BaseOpponent :: BaseOpponent;
};

class Tornbery : public BaseOpponent{
    public:
        using BaseOpponent :: BaseOpponent;
};

class Queen : public BaseOpponent{
    public:
        using BaseOpponent :: BaseOpponent;
};

class BaseItem {
public:
    virtual bool canUse ( BaseKnight * knight ,ItemType item_type) =0;
    virtual void use ( BaseKnight * knight ) = 0;
};

class _BaseItem : public BaseItem
{
    public:
    ItemType item_type;
    int num;
    _BaseItem(ItemType type){
        item_type=type;
    }
    bool canUse ( BaseKnight * knight ,ItemType item_type){
        return 0;
    }
    void use ( BaseKnight * knight ){
        return;
    };
};
    

class node{
    public:
    node *next;
    _BaseItem* item;
    node() {};
    node(_BaseItem *it) {
        item=it;
        next=NULL;
    }
};

template<typename T> class BaseBag {
public:
    T* head=NULL;
    int size();
    BaseBag();
    BaseBag(int anti, int phoenixI);
    BaseBag(BaseKnight* kn, int anti, int phoenixI);
    virtual bool insertFirst ( BaseItem * item ){
        return 0;
    }
    virtual BaseItem * get(ItemType itemType){
        return NULL;
    }
    virtual bool insertFirst(_BaseItem * item,int limit, T*& head);
    void get(ItemType itemType,T*& head);
    void lose_bag(T*& head);
    virtual string toString();
    ~BaseBag(){
        T* tmp=head;
        while (head!=NULL){
            head=head->next;
            delete tmp;
            tmp=head;
        }
    }
};

class BaseKnight{
public:
    int id;
    int maxhp;
    int hp;
    int level;
    int gil;
    int antidote;
    int phoenixdownI;
    bool poison=0;
    BaseBag<node> * bag;
    bool prime (int hp){
        if (hp<2)   
            return 0;
        for (int i=2;i*i<=hp;i++)
            if (hp%i==0)
                return 0;
        return 1;
    }
    KnightType knight_Type(){
        if (prime(maxhp))
            return PALADIN;
        if (maxhp==888)
            return LANCELOT;
        int a=maxhp%10;
        int b=(maxhp%100)/10;
        int c=maxhp/100;
        if ((maxhp<=999 && maxhp >=100)  &&  (a*a==b*b+c*c || b*b==a*a+c*c || c*c==a*a+b*b) && (a>0 && b>0 && c>0))
            return DRAGON;
        return NORMAL;       
    };
    int bag_limit();
    double knightBaseDamage[3]={0.06,0.05,0.075};
    static BaseKnight * create(int _id, int _maxhp, int _level, int _phoenixdownI, int _gil, int _antidote){
        BaseKnight *a=new BaseKnight [6];
        a->id=_id; a->maxhp=_maxhp; a->level=_level; a->gil=_gil; a->antidote=_antidote; a->phoenixdownI=_phoenixdownI; a->hp=a->maxhp;
        return a;
    }
    ~BaseKnight(){
        delete bag;
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
        for (int i=0;i<n;i++)
            if (knight[i])
                delete [] knight[i];
        delete [] knight;
    };
    bool met_omega;
    bool met_hades;
    bool fight(BaseOpponent * target);
    bool adventure (Events * events);
    int count() const;
    BaseKnight * lastKnight() const;
    void collect_gil(BaseKnight * lnkight, int op_gil);
    bool can_revive(BaseKnight * lknight);
    bool hasPaladin;
    bool hasLancelot;
    bool hasGuinevere;
    bool hasExcalibur;
    bool win_Ultimecia;
    bool hasPaladinShield() const{
        return hasPaladin;
    };

    bool hasLancelotSpear() const{
        return hasLancelot;
    };
    bool hasGuinevereHair() const{
        return hasGuinevere;
    };
    bool hasExcaliburSword() const{
        return hasExcalibur;
    };
    void printInfo() const;
    void printResult(bool win) const;
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