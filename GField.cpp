#include "GField.h"
#include "GFNumber.h"

////////////////////////////////////////  Constructors & Destructor  //////////////////////////////

/**
 * Default constructor
 */
GField::GField():_p(2), _l(1)
{

}


/**
 * Constructor #1
 * @param p the p value of this field
 */
GField::GField(long p)
{
	assert(p != 0);
	if(p < 0)
	{
		p *= (-1);
	}
	assert(GField::isPrime(p));
	_p = p;
	_l = 1;
}


/**
 * Constructor #2
 * @param p p value of the field
 * @param l l value of the field
 */
GField::GField(long p, const long& l)
{
	assert(p != 0);
	if(p < 0)
	{
		p *= (-1);
	}
	assert(GField::isPrime(p) && l > 0);
	_p = p;
	_l = l;
}


/**
 * Copy constructor
 * @param other another field
 */
GField::GField(const GField &other)
{
	long p = other._p;
	if(p < 0)
	{
		p *= (-1);
	}
	assert(GField::isPrime(p) && other._l > 0);
	_p = p;
	_l = other._l;
}



/**
 * Destructor
 */
GField::~GField()
{

}



////////////////////////////////////////   Class Methods    ///////////////////////////////////////

/**
 * Returns the p value of this field
 * @return p value
 */
const long& GField::getChar() const
{
	return _p;
}

/**
 * Returns the l value of this field
 * @return l value of this field
 */
const long& GField::getDegree() const
{
	return _l;
}

/**
 * Set p value of this field
 * @param p p value
 */
void GField::setChar(const long& p)
{
	assert(isPrime(p));
	_p = p;
}


/**
 * Set l value of this field
 * @param l l value
 */
void GField::setDegree(const long& l)
{
	assert(l > 0);
	_l = l;
}


/**
 * Returns p^l which is the order of this field
 * @return order of this field
 */
const long GField::getOrder() const
{
	return (long)pow(_p, _l);
}


/**
 * Check if the number p is a prime number
 * @param p the number
 * @return true if the number is a prime number
 */
bool GField::isPrime(const long& p)
{


	int size = 0;

	if(p == 2)
	{
		return true;
	}
	if(p < 2 || p % 2 == 0)
	{
		return false;
	}
	long *factors = new long[0];
	factors = _directSearchFactorization(p, factors, &size);
	delete[] factors;
	if(!size)
	{
		return true;
	}

	return false;
}

/**
 * Creates a number in this field with the value k
 * @param k the value of the number
 * @return a GFNumber
 */
GFNumber GField::createNumber(const long& k)
{
	GField gField(_p, _l);
	return GFNumber(k, gField);
}


/**
 * Returns the gcd value of a and b
 * @param a a number
 * @param b a number
 * @return the gcd value number
 */
GFNumber GField::gcd(const GFNumber& a, const GFNumber& b)
{
	assert((a.getField().getOrder() == getOrder()) && (b.getField().getOrder() == getOrder()));
	return createNumber(_gcd(a.getNumber(), b.getNumber()));
}


/**
 * Helper function
 * @param a a number
 * @param b a number
 * @return gcd value of the two numbers
 */
long GField::_gcd(const long& a, const long& b)
{
	assert(a != 0 || b != 0);
	return _gcd11(a, b);
}


/**
 * helper function
 * @param a number
 * @param b number
 * @return gcd of two numbers
 */
long GField::_gcd11(long a, long b)
{
	while(a != b)
	{
		if(a > b)
		{
			a -= b ;
		}
		else
		{
			b -= a;
		}
	}
	return a;
}



/**
 * direct search factorization algorithm
 * @param n number
 * @param factors prime factors
 * @param size number of prime factors
 * @return prime factors
 */
long* GField::_directSearchFactorization(long n, long *factors, int *size)
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


////////////////////////////////////////   Operators    ///////////////////////////////////////

/**
 * Overload '=' operator to place one GField into another
 * @param other The GField object to be placed in another GField object
 * @return A reference to this GField object after the other GField was placed into it
 */
GField& GField::operator=(const GField &other)
{
	_p = other._p;
	_l = other._l;
	return *this;
}


/**
 * Overload '==' operator to check if two GField objects are equal
 * @param other A field
 * @return True if the fields are equal. Otherwise, false.
 */
bool GField::operator==(const GField &other)
{

	return (getOrder() == other.getOrder());
}


/**
 * Overload '!=' operator to check if two GField objects are not equal
 * @param other A field
 * @return True if the fields are not equal. Otherwise, false.
 */
bool GField::operator!=(const GField &other)
{

	return (getOrder() != other.getOrder());
}


/**
 * Overload '<<' operator from std:cout to print GField object in the format "GF({char}**{degree})"
 * @param out A reference to the output
 * @param gField the field to be printed
 * @return the output containing values of gField
 */
std::ostream& operator<<(std::ostream &out, const GField &gField)

{
	out << "GF(" << gField._p << "**" << gField._l << ")";
	return out;
}


/**
* Overload '>>' operator from std:cin to receive GField object in the format {char}{degree}
* @param in A reference to the input
* @param gField A field in which the input values will be saved
* @return the input istream
*/
std::istream& operator>>(std::istream &in, GField &gField)
{
	//I think I should check the values before placing them in the object
	in >> gField._p >> gField._l;
	return in;
}

