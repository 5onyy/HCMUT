#ifndef __MAIN_H__
#define __MAIN_H__

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <math.h>
#include <stack>
#include <iomanip>
#include <vector>

using namespace std;

string Infix2Postfix(string infix);
string Infix2Prefix(string infix);
string PostfixPrefixCalculator(string input);
string LogicInfix2Postfix(string infix);
string LogicInfix2Prefix(string infix);
string LogicPostfixPrefixCalculator(string input,string varlue);

#endif