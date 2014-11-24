#include<thread>
#include<iostream>
#include<future>
using namespace std;

void f()
{
  for(int i = 0; i < 1000;i++) {
    cout << i << endl;
  }
}

int main()
{
  auto fut = async(f);
  auto fut2 = async(f);
  fut.get();
  fut2.get();
  return 0;
}
