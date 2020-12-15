#include "TransformModule.h"

double Transform::run(AvOperations& _AvOp, error_t& curError)
{
	AvOp = _AvOp;
	double result;

	parseString(curError);

	if (curError != ERROR_OK)
		return 0;

	return findResult(curError);
}

void Transform::parseString(error_t& curError)
{
	string delimiter = " ";

	while (curError == ERROR_OK && !str.empty())
	{
		curToken = SeparateToken(delimiter);

		if (curToken.empty())
			continue;

		else if (isdigit(curToken[0]))
		{
			size_t end = 1;
			double number = stod(curToken, &end);

			numStack.push(number);
			continue;
		}

		else if (IsUnaryMinus())
		{
			numStack.push(0);
			opStack.push("-");
		}

		else if (isLeftBracket())
		{
			opStack.push("(");
		}

		else if (isRightBracket())
			processWithRightBrack(curError);

		else
			processWithOperation(curError);

		prevToken = curToken;
	}
}

string Transform::SeparateToken(string& delimiter)
{
	int pos = str.find(delimiter);

	if (pos == string::npos)
	{
		pos = str.length();
	}
	string curToken = str.substr(0, pos);

	if (pos != str.length())
	{
		str.erase(0, delimiter.length());
	}
	str.erase(0, pos);
	return curToken;
}

error_t Transform::Calculate()
{
	IOperations* opClass;
	double left, right, result;
	if (numStack.empty() || opStack.empty())
	{
		return ERROR_STACK_EMPTY;
	}
	
	opClass = (IOperations*)AvOp.getOperationClass(opStack.top());
	opStack.pop();

	if (opClass->GetNumArgs() == 2)
	{
		if (numStack.size() < 2)
		{
			return ERROR_STACK_EMPTY;
		}

		right = numStack.top();
		numStack.pop();

		left = numStack.top();
		numStack.pop();

		result = opClass->use(left, right);

	}
	else
	{
		if (numStack.empty())
		{
			return ERROR_STACK_EMPTY;
		}

		right = numStack.top();
		numStack.pop();

		result = opClass->use(right);
		
	}
	numStack.push(result);
	return ERROR_OK;
}



bool Transform::IsUnaryMinus()
{
	return curToken == "-" && AvOp.isOperation("-") && ((prevToken.empty()) || (prevToken == "(") || !isdigit(prevToken[0]));
}

void Transform::processWithOperation(error_t& curError)
{
	if (!AvOp.isOperation(curToken))
	{
		curError = ERROR_FIND_OP;
		return;
	}

	if (opStack.empty() || opStack.top() == "(" || (AvOp.getOperationClass(curToken)->GetPriority() > AvOp.getOperationClass(opStack.top())->GetPriority()))
	{
		opStack.push(curToken);
		return;
	}

	while (!opStack.empty() && (AvOp.getOperationClass(curToken)->GetPriority() <= AvOp.getOperationClass(opStack.top())->GetPriority()))
	{
		if ((curError = Calculate()) != ERROR_OK)
			return;
	}

	opStack.push(curToken);
}

void Transform::processWithRightBrack(error_t& curError)
{
	if (isLeftBracket())
	{
		curError = ERROR_INPUT;
		return;
	}

	while (!opStack.empty() && opStack.top() != "(")
	{
		if ((curError = Calculate()) != ERROR_OK)
			return;
	}
	opStack.pop();
}



double Transform::findResult(error_t& curError)
{
	while (!opStack.empty())
	{
		if ((curError = Calculate()) != ERROR_OK)
			return 0;
	}

	if (numStack.size() != 1)
	{
		curError = ERROR_INPUT;
		return 0;
	}
	else
	{
		double result = numStack.top();
		numStack.pop();
		return result;
	}
}