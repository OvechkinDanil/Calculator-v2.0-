// sin.cpp : Определяет экспортируемые функции для DLL.
//

#include "pch.h"
#include "framework.h"
#include "sin.h"


SIN_API IOperations* GetClass()
{
  return new Csin();
}

double Csin::use(double a, double b)
{
  return sin(a);
}
