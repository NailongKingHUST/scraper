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
struct DistL {
  unsigned NameA, NameB;
  double Dis;
  const char operator<(const DistL& x) const { return Dis < x.Dis; }
  void Prt() {
    printf("%u->%u %.10lf\n", NameA, NameB, Dis);
  }
};
signed main() {
  // freopen("../bin/Log.txt", "w", stdout);
  Dot CurLst[10005];
  char OpenFileName[105], TmpC[105];
  unsigned Lst[10005], Len = 0;
#ifdef WEEK
  freopen("../data/weekLog.txt", "r", stdin);
  freopen("../data/weekDist.txt", "w", stdout);
#else 
  freopen("../data/maxLog.txt", "r", stdin);
  freopen("../data/maxDist.txt", "w", stdout);
#endif

  map<unsigned, Complex> List;
  vector<DistL> Dists;
  while (1) {
    unsigned A;
    Complex CA;
    cin >> A >> CA.real >> CA.imag;
    if (!A) break;
    List[A] = CA;
  }
  for (auto i : List) {
    double CurMn(1e9), CurD;
    unsigned CurID = 0;
    for (auto j : List) if (i.first != j.first) {
      CurD = i.second.Delt(j.second);
      if (CurD < CurMn) CurMn = CurD, CurID = j.first;
    }
    Dists.push_back({ i.first, CurID, CurMn });
  }
  sort(Dists.begin(), Dists.end());
  for (auto i : Dists) i.Prt();
  return 0;
}
/*
g++ Dist.cpp -o ../bin/ft.exe
../bin/ft.exe
*/