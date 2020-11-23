#include "Errors.h"

Errors::Errors()
{
	ErrorsList[ERROR_BRACK] = "ERROR: BRACKETS\n";
	ErrorsList[ERROR_INPUT] = "ERROR: INCORRECT INPUT!\n";
	ErrorsList[ERROR_FUNC] = "ERROR: INCORRECT EXPRESSION IN FUNC\n";
	ErrorsList[ERROR_OPERATION] = "ERROR: OPERATIONS FAILED!\n";
	ErrorsList[ERROR_INF] = "ERROR: PROBLEM WITH INF\n";
	ErrorsList[ERROR_NUM_SIZE] = "ERROR: THE NUMBER IS TOO LARGE/SMALL\n";
	ErrorsList[ERROR_MEMORY] = "ERROR: NOT ENOUGHT MEMORY FOR THIS EXPRESSION\n";
	ErrorsList[ERROR_STACK_EMPTY] = "ERROR: STACK IS EMPTY. MAYBE PROBLEM WITH THE EXPRESSION\n";
	ErrorsList[ERROR_INPUT] = "ERROR: INCORRECT INPUT\n";
	ErrorsList[ERROR_VAR] = "ERROR: VARIABLE DEFINITION\n";
	ErrorsList[ERROR_MEMORY_EOF] = "ERROR: MEMORY EOF\n";
	ErrorsList[ERROR_OPEN_FILE] = "ERROR: CANNOT OPEN FILE\n";
	ErrorsList[ERROR_NO_DLL] = "ERROR: NO DLL IN PLUGINS DIRECTORY\n";
	ErrorsList[ERROR_OPEN_DLL] = "ERROR: CANNOT OPEN DLL\n";
	ErrorsList[ERROR_GET_FACTORY_FUNC] = "ERROR: CANNOT GET FACTORY FUNC FROM DLL\n";
	ErrorsList[ERROR_FIND_OP] = "ERROR: THIS OPERATION/FUNCTION IS NOT LOADED FROM DLL\n";

	curError = ERROR_OK;
}

void Errors::checkError()
{
	if (curError != ERROR_OK)
	{
		this->print();
		curError = ERROR_OK;
	}
}

void Errors::print()
{
	if (ErrorsList.find(curError) != ErrorsList.end())
	{
		std::cout << ErrorsList.find(curError)->second;
	}
}