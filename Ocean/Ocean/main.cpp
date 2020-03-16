//
//  main.cpp
//  Ocean
//
//  Created by Sam MAO on 2020-03-08.
//  Copyright © 2020 Sam MAO. All rights reserved.
//

#include <iostream>
#include "ocean_struct.h"
#include "math_utils.hpp"

int main(int argc, const char * argv[]) {
	// Test code
	int fs = 1000;
	GLfloat period = 1.0/(GLfloat) fs;
	int len = 8;
	vector<math_utils::Complex> t;
	
	for (int i=0; i<len; i++) {
		math_utils::Complex temp(0.7*sin(2*glm::pi<GLfloat>()*50*period*i)+sin(2*glm::pi<GLfloat>()*120*period*i), 0);
		t.push_back(temp);
	}
	
	vector<math_utils::Complex> out;
	out.resize(len);
	math_utils::FFT fourier(len);
	fourier.fft(t, out, 1, 0);
	
	return 0;
}
