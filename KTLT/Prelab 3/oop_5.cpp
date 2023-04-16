class ClockType
{
public:
    ClockType();
      
    void setTime(int, int, int);
    void printTime() const;

private:
    int hr;
    int min;
    int sec;
};

void ClockType::printTime() const
{
   if (hr < 10)
      cout << "0";
   cout << hr << ":";
   if (min < 10)
      cout << "0";
   cout << min << ":";
   if (sec < 10)
      cout << "0";
   cout << sec;
}

void ClockType::setTime(int x,int y,int z){
    ClockType::hr=(x>=0 && x<24) ? x :0;
    ClockType::min=(y>=0 && y<60) ? y :0;
    ClockType::sec=(z>=0 && z<60) ? z :0;
}
