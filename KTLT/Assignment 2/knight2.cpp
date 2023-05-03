#include "knight2.h"
#define debug(x) { cout << #x << " = "; cout << (x) << endl; }

/* * * BEGIN implementation of class BaseBag * * */

/* * * END implementation of class BaseBag * * */

/* * * BEGIN implementation of class BaseKnight * * */

 string BaseKnight::toString() const {
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
    s+="[Knight:id:" + to_string(id) 
        + ",hp:" + to_string(hp) 
        + ",maxhp:" + to_string(maxhp)
        + ",level:" + to_string(level)
        + ",gil:" + to_string(gil)
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
    debug(n_ev);
    ev=new int [n_ev];
    for (int i=0;i<n_ev;i++)
        ife>>ev[i];
}
/* * * END implementation of class Events * * */    

/* * * BEGIN implementation of class NormalType * * */
BaseOpponent :: BaseOpponent(int pos, int _id){
    i=pos;
    id=_id;
}
/* * * END implementation of class NormalType * * */

/* * * BEGIN implementation of class ArmyKnights * * */

int ArmyKnights:: count() const{
    return n;
}
BaseKnight* ArmyKnights:: lastKnight() const{
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
        ifa>>id>>maxhp>>level>>gil>>antidote>>phoenixdownI; 
        //debug(id);  debug(maxhp);   debug(level);   debug(gil); debug(antidote);    debug(phoenixdownI);
        this->knight[i]=this->knight[i]->create(id,maxhp,level,gil,antidote,phoenixdownI);
    }
}

bool ArmyKnights::fight(BaseOpponent * opponent){
    debug(opponent -> id);
    if (opponent->id >=1 && opponent->id <=5){
        debug(knight[cur]->level);
        if (knight[cur]->level < opponent -> levelO()){
            int bd=opponent->base_damage();
            int levelo=opponent->levelO();
            int lv=knight[cur]->level;
            knight[cur]->hp=knight[cur]->hp - bd * (levelo-lv);
            return 0;
        }
    }
    return 1;
}

bool ArmyKnights::adventure(Events * events){
    for (int i=0;i<events->count();i++)
    {
        if (events->get(i) >=1 && events->get(i)<=5)
        {
            BaseOpponent *target= new BaseOpponent(i,events->get(i));
            debug(target -> i);
            debug(target -> id);
            bool flag=fight(target);
            return flag;
        }
    }
}

void ArmyKnights::printInfo() const {
    cout << "No. knights: " << this->count();
    if (this->count() > 0) {
        BaseKnight * lknight = lastKnight(); // last knight
        cout << ";" << lknight->toString();
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
/*     debug(events -> n_ev);
    debug(events -> count());
    debug(events -> get(0)); */
}

void KnightAdventure:: run()
{
    bool f=armyKnights->adventure(events);
    debug(f);
} 

/* * * END implementation of class KnightAdventure * * */