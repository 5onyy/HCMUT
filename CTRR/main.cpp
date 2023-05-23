#include "main.h"

int main()
{
    string infix_arimethic,infix_logic;
    ifstream fin("t.inp");
    freopen("t.out","w",stdout);
    getline(fin,infix_arimethic);
    getline(fin,infix_logic);
    //getline(fin,logic_value);
    string logic_value="a b c d e f g h i j k l m n o p q r s t u v w x y z 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1";
    string postfix_arimethic="",prefix_arimethic="",postfix_logic="",prefix_logic="";
    postfix_arimethic=Infix2Postfix(infix_arimethic);
    prefix_arimethic=Infix2Prefix(infix_arimethic);
    postfix_logic=LogicInfix2Postfix(infix_logic);
    prefix_logic=LogicInfix2Prefix(infix_logic);
    cout<<"Infix arimethic to postfix expression: " <<postfix_arimethic<<endl;
    cout<<"Infix armiethic to postfix expression: " <<prefix_arimethic<<endl;
    cout<<"Postfix arimethic evaluation: "<<PostfixPrefixCalculator(postfix_arimethic)<<endl;
    cout<<"Prefix arimethic evaluation: "<<PostfixPrefixCalculator(prefix_arimethic)<<endl;
    
    
    cout<<"Postfix logic expression: "<<postfix_logic<<endl;
    cout<<"Prefix logic expression: "<<prefix_logic<<endl;
    cout<<"Value: "<<logic_value<<endl;
    cout<<"Postfix Logic evaluation: "<<LogicPostfixPrefixCalculator(postfix_logic,logic_value)<<endl;
    cout<<"Prefix Logic evaluation: "<<LogicPostfixPrefixCalculator(prefix_logic,logic_value);
}