#ifndef __KNIGHT_H__
#define __KNIGHT_H__

#include "main.h"

void _BoswerSurrendered(int& HP, int& level, int& remedy, int& maidenkiss, int& phoenixdown, int& rescue);
void _CombatAssessment1_5(int& HP, int& level, int& i, float bD, int& king_arthur, int& lancelot);
int _Shaman(int& HP, int& level, int& remedy, int& phoenixdown, int& i, int& maxHP, int& king_arthur, int& lancelot);
int _SirenVajsh(int& level, int& maidenkiss, int& i, int& king_arthur, int& lancelot);
int _IncrementNearestPrime(int n);
void _MushMario(int& HP, int& level, int& phoenixdown, int& i, int& maxHP);
void _Bowser(int& level, int& rescue, int& i, int& king_arthur, int& lancelot);

void display(int HP, int level, int remedy, int maidenkiss, int phoenixdown, int rescue);
void adventureToKoopa(string file_input, int & HP, int & level, int & remedy, int & maidenkiss, int & phoenixdown, int & rescue);

#endif // __KNIGHT_H__