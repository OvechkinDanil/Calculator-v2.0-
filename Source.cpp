#include "Errors.h"
#include "InterfaceModule.h"
#include "AvOperations.h"

using namespace std;

int main(int argc, char* argv[])
{
  Errors err;
  error_t curError;
  string str;
  AvOperations AvOp;
  IOperations* curClass;
  /*if (argc > 1)
  {
    ifstrfin(argv[1]);
    if (!fin.is_open())
    {
      err.print(ERROR_OPEN_FILE);
      return -1;
    }
  }*/
  
  string arg = argv[0];
  string path = arg.substr(0, arg.find_last_of('\\')) + "\\plugins";

  curError = AvOp.LoadOperations(path);

  err.setCurError(curError);
  if (curError != ERROR_OK)
  {
    err.checkError();
    exit(-1);
  }
  while (getline(cin, str))
  {
    curError = Process(AvOp, str);
    err.setCurError(curError);
    err.checkError();
  }
  
  AvOp.FreeDLLs();
}
  