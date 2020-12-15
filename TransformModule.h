#pragma once
#include "Errors.h"
#include "AvOperations.h"
#include <stack>
#include <string>

using namespace std;

class Transform
{
private:

	string str;

	string curToken;

	string prevToken;

	AvOperations AvOp;

	stack <double> numStack;

	stack <string> opStack;

	void parseString(error_t& curError);

	double findResult(error_t& curError);

	string SeparateToken(string& delimiter);

	error_t Calculate();

	bool IsUnaryMinus();

	void processWithOperation(error_t& curError);

	void processWithRightBrack(error_t& curError);

	bool isLeftBracket() { return curToken == "("; }

	bool isRightBracket() { return curToken == ")"; }

public:

	Transform(string _buf) : str(_buf) { }

	double run(AvOperations& AvOp, error_t& curError); // transform str to tokens

	~Transform() {};
};