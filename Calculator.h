#pragma once
#include "Errors.h"
#include <string>
#include "AvOperations.h"
#include "TransformModule.h"


class Calculator
{
public:
	Calculator(AvOperations& _AvOp) : AvOp(_AvOp) {}
	void run(Errors& err);
private:
	double result = 0;
	string str;
	error_t curError = ERROR_OK;
	AvOperations AvOp;

	int numberOfSubString(string sub);	
	bool checkBrackets();
	bool findErrorsAfterProcessing();
	void processString();
	bool checkResult() { return isnan(result) || isinf(result); };

};