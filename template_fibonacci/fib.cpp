#include<iostream>
using namespace std;

template<int i>
struct Fib {
  static const int unsigned value = Fib<i-1>::value + Fib<i-2>::value;
};

template<>
struct Fib<0> {
  static const int unsigned value = 0;
};

template<>
struct Fib<1> {
  static const int unsigned value = 1;
};

int main()
{
  cout << Fib<10>::value << endl;
}