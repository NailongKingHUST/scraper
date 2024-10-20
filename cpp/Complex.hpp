#ifndef MyComp
#define MyComp

#include<bits/stdc++.h>
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
  double ModV() const {
    double Rt(real * real + imag * imag);
    return sqrt(Rt);
  }
  double Delt(const Complex& x) const {
    return (*this - x).ModV() / ModV();
  }
  void Prt() {
    printf("(%lf, %lf)\n", real, imag);
  }
};
struct Dot {
  unsigned Time, Val;
};
#endif