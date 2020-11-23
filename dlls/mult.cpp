// mult.cpp : Определяет экспортируемые функции для DLL.
//

#include "pch.h"
#include "framework.h"
#include "mult.h"


MULT_API IOperations* GetClass()
{
  return new CMult();
}


double CMult::use(double a, double b)
{
  return a * b;
}


