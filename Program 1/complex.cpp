// Jasenko Cordalija, CS342, Complex Numbers, 10/13/2015
// Complex class

#include "complex.h"

//----------------- Complex Constructor--------------------
// Constructors for 0, 1, 2 arguments/ parameters

complex::complex(double r, double i) {		// real and imaginary specified
	real = r;
	imaginary = i;
}

//----------------- Get Real & Get Imaginary---------------

double complex::getReal() {					// gets the real of complex number
	return real;
}

double complex::getImaginary() {			// gets the imaginary number of a complex
	return imaginary;
}

//----------------- Math Operator Overload -----------------
//----------------- Operator Overload + --------------------
// Overloads (+) for addition of 2 complex numbers

complex complex::operator+(const complex& a) const {	// adds complex numbers and returns answer
	complex sum;

	sum.real = (real + a.real);
	sum.imaginary = (imaginary + a.imaginary);

	return sum;											
}

//----------------- Operator Overload - -------------------
// Overloads (-) for subtraction of 2 complex numbers

complex complex::operator-(const complex& s) const {	// subtracts complex numbers and returns answer
	complex sub;

	sub.real = (real - s.real);
	sub.imaginary = (imaginary - s.imaginary);

	return sub;											
}

//----------------- Operator Overload * --------------------
// Overloads (*) for multipling of 2 complex numbers

complex complex::operator*(const complex& m) const {	// multiplies complex numbers and returns answer
	complex mult;

	// 2 imaginary numbers equal negative real so subtraction is required
	mult.real = ((real * m.real) - (imaginary * m.imaginary));
	mult.imaginary = ((real * m.imaginary) + (imaginary * m.real));

	return mult;
}

//----------------- Operator Overload / -------------------
// Overloads (/) for dividing of 2 complex numbers

complex complex::operator/(const complex& d) const {	// divides complex numbers
	complex div;

	if (d.real == 0 && d.imaginary == 0) {			// Number IS undefined, but will return 0 for clarity
		return 0;
	}
	else 
	{
		div.real = (((real * d.real) + (imaginary * d.imaginary)) / ((d.real * d.real) + (d.imaginary * d.imaginary)));
		div.imaginary = (((imaginary * d.real) - (real * d.imaginary)) / ((d.real * d.real) + (d.imaginary * d.imaginary)));
	}
	return div;
}

//----------------- Implementing Conjugate -----------------
// Returns conjugate of inputed complex number

complex complex::conjugate() const {
	complex conj;

	conj.real = real;
	conj.imaginary = -imaginary;	// if imaginary is negative give positive and vice-versa

	return conj;
}

//---------------- Implementing Comparison -----------------
// Compares if complex numbers are equal or not returns true/false
//---------------- Operator == -----------------------------
// Compares if 2 complex numbers are equal

bool complex::operator==(const complex& c) const {

	return (real == c.real && imaginary == c.imaginary);
}

//---------------- Operator != -----------------------------
// Compers if 2 complex numbers are not equal

bool complex::operator!=(const complex& c) const {

	return (real != c.real || imaginary != c.imaginary);
}

//---------------- Assignment Operator Overload ------------
//---------------- Operator += -----------------------------
// Adds one complex number or integer to the other 

complex& complex::operator+=(const complex& c) { // because of & it causes per changes to the one on the right

	real = real + c.real;
	imaginary = imaginary + c.imaginary;

	return *this;
}

//--------------- Operator -= ------------------------------
// Subtracts one complex number or integer to the other

complex& complex::operator-=(const complex& c) {

	real = real - c.real;
	imaginary = imaginary - c.imaginary;

	return *this;
}

//--------------- Operator *= ------------------------------
// Multiplies one complex number or integer by the other

complex& complex::operator*=(const complex& c) {

	double temp = ((real * c.real) - (imaginary * c.imaginary));
	imaginary = ((real * c.imaginary) + (imaginary * c.real));
	real = temp;

	return *this;
}

//--------------- Operator /= ------------------------------
// Divides one complex number or integer by the other

complex& complex::operator/=(const complex& c) {
	double temp;
	
	// assumption, if 0 says its undefined then gives exact question and answer of 0
	if (c.real == 0 && c.imaginary == 0) {		
		cout << "Number undefined, " ;
	}
	else {
		temp = (((real * c.real) + (imaginary * c.imaginary)) / ((c.real * c.real) + (c.imaginary * c.imaginary)));
		imaginary = (((imaginary * c.real) - (real * c.imaginary)) / ((c.real * c.real) + (c.imaginary * c.imaginary)));
		real = temp;

		return *this;
	}
}

//--------------- Input and Output stream-------------------------
//------------------------ overload>> ----------------------------
// Operator >> overload (input), allows for input of complex numbers

istream& operator>>(istream &input, complex &c) {
	input >> c.real;
	input >> c.imaginary;

	return input;
}

//------------------------- overload<< -------------------------
// Operator << overload (output), outputs of complex numbers

ostream& operator<<(ostream &output, const complex &c) {

	if (c.real == 0 && c.imaginary == 0) {	// returns 0 if both are 0
		output << 0;
	}
	else if (c.real == 0 && c.imaginary == -1) { // this code and below gives 1 a i only without the 1 infront
		output << "-" << "i";
	}
	else if (c.real == 0 && c.imaginary == 1) {
		output << "i";
	}
	else if (c.real == 0) {					// assumption if real is 0 not to display it, only display imaginary
		output << c.imaginary << "i";
	}
	else if (c.real != 0 && c.imaginary == 0) {
		output << c.real;
	}
	else if (c.real != 0 && c.imaginary == 1) { // this code and below check for + vs - 1 to give only i
		output << c.real << "+" << "i";
	}
	else if (c.real != 0 && c.imaginary == -1) {
		output << c.real << "-" << "i";
	}
	else if (c.real != 0 && c.imaginary > 0) {	// this code and below check for + vs - imaginary number
		output << c.real << "+" << c.imaginary << "i";
	}
	else if (c.real != 0 && c.imaginary < 0) {
		output << c.real << c.imaginary << "i";
	}

	return output;

}

//-------------------------------------------------------------------


