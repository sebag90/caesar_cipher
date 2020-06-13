#include <thread>
#include <future>
#include <iostream>

int simplefunc(int a, int b)
{ 
    return a + b;
}

int main()
{
      auto ciao = std::async(simplefunc, 1, 2);
      int simple = ciao.get();

      std::cout << simple << std::endl;
}