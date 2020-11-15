#ifndef EX1_GFNUMBER_H
#define EX1_GFNUMBER_H
#include "GField.h"
#include <cmath>
#include <iostream>

class GField;

/**
 * This class represents a number in a field
 */
class GFNumber
{

public:

	////////////////////////////////////  Constructors & Destructor  //////////////////////////////
	/**
	 * Default constructor
	 */
	GFNumber();

	/**
	 * Constructor #1
     * @param n A number in the 2 ^ 1 order field
	 */
	GFNumber(const long &n);

	/**
     * Constructor #2
     * @param n A number in the given field
     * @param field A field
     */
	GFNumber(const long &n, const GField &field);

	/**
	 * Copy constructor
	 * @param other Another field
	 */
	GFNumber(const GFNumber& other);

	/**
	 * Destructor
	 */
	~GFNumber();


	////////////////////////////////////   Class Methods    ///////////////////////////////////////

	/**
	 * Function returns the value of the number represented by this class
	 * @return value of the number represented by this class
	 */
	const long& getNumber() const;

	/**
	 * Function returns the field of this number
	 * @return field of this number
	 */
	const GField& getField() const;


	/**
     * Returns prime factors of this number
     * @param size number of prime factors
     * @return prime numbers of this number
     */
	GFNumber* getPrimeFactors(int *size);

	/**
	 * Prints prime factors of this number
	 */
	void printFactors();

	/**
	 * Check if this number is prime
	 * @return true if this number is prime
	 */
	bool getIsPrime();







	///////////////////////////////////   Operators   /////////////////////////////////////////////


	/**
     * Overload '=' operator to place one GFNumber into another
     * @param other The GFNumber object to be placed in another GFNumber object
     * @return A reference to this GFNumber object after the other number was placed into it
     */
	GFNumber& operator=(const GFNumber& other);

    /**
     * Overload '+' operator to add two GFNumber objects
     * @param other The right number to be added to the left number
     * @return The result of adding the right number to this (the left) number
     */
	GFNumber operator+(const GFNumber& other);

	/**
     * Overload '+' operator to add a GFNumber object with a long number
     * @param left A GFNumber object
     * @param right A long number
     * @return The result of addition of the two numbers
     */
	friend GFNumber operator+(const GFNumber& left, const long& right);

	/**
     * Overload '+=' operator to add a GFNumber object to this GFNumber object
     * @param other The GFNumber object to be added to this object
     * @return This object with the addition of the other object
     */
	GFNumber& operator+=(const GFNumber& other);


    /**
     * Overload '+=' operator to add a GFNumber object with a long number
     * @param left A GFNumber object
     * @param right A long number
     * @return The result of addition
     */
	friend GFNumber& operator+=(GFNumber &left, const long &right);

	/**
     * Overload '-' operator to subtract two GFNumber objects
     * @param other The right number to be subtracted from the left number
     * @return The result of subtracting the right number from this (the left) number
     */
	GFNumber operator-(const GFNumber& other);


    /**
     * Overload '-' operator to subtract a long number from a GFNumber object
     * @param left A GFNumber object
     * @param right A long number
     * @return The subtraction of the two numbers
     */
	friend GFNumber operator-(const GFNumber& left, const long &right);

	/**
     * Overload '-=' operator to subtract a GFNumber object from this GFNumber object
     * @param other The GFNumber object to be subtracted from this object
     * @return This object with the subtraction of the other object
     */
	GFNumber& operator-=(const GFNumber& other);


    /**
     * Overload '-=' operator to subtract a long number from a GFNumber
     * @param left A GFNumber object
     * @param right A long number
     * @return The result of subtraction
     */
	friend GFNumber& operator-=(GFNumber &left, const long &right);

    /**
     * Overload '*' operator to multiply two GFNumber objects
     * @param other The right number to be multiplied with the left number
     * @return The result of multiplying the right number with this (the left) number
     */
	GFNumber operator*(const GFNumber& other);

	/**
     * Overload '*' operator to multiply a long number with a GFNumber object
     * @param left A GFNumber object
     * @param right A long number
     * @return The multiplication of the two numbers
     */
	friend GFNumber operator*(const GFNumber& left, const long &right);

	/**
     * Overload '*=' operator to multiply a GFNumber object with this GFNumber object
     * @param other The GFNumber object to be multiplied by this object
     * @return This object after multiplication by the other GFNumber object
     */
	GFNumber& operator*=(const GFNumber& other);

	/**
     * Overload '*=' operator to multiply a GFNumber object with a long number
     * @param left A GFNumber object
     * @param right A long number
     * @return The multiplication result
     */
	friend GFNumber& operator*=(GFNumber &left, const long &right);


    /**
     * Overload '%' operator to perform modulo operation of two GFNumber objects
     * @param other The right number
     * @return The result of modulo operation of two GDNumber objects
     */
	GFNumber operator%(const GFNumber& other);

    /**
     * Overload '%=' operator to modulo this GFNumber object with the other GFNumber object
     * @param other The other GFNumber object
     * @return This object modulo the other object
 	 */
    GFNumber& operator%=(const GFNumber& other);

	/**
     * Overload '==' operator to check if two GFNumber objects are equal
     * @param other A number from some field
     * @return True if the numbers are equal. Otherwise, false.
     */
	bool operator==(const GFNumber& other);


    /**
     * Overload '!=' operator to check if two GFNumbers are not equal
     * @param other A number from some field
     * @return True if the numbers are not equal. Otherwise, returns false.
     */
	bool operator!=(const GFNumber& other);


	/**
     * Overload '<' operator to check if this GFNumber object is smaller than other GFNumber object
     * @param other The other GFNumber object
     * @return True if this number is smaller than the other number. Otherwise, false.
     */
	bool operator<(const GFNumber& other);


    /**
     * Overload '>' operator to check if this GFNumber object is bigger than other GFNumber object
     * @param other The other GFNumber object
     * @return True if this number is bigger than the other number. Otherwise, false.
     */
	bool operator>(const GFNumber& other);

	/**
     * Overload '<=' operator to check if this GFNumber object is smaller or equal to the other
     * GFNumber object
     * @param other The other GFNumber object
     * @return True if this number is smaller or equal to the other number. Otherwise, false.
     */
	bool operator<=(const GFNumber& other);

	/**
     * Overload '>=' operator to check if this GFNumber object is bigger or equal to the other
     * GFNumber object
     * @param other The other GFNumber object
     * @return True if this number is bigger or equal to the other number. Otherwise, false.
     */
	bool operator>=(const GFNumber& other);

    /**
     * Overload '<<' operator from std:cout to print GFNumber object in the format "{n} GF(p**l)"
     * @param out A reference to the output
     * @param gfNumber the number to be printed
     * @return the output containing values of gfNumber
     */
	friend std::ostream& operator<<(std::ostream &out, const GFNumber &gfNumber);

    /**
     * Overload '>>' operator from std:cin to receive GFNumber object in the format {n}{GF}
     * @param in A reference to the input
     * @param gfNumber A number in which the input values will be saved
     * @return the input istream
     */
	friend std::istream& operator>>(std::istream &in, GFNumber &gfNumber);


private:

	long _n;             // the value of the number
	GField _gField;      // the field of the number

	/**
     * direct search factorization algorithm
     * @param n number
     * @param factors prime factors
     * @param size number of prime factors
     * @return prime factors
     */
	long* _directSearchFactorization(long n, long *factors, int *size);

	/**
	 * A helper function
	 * @param n number
	 * @param factors prime factors
	 * @param size number of prime factors
	 * @return prime factors of the number
	 */
	long* _getPrimeFactors1(const long &n, long *factors, int *size);

    /**
     * Helper function - rho Algorithm
     * @param num a number
     * @return a prime factor of num
     */
	long _rhoAlgorithm(const long &n);

	/**
     * The polinom from rho Algorithm
     * @param x a number
     * @return the value of the polinom x^2 + 1
     */
	long _f(const long& x);


};


#endif //EX1_GFNUMBER_H
