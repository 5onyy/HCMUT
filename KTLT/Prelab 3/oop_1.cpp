class ClockType
{
   public:
      ClockType(int h, int m, int s); //constructor with parameters
      ClockType(); //default constructor
      
      void printTime() const;

   private:
      int hr;
      int min;
      int sec;
};

void ClockType::printTime() const { 
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

ClockType :: ClockType(int h,int m, int s)
{
    hr=(h>=0 && h<24) ? h : 0 ;
    min=(m>=0 && m<60) ? m : 0;
    sec=(s>=0 && s<60) ? s :0;
}

ClockType:: ClockType()
{
    hr=0;
    min=0;
    sec=0;
}

