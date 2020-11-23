// pow.cpp : Определяет экспортируемые функции для DLL.
//

#include "pch.h"
#include "framework.h"
#include "minus.h"


MINUS_API IOperations* GetClass()
{
  return new CMinus();
}

double CMinus::use(double a, double b)
{
  return a - b;
}
