#include <iostream>

#ifdef DIV_EXPORTS
#define DIV_API __declspec(dllexport)
#else
#define DIV_API __declspec(dllimport)
#endif

class IOperations
{
public:
	virtual int GetNumArgs() = 0;
	virtual int GetPriority() = 0;
	virtual std::string GetOperationName() = 0;
	virtual double use(double a, double b = 0) = 0;
};

class CDiv : public IOperations
{
private:
	int priority = 2;
	int numArgs = 2;
	std::string name = "/";
public:
	CDiv() {};
	double use(double a, double b) override;
	std::string GetOperationName() override { return name; }
	int GetNumArgs() override { return numArgs; }
	int GetPriority() override { return priority; }
	~CDiv() {};
};

extern "C" DIV_API IOperations * GetClass();

