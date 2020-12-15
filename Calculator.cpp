#include "Calculator.h"

void Calculator::run(Errors& err)
{
  while (getline(cin, str))
  {
    processString();

    if (curError != ERROR_OK)
      err.print(curError);

  }
}

void Calculator::processString()
{
  int length = str.length();

  Transform tr(str);

  if (!checkBrackets())
    return;

  result = tr.run(AvOp, curError);

  if (findErrorsAfterProcessing())
    return;

  cout << str << " == " << result << endl;
}

bool Calculator::findErrorsAfterProcessing()
{
  if (curError != ERROR_OK)
    return true;

  if (checkResult())
  {
    curError = ERROR_INF;
    return true;
  }
}

bool Calculator::checkBrackets()
{
  int numLeftBrackets, numRightBrackets;

  numLeftBrackets = numberOfSubString("(");

  numRightBrackets = numberOfSubString(")");

  if (numLeftBrackets - numRightBrackets != 0)
  {
    curError = ERROR_BRACK;
    return false;
  }
  else
    return true;

}

int Calculator::numberOfSubString(string sub)
{
  int pos = 0, counter = 0, start = 0;
  for (;;)
  {
    pos = str.find(sub, start);
    if (pos != -1)
    {
      start = pos + sub.size();
      counter++;
    }
    else
      break;
  }
  return counter;
}



