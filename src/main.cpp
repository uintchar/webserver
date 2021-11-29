#include <iostream>

#include <stdio.h>

#include "test.h"

int main()
{
  std::cout << "main start" << std::endl;

  testFunc1();

  std::cout << "main end" << std::endl;

  return 0;
}