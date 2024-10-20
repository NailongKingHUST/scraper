#ifndef MyFT
#define MyFT

#include<bits/stdc++.h>
#include "Complex.hpp"
using namespace std;

const double PI = 3.1415926535897932384626433832795;

Complex FTonDay(const Dot* x, unsigned Len) {
  Complex Base[24], Rt(0, 0);
  double Sum = 0;

  Base[1] = { cos(PI / 12), sin(PI / 12) };
  Base[0] = { 1, 0 };
  Base[2] = { sqrt(3) / 2, 0.5 };
  Base[4] = { 0.5, sqrt(3) / 2 };
  Base[3] = Base[2] * Base[1];
  Base[5] = Base[4] * Base[1];
  for (unsigned i = 6; i < 24; ++i)
    Base[i] = { -Base[i - 6].imag, Base[i - 6].real };
  for (unsigned i = 0; i < Len; ++i) {
    unsigned Time = (x[i].Time / 3600) % 24;
    // printf("Here Time %u Base", x[i].Time), Base[Time].Prt();
    Rt = Rt + Base[Time] * x[i].Val;
    Sum += x[i].Val;
  }
  return Rt / Sum;
}
Complex FTonWeek(const Dot* x, unsigned Len) {
  Complex Base[7], Rt(0, 0);
  double Sum = 0;
  // printf("Here\n");
  Base[1] = { cos(PI * 2 / 7), sin(PI * 2 / 7) };
  Base[0] = { 1, 0 };
  for (unsigned i = 2; i < 7; ++i)
    Base[i] = Base[i - 1] * Base[1];
  // for (unsigned i = 0; i < 7; ++i) Base[i].Prt();
  for (unsigned i = 0; i < Len; ++i) {
    unsigned Time = (x[i].Time / 86400 + 4) % 7;
    // printf("Here Time %u Base", x[i].Time), Base[Time].Prt();
    Rt = Rt + Base[Time] * x[i].Val;
    Sum += x[i].Val;
  }
  return (Rt / Sum) * 100;
}
#endif

/*
g++ ft.cpp main.cpp -o ../bin/ft.exe
*/