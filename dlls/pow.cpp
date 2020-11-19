// pow.cpp : Определяет экспортируемые функции для DLL.
//

#include "pch.h"
#include "framework.h"
#include "pow.h"


POW_API IOperations* GetClass()
{
  return new Cpow();
}

double Cpow::use(double a, double b)
{
  return pow(a, b);
}
