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

	string FindSubStrWithNum(string::iterator& it);

	double FindNumber(string::iterator& it, int& spaces, error_t& curError);

	error_t Calculate(AvOperations& AvOp, stack <double>& numStack, stack <string>& opStack);

	string FindOperation(AvOperations& AvOp, string::iterator& it, int& spaces);

	bool IsUnaryMinus(string::iterator& it, int& space);

public:

	Transform(string _buf, int _length) { str = _buf; lengthBuf = _length; }; 

	double run(AvOperations& AvOp, error_t& curError); // transform str to tokens

	~Transform() {};
};