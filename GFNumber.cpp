#include "GFNumber.h"
#include "GFNumber.h"
#include <algorithm>




////////////////////////////////////////  Constructors & Destructor  //////////////////////////////

/**
 * Default constructor
 */
GFNumber::GFNumber():_n(0), _gField(2, 1)
{

}


/**
 * Constructor #1
 * @param n A number in the 2 ^ 1 order field
 */
GFNumber::GFNumber(const long &n):_gField(2, 1)
{
	_n = (long)fmod(n, 2);
	if(_n < 0)
	{
		_n += 2;
	}

}


/**
 * Constructor #2
 * @param n A number in the given field
 * @param field A field
 */
GFNumber::GFNumber(const long &n, const GField &field):_gField(field)
{
	_n = (long)fmod(n, _gField.getOrder());
	if(_n < 0)
	{
		_n += _gField.getOrder();
	}
}


/**
 * Copy constructor
 * @param other Another field
 */
GFNumber::GFNumber(const GFNumber &other):_n(other._n), _gField(other._gField)
{}


/**
 * Destructor
 */
GFNumber::~GFNumber() = default;



////////////////////////////////////////   Class Methods    ///////////////////////////////////////

/**
 * Function returns the value of the number represented by this class
 * @return value of the number represented by this class
 */
const long& GFNumber::getNumber() const
{
	return _n;
}


/**
 * Function returns the field of this number
 * @return field of this number
 */
const GField& GFNumber::getField() const
{
	return _gField;
}


/**
 * Check if this number is prime
 * @return true if this number is prime
 */
bool GFNumber::getIsPrime()
{
	return GField::isPrime(_n);
}


/**
 * Returns prime factors of this number
 * @param size number of prime factors
 * @return prime numbers of this number
 */
GFNumber* GFNumber::getPrimeFactors(int *size)
{
	GFNumber *primeFactorsArr = new GFNumber[0];
	long *primeFactorsTemp = new long[0];
	long num = _n;
	*size = 0;

	primeFactorsTemp = _getPrimeFactors1(num, primeFactorsTemp, size);
	if(*size > 0)
	{
		delete[] primeFactorsArr;
		primeFactorsArr = new GFNumber[*size];
		for(int i = 0; i < *size; i++)
		{
			primeFactorsArr[i] = _gField.createNumber(primeFactorsTemp[i]);
		}
	}
	delete[] primeFactorsTemp;
	return primeFactorsArr;

}


/**
 * A helper function
 * @param n number
 * @param factors prime factors
 * @param size number of prime factors
 * @return prime factors of the number
 */
long* GFNumber::_getPrimeFactors1(const long& num, long *factors, int *size)
{
	long *factorsTemp;

	if(GField::isPrime(num) || num < 2)
	{
		return factors;
	}
	if(num % 2 == 0)
	{

		factors = _directSearchFactorization(num, factors, size);
		return factors;
	}

	long num1 = num, num2 = num;
	long temp = _rhoAlgorithm(num1);
	if (temp == -1)
	{
		factors = _directSearchFactorization(num, factors, size);
		return factors;
	}

	int i = 0;
	while (true)
	{
		factorsTemp = new long[i + 1];
		for (int k = 0; k < i; k++)
		{
			factorsTemp[k] = factors[k];
		}
		delete[] factors;
		factors = factorsTemp;

		factors[i] = temp;
		num2 /= temp;
		i++;
		*size = i;
		if (GField::isPrime(num2))
		{
			factorsTemp = new long[i + 1];
			for (int k = 0; k < i ; k++)
			{
				factorsTemp[k] = factors[k];
			}
			delete[] factors;
			factors = factorsTemp;

			factors[i] = num2;
			*size = i + 1;
			return factors;
		}

		temp = _rhoAlgorithm(num2);
		if (temp == -1)
		{
			factors = _directSearchFactorization(num1, factors, size);


			delete[] factorsTemp;
			return factors;
		}
	}
}

/**
 * Helper function - rho Algorithm
 * @param num a number
 * @return a prime factor of num
 */
long GFNumber::_rhoAlgorithm(const long &num)
{
	long n = num;
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_int_distribution<long> dist(1, n - 2);

	long x = dist(mt), p = 1;
	long y = x;

	while(p == 1)
	{
		x = _f(x);
		y = _f(_f(y));
		p = std::__gcd(labs(x - y), n);
		// p = gcd1(labs(x - y), n);
	}

	if(p == n)
	{
		return -1;
	}
	return p;
}

/**
 * The polinom from rho Algorithm
 * @param x a number
 * @return the value of the polinom x^2 + 1
 */
long GFNumber::_f(const long& x)
{
	return (long)(pow(x, 2) + 1);
}


/**
 * direct search factorization algorithm
 * @param n number
 * @param factors prime factors
 * @param size number of prime factors
 * @return prime factors
 */
long* GFNumber::_directSearchFactorization(long n, long *factors, int *size)
{
	int i = 2, j = 0;

	while (i <= floor(sqrt(n)))
	{
		if(n % i == 0)
		{
			long *newFactors = new long[j + 1];
			for(int k = 0; k < j; k++)
			{
				newFactors[k] = factors[k];
			}
			delete[] factors;
			factors = newFactors;


			factors[j] = i;
			j++;
			n = (long)(n / floor(i));
		}
		else
		{
			i++;
		}
	}
	if(n > 1)
	{
		long *newFactors = new long[j + 1];
		for(int k = 0; k < j; k++)
		{
			newFactors[k] = factors[k];
		}
		delete[] factors;
		factors = newFactors;

		factors[j] = n;
	}
	if(j)
	{
		*size = j + 1;
	}
	return factors;
}






/**
 * Prints prime factors of this number
 */
void GFNumber::printFactors()
{

	GFNumber *primeFactors;
	int size = 0;
	primeFactors = getPrimeFactors(&size);
	std::cout << _n << "=";
	if(size == 0)
	{
		std::cout << _n << "*1" << std::endl;
		delete[] primeFactors;
		return;
	}
	std::cout << primeFactors[0]._n;
	for (int i = 1; i < size; i++)
	{
		std::cout << "*" << primeFactors[i]._n;
	}
	std::cout << std::endl;
	delete[] primeFactors;


}




////////////////////////////////////////   Operators    ///////////////////////////////////////

/**
 * Overload '==' operator to check if two GFNumber objects are equal
 * @param other A number from some field
 * @return True if the numbers are equal. Otherwise, false.
 */
bool GFNumber::operator==(const GFNumber &other)
{
	return (_n == other._n && _gField.getChar() == other.getField().getChar());
}


/**
 * Overload '!=' operator to check if two GFNumbers are not equal
 * @param other A number from some field
 * @return True if the numbers are not equal. Otherwise, returns false.
 */
bool GFNumber::operator!=(const GFNumber &other)
{
	return (_n != other._n || _gField.getChar() != other.getField().getChar());
}


/**
 * Overload '<<' operator from std:cout to print GFNumber object in the format "{n} GF(p**l)"
 * @param out A reference to the output
 * @param gfNumber the number to be printed
 * @return the output containing values of gfNumber
 */
std::ostream& operator<<(std::ostream &out, const GFNumber &gfNumber)
{
	out << gfNumber._n << " GF(" << gfNumber._gField.getChar() << "**" << gfNumber._gField.getDegree() << ")";
	return out;
}


/**
 * Overload '>>' operator from std:cin to receive GFNumber object in the format {n}{GF}
 * @param in A reference to the input
 * @param gfNumber A number in which the input values will be saved
 * @return the input istream
 */
std::istream& operator>>(std::istream &in, GFNumber &gfNumber)
{
	long n, p, l, tempN;
	in >> tempN >> p >> l;

	if(p < 0)
	{
		p *= (-1);
	}
	assert(GField::isPrime(p) && l > 0);

	gfNumber._gField.setChar(p);
	gfNumber._gField.setDegree(l);

	n = (long)fmod(tempN, gfNumber._gField.getOrder());
	if(n < 0)
	{
		n += gfNumber._gField.getOrder();
	}
	gfNumber._n = n;
	return in;
}


/**
 * Overload '=' operator to place one GFNumber into another
 * @param other The GFNumber object to be placed in another GFNumber object
 * @return A reference to this GFNumber object after the other number was placed into it
 */
GFNumber& GFNumber::operator=(const GFNumber &other)
{
	_n = other._n;
	_gField.setChar(other.getField().getChar());
	_gField.setDegree(other.getField().getDegree());
	return *this;
}


/**
 * Overload '+' operator to add two GFNumber objects
 * @param other The right number to be added to the left number
 * @return The result of adding the right number to this (the left) number
 */
GFNumber GFNumber::operator+(const GFNumber &other)
{
	assert(_gField.getOrder() == other.getField().getOrder());
	GFNumber result(_n + other._n, _gField);
	return result;

}


/**
 * Overload '+' operator to add a GFNumber object with a long number
 * @param left A GFNumber object
 * @param right A long number
 * @return The result of addition of the two numbers
 */
GFNumber operator+(const GFNumber& left, const long &right)
{
	return GFNumber(left._n + right, left._gField);
}


/**
 * Overload '+=' operator to add a GFNumber object to this GFNumber object
 * @param other The GFNumber object to be added to this object
 * @return This object with the addition of the other object
 */
GFNumber& GFNumber::operator+=(const GFNumber &other)
{
	assert(_gField.getOrder() == other.getField().getOrder());
	long tempN = _n + other._n;
	_n = tempN % _gField.getOrder();
	if(_n < 0)
	{
		_n += _gField.getOrder();
	}
	return *this;
}

/**
 * Overload '-' operator to subtract two GFNumber objects
 * @param other The right number to be subtracted from the left number
 * @return The result of subtracting the right number from this (the left) number
 */
GFNumber GFNumber::operator-(const GFNumber &other)
{
	assert(_gField.getOrder() == other.getField().getOrder());
	GFNumber result(_n - other._n, _gField);
	return result;

}


/**
 * Overload '-' operator to subtract a long number from a GFNumber object
 * @param left A GFNumber object
 * @param right A long number
 * @return The subtraction of the two numbers
 */
GFNumber operator-(const GFNumber &left, const long &right)
{
	return GFNumber(left._n - right, left._gField);
}


/**
 * Overload '-=' operator to subtract a GFNumber object from this GFNumber object
 * @param other The GFNumber object to be subtracted from this object
 * @return This object with the subtraction of the other object
 */
GFNumber& GFNumber::operator-=(const GFNumber &other)
{
	assert(_gField.getOrder() == other.getField().getOrder());
	long tempN = _n - other._n;
	_n = tempN % _gField.getOrder();
	if(_n < 0)
	{
		_n += _gField.getOrder();
	}
	return *this;
}


/**
 * Overload '-=' operator to subtract a long number from a GFNumber
 * @param left A GFNumber object
 * @param right A long number
 * @return The result of subtraction
 */
GFNumber& operator-=(GFNumber &left, const long &right)
{
	GFNumber rightNum(right, left._gField);
	return left -= rightNum;
}

/**
 * Overload '+=' operator to add a GFNumber object with a long number
 * @param left A GFNumber object
 * @param right A long number
 * @return The result of addition
 */
GFNumber& operator+=(GFNumber &left, const long &right)
{
	GFNumber gfNumber(right, left._gField);
	return left += gfNumber;
}

/**
 * Overload '*' operator to multiply two GFNumber objects
 * @param other The right number to be multiplied with the left number
 * @return The result of multiplying the right number with this (the left) number
 */
GFNumber GFNumber::operator*(const GFNumber &other)
{
	assert(_gField.getOrder() == other.getField().getOrder());
	GFNumber result(_n * other._n, _gField);
	return result;
}


/**
 * Overload '*' operator to multiply a long number with a GFNumber object
 * @param left A GFNumber object
 * @param right A long number
 * @return The multiplication of the two numbers
 */
GFNumber operator*(const GFNumber &left, const long &right)
{
	return GFNumber(left._n * right, left._gField);
}


/**
 * Overload '*=' operator to multiply a GFNumber object with this GFNumber object
 * @param other The GFNumber object to be multiplied by this object
 * @return This object after multiplication by the other GFNumber object
 */
GFNumber& GFNumber::operator*=(const GFNumber &other)
{
	assert(_gField.getOrder() == other.getField().getOrder());
	long tempN = _n * other._n;
	_n = tempN % _gField.getOrder();
	if(_n < 0)
	{
		_n += _gField.getOrder();
	}
	return *this;
}


/**
 * Overload '*=' operator to multiply a GFNumber object with a long number
 * @param left A GFNumber object
 * @param right A long number
 * @return The multiplication result
 */
GFNumber& operator*=(GFNumber &left, const long &right)
{
	GFNumber gfNumber(right, left._gField);
	return left *= gfNumber;
}


/**
 * Overload '%' operator to perform modulo operation of two GFNumber objects
 * @param other The right number
 * @return The result of modulo operation of two GDNumber objects
 */
GFNumber GFNumber::operator%(const GFNumber &other)
{
	assert(_gField.getOrder() == other.getField().getOrder() && other._n != 0);
	GFNumber result(_n % other._n, _gField);
	return result;

}


/**
 * Overload '%=' operator to modulo this GFNumber object with the other GFNumber object
 * @param other The other GFNumber object
 * @return This object modulo the other object
 */
GFNumber& GFNumber::operator%=(const GFNumber &other)
{
	assert((_gField.getOrder() == other.getField().getOrder()) && other._n != 0);
	long tempN = _n % other._n;
	_n = tempN % _gField.getOrder();
	if(_n < 0)
	{
		_n += _gField.getOrder();
	}
	return *this;
}


/**
 * Overload '>=' operator to check if this GFNumber object is bigger or equal to the other
 * GFNumber object
 * @param other The other GFNumber object
 * @return True if this number is bigger or equal to the other number. Otherwise, false.
 */
bool GFNumber::operator>=(const GFNumber &other)
{
	assert(_gField.getOrder() == other.getField().getOrder());
	return _n >= other._n;
}

/**
 * Overload '>' operator to check if this GFNumber object is bigger than other GFNumber object
 * @param other The other GFNumber object
 * @return True if this number is bigger than the other number. Otherwise, false.
 */
bool GFNumber::operator>(const GFNumber &other)
{
	assert(_gField.getOrder() == other.getField().getOrder());
	return _n > other._n;
}

/**
 * Overload '<=' operator to check if this GFNumber object is smaller or equal to the other
 * GFNumber object
 * @param other The other GFNumber object
 * @return True if this number is smaller or equal to the other number. Otherwise, false.
 */
bool GFNumber::operator<=(const GFNumber &other)
{
	assert(_gField.getOrder() == other.getField().getOrder());
	return _n <= other._n;
}

/**
 * Overload '<' operator to check if this GFNumber object is smaller than other GFNumber object
 * @param other The other GFNumber object
 * @return True if this number is smaller than the other number. Otherwise, false.
 */
bool GFNumber::operator<(const GFNumber &other)
{
	assert(_gField.getOrder() == other.getField().getOrder());
	return _n < other._n;
}


