#include "InterfaceModule.h"

error_t Process(AvOperations& AvOp, string str)
{
	error_t err = ERROR_OK;
	double result;
	int length = str.length();
	const char* c_str = str.c_str();
	int brackets = 0, spaces = 0;

	Transform tr(str, length);

	for (int i = 0; i < length; i++)
	{
		if (isspace(c_str[i]))
			spaces++;

		else if (c_str[i] == '(')
			brackets++;

		else if (c_str[i] == ')')
			brackets--;

		if (brackets < 0)
		{
			return ERROR_BRACK;
		}
	}

	if (brackets != 0)
	{
		return ERROR_BRACK;
	}
	
	if (spaces == length)
	{
		puts(c_str);
		return ERROR_OK;
	}
	
	result = tr.run(AvOp, err);

	if (err != ERROR_OK)
		return err;

	if (isnan(result) || isinf(result))
		return ERROR_INF;
	
	cout << str << " == " << result << endl;

	return ERROR_OK;
}