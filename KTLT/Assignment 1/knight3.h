#ifndef __KNIGHT_H__
#define __KNIGHT_H__

#include "main.h"

bool findString(const string instr, const string target);//Find if a char or a string is availible on the string
bool Prime(const long long int level);//Check if a number is a prime or not
void Convert(const string innum[], const long long int numOfValues, long long int& maxi2, long long int& mini2);//Convert each x1
void Mount(const string innum[], const long long int numOfValues, long long int& mtx, long long int& mti);//Check if a array is in a mountain shape or not
long long int findPos(string innum[], const long long int numOfValues, const long long int mode);//Find pos of the max or min number in array
long long int first2Num(const long long int innum);//Get first 2 num (for MushMario case)
string remainingNum(const int innum);//Get ms string (for MushMario case)
long long int findClosetFib(const long long int innum);//Get the closet Fibonacci number smalong longer than the input number
long long int findClosetPrime(const long long int innum);//Get the closet prime number larger than the input number
long long int countChar(const string data, const char inchar);//Count the numbers of char appears in the string
void dataFilter(const string instr, string data[], const char filtered_char);//Seperate data respectively in the string
void readData(const string file_input, string& data, const long long int line);//Read each line in tc1_input
void getKnightData(const string data, int& HP, int& level, int& remedy, int& maidenkiss, int& phoenixdown);//Get each data of Knight's information
long long int getLevelO(const long long int order);//Get levelO 
void deBuffAdjust(int deBuff[], const char in_operator, const int indeBuff);//Adding or removing debuff on knight
void usePhoenix(const int maxHP, const int level_before, float& HP, int& level, int& phoenixdown, int& tiny_times, int& frog_times, int deBuff[]);//Use Phoenixdown if needed
void useRemedy(int& remedy);//Use Remedy if needed
void useMaidenkiss(int& maidenkiss);//Use Maidenkiss if needed
void MushMarioHP(const int maxHP, float& HP, const int level, const int phoenixdown);//Adjusting HP (MushMario case)
void MushGhostProcess(const int maxHP, const string MushType, const string file[], const int level_before, int& tiny_times, int& frog_times, float& HP, int& level, int& phoenixdown, int& rescue, int deBuff[]);//Processing MushGhost event
void eventProcess(const int maxHP, const string event, const long long int order, const string file[], bool& met_aclepius, bool& met_merlin, int& tiny_times, int& frog_times, int deBuff[], const int knightIdentity, float &HP, int& level, int& remedy, int& maidenkiss, int& phoenixdown, int& rescue);//Go through one by one event
void KoopaProgess(const string data, const string file, float& HP, int& level, int& remedy, int& maidenkiss, int& phoenixdown, int& rescue);//Go through along long the events
void display(const float HP, const int level, const int remedy, const int maidenkiss, const int phoenixdown, const int rescue);//Display knight's data
void adventureToKoopa(const string file_input, int& HP, int& level, int& remedy, int& maidenkiss, int& phoenixdown, int& rescue);

#endif // __KNIGHT_H__