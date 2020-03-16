//
//  math_utils.cpp
//  Ocean
//
//  Created by Sam MAO on 2020-03-08.
//  Copyright © 2020 Sam MAO. All rights reserved.
//

#include "math_utils.hpp"

using namespace math_utils;

Complex::Complex() { 
	this->x_ = 0.0;
	this->y_ = 0.0;
}

Complex::Complex(GLfloat w, GLfloat x) {
	this->x_ = w;
	this->y_ = x;
}

math_utils::Complex Complex::conjugation() { 
	return Complex(this->x_, -this->y_);
}

math_utils::Complex Complex::operator+(const math_utils::Complex &comp) const {
	return Complex(this->x_ + comp.X(), this->y_ + comp.Y());
}

math_utils::Complex Complex::operator-(const math_utils::Complex &comp) const {
	return Complex(this->x_ - comp.X(), this->y_ - comp.Y());
}

math_utils::Complex Complex::operator*(const math_utils::Complex &comp) const {
	return Complex(this->x_*comp.X() - this->y_*comp.Y(), this->x_*comp.Y() + this->y_*comp.X());
}

math_utils::Complex Complex::operator*(const GLfloat scalar) const { 
	return Complex(this->x_* scalar, this->y_ * scalar);
}

math_utils::Complex &Complex::operator=(const math_utils::Complex &comp) { 
	this->x_ = comp.X();
	this->y_ = comp.Y();
	return *this;
}

FFT::FFT(GLuint n):n_(n) {
	stages_ = (GLuint) glm::log2((GLdouble)n_);
	input_vector_.resize(n_);
	this->getInputVector(input_vector_);
	w_table_.resize(stages_);
	this->getRootUnityTable(w_table_);
}

FFT::~FFT() {
	if (!input_vector_.empty())
		input_vector_.clear();
	
	if (!w_table_.empty()) {
		for (int i = 0; i < w_table_.size(); i++) {
			if (!w_table_[i].empty())
				w_table_[i].clear();
		}
	}
}

GLuint FFT::bitReversal(GLuint num) {
	GLuint rev = 0;
	for (int i = 0; i < stages_; i++) {
		if ((num & (1<<i))) {
			rev |= 1 << ((stages_-1) - i);
		}
	}
	return rev;
}

void FFT::getInputVector(vector<GLuint> input) {
	for (int i = 0; i < n_; i++) {
		input.push_back(bitReversal(i));
	}
}

Complex FFT::getRootUnity(GLuint index, GLuint n) {
	GLfloat two_pi = glm::two_pi<GLfloat>();
	// Make cos(pi/2) and sin(pi) equal to 0
	GLfloat x = fabs(cos(two_pi * index / n)) < numeric_limits<GLfloat>::epsilon() ? 0 : cos(two_pi * index / n);
	GLfloat y = fabs(sin(two_pi * index / n)) < numeric_limits<GLfloat>::epsilon() ? 0 : sin(two_pi * index / n);
	return Complex(x, y);
}

void FFT::getRootUnityTable(vector<vector<Complex>>& table) {
	for (int i = 1; i <= stages_; i++) {
		GLint pow_of_2 = pow(2, i);
		vector<Complex> row(pow_of_2);
		for (int j = 0; j < pow_of_2; j++) {
			!j ? row[j] = (this->getRootUnity(j, pow_of_2))
			: row[pow_of_2 - j] = (this->getRootUnity(j, pow_of_2));
		}
		table.push_back(row);
	}
}

void FFT::fft(vector<Complex>& in, vector<Complex>& out, GLint stride, GLint offset) {
	// Bit reverse copy
	vector<Complex> result;
	result.resize(n_);
	for (int i=0; i < n_; i++) {
		result.push_back(in[input_vector_[i]*stride + offset]);
	}
	
	for (int i=0; i < stages_; i++) {
		int m = pow(2, i+1);
		for (int k = 0; k < n_; k += m) {
			for (int j = 0; j < m/2; j++) {
				Complex u = result[k+j];
				Complex t = result[k+j+m/2];
				result[k+j] = u + t*w_table_[i][j];
				result[k+j+m/2] = u + t*w_table_[i][j+m/2];
			}
		}
	}
	
	for (int i = 0; i < n_; i++) {
		out[i*stride + offset] = result[i];
	}
}
