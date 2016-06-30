#include <iostream>
#include <unistd.h>

int age = 23;

int main()
{
	sleep(2);
	std::cout << "I am Adrian.\n" << "Age: " << age << "\n";
	return 0;
}
