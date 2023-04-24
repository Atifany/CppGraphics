
#include <iostream>

class Base
{
	public:
		virtual void foo()
		{
			std::cout << "Im Base class!\n";
		}
};

class Deri : public Base
{
	public:
		// void foo() override
		// {
		// 	std::cout << "Im Deri class!\n";
		// }
};

int main()
{
	Deri* deri = new Deri();
	Base* base = deri;
	base->foo();
}
