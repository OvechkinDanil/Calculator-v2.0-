#include "TransformModule.h"

string Transform::FindSubStrWithNum(string::iterator& it)
{
	bool dot = false;
	string s_num;

	while (it != str.end() && !dot && (isdigit(*it) || *it == '.'))
	{
		s_num.push_back(*it);

		if (*it == '.')
			dot = true;
		it++;
	}
	it--;
	return s_num;
}

double Transform::FindNumber(string::iterator& it, int& spaces, error_t& curError)
{
	double number = 0;
	string s_num;

	if (spaces != 0 && (it - spaces - 1) >= str.begin() && isdigit(*(it - spaces - 1))) {
		curError = ERROR_INPUT;
	}
	spaces = 0;
	
	s_num = FindSubStrWithNum(it);
	number = atoi(s_num.c_str());

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

string Transform::FindOperation(AvOperations& AvOp, string::iterator& it, int& spaces)
{
	string op;

	spaces = 0;

	while (it != str.end() && !isspace(*it) && !isdigit(*it) && *it != '(' && *it != ')')
	{
		op.push_back(*it);
		if (AvOp.isOperation(op))
		{
			return op;
		}
		it++;
	}
	it--;
	return op;
}

bool Transform::IsUnaryMinus(string::iterator& it, int& space)
{
	return ((it - space == str.begin()) || (*(it - space - 1) == '(') || !isdigit(*(it - space - 1)));
}

double Transform::run(AvOperations& AvOp, error_t& curError)
{

	string curOp;

	stack <double> numStack;
	stack <string> opStack;


	int i,
		  space = 0;
	double number, result;


	for (string::iterator it = str.begin(); it != str.end(); it++)
	{

		if (isspace(*it))
		{
			space++;
			continue;
		}

		else if (isdigit(*it)) 
		{
			number = FindNumber(it, space, curError);
			numStack.push(number);
			continue;
		}

		else if (*it == '-' && AvOp.isOperation("-") && IsUnaryMinus(it, space))
		{
			space = 0;
			numStack.push(0);
			opStack.push("-");
		}

		else if (*it == '(')
		{
			opStack.push("(");
			space = 0;
		}

		else if (*it == ')')
		{
			if (*(it-space-1) == '(')
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
			curOp = FindOperation(AvOp, it, space);

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