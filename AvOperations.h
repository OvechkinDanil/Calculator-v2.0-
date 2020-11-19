#pragma once
#include "OperationInterface.h"
#include <map>
#include <vector>
#include <filesystem>
#include <Windows.h>
#include "Errors.h"

typedef IOperations* (_cdecl* f_funci)();

using namespace std;

class AvOperations
{
private:
	vector<HINSTANCE> instances;
	map <string, IOperations*> AvailiableOperations;
	error_t getClassFromDLL(WCHAR* DLLname);

public:
	AvOperations() {};
	bool isOperation(string op) { return AvailiableOperations.find(op) != AvailiableOperations.end(); }
	IOperations* getOperationClass(string op);
	error_t LoadOperations(string directory);
	void FreeDLLs();
	~AvOperations() {};
};