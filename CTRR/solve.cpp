#include "main.h"

#define debug(x) { cout << #x << " = "; cout << (x) << endl; }
#define sz(s) (int)s.size()


int priority(char op)
{
    if (op == '-' || op == '+')
        return 1;
    if (op == '*' || op =='/')
        return 2;
    if (op == '^')
        return 3;
    return -1;
}

int inverse_logic_priority(string lg)
{
    if (lg == "~")   return 4;
    if (lg == "&" || lg =="|")  return 3;
    if (lg == ">-<")    return 2;
    if (lg == ">-") return 1;
    return -1;
}

int logic_priority(string lg)
{
    if (lg == "~")   return 4;
    if (lg == "&" || lg =="|")  return 3;
    if (lg == "->")    return 2;
    if (lg == "<->") return 1;
    return -1;
}
bool isLogicOperator(char ch)
{
    return (ch=='>' || ch=='<' || ch=='-' || ch=='&' || ch=='~' || ch=='|'); 
}

bool isOperator(char op)
{
    return (op == '+' || op == '-' || op == '*' || op == '/' || op == '^');
}

string Infix2Postfix(string infix)
{
    string postfix="";
    stack<char> st;
    for (int i=0;i<sz(infix);i++)
    {
        char ch=infix[i];
        if (infix[i] >= '0' && infix[i]<='9')
        {
            if (infix[i-1]>='0' && infix[i-1]<='9')
                postfix=postfix+ infix[i];
            else postfix=postfix+' '+ infix[i];
        }   
        else if (ch == '(')
            st.push(ch);
        else if (ch == ')')
        {
            while (st.top() != '('){
                postfix=postfix + ' '+ st.top();
                st.pop();
            }
            st.pop();
        }
        else if (isOperator(ch))
        {
            while (!st.empty() && st.top()!='(' && priority(ch) <= priority(st.top()))
            {
                postfix=postfix+ ' ' +st.top();
                st.pop();
            }
            st.push(ch);
        }
    }
    while (!st.empty())
    {
        postfix=postfix+ ' '+ st.top();
        st.pop();
    }
    postfix.erase(0,1);
    return postfix;
}

string reverse_string(string s){
    string ans=s;
    for (int i=0;i<sz(s);i++)
        ans[i]=s[sz(s)-i-1];
    return ans;
}

string Infix2Prefix(string infix)
{
    infix=reverse_string(infix);
    for (int i=0;i<sz(infix);i++)
    {
        if (infix[i]=='(')
            infix[i]=')';
        else if (infix[i]==')')
            infix[i]='(';
    }

    infix='(' + infix + ')';
    stack<char> st;
    string prefix="";
    for (int i=0;i<sz(infix);i++)
    {
        char ch=infix[i];
        if (ch >='0' && ch <='9')
        {
            if (infix[i-1] >= '0' && infix[i-1]<='9')
                prefix += ch;
            else prefix=prefix +' '+ ch;
        }
        else if (ch=='(')
            st.push('(');
        else if (ch==')')
        {
            while (st.top() != '(')
            {
                prefix=prefix+' '+st.top();
                st.pop();
            }
            st.pop();
        }
        else if (isOperator(ch)){
            if (ch=='^')
            {
                while (priority(ch)<priority(st.top()))
                {
                    prefix=prefix +' '+st.top();
                    st.pop();
                }
            }
            else
            {
                while (priority(ch)<priority(st.top()))
                {
                    prefix=prefix +' '+st.top();
                    st.pop();
                }
            }
            st.push(ch);
        }
    }
    while (!st.empty())
    {
        prefix=prefix+' '+st.top();
        st.pop();
    }
    prefix=reverse_string(prefix);
    return prefix;
}

double pow(int a,int b){
    double t=1;
    for (int i=0;i<b;i++)
        t*=a;
    return t;
} 

double PostfixCalculator(string input)
{
    stack<double> st;
    for (int i=0;i<sz(input);i++)
    {
        double num=0;
        char ch=input[i];
        if (ch==' ')
            continue;
        else if (ch>='0' && ch<='9')
        {
            while (ch>='0' && ch<='9'){
                num=num*10 + (int)(ch-'0');
                i++;
                ch=input[i];
            }
            i--;
            st.push(num);
        }
        else if (isOperator(ch))
        {
            double num1=st.top();
            st.pop();
            double num2=st.top();
            st.pop();
            if (ch=='+')    st.push(num2+num1);
            if (ch=='-')    st.push(num2-num1);
            if (ch=='*')    st.push(num2*num1);
            if (ch=='/')    st.push(num2/num1);
            if (ch=='^')    st.push(pow(num2,num1));
        }
        //debug(st.top());
    }
    return st.top();
}

double PrefixCalculator(string input)
{
    stack<double> st;
    input=reverse_string(input);
    for (int i=0;i<sz(input);i++)
    {
        double num=0;
        char ch=input[i];
        if (ch==' ')
            continue;
        else if (ch>='0' && ch<='9')
        {
            string tmp="";
            while (ch>='0' && ch<='9'){
                tmp=ch+tmp;
                i++;
                ch=input[i];
            }
            i--;
            int x=stoi(tmp);
            st.push((double)x);
        }
        else if (isOperator(ch))
        {
            double num1=st.top();
            st.pop();
            double num2=st.top();
            st.pop();
            if (ch=='+')    st.push(num1+num2);
            if (ch=='-')    st.push(num1-num2);
            if (ch=='*')    st.push(num2*num1);
            if (ch=='/')    st.push(num1/num2);
            if (ch=='^')    st.push(pow(num1,num2));
        }
        //debug(st.top());
    }
    return st.top();
}

string PostfixPrefixCalculator(string input){
    char ch=input[0];
    double ans=0;
    if (ch>='0' && ch<='9')
        ans=PostfixCalculator(input); 
    else 
        ans=PrefixCalculator(input);
    stringstream tmp;
    tmp << fixed << setprecision(4) << ans;
    string res=tmp.str();
    int i;
    for (i=sz(res)-1;res[i]=='0';i--);

    if (res[i]=='.')
        res=res.substr(0,i);
    else 
        res=res.substr(0,i+1);
    return res;
}

string LogicInfix2Postfix(string infix){
    string ans="";
    stack<string> st;
    //debug(infix);

    infix='('+infix+')';
    for (int i=0;i<sz(infix);i++)
    {
        char ch=infix[i];
        string s{ch};
        if (ch==' ')    continue;
        else if ((ch>='a' && ch <='z') || (ch>='A' && ch<='Z'))
            ans=ans+ch;
        else if (ch=='(')
            st.push(s);
        else if (ch==')')
        {
            while (st.top()!="(")
            {
                ans=ans+st.top();
                st.pop();
            }
            st.pop();
        }
        else if (isLogicOperator(ch))
        {
            if (ch=='<' || ch == '-'|| ch == '>')
            {
                s="";
                while (ch=='<' || ch == '-'|| ch == '>')
                {
                    s=s+ch;
                    i++;
                    ch=infix[i];
                }
                i--;
            }
            while (!st.empty() && st.top()!="(" && logic_priority(s) <= logic_priority(st.top()))
            {
                ans=ans+st.top();
                st.pop();
            }
            st.push(s);
        }
    }
    while (!st.empty())
    {
        ans=ans+st.top();
        st.pop();
    }
    return ans;
}

string LogicInfix2Prefix(string infix)
{
    string ans="";
    stack<string> st;
    infix=reverse_string(infix);
    for (int i=0;i<sz(infix);i++)
    {
        if (infix[i]=='(')
            infix[i]=')';
        else if (infix[i]==')')
            infix[i]='(';
    }
    //debug(infix);

    infix='('+infix+')';
    for (int i=0;i<sz(infix);i++)
    {
        char ch=infix[i];
        string s{ch};
        if (ch==' ')    continue;
        else if ((ch>='a' && ch <='z') || (ch>='A' && ch<='Z'))
            ans=ans+ch;
        else if (ch=='(')
            st.push(s);
        else if (ch==')')
        {
            while (st.top()!="(")
            {
                ans=ans+st.top();
                st.pop();
            }
            st.pop();
        }
        else if (isLogicOperator(ch))
        {
            if (ch=='<' || ch == '-'|| ch == '>')
            {
                s="";
                while (ch=='<' || ch == '-'|| ch == '>')
                {
                    s=s+ch;
                    i++;
                    ch=infix[i];
                }
                i--;
            }
            while (!st.empty() && inverse_logic_priority(s) < inverse_logic_priority(st.top()))
            {
                ans=ans+st.top();
                st.pop();
            }
            st.push(s);
        }
    }
    while (!st.empty())
    {
        ans=ans+st.top();
        st.pop();
    }
    ans=reverse_string(ans);
    return ans;
}

string PostfixLogicCalculator(string input)
{
    string res="";
    stack<char> st;
    for (int i=0;i<sz(input);i++)
    {
        char ch=input[i];
        if (ch==' ')    continue;
        else if (ch=='0' || ch=='1')
            st.push(ch);
        else if (isLogicOperator(ch))
        {
                            cout<<"OPERATOR !!! "<<endl;
            if (ch=='~') 
                st.top()=(char) ('1'- st.top() +'0');
            else
            {
                int val1=st.top()-'0';
                st.pop();
                int val2=st.top()-'0';
                st.pop();
                debug(val2);
                debug(val1);
                if (ch=='&')
                    st.push((char) (val1*val2 + '0'));
                else if (ch=='|')
                {
                    if (val1 ==1 || val2==1)
                        st.push('1');
                    else st.push('0');
                }
                else if (ch=='-')
                {
                    i++;
                    if (val2==1 && val1==0)
                        st.push('0');
                    else st.push('1');
                }
                else if (ch=='<')
                {
                    i+=2;
                    if (val1==val2)
                        st.push('1');
                    else st.push('0');
                }
            }
        }
        debug(st.size());
        debug(st.top());
        debug(i);
    }
    res=res+st.top();
    debug(res);
    return res;
}

string PrefixLogicCalculator(string input)
{
    input=reverse_string(input);
    //debug(input);
    stack<char> st;
    string res="";
    for (int i=0;i<sz(input);i++)
    {
        char ch=input[i];
        string s{ch};
        if (ch==' ')    continue;
        else if (ch=='0' || ch=='1')
            st.push(ch);
        else if (isLogicOperator(ch))
        {
            if (ch=='~')
                st.top()= ((char) ('1' - st.top() +'0'));
            else 
            {
                int val1=st.top()-'0';
                st.pop();
                int val2=st.top()-'0';
                st.pop();
/*                 debug(val2);
                debug(val1); */
                if (ch=='|')
                {
                    if (val1 ==1 || val2==1)
                        st.push('1');
                    else st.push('0');
                }
                else if (ch=='&')
                    st.push((char) (val1*val2 + '0'));
                else if (ch=='>' || ch=='-' || ch=='<')
                {
                    s="";
                    while (ch=='<' || ch=='-' || ch=='>')
                    {
                        s=s+ch;
                        i++;
                        ch=input[i];
                    }
                    i--;
                    if (s==">-"){
                        if (val1==1 && val2==0)
                            st.push('0');
                        else st.push('1');
                    }
                    else if (s==">-<"){
                        if (val2 == val1)   
                            st.push('1');
                        else st.push('0');
                    }
                }
            }   
        } 
/*         debug(st.size());
        debug(st.top()); */
    }
    res=res+st.top();
    return res;
}

string LogicPostfixPrefixCalculator(string input,string value)
{
    stack<char> st;
    string result;
    size_t len = value.length() - 1;
    size_t temp = len / 2 + 1;
    size_t k = 0;
    for (char i : input){
        if (!(i >= 'a' && i <= 'z')) {
            result += i;
            continue;
        }
        while(k < temp){
            if (i == value[k]){
                result += value[temp + k];
                break;
            }
            k += 2;
        }
        k = 0;
    }
    //debug(result);
    if(isdigit(result[0])) {
        for (int i = 0; i < (int)result.length(); i++) {
            if (isdigit(result[i])) {
                st.push(result[i]);
            }
            else {
                if (result[i] == '~') {
                    char val = st.top();
                    st.pop();
                    if (val == '1') {
                        st.push('0');
                    } else
                        st.push('1');
                }
                if (result[i] == '|') {
                    char val1 = st.top();
                    st.pop();
                    char val2 = st.top();
                    st.pop();
                    if (val1 == '1' || val2 == '1') {
                        st.push('1');
                    } else
                        st.push('0');
                }
                if (result[i] == '&') {
                    char val1 = st.top();
                    st.pop();
                    char val2 = st.top();
                    st.pop();
                    if (val1 == '1' && val2 == '1') {
                        st.push('1');
                    } else
                        st.push('0');
                }
                if (result[i] == '-' && result[i + 1] == '>' && result[i - 1] != '<') {
                    i++;
                    char val1 = st.top();
                    st.pop();
                    char val2 = st.top();
                    st.pop();
                    if (val2 == '0') {
                        st.push('1');
                    } else {
                        if (val1 == '1')
                            st.push('1');
                        else
                            st.push('0');
                    }
                }
                if (result[i] == '<' && result[i + 1] == '-' && result[i + 2] == '>') {
                    i += 2;
                    char val1 = st.top();
                    st.pop();
                    char val2 = st.top();
                    st.pop();
                    if (val1 == val2)
                        st.push('1');
                    else
                        st.push('0');
                }
            }
        }
    }
    else{
        for (int i = (int)result.length() - 1; i >= 0; i--) {
            if (isdigit(result[i])) {
                st.push(result[i]);
            }
            else {
                if (result[i] == '~') {
                    char val = st.top();
                    st.pop();
                    if (val == '1') {
                        st.push('0');
                    } else
                        st.push('1');
                }
                if (result[i] == '|') {
                    char val1 = st.top();
                    st.pop();
                    char val2 = st.top();
                    st.pop();
                    if (val1 == '1' || val2 == '1') {
                        st.push('1');
                    } else
                        st.push('0');
                }
                if (result[i] == '&') {
                    char val1 = st.top();
                    st.pop();
                    char val2 = st.top();
                    st.pop();
                    if (val1 == '1' && val2 == '1') {
                        st.push('1');
                    } else
                        st.push('0');
                }
                if (result[i] == '>' && result[i - 1] == '-' && result[i - 2] != '<') {
                    i--;
                    char val1 = st.top();
                    st.pop();
                    char val2 = st.top();
                    st.pop();
                    if (val1 == '0') {
                        st.push('1');
                    } else {
                        if (val2 == '1')
                            st.push('1');
                        else
                            st.push('0');
                    }
                }
                if (result[i] == '>' && result[i - 1] == '-' && result[i - 2] == '<') {
                    i -= 2;
                    char val1 = st.top();
                    st.pop();
                    char val2 = st.top();
                    st.pop();
                    if (val1 == val2)
                        st.push('1');
                    else
                        st.push('0');
                }
            }
        }
    }
    char final = st.top();
    st.pop();
    return (final=='1' ? "TRUE" : "FALSE");
}