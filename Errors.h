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
  error_t curError;
  std::map<error_t, std::string> ErrorsList;
  void print();
public:
  Errors();
  void setCurError(error_t c_err) { curError = c_err; };
  void checkError();
  ~Errors() {};
};
