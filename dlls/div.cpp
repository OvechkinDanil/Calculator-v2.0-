// mult.cpp : Определяет экспортируемые функции для DLL.
//

#include "pch.h"
#include "framework.h"
#include "div.h"


DIV_API IOperations* GetClass()
{
  return new CDiv();
}


double CDiv::use(double a, double b)
{
  return a / b;
}


