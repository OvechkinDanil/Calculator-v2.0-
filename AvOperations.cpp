#include "OperationInterface.h"
#include "AvOperations.h"

error_t AvOperations::LoadOperations(string directory)
{
  IOperations* baseClass = NULL;

  for (auto& p : filesystem::directory_iterator(directory)) 
  {

    std::string filename = p.path().string();
    std::string typeFile = filename.substr(filename.find_last_of('.'), filename.length() - 1);

    if (typeFile != ".dll")
      continue;

    HINSTANCE hGetProcIDDLL = LoadLibrary(p.path().wstring().c_str());

    if (!hGetProcIDDLL)
      return ERROR_OPEN_DLL;

    f_funci funci = (f_funci)(GetProcAddress(hGetProcIDDLL, "GetClass"));

    if (!funci) 
    {
      FreeLibrary(hGetProcIDDLL);
      return ERROR_GET_FACTORY_FUNC;
    }

    baseClass = (IOperations*)funci();

    instances.push_back(hGetProcIDDLL);

    AvailiableOperations.insert(make_pair(baseClass->GetOperationName(), baseClass));
  }

  return ERROR_OK;
}


IOperations* AvOperations::getOperationClass(string op)
{
  if (AvailiableOperations.find(op) != AvailiableOperations.end())
  {
    return AvailiableOperations.find(op)->second;
  }
  return NULL;
}

void AvOperations::FreeDLLs()
{
  for (auto const& dll : instances)
  {
    FreeLibrary(dll);
  }
}

