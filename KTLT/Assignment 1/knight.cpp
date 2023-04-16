#include "knight.h"

#define debug(x) { cout << #x << " = "; cout << (x) << endl; }
#define success  { display(HP,level,remedy,maidenkiss,phoenixdown,1);   exit(0);}
#define die {display(HP,level,remedy,maidenkiss,phoenixdown,-1);   exit(0);}
#define fail {display(HP,level,remedy,maidenkiss,phoenixdown,0);   exit(0);}
#define to_lower(x) {x|=32;}
#define _debug {for (int i=0;i<n2;i++)  cout<<"mush["<<i<<"]="<<mush[i]<<" ";      cout<<endl;}

void display(int HP, int level, int remedy, int maidenkiss, int phoenixdown, int rescue) {
    cout << "HP=" << HP
        << ", level=" << level
        << ", remedy=" << remedy
        << ", maidenkiss=" << maidenkiss
        << ", phoenixdown=" << phoenixdown
        << ", rescue=" << rescue << endl;
}

void use_remedy(int &HP,int max_HP,int &remedy,int &turn_left,bool &small)
{
    HP=min(HP*5,max_HP);
    remedy--;
    turn_left=0;
    small=0;
}

void use_maidenkiss(int &level,int prev_level,int &maidenkiss, int &turn_left2,bool &frog)
{
    level=prev_level;
    maidenkiss--;
    turn_left2=0;
    frog=0;
}

void use_phoenixdown(int &HP,int max_HP, int &phoenixdown, bool &frog, bool &small, int &round_left,int &round_left2,int &level, int&prev_level)
{
    if (phoenixdown>0)
    {
        if (frog==1)    level=prev_level;
        phoenixdown--;  
        frog=0;
        small=0;
        HP=max_HP;  
        round_left2=0;      
        round_left=0;

    }
}

void combat(int index,int ev_i, int &HP, int &level, int &phoenixdown,int max_HP)
{
    int b=index%10;
    int levelO= index > 6?(b>5?b:5) : b;
    //debug(levelO);
    if (level> levelO)
        level=min(10,level+1);
    if (level < levelO)
    {
        double base_damage[6]={0,1,1.5,4.5,7.5,9.5};
        double damage = base_damage[ev_i] * levelO * 10.0;
        double hp1=HP;
        hp1 -= damage;
        //debug(damage);
        HP=(int)hp1;
        //debug(HP); 
    }
 
}

void shaman(int index, int ev_i,int &HP,int &level,int &remedy, int &max_HP,int &round_left, bool &small,bool frog)
{
    if (frog==1 || small==1)   return;
    int b=index%10;
    int levelO= index > 6?(b>5?b:5) : b;
    //debug(levelO);
    if (level> levelO)
        level=min(10,level+2);
    if (level < levelO)
    {
        small=1;
        if (round_left==0 && small==1)
        {
            if (remedy>0)
            {   remedy--;
                round_left=0;
                small=0;
                return;
            }
            round_left=4;         HP/=5;
            if (HP==0)  HP=1;   
        }
    }    
}

void siren(int index,int ev_i,int &HP, int &level,int &maidenkiss,int &prev_level, int &round_left2, bool &frog,bool small)
{
    if (small==1 || frog==1)   return;
    int b=index%10;
    int levelO= index > 6?(b>5?b:5) : b;
    //debug(levelO);
    if (!frog)
        {prev_level=level;}
    if (level> levelO)
        level=min(10,level+2);
    if (level < levelO)
    {
        frog=1;
        if (round_left2==0 && frog==1)
        {
            if (maidenkiss>0)
            {use_maidenkiss(level,prev_level,maidenkiss,round_left2,frog);   return;}
            round_left2=4;         level=1;   
        }
    }
    //debug(remedy);    
}

void mush_fibo(int &HP)
{
    if (HP==1)
        return;
    int fib[10001];
    fib[1]=fib[2]=1;
    if (HP==1)  return;
    for (int i=2;i<=20;i++)
    {
        fib[i]=fib[i-1]+fib[i-2];
        //debug(fib[i]);
        if (fib[i]>=HP)   { HP=fib[i-1];     return;}
    }
}

void mush_ghost_1(int n2,int *mush,int &HP,int max_HP)
{
    int maxx=-1e9,minn=1e9,maxi,mini;
    for (int i=0;i<n2;i++)
        if (maxx<=mush[i])
            {maxx=mush[i];   maxi=i;}
    for (int i=0;i<n2;i++)
        if (minn>=mush[i])
           {minn=mush[i];  mini=i;}
/*     debug(HP);
    debug(maxi);    debug(mini);   */
    HP-=(maxi+mini);
    HP=min(HP,max_HP);
}

void mush_ghost_2(int n2,int *mush,int &HP,int max_HP)
{
    auto find_pos_max=[](int n2,int *mush){
        int maxx=-1e9,maxi;
        for (int i=0;i<n2;i++)
            if (maxx<mush[i])
                {maxx=mush[i];   maxi=i;}
        return maxi;
    }; 
    int peak=find_pos_max(n2,mush);
    auto check_peak=[](int n2,int *mush,int peak){
        for (int i=peak;i>0;i--)
            if (mush[i-1]>=mush[i])
                return 0;
        for (int i=peak;i<n2-1;i++)
            if (mush[i]<=mush[i+1])
                return 0;
        return 1;
    };
    int flag=check_peak(n2,mush,peak),mtx,mti;
    if (flag==0)
        mtx=-2,mti=-3;
    else mtx=peak,mti=mush[peak];
/*     debug(mtx);
    debug(mti);  */
    HP-=(mtx+mti);
    HP=min(HP,max_HP);
}

void mush_ghost_3(int n2,int *mush,int &HP,int max_HP)
{
    for (int i=0;i<n2;i++)
    {
        mush[i]= mush[i]<0? -mush[i] : mush[i];
        mush[i]= (17*mush[i]+9)%257;
    }
/*     cout<<"mush_ghost_3"<<endl;
    _debug;      */   
    int maxx=-1e9,minn=1e9,maxi2,mini2;
    for (int i=0;i<n2;i++)
        if  (maxx<mush[i])
            {maxx=mush[i];  maxi2=i;}
    for (int i=0;i<n2;i++)
        if  (minn>mush[i])
            {minn=mush[i];  mini2=i;}
    HP-=(maxi2+mini2);
    HP=min(HP,max_HP);
    
/*     for (int i=0;i<n2;i++)
        cout<<"mush["<<i<<"]="<<mush[i]<<" ";   
    cout<<endl;  
    debug(HP);  */
}

void mush_ghost_4(int n2,int *mush, int &HP,int max_HP)
{
    for (int i=0;i<n2;i++)
    {
        mush[i]= mush[i]<0? -mush[i] : mush[i];
        mush[i]= (17*mush[i]+9)%257;
    }
/*     cout<<"mush_ghost_4: "<<endl;
    _debug;  
    
    debug(HP); */
    auto check=[](int n2,int *mush){
        if (n2==1)
            return -1;
        else if (n2==2 && mush[0]==mush[1])
            return -1;
        else if (n2==2)
        {
            if (mush[0]>mush[1])    return 1;
            return 0;
        }
        else if (n2>=3 &&  (mush[1]==mush[2] && mush[0]==mush[1]))
            return -1;
        int first=-1e9,second=-1e9,second_i,first_i;
        for (int i=0;i<=2;i++)
        {
            if (mush[i]>first)
            {
                second=first;
                second_i=first_i;
                first=mush[i];
                first_i=i;
            }
            else if (mush[i]>second && mush[i]!=first)
                {second=mush[i]; second_i=i;}
        }
        return second_i;
    };

    int max2_3i=check(n2,mush), max2_3x=mush[max2_3i];
//    debug(max2_3i); debug(max2_3x);
    if (max2_3i==-1)
        HP=min(HP+12,max_HP);
    else
        {  
         HP-=(max2_3x+max2_3i);}
    HP=min(HP,max_HP);
//    debug(HP); 
}

void mush_ghost(int number_of_event,string evi, int &HP,int max_HP,int &phoenixdown, string file_name,bool &frog, bool &small,int &round_left,int &round_left2,int &level,int &prev_level)
{
    /*  READ FILE */
    ifstream fin_ghost(file_name);
    int n2;
    string s;
    getline(fin_ghost,s);
    n2=stoi(s);
    getline(fin_ghost,s);
    stringstream _sghost(s);
    int i=0,mush[101],processing_mush[101];
    while (_sghost.good())
    {
        string sub;
        getline(_sghost,sub,',');
        mush[i++]=stoi(sub); 
    }
    /* -------------------------------- */

    /* -----------SOLVE---------------- */
    for (int i=2;i<evi.size();i++)
    {
        if (evi[i]=='1')
            mush_ghost_1(n2,mush,HP,max_HP);
        if (evi[i]=='2')
            mush_ghost_2(n2,mush,HP,max_HP);
        if (evi[i]=='3')
        {
            for (int i=0;i<n2;i++)
                processing_mush[i]=mush[i];
            mush_ghost_3(n2,processing_mush,HP,max_HP);
        }
        if (evi[i]=='4'){
            for (int i=0;i<n2;i++)
                processing_mush[i]=mush[i];
            mush_ghost_4(n2,processing_mush,HP,max_HP);
        } 
        if (HP<=0 && phoenixdown>0)      // can use
            {HP= max_HP;   use_phoenixdown(HP,max_HP,phoenixdown,frog,small,round_left,round_left2,level,prev_level);}
        else if (HP<=0 && phoenixdown==0)
            return;
/*         cout<<"finish event:"<<evi[i]<<" "<<endl;
        _debug;
        debug(HP);  */          
    }
}

void loot_asclepius(int &remedy, int &maidenkiss, int &phoenixdown, string file_name,bool &frog,bool &small)
{
    ///READ FILE
    ifstream  fin_as(file_name);
    int r1,c1;
    string _r1,_r2;
    getline(fin_as,_r1);
    getline(fin_as,_r2);
    /* ---------------------------------- */
    r1=stoi(_r1);
    c1=stoi(_r2);
    for (int i=0;i<r1;i++)
    {
        string _line;
        getline (fin_as,_line);
        stringstream as(_line);
        string item;
        int c=0;
        for (int j=0;j<c1;j++)
        {
            as>>item;
            if (c==3)   break;
            if (item=="16")
                {remedy=min(remedy+1,99);    c++;  }
            if (item=="17")
                {maidenkiss=min(maidenkiss+1,99);   c++;            }
            if (item=="18")
                {phoenixdown=min(phoenixdown+1,99);  c++;           }
        }
    }
}

void meet_merlin(int &HP, int &max_HP,string file_name)
{
    ifstream fin_merlin(file_name);
    int n9;
    fin_merlin>>n9;

    auto check= [](string name){
        if (name.find("Merlin") != string::npos || name.find("merlin")!=string::npos)
            return 3;
        for (int i=0;i<name.size();i++)
            to_lower(name[i]);             // LOWERCASE
        for (int i=0;i<name.size();i++)
        if (name.find('m')!=string::npos && name.find('e')!=string::npos && name.find('r')!=string::npos && name.find('l')!=string::npos && name.find('i')!=string::npos && name.find('n')!=string::npos)    
            return 2;    
        return 0;
    };

    while (n9--)
    {
        string name;
        fin_merlin >> name;
        int magic=check(name);
        //debug(magic);
        HP=min(HP+magic,max_HP);
        //debug(HP);
    }
}

/* string find_file(string t,string *_file )
{
    for (int i=0;i<5;i++)
        if (_file[i].find(t) != string::npos)
            return _file[i];
} */

void adventureToKoopa(string file_input, int & HP, int & level, int & remedy, int & maidenkiss, int & phoenixdown, int & rescue) 
{
    //freopen("test.ans","w",stdout);
    ifstream fin(file_input);
    rescue=1;
    string _file[5];

    // READ DATA
    string data;
    getline (fin,data);
    stringstream ss(data);
    string hp, levell,reme,maiden,phoenix;
    ss>>hp>>levell>>reme>>maiden>>phoenix;
    HP=stoi(hp);        level=stoi(levell);       remedy=stoi(reme);        maidenkiss=stoi(maiden);     phoenixdown=stoi(phoenix);   
    int max_HP=HP;
 
    //READ EVENT
    int count=0,round_left=0,round_left2=0,prev_level=level,mark=0;
    bool small=0,frog=0,has_met_asclepius=0,arthur=0,lancelot=0,has_met_merlin=0,finish=0,save=0;
    string ev,file;
    getline (fin,ev);
    getline (fin,file);
    
    // READ FILE 
    stringstream ss3(file);
    int i=0;
    while (ss3.good())
    {
        string sub;
        getline(ss3,sub,',');
        _file[i++]=sub;   
    }

    // Check if knight is Arthur or Lancelot
    auto prime = [](int n){
        if (n<2)    return 0;
        for (int i=2;i*i<=n;i++)
            if (n%i==0)
                return 0;
        return 1;
    };
    if (HP==999)    arthur=1;
    if (prime(HP))  lancelot=1;

    ///Solve
    string ev_tmp=ev;
    for (int i=0;i<ev_tmp.size()-1;i++)
        if (ev_tmp[i]==' '&& ev_tmp[i+1]!=' ')
            mark++;
    mark++;
    stringstream ss2(ev);
    string evi;
    int num;
    while (ss2>>evi)
    { 
        count++;
        //debug(count);
        if (evi.size()<3)
            num=stoi(evi);
/*         if (num==7)
            debug(small);
            debug(round_left); */
        if (evi=="0")
            success;
        if (round_left==0 && small==1)
            {HP=min(HP*5,max_HP);   small=0;}
        if (round_left2==0 && frog==1)
            {level=prev_level;   frog=0;} 
        if (evi=="1" || evi=="2" || evi=="3" || evi=="4" || evi=="5")
        {
            if (arthur || lancelot) level=min(level+1,10);
            else 
                combat(count,num,HP,level,phoenixdown,max_HP);
        }          
        if (evi=="6")
        {
            if (arthur || lancelot) level=min(level+2,10);
            else 
                shaman(count,num,HP,level,remedy,max_HP,round_left,small,frog);
        }
        if (evi=="7")
        {
            if (arthur || lancelot) level=min(10,level+2);
            else
                siren(count,num,HP,level,maidenkiss,prev_level,round_left2,frog,small);        
        }
        if (evi=="11")
        {
            int s1;
            auto calculate_s1=[](int level, int phoenixdown)
            {
                int n1=((level+phoenixdown)%5+1)*3;
                int c=0,s=0;
                for (int i=99;i>=1;i-=2)
                {
                    s+=i;   c++;
                    if (c==n1)  return s;
                }
            };
            s1=calculate_s1(level,phoenixdown);
            //debug(s1);
            auto prime = [](int n)
            {
                if (n<2)    return 0;
                for (int i=2;i*i<=n;i++)
                    if (n%i==0)
                        return 0;
                return 1;
            };
            HP=HP+(s1%100);
            //debug(HP);
            while (prime(HP+1)==0)
                HP++;
            HP++;
            //debug(HP);
            HP=min(HP,max_HP);
        }
        if (evi=="12")
        {
            mush_fibo(HP);       
        }    
        if (evi.size()>=3)
        {
            string file_name=_file[0];
            //debug(file_name);
            int number_of_event=evi.size()-2;
            //debug(number_of_event);
            
            mush_ghost(number_of_event,evi,HP,max_HP,phoenixdown,file_name,frog,small,round_left, round_left2,level,prev_level);
            
        }
        if (evi=="15")
            remedy=min(remedy+1,99);
        if (evi=="16")
            maidenkiss=min(maidenkiss+1,99);
        if (evi=="17")
            phoenixdown=min(phoenixdown+1,99);
        if (evi=="19")    //aphelious
        {
            if (!has_met_asclepius)
            {
                loot_asclepius(remedy,maidenkiss,phoenixdown,_file[1],frog,small);            
                has_met_asclepius=1;
            }     
        }
        if (evi=="18")
        {
            if (!has_met_merlin)
            {
                meet_merlin(HP,max_HP,_file[2]);
                has_met_merlin=1;
            }
        }
        if (evi=="99")
        {
            if (lancelot)
            {
                if (level < 8)
                    fail;
            }             
            else if (!arthur && level < 10)
                    fail;
            level=10;
        }

        /*update*/
        if (HP<=0 && phoenixdown==0) fail;
        if (HP<=0 && phoenixdown>0)  {
            use_phoenixdown(HP,max_HP,phoenixdown,frog,small,round_left,round_left2,level,prev_level);
        }

        /*update shaman*/

        if (small && round_left >0 && remedy>0)        // USE ITEM
            use_remedy(HP,max_HP,remedy,round_left,small);
        if (small)  round_left=max(round_left-1,0); 
        if (round_left==0 && small==1)
        {HP=min(HP*5,max_HP);   small=0;} 
        //debug(round_left);
        //debug(small);
        /*update siren*/

        if (frog && round_left2>0 && maidenkiss>0)    // USE ITEM
            use_maidenkiss(level,prev_level,maidenkiss,round_left2,frog);
        if (frog)   round_left2=max(round_left2-1,0);
        if (round_left2==0 && frog==1)
            {level=prev_level;   frog=0;}
        if (count==mark)    break;   
        display(HP,level,remedy,maidenkiss,phoenixdown,-1);
    }
    if (round_left==0 && small==1)
        {HP=min(HP*5,max_HP);   small=0;}
    if (round_left2==0 && frog==1)
            {level=prev_level;   frog=0;} 
    if (HP>0)  success;
    if (HP<=0)   fail;       
}
