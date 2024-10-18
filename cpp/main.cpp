#include<bits/stdc++.h>

#include "ft.hpp"

using namespace std;

unsigned RD() {
  char CurC = getchar();
  unsigned Res = 0;
  while (CurC < '0' || CurC > '9') CurC = getchar();
  while (CurC >= '0' && CurC <= '9')
    Res = Res * 10 + CurC - '0', CurC = getchar();
  return Res;
}
Complex FTonDay(const Dot* x, unsigned Len);
signed main() {
  // freopen("../bin/Log.txt", "w", stdout);
  Dot CurLst[10005];
  char OpenFileName[105], TmpC[105];
  unsigned Lst[10005], Len = 0;
  freopen("../data.json", "r", stdin);
  do {
    Lst[Len] = RD(), getchar(), getchar();
    cin.getline(TmpC, 100);
    // printf("Len %u Lst %u\n", Len, Lst[Len]);
    RD(), ++Len;
  } while (Lst[Len - 1] != 364210);
  for (unsigned i(0); i < Len; ++i) {
    unsigned Start, Step, Cnt = 0;
    char CurC;
    sprintf(OpenFileName, "../data/%u.json", Lst[i]);
    // printf("%s\n", OpenFileName);
    freopen(OpenFileName, "r", stdin);
    Start = RD(), Step = RD();
    getchar(), getchar(), getchar(), getchar(), getchar(), getchar(), getchar();
    do {
      CurC = getchar();
      // if (i == 4) printf("%u %c\n", Lst[i], CurC);
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
        // if (i == 4)
        //   printf("%u: %u, %u\n", Cnt, CurLst[Cnt - 1].Time, CurLst[Cnt - 1].Val);
      }
      Start += Step;
    } while (CurC != ']');
    // FTonDay(CurLst, Cnt).Prt();
    printf("%u ", Lst[i]);
    FTonWeek(CurLst, Cnt).Prt();
  }
  return 0;
}
/*
g++ main.cpp -o ../bin/ft.exe
*/