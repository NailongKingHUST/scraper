#include<bits/stdc++.h>

#include "ft.hpp"

using namespace std;

Complex FTonDay(const Dot* x, unsigned Len);
signed main() {
  Dot CurLst[10005];
  unsigned Id, Start, Step, Cnt = 0;
  char OpenFileName[105];

  scanf("%u", &Id);
  sprintf(OpenFileName, "../data/%u.json", Id);

  freopen(OpenFileName, "r", stdin);
  scanf("%u%u", &Start, &Step);
  getchar(), getchar(), getchar(), getchar(), getchar(), getchar(), getchar(), getchar();
  char CurC;
  do {
    CurC = getchar();
    while (!((CurC >= '0' && CurC <= '9') || (CurC >= 'a' && CurC <= 'z'))) CurC = getchar();
    if (CurC == 'n') getchar(), getchar(), getchar(), getchar();
    else {
      CurLst[Cnt].Time = Start;
      CurLst[Cnt].Val = 0;
      while (CurC >= '0' && CurC <= '9') {
        CurLst[Cnt].Val = CurLst[Cnt].Val * 10 + CurC - '0';
        CurC = getchar();
      }
      ++Cnt;
    }
    Start += Step;
  } while (CurC != ']');
  FTonDay(CurLst, Cnt).Prt();
  return 0;
}
/*
g++ main.cpp -o ../bin/ft.exe
*/