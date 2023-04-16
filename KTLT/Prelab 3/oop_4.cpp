class Integer{
    private:
        int val;
    public:
        Integer(int val){
            Integer::val=val;
        }
        void setValue (int x){
            val=x;
        }
        int getValue(){
            return val;
        }  
};