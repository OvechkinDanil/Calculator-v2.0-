#pragma once
#include "Errors.h"
#include "AvOperations.h"
#include <stack>

using namespace std;

class Transform
{
private:

	string str;

	int lengthBuf;

	double FindNumber(const char* string, int& index, int& spaces, error_t& curError); 

	error_t Calculate(AvOperations& AvOp, stack <double>& numStack, stack <string>& opStack);

	string FindOperation(AvOperations& AvOp, const char* str, int& index, int& spaces, error_t& curError);

	bool IsUnaryMinus(const char* string, int& index, AvOperations& AvOp, int& space);

public:

	Transform(string _buf, int _length) { str = _buf; lengthBuf = _length; }; 

	double run(AvOperations& AvOp, error_t& curError); // transform str to tokens

	~Transform() {};
};