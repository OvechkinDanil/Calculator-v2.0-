// pow.cpp : Определяет экспортируемые функции для DLL.
//

#include "pch.h"
#include "framework.h"
#include "plus.h"


PLUS_API IOperations* GetClass()
{
  return new CPlus();
}

double CPlus::use(double a, double b)
{
  return a + b;
}
