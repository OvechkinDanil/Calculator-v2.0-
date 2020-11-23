#include "TransformModule.h"

double Transform::FindNumber(const char* string, int& index, int& spaces, error_t& curError)
{
	double number = 0;
	char* endstr;
	if (spaces != 0 && (index - spaces - 1) >= 0 && isdigit(string[index - spaces - 1])) {
		curError = ERROR_INPUT;
	}
	spaces = 0;
	number = strtod(string + index, &endstr);
	index += endstr - (string + index) - 1;
	
	return number;
}

error_t Transform::Calculate(AvOperations& AvOp, stack <double>& numStack, stack <string>& opStack)
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

string Transform::FindOperation(AvOperations& AvOp, const char* str, int& index, int& spaces, error_t& curError)
{
	string op;

	spaces = 0;

	while (index < lengthBuf && !isspace(str[index]) && !isdigit(str[index]) && str[index] != '(' && str[index] != ')')
	{
		op.push_back(str[index]);
		if (AvOp.isOperation(op))
		{
			return op;
		}
		index++;
	}
	index--;
	return op;
}

bool Transform::IsUnaryMinus(const char* string, int& index, AvOperations& AvOp, int& space) 
{
	return ((index - space == 0) || (string[index - space - 1] == '(') || !isdigit(string[index - space - 1])); 
}

double Transform::run(AvOperations& AvOp, error_t& curError)
{

	string curOp;

	stack <double> numStack;
	stack <string> opStack;


	int i,
		  space = 0;
	double number, result;
	const char* buf = str.c_str();


	for (i = 0; curError == ERROR_OK && i < lengthBuf; i++) // ìá èñïîëüçîâàòü èòåðàòîð
	{

		if (isspace(buf[i]))
		{
			space++;
			continue;
		}

		else if (isdigit(buf[i])) 
		{
			number = FindNumber(buf, i, space, curError);
			numStack.push(number);
			continue;
		}

		else if (buf[i] == '-' && AvOp.isOperation("-") && IsUnaryMinus(buf, i, AvOp, space))
		{
			space = 0;
			numStack.push(0);
			opStack.push("-");
		}

		else if (buf[i] == '(')
		{
			opStack.push("(");
			space = 0;
		}

		else if (buf[i] == ')')
		{
			if (buf[i - space - 1] == '(')
			{
				curError = ERROR_INPUT;
				return 0;
			}
				
			space = 0;
			while (!opStack.empty() && opStack.top() != "(")
			{
				if ((curError = Calculate(AvOp, numStack, opStack)) != ERROR_OK)
					return 0;
			}
			opStack.pop();
		}

		else
		{
			curOp = FindOperation(AvOp, buf, i, space, curError);

			if (curError != ERROR_OK)
				return 0;

			if (!AvOp.isOperation(curOp))
			{
				curError = ERROR_FIND_OP;
				return 0;
			}

			if (opStack.empty() || opStack.top() == "(" || (AvOp.getOperationClass(curOp)->GetPriority() > AvOp.getOperationClass(opStack.top())->GetPriority()))
			{
				opStack.push(curOp);
				continue;
			}

			while (!opStack.empty() && (AvOp.getOperationClass(curOp)->GetPriority() <= AvOp.getOperationClass(opStack.top())->GetPriority()))
			{
				if ((curError = Calculate(AvOp, numStack, opStack)) != ERROR_OK)
					return 0;
			}
	
			opStack.push(curOp);

		}


	}

	while (!opStack.empty())
	{
		if ((curError = Calculate(AvOp, numStack, opStack)) != ERROR_OK)
			return 0;
	}

	if (numStack.size() != 1)
	{
		return ERROR_INPUT;
	}
	else
	{
		result = numStack.top();
		numStack.pop();
	}
	
	return result;		
}
