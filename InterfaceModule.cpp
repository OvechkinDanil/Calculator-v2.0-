#include "InterfaceModule.h"

error_t Process(AvOperations& AvOp, string str)
{
	error_t err = ERROR_OK;
	double result;
	int length = str.length();
	int brackets = 0, spaces = 0;

	Transform tr(str, length);

	for (string::iterator it = str.begin(); it != str.end(); ++it)
	{
		if (isspace(*it))
			spaces++;

		else if (*it == '(')
			brackets++;
		else if (*it == ')')
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
	
	if (spaces == str.length())
	{
		cout << str << endl;
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