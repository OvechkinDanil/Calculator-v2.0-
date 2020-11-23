// Приведенный ниже блок ifdef — это стандартный метод создания макросов, упрощающий процедуру
// экспорта из библиотек DLL. Все файлы данной DLL скомпилированы с использованием символа POW_EXPORTS
// Символ, определенный в командной строке. Этот символ не должен быть определен в каком-либо проекте,
// использующем данную DLL. Благодаря этому любой другой проект, исходные файлы которого включают данный файл, видит
// функции POW_API как импортированные из DLL, тогда как данная DLL видит символы,
// определяемые данным макросом, как экспортированные.
#include <math.h>
#include <iostream>

#ifdef POW_EXPORTS
#define POW_API __declspec(dllexport)
#else
#define POW_API __declspec(dllimport)
#endif

class IOperations
{
public:
	virtual int GetNumArgs() = 0;
	virtual int GetPriority() = 0;
	virtual std::string GetOperationName() = 0;
	virtual double use(double a, double b = 0) = 0;
};

class Cpow : public IOperations
{
private:
	int priority = 3;
	int numArgs = 2;
	std::string name = "^";
public:
	Cpow() {};
	double use(double a, double b = 0) override;
	std::string GetOperationName() override { return name; }
	int GetNumArgs() override { return numArgs; }
	int GetPriority() override { return priority; }
	~Cpow() {};
};


extern "C" POW_API IOperations* GetClass();
