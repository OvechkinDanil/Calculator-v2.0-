#pragma once
#include <iostream>

class IOperations
{
public:
  virtual int GetNumArgs() = 0;
  virtual int GetPriority() = 0;
  virtual std::string GetOperationName() = 0;
  virtual double use(double a, double b = 0) = 0;
};