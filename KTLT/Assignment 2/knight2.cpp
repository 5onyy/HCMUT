#include "knight2.h"
#define debug(x) { cout << #x << " = "; cout << (x) << endl; }

/* * * BEGIN implementation of class BaseBag * * */

template<typename T> bool BaseBag<T> :: insertFirst(_BaseItem * item,int limit, T *&head)
{
    if (size()<limit)
    {
        T* n = new T(item);
        n->next=head;
        head=n;
        //debug(size());
        return 1;
    }
    return 0;
}

template<typename T> int BaseBag<T> ::size(){
    node *tmp=head;
    if (tmp==NULL) 
        return 0;
    int count=1;
    while (tmp->next != NULL)
    {
        count++;
        tmp=tmp->next;
    }
    return count;
}

template<typename T> void BaseBag<T> :: get(ItemType itemType,T*& head){
    if (head->item->item_type==itemType){
        //_BaseItem *anss=head->item;
        head=head->next;
        return;
    }
    else{
        T* prevY=NULL;
        T* curY=head;
        T* prevX=NULL;
        T* curx=head;
        while(curY!=NULL){
            if (curY->item->item_type==itemType)
                break;
            prevY=curY;
            curY=curY->next;
        }
        if (curY==NULL)    return;
        prevY->next=curx;
        head=curY;
        T *tmp=curY->next;
        curY->next=curx->next;
        curx->next=tmp;

        head=head->next;
        return;
    }
}

template<typename T> string BaseBag<T> :: toString(){
    string typestring[5]={"Antidote","PhoenixI","PhoenixII","PhoenixIII","PhoenixIV"};
    string s="";
    if (size()==0)
        return "Bag[count=0;]";
    T* tmp= head;
    //debug(size());
    //debug(head->item->item_type);
    int id=tmp->item->item_type;
    //debug(id);
    s=s + "Bag[count=" 
        + to_string(size())
        + ";"
        + typestring[id];
    tmp=tmp->next;
    while (tmp != NULL)
    {
        int id=tmp->item->item_type;
        s=s +","
            +typestring[id];
        tmp=tmp->next;
    }
    s+="]";
    //debug(s);
    return s;
}

template<typename T> BaseBag<T> :: BaseBag(int anti, int phoenixI){
    for (int i=0;i<phoenixI;i++)
    {
        _BaseItem* tmp=new _BaseItem(phoenixdownI);
        T* n = new T(tmp);
        n->next=head;
        head=n;
    }

    for (int i=0;i<anti;i++)
    {
        _BaseItem* tmp= new _BaseItem(antidote);
        T* n = new T(tmp);
        n->next=head;
        head=n;
    }

}

template<typename T> void BaseBag<T> :: lose_bag(T*& head){
    if (size()< 3)
        head=NULL;
    else 
        head=head->next->next->next;
    return;
}
/* * * END implementation of class BaseBag * * */

/* * * BEGIN implementation of class BaseKnight * * */

 string BaseKnight::toString() {
    string typeString[4] = {"PALADIN", "LANCELOT", "DRAGON", "NORMAL"};
    // inefficient version, students can change these code
    //      but the format output must be the same
    int num=knight_Type();
    string s("");
    s += "[Knight:id:" + to_string(id) 
        + ",hp:" + to_string(hp) 
        + ",maxhp:" + to_string(maxhp)
        + ",level:" + to_string(level)
        + ",gil:" + to_string(gil)
        + "," + bag->toString()
        + ",knight_type:" + typeString[num]
        + "]";

/*     s+="[Knight:id:" + to_string(id) 
        + ",hp:" + to_string(hp) 
        + ",maxhp:" + to_string(maxhp)
        + ",level:" + to_string(level)
        + ",gil:" + to_string(gil)
        + ",knight_type:" + typeString[num]
        +"]"; */
    return s;
}

int BaseKnight:: bag_limit(){
        int a[4]={100000,16,14,19};
        return a[knight_Type()];
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
    delete [] ev;
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
    //freopen("t.out","w",stdout);
    ifstream ifa(file_armyknights);
    ifa>>n;
    //debug(n);
    cur=n-1;
    this->knight= new BaseKnight *[n];
    for (int i=0;i<n;i++)
    {
        int id,maxhp,level,gil,antidote,phoenixdownI;
        ifa>>maxhp>>level>>phoenixdownI>>gil>>antidote; 
        //debug(id);  debug(maxhp);   debug(level);   debug(gil); debug(antidote);    debug(phoenixdownI);
        this->knight[i]=this->knight[i]->create(i+1,maxhp,level,phoenixdownI,gil,antidote);
        if (knight[i]->knight_Type()==DRAGON){
            knight[i]->bag=new BaseBag<node>(0,phoenixdownI);
        }
        else{
            knight[i]->bag=new BaseBag<node>(antidote,phoenixdownI);
            //debug(knight[i]->bag->size());
            //printInfo();
        }
    }
    met_omega=0;
    met_hades=0;
    hasPaladin=0;
    hasLancelot=0;
    hasGuinevere=0;
    hasExcalibur=0;
    win_Ultimecia=0;
}

bool ArmyKnights :: can_revive(BaseKnight * lknight)
{
    /// BEGIN IMPLEMENTATION FIND PHOENIXDOWN
    if (lknight->hp<=0){
        //debug(lknight->bag->size());
        node *tmp=lknight->bag->head;
        while (tmp!=NULL)
        {
            if (tmp->item->item_type==phoenixdownI)
            {
                //cout<<"find phoenixI"<<endl;
                lknight->bag->get(phoenixdownI,lknight->bag->head);
                //free(vp);
                lknight->hp=lknight->maxhp;
                return 1;
            }                
            if (tmp->item->item_type==phoenixdownII && lknight->hp < lknight->maxhp/4)
            {
                lknight->bag->get(phoenixdownII,lknight->bag->head);
                lknight->hp=lknight->maxhp;
                //free(vp);
                return 1;
            }
            if (tmp->item->item_type==phoenixdownIII && lknight->hp < lknight->maxhp/3)
            {
                lknight->bag->get(phoenixdownIII,lknight->bag->head);
                //free(vp);
                lknight->hp=lknight->maxhp/3;
                return 1;
            }
            if (tmp->item->item_type==phoenixdownIV && lknight->hp < lknight ->maxhp/2)
            {
                lknight->bag->get(phoenixdownIV,lknight->bag->head);
                //free(vp);
                lknight->hp=lknight->maxhp/2;
                return 1;
            }
            tmp=tmp->next;
        }
    }
    else
    {
        node *tmp= lknight->bag->head;
        while (tmp != NULL)
        {
            if (tmp->item->item_type>=2 && tmp->item->item_type<=4)
            {
                ItemType t=tmp->item->item_type;
                if (t==phoenixdownII && lknight->hp<lknight->maxhp/4)
                {
                    //cout<<"find phoenixII"<<endl;
                    lknight->bag->get(phoenixdownII,lknight->bag->head);
                    lknight->hp=lknight->maxhp;
                    return 1;
                }
                if (t==phoenixdownIII && lknight->hp<lknight->maxhp/3)
                {
                    //cout<<"find phoenixIII"<<endl;
                    lknight->bag->get(phoenixdownIII,lknight->bag->head);
                    lknight->hp+=lknight->maxhp/4;
                    return 1;
                }
                if (t==phoenixdownIV && lknight->hp<lknight->maxhp/2)
                {
                    lknight->bag->get(phoenixdownIV,lknight->bag->head);
                    lknight->hp+=lknight->maxhp/5;
                    return 1;
                }
            }
            tmp=tmp->next;
        }
        return 1;
    }

    /// END IMPLEMENTATION FIND PHOENIXDOWN

    /// USING GIL
    if (lknight->hp<=0)
    {
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
    }
    return 1;
}

void ArmyKnights::collect_gil(BaseKnight * lknight, int op_gil)
{
    if (lknight->gil + op_gil > 999)
    {    
        int gil=op_gil;
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
        lknight->gil += op_gil;
}

bool ArmyKnights::fight(BaseOpponent * target){
    BaseKnight * lknight = lastKnight();
    if (target->id >=1 && target->id <=5)
    {
        normalType * opponent=new normalType (target->i, target->id);
        if (lknight->knight_Type()==1 || lknight->knight_Type()==0) //is PALADIN OR LANCELOT
        {
            //Start collecting gil
            collect_gil(lknight,opponent->gil());
            delete opponent;
            return 1;
        }
        if (lknight->level < opponent -> levelO())
        {
            int bd=opponent->base_damage();
            int levelo=opponent->levelO();
            int lv=lknight->level; 
            lknight->hp=lknight->hp - bd * (levelo-lv);
            // When HP<=0 
            if (lknight->hp <=0 ){
                delete opponent;    return 0;
            }
        }
        else
        {
            //Start collecting gil
            collect_gil(lknight,opponent->gil());
            //debug(lknight->gil);
            delete opponent;
            return 1;
        }
        delete opponent;
        return 1;        
    }
    if (target->id == 6)
    {
        Tornbery* opponent = new Tornbery (target->i, target -> id);
        if (lknight->level >= opponent -> levelO()){
            lknight -> level = min (lknight -> level +1, 10);
        }
        else
        {
            if (lknight-> knight_Type()==2) {
                delete opponent;    return 1;       //is DRAGON}
            }       
            if (lknight -> antidote >0)
            {
                lknight -> antidote--;
                lknight->bag->get(antidote,lknight->bag->head);
                //free(tm);
            }
            else
            {
                lknight->bag->lose_bag(lknight->bag->head);  ///LAST KNIGHT WILL DROP 3 BAGS
                lknight->hp-=10;
                /// IF lKNIGHT dies
                if (lknight->hp <= 0)
                    {delete opponent;   return 0;  }
            }
        }
        delete opponent;
        return 1;
    }
    if (target->id == 7)
    {
        Queen* opponent = new Queen (target -> i, target -> id);
        {
            if (lknight->level >= opponent -> levelO()){
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
            else if (lknight->knight_Type()!=0) lknight->gil/=2;
        }
        delete opponent;
        return 1;
    } 
    if (target->id == 8)
    {
        if (lknight->gil >= 50)
        {
            if (lknight->hp < lknight -> maxhp /3)
            {
                if (lknight->knight_Type()!=0)
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
        if ((lknight->level == 10 && lknight -> hp == lknight -> maxhp) || (lknight->knight_Type()==2)) // DRAGON TYPE
        {
            met_omega=1;
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
        if (lknight->level==10 || (lknight->knight_Type()==0 && lknight -> level >=8))
        {
            met_hades=1;
            hasPaladin=1;
            return 1;
        }
        lknight-> hp=0;
        return 0;
    }
    if (target->id == 99)
    {
        if (hasExcaliburSword())
        {
            win_Ultimecia=1;    return 1;
        }
        else if (hasPaladinShield() && hasLancelotSpear() && hasGuinevereHair())  //accept fight
        {
            int Ultimecia_hp=5000,tmp=-1;
            for (cur;cur>=0;cur--)
            {
                if (knight[cur]->knight_Type()==3){
                     if (tmp==-1)   tmp=cur;
                     continue;   //NORMAL
                }   
                int damage= (double)knight[cur]->hp * (double)knight[cur]->level * knight[cur]->knightBaseDamage[knight[cur]->knight_Type()];
                Ultimecia_hp-=damage;
                if (Ultimecia_hp<=0)    
                    {win_Ultimecia=1;   cur=tmp;  return 1;}
                n--;
                knight[cur]->hp=0;
            }
            if (Ultimecia_hp>0)
            {
                n=0;
                cur=-1;
                return 0;
            }
        }
        else 
        {
            n=0;
            cur=-1;
            return 0;
        }
    }
    if (target->id == 95)
        hasPaladin=1;
    if (target->id == 96)
        hasLancelot=1;
    if (target->id == 97)
        hasGuinevere=1;
    if (target->id ==98)
        hasExcalibur=(hasGuinevere+hasLancelot+hasPaladin)/3;
    if (target->id >=112 && target->id <=114)
    {
        ItemType name;
        if (target->id==112)    name=phoenixdownII;
        if (target->id==113)    name=phoenixdownIII;
        if (target->id==114)    name=phoenixdownIV;
        int i=cur;
        _BaseItem *vp = new _BaseItem(name);
        bool f=knight[i]->bag->insertFirst(vp,knight[i]->bag_limit(),knight[i]->bag->head);
        //debug(f);
        while (f==0 && i>0){
            i--;
            f=knight[i]->bag->insertFirst(vp,knight[i]->bag_limit(),knight[i]->bag->head);
        }
        //debug(i);
        //debug(knight[i]->bag->head->item->item_type);
        return 1;
    }
    return 1;
}

bool ArmyKnights::adventure(Events * events){
    BaseKnight * lknight = lastKnight();
    for (int i=0;i<events->count();i++)
    {
        lknight=lastKnight();
        BaseOpponent *target= new BaseOpponent(i,events->get(i));
        int prevhp=lknight->hp;
        bool flag=fight(target);
        //debug(flag);
        //debug(lknight->hp);
        if (events->get(i)==99 && win_Ultimecia==0){
            
            printInfo();
            delete target;
            return 0;
        }    
        else if (events->get(i)==99 && win_Ultimecia==1){
            printInfo();
            delete target;
            return 1;
        }
        //debug(prevhp);
        if (flag==0 || prevhp > lknight->hp)
        {
            //cout<<lknight->toString()<<endl;
            if (can_revive(lknight))
                flag=1;    
            if (cur<0){
                printInfo();
                delete target;
                return 0;
            }
        }
        printInfo();
        delete target;
    }
    return 1;
}

void ArmyKnights::printInfo() const {
    cout << "No. knights: " << this->count();
    if (this->count() > 0) {
/*         for (int i=0;i<n;i++){
            cout << knight[i]->toString()<<endl;
        } */
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
    bool res=armyKnights->adventure(events);
    armyKnights->printResult(res);
    //armyKnights->printInfo();
} 

/* * * END implementation of class KnightAdventure * * */