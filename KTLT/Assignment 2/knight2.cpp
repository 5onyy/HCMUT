#include "knight2.h"

/* * * BEGIN implementation of class BaseBag * * */

/* * * END implementation of class BaseBag * * */

/* * * BEGIN implementation of class BaseKnight * * */
string BaseKnight::toString() const {
    string typeString[4] = {"PALADIN", "LANCELOT", "DRAGON", "NORMAL"};
    // inefficient version, students can change these code
    //      but the format output must be the same
    string s("");
    s += "[Knight:id:" + to_string(id) 
        + ",hp:" + to_string(hp) 
        + ",maxhp:" + to_string(maxhp)
        + ",level:" + to_string(level)
        + ",gil:" + to_string(gil)
        + "," + bag->toString()
        + ",knight_type:" + typeString[knightType]
        + "]";
    return s;
}


/* * * END implementation of class BaseKnight * * */

/* * * BEGIN implementation of class ArmyKnights * * */

int ArmyKnights:: count() const{
    return n;
}

ArmyKnights:: ArmyKnights(const string & file_armyknights){
    ifstream ifa(file_armyknights);
    ifa>>n;
    ArmyKnights.knight= new BaseKnight*[n];
    for (int i=0;i<n;i++)
    {
        int id,maxhp,level,gil,antidote,phoenixdownI;
        cin>>id>>maxhp>>level>>gil>>antidote>>phoenixdownI; 
        ArmyKnights.knight[i]=BaseKnight.create(id,maxhp,level,gil,antidote,phoenixdownI);
    }
}

void ArmyKnights::printInfo() const {
    cout << "No. knights: " << this->count();
    if (this->count() > 0) {
        BaseKnight * lknight = lastKnight(); // last knight
        cout << ";" << lknight->toString();
    }
    cout << ";PaladinShield:" << this->hasPaladinShield()
        << ";LancelotSpear:" << this->hasLancelotSpear()
        << ";GuinevereHair:" << this->hasGuinevereHair()
        << ";ExcaliburSword:" << this->hasExcaliburSword()
        << endl
        << string(50, '-') << endl;
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

void KnightAdventure ::loadArmyKnights(const string &file_armyknights){
    armyKnights(file_armyknights);
}

void KnightAdventure ::loadEvents(const string &file_events){
    
}

/* * * END implementation of class KnightAdventure * * */