#include <iostream>

#ifdef MINUS_EXPORTS
#define MINUS_API __declspec(dllexport)
#else
#define MINUS_API __declspec(dllimport)
#endif

class IOperations
{
public:
	virtual int GetNumArgs() = 0;
	virtual int GetPriority() = 0;
	virtual std::string GetOperationName() = 0;
	virtual double use(double a, double b = 0) = 0;
};

class CMinus : public IOperations
{
private:
	int priority = 1;
	int numArgs = 2;
	std::string name = "-";
public:
	CMinus() {};
	double use(double a, double b = 0) override;
	std::string GetOperationName() override { return name; }
	int GetNumArgs() override { return numArgs; }
	int GetPriority() override { return priority; }
	~CMinus() {};
};


extern "C" MINUS_API IOperations * GetClass();