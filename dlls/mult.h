#include <iostream>

#ifdef MULT_EXPORTS
#define MULT_API __declspec(dllexport)
#else
#define MULT_API __declspec(dllimport)
#endif

class IOperations
{
public:
	virtual int GetNumArgs() = 0;
	virtual int GetPriority() = 0;
	virtual std::string GetOperationName() = 0;
	virtual double use(double a, double b = 0) = 0;
};

class CMult : public IOperations
{
private:
		int priority = 2;
		int numArgs = 2;
		std::string name = "*";
public:
		CMult() {};
		double use(double a, double b) override;
		std::string GetOperationName() override { return name; }
		int GetNumArgs() override { return numArgs; }
		int GetPriority() override { return priority; }
		~CMult() {};
};

extern "C" MULT_API IOperations* GetClass();


