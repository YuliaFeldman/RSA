#include <iostream>
#include "GFNumber.h"
#include "GField.h"
#include <cassert>

/**
 * The main function of this program
 * @return
 */
int main()
{
	GFNumber num1, num2;
	std::cin>>num1>>num2;
	assert(num1.getField().getOrder() ==  num2.getField().getOrder());
	std::cout << num1 + num2 << std::endl;
	std::cout << num1 - num2 << std::endl;
	std::cout << num2 - num1 << std::endl;
	std::cout << num1 * num2 << std::endl;
	num1.printFactors();
	num2.printFactors();


	return 0;
}