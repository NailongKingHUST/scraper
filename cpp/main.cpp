#include<bits/stdc++.h>

#include "ft.hpp"

using namespace std;

#define WEEK

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

    #ifdef WEEK
      if (Lst[Len] == 2076040 || Lst[Len] == 1638720 || Lst[Len] == 1584640) {
        Len--; // skip no data
      }
    #endif

    // printf("Len %u Lst %u\n", Len, Lst[Len]);
    RD(), ++Len;
  // } while (Lst[Len - 1] != 364210); // shit data 
  } while (Lst[Len - 1] != 696370); // shit data 


  cerr << "tot Datas: " << Len << endl;

  double maxX = -1e9, maxY = -1e9, minX = 1e9, minY = 1e9;

  for (unsigned i(0); i < Len; ++i) {
    unsigned Start, Step, Cnt = 0;
    char CurC;
    sprintf(OpenFileName, "../data/%u.json", Lst[i]);
    // printf("%s\n", OpenFileName);

    // cerr << "Process File " << string(OpenFileName) << endl;
    
    freopen(OpenFileName, "r", stdin);
    Start = RD(), Step = RD();
    getchar(), getchar(), getchar(), getchar(), getchar(), getchar(), getchar();
    do {
      CurC = getchar();

      // cerr << "CurC = " << CurC << endl;

      if (CurC == ']' || CurC == '}') break;
      
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

    #ifdef WEEK
      auto res = FTonDay(CurLst, Cnt);
      // printf("self.add(Dot(ax.c2p(%.2lf, %.2lf), radius=0.06))\n", res.real, res.imag);
      printf("self.add(Text(\"%u\", font_size=12).next_to(Dot(ax.c2p(%.2lf, %.2lf), radius=0.06), UR, 0.01))\n", Lst[i], res.real, res.imag);
    #else 
      auto res = FTonWeek(CurLst, Cnt);
      // printf("self.add(Dot(ax.c2p(%.2lf, %.2lf), radius=0.06))\n", res.real, res.imag);
      printf("self.add(Text(\"%u\", font_size=12).next_to(Dot(ax.c2p(%.2lf, %.2lf), radius=0.06), UR, 0.01))\n", Lst[i], res.real, res.imag);
    #endif
    // FTonDay(CurLst, Cnt).Prt();
    // printf("%u ", Lst[i]);

    // res.Prt();
    maxX = max(maxX, res.real);
    maxY = max(maxY, res.imag);
    minX = min(minX, res.real);
    minY = min(minY, res.imag);
  }

  cerr << "maxX = " << maxX << endl;
  cerr << "maxY = " << maxY << endl;
  cerr << "minX = " << minX << endl;
  cerr << "minY = " << minY << endl;

  return 0;
}
/*
g++ main.cpp -o ../bin/ft.exe
*/