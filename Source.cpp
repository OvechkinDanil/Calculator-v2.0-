#include "Errors.h"
#include "Calculator.h"
#include "AvOperations.h"

using namespace std;

int main(int argc, char* argv[])
{
  Errors err;
  error_t curError;
  string str;
  AvOperations AvOp;
  
  string arg = argv[0];
  string path = arg.substr(0, arg.find_last_of('\\')) + "\\plugins";

  curError = AvOp.LoadOperations(path);

  if (curError != ERROR_OK)
  {
    err.print(curError);
    exit(-1);
  }
  
  Calculator calc(AvOp);
  calc.run(err);
  
  AvOp.FreeDLLs();
}
  