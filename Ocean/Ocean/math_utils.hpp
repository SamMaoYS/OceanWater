//
//  math_utils.hpp
//  Ocean
//
//  Created by Sam MAO on 2020-03-08.
//  Copyright © 2020 Sam MAO. All rights reserved.
//

#ifndef math_utils_hpp
#define math_utils_hpp

#include "ocean_lib.h"

namespace math_utils {
// Complex Number
class Complex {
public:
	Complex();
	Complex(GLfloat x, GLfloat y);
	~Complex() {}
	
	// Conjugation of complex number x + yi -> x - yi
	Complex conjugation();
	
	// X is the real part, Y is imaginary part of a complex number
	inline GLfloat X() const { return this->x_; }
	inline GLfloat Y() const { return this->y_; }
	
	// Math operation of complex number
	Complex operator+(const Complex & comp) const;
	Complex operator-(const Complex & comp) const;
	Complex operator*(const Complex & comp) const;
	Complex operator*(const GLfloat scalar) const;
	Complex &operator=(const Complex & comp);

private:
	GLfloat x_, y_;
};

// Fast Fourier Transform
class FFT {
public:
	FFT(GLuint n);
	~FFT();
	
	// Reverse a number according to binary bits
	GLuint bitReversal(GLuint num);
	// get the bit reversed input vector
	void getInputVector(vector<GLuint> input);
	// Get the root unity of a complex plane commonly writes as W
	Complex getRootUnity(GLuint x, GLuint y);
	// Get the root unity matrix
	void getRootUnityTable(vector<vector<Complex>>& table);
	// Perform the fast fourier transform
	void fft(vector<Complex>& in, vector<Complex>& out, GLint stride, GLint offset);
	
private:
	// Number of points
	GLuint n_;
	// The number of stages FFT requires which is log2(number of points)
	GLuint stages_;
	// The bit inversed input vector
	vector<GLuint> input_vector_;
	// The table of roots of unity of all the power of 2 input points
	vector<vector<Complex>> w_table_;
};
}

#endif /* math_utils_hpp */
