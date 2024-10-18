#include<bits/stdc++.h>

#include "ft.hpp"

using namespace std;

struct Complex {
  double real, imag;
  Complex(double r = 0, double i = 0) : real(r), imag(i) {}
  Complex operator+(const Complex& b) const {
    return Complex(real + b.real, imag + b.imag);
  }
  Complex operator-(const Complex& b) const {
    return Complex(real - b.real, imag - b.imag);
  }
  Complex operator*(const Complex& b) const {
    return Complex(real * b.real - imag * b.imag, real * b.imag + imag * b.real);
  }
  Complex operator/(const Complex& b) const {
    double den = b.real * b.real + b.imag * b.imag;
    return Complex((real * b.real + imag * b.imag) / den,
      (imag * b.real - real * b.imag) / den);
  }
  Complex operator/(const double b) const {
    return Complex(real / b, imag / b);
  }
  Complex operator*(const double b) const {
    return Complex(real * b, imag * b);
  }
}BaseDay[24];
struct Dot {
  unsigned Time, Val;
};
signed main() {
  Dot CurLst[10005];
  unsigned Id;
  char OpenFileName[105];

  scanf("%u", &Id);
  spritnf(OpenFileName, "../data/%u.json", Id);

  return 0;
}
/*
g++ ft.cpp main.cpp -o ../bin/ft.exe
*/