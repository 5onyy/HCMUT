#include "knight2.h"
#define debug(x) { cout << #x << " = "; cout << (x) << endl; }

/* * * BEGIN implementation of class BaseBag * * */

/* * * END implementation of class BaseBag * * */

/* * * BEGIN implementation of class BaseKnight * * */

 string BaseKnight::toString() {
    string typeString[4] = {"PALADIN", "LANCELOT", "DRAGON", "NORMAL"};
    // inefficient version, students can change these code
    //      but the format output must be the same
    string s("");
/*     s += "[Knight:id:" + to_string(id) 
        + ",hp:" + to_string(hp) 
        + ",maxhp:" + to_string(maxhp)
        + ",level:" + to_string(level)
        + ",gil:" + to_string(gil)
        + "," + bag->toString()
        + ",knight_type:" + typeString[BaseKnight.knight_Type()]
        + "]"; */
    int num=knight_Type();
    s+="[Knight:id:" + to_string(id) 
        + ",hp:" + to_string(hp) 
        + ",maxhp:" + to_string(maxhp)
        + ",level:" + to_string(level)
        + ",gil:" + to_string(gil)
        + ",knight_type:" + typeString[num]
        +"]";
    return s;
}

/* * * END implementation of class BaseKnight * * */

/* * * BEGIN implementation of class Events * * */
int Events :: count() const{
    return n_ev;
}

int Events :: get(int i) const{
    return ev[i];
}

Events:: ~Events(){
    delete ev;
}

Events:: Events (const string & file_events){
    ifstream ife(file_events);
    ife>>n_ev;
    ev=new int [n_ev];
    for (int i=0;i<n_ev;i++)
        ife>>ev[i];
}
/* * * END implementation of class Events * * */    

/* * * BEGIN implementation of class NormalType * * */
/* BaseOpponent :: BaseOpponent(int pos, int _id){
    i=pos;
    id=_id;
} */
/* * * END implementation of class NormalType * * */

/* * * BEGIN implementation of class ArmyKnights * * */

int ArmyKnights:: count() const{
    return n;
}
BaseKnight* ArmyKnights:: lastKnight() const{
    if (cur<0)  return NULL;
    return knight[cur];
}
ArmyKnights:: ArmyKnights(const string & file_armyknights){
    ifstream ifa(file_armyknights);
    ifa>>n;
    cur=n-1;
    this->knight= new BaseKnight *[n];
    for (int i=0;i<n;i++)
    {
        int id,maxhp,level,gil,antidote,phoenixdownI;
        ifa>>maxhp>>level>>phoenixdownI>>gil>>antidote; 
        //debug(id);  debug(maxhp);   debug(level);   debug(gil); debug(antidote);    debug(phoenixdownI);
        this->knight[i]=this->knight[i]->create(i+1,maxhp,level,phoenixdownI,gil,antidote);
    }
    met_omega=0;
    met_hades=0;
    hasPaladinShield=0;
    hasLancelotSpear=0;
    hasGuinevereHair=0;
    hasExcaliburSword=0;
    win_Ultimecia=0;
}

bool ArmyKnights :: can_revive(BaseKnight * lknight)
{
    /// BEGIN IMPLEMENTATION FIND PHOENIXDOWN
    /// END IMPLEMENTATION FIND PHOENIXDOWN

    /// USING GIL
    if (lknight->gil >= 100)
    {
        lknight -> gil -=100;
        lknight -> hp = lknight -> maxhp /2;
        return 1;
    } 
    else {
        cur --; // one knight dies
        n--;     
        lknight=lastKnight();
        return 0;
    }
    return 1;
}

bool ArmyKnights::fight(BaseOpponent * target){
    BaseKnight * lknight = lastKnight();
    if (target->id >=1 && target->id <=5)
    {
        normalType * opponent=new normalType (target->i, target->id);
        if (lknight->level < opponent -> levelO())
        {
            int bd=opponent->base_damage();
            int levelo=opponent->levelO();
            int lv=lknight->level; 
            lknight->hp=lknight->hp - bd * (levelo-lv);
            
            // When HP<=0 
            if (lknight->hp <=0 )
                return 0;
        }
        else
        {
            //Start collecting gil
            if (lknight->gil + opponent ->gil() > 999)
            {    
                int gil=opponent -> gil();
                int new_cur=cur;
                BaseKnight * new_lknight=knight[new_cur];
                while (new_cur>= 0 && gil>0){
                    int tmp=999-new_lknight->gil;
                    //debug(tmp);
                    gil-=tmp;
                    new_lknight->gil+=tmp;
                    knight[new_cur]->gil=new_lknight->gil;
                    new_cur --;
                    new_lknight=knight[new_cur];
                }
                //debug(gil);
            }
            else 
                lknight->gil += opponent -> gil();
            return 1;
        }
        return 1;        
    }
    if (target->id == 6)
    {
        Tornbery* opponent = new Tornbery (target->i, target -> id);
        if (lknight->level > opponent -> levelO()){
            lknight -> level = min (lknight -> level +1, 10);
        }
        else
        {
            if (lknight -> antidote >0)
            {
                lknight -> antidote--;
            }
            else
            {
                lknight->hp-=10;
                ///BEGIN IMPLEMENTATION KNIGHT DROP THEIR BAG
                ///END IMPLEMENTATION KNIGHT DROP THEIR BAG

                /// IF lKNIGHT dies
                if (lknight->hp <= 0)
                    return 0;
            }
        }
        return 1;
    }
    if (target->id == 7)
    {
        Queen* opponent = new Queen (target -> i, target -> id);
        {
            if (lknight->level > opponent -> levelO()){
                lknight->gil *=2;
                if (lknight->gil > 999)
                {
                    int tmp=lknight->gil-999;
                    lknight->gil=999;
                    int new_cur=cur-1;
                    while (new_cur >=0 && tmp>0)
                    {
                        int add=min(999-knight[new_cur]->gil,tmp);
                        knight[new_cur]->gil+=add;
                        tmp-=add;
                        new_cur--;
                    }
                    //debug(tmp);                    
                }
            }
            else lknight->gil/=2;
        }
        return 1;
    } 
    if (target->id == 8)
    {
        if (lknight->gil >= 50)
        {
            if (lknight->hp < lknight -> maxhp /3)
            {
                lknight->gil-=50;
                lknight->hp+=lknight->maxhp/5;
            }
        }
        return 1;
    }
    if (target->id == 9)
        lknight->hp=lknight->maxhp;
    if (target->id == 10)
    {
        if (met_omega)  return 1;
        met_omega=1;
        if ((lknight->level == 10 && lknight -> hp == lknight -> maxhp) || (lknight->knight_Type()==2)) // DRAGON TYPE
        {
            lknight->level=10;
            lknight->gil=999;
            return 1;
        }
        lknight->hp=0;
        return 0;
    }
    if (target->id == 11)
    {
        if (met_hades)  return 1;
        met_hades=1;
        if (lknight->level==10 || (lknight->knight_Type()==0 && lknight -> level >=8))
        {
            hasPaladinShield=1;
            return 1;
        }
        lknight-> hp=0;
        return 0;
    }
    if (target->id == 12)
    {
        if (hasExcaliburSword)
        {
            win_Ultimecia=1;    return 1;
        }
        else if (hasPaladinShield && hasLancelotSpear && hasGuinevereHair)  //accept fight
        {
            int Ultimecia_hp=5000;
            {
                for (int i=cur;i>=0;i++)
                {
                    if (knight[i]->knight_Type()==3)    continue;
                    int damage= knight[i]->hp * knight[i]->level * knight[i]->knightBaseDamage[knight[i]->knight_Type()];
                    Ultimecia_hp-=damage;
                    if (Ultimecia_hp<=0)    
                        {win_Ultimecia;  return 1;}
                    knight[i]->hp=0;
                }
            }
        }
    }
}

bool ArmyKnights::adventure(Events * events){
    BaseKnight * lknight = lastKnight();
    for (int i=0;i<events->count();i++)
    {
        BaseOpponent *target= new BaseOpponent(i,events->get(i));
        bool f=fight(target);
        while (f==0)
        {
            //cout<<lknight->toString()<<endl;
            lknight=lastKnight();
            if (can_revive(lknight))
                break;
            if (cur<0)
                return 0;
            f=fight(target);    
        }
    }
    return 1;
}

void ArmyKnights::printInfo() const {
    cout << "No. knights: " << this->count()<<endl;
    if (this->count() > 0) {
        for (int i=0;i<n;i++){
            cout << knight[i]->toString()<<endl;
        }
        BaseKnight * lknight = lastKnight(); // last knight
        
    }
/*     cout << ";PaladinShield:" << this->hasPaladinShield()
        << ";LancelotSpear:" << this->hasLancelotSpear()
        << ";GuinevereHair:" << this->hasGuinevereHair()
        << ";ExcaliburSword:" << this->hasExcaliburSword()
        << endl
        << string(50, '-') << endl; */
}

void ArmyKnights::printResult(bool win) const {
    cout << (win ? "WIN" : "LOSE") << endl;
}

/* * * END implementation of class ArmyKnights * * */

/* * * BEGIN implementation of class KnightAdventure * * */
KnightAdventure::KnightAdventure() {
    armyKnights = nullptr;
    events = nullptr;
}
KnightAdventure :: ~KnightAdventure(){
    delete armyKnights;
    delete events;

}
void KnightAdventure ::loadArmyKnights(const string &file_armyknights){
    armyKnights=new ArmyKnights(file_armyknights);
}

void KnightAdventure ::loadEvents(const string &file_events){
    events=new Events(file_events);    
}

void KnightAdventure:: run()
{
    bool f=armyKnights->adventure(events);
    armyKnights->printInfo();
} 

/* * * END implementation of class KnightAdventure * * */