#ifndef EX1_GFIELD_H
#define EX1_GFIELD_H

#include <iostream>
#include <cassert>
#include <cmath>
#include <random>




class GFNumber;

/**
 * This class represents a field
 */
class GField
{

public:


	////////////////////////////////////  Constructors & Destructor  //////////////////////////////
	/**
	 * Default constructor
	 */
	GField();

	/**
	 * Constructor #1
	 * @param p the p value of this field
	 */
	GField(long p);

	/**
	 * Constructor #2
	 * @param p p value of the field
	 * @param l l value of the field
	 */
	GField(long p, const long& l);

	/**
	 * Copy constructor
	 * @param other another field
	 */
	GField(const GField& other);

	/**
	 * Destructor
	 */
	~GField();


	////////////////////////////////////   Class Methods    ///////////////////////////////////////

	/**
	 * Returns the p value of this field
	 * @return p value
	 */
	const long& getChar() const;

	/**
	 * Set p value of this field
	 * @param p p value
	 */
	void setChar(const long& p);

	/**
	 * Returns the l value of this field
	 * @return l value of this field
	 */
	const long& getDegree() const;

	/**
	 * Set l value of this field
	 * @param l l value
	 */
	void setDegree(const long& l);

	/**
	 * Returns p^l which is the order of this field
	 * @return order of this field
	 */
	const long getOrder() const;

	/**
	 * Check if the number p is a prime number
	 * @param p the number
	 * @return true if the number is a prime number
	 */
	static bool isPrime(const long& p);

	/**
	 * Creates a number in this field with the value k
	 * @param k the value of the number
	 * @return a GFNumber
	 */
	GFNumber createNumber(const long& k);


	/**
	 * Returns the gcd value of a and b
	 * @param a a number
	 * @param b a number
	 * @return the gcd value number
	 */
	GFNumber gcd(const GFNumber& a, const GFNumber& b);




	///////////////////////////////////   Operators   /////////////////////////////////////////////

	/**
     * Overload '=' operator to place one GField into another
     * @param other The GField object to be placed in another GField object
     * @return A reference to this GField object after the other GField was placed into it
     */
	GField& operator=(const GField& other);

	/**
     * Overload '==' operator to check if two GField objects are equal
     * @param other A field
     * @return True if the fields are equal. Otherwise, false.
     */
	bool operator==(const GField& other);

	/**
     * Overload '!=' operator to check if two GField objects are not equal
     * @param other A field
     * @return True if the fields are not equal. Otherwise, false.
     */
	bool operator!=(const GField& other);

	/**
     * Overload '<<' operator from std:cout to print GField object in the format "GF({char}**{degree})"
     * @param out A reference to the output
     * @param gField the field to be printed
     * @return the output containing values of gField
     */
	friend std::ostream& operator<<(std::ostream &out, const GField &gField);

	/**
   * Overload '>>' operator from std:cin to receive GField object in the format {char}{degree}
   * @param in A reference to the input
   * @param gField A field in which the input values will be saved
   * @return the input istream
   */
	friend std::istream& operator>>(std::istream &in, GField &gField);


private:

	long _p;  // char of this field

	long _l;  // degree of this field

	/**
     * direct search factorization algorithm
     * @param n number
     * @param factors prime factors
     * @param size number of prime factors
     * @return prime factors
     */
	static long* _directSearchFactorization(long n, long *factors, int *size);

	/**
     * Helper function
     * @param a a number
     * @param b a number
     * @return gcd value of the two numbers
     */
	long _gcd(const long& a, const long& b);

	/**
	 * helper function
	 * @param a number
	 * @param b number
	 * @return gcd of two numbers
	 */
	long _gcd11(long a, long b);
};

#endif //EX1_GFIELD_H
