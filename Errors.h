#pragma once
#include <map>
#include <iostream>

typedef enum
{
  ERROR_OK,
  ERROR_BRACK,
  ERROR_INPUT,
  ERROR_OPERATION,
  ERROR_FUNC,
  ERROR_INF,
  ERROR_NUM_SIZE,
  ERROR_MEMORY,
  ERROR_STACK_EMPTY,
  ERROR_MEMORY_EOF,
  ERROR_VAR,
  ERROR_OPEN_FILE,
  ERROR_NO_DLL,
  ERROR_OPEN_DLL,
  ERROR_GET_FACTORY_FUNC,
  ERROR_FIND_OP
} error_t;


class Errors 
{
private:
  std::map<error_t, std::string> ErrorsList;
public:
  Errors();
  void print(error_t err);
  ~Errors() {};
};
