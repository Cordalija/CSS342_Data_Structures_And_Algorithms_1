// Jasenko Cordalija, CS342, Complex Numbers, 10/13/2015
// Complex class

#ifndef COMPLEX_H
#define COMPLEX_H
#include <iostream>
using namespace std;

class complex {

	// I/O stream operators
	friend ostream& operator<<(ostream&, const complex&);
	friend istream& operator>>(istream&, complex&);

public:
	complex(double = 0.0, double = 0.0);

	// functions get real and imaginary numbers
	double getReal();
	double getImaginary();

	// math operators +,-,*,/ added
	complex operator+(const complex &) const;  // adds complex
	complex operator-(const complex &) const;  // subtracts complex
	complex operator*(const complex &) const;  // multiples complex
	complex operator/(const complex &) const;  // divides complex

	// conjugate complex number
	complex conjugate() const;

	// comparison operators added to compare object, parameter
	bool operator==(const complex &) const;  // compares if equal
	bool operator!=(const complex &) const;  // compares if not equal

	// assignment operator
	complex& operator+=(const complex &);   // adds 1st object (current) and adds param to it
	complex& operator-=(const complex &);	// subtracts 1st object by the second (param)
	complex& operator*=(const complex &);	// 1st object gets multiplied by second (param)
	complex& operator/=(const complex &);	// 1st object gets divided by second (param)

private:
	double real;			// real of complex as a double
	double imaginary;		// imaginary of a complex as double

};
#endif
