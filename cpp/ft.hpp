#include<bits/stdc++.h>
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
    Rt = Rt + Base[Time] * x[i].Val;
    Sum += x[i].Val;
  }
  Sum /= Len;
  return Rt / Sum;
}
/*
g++ ft.cpp main.cpp -o ../bin/ft.exe
*/