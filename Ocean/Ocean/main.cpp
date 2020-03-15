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
	math_utils::FFT fft(8);
	GLuint a = fft.bitReversal(1);
	
	vector<vector<math_utils::Complex>> comp;
	fft.getRootUnityTable(comp);
	for (int i = 0; i<3; i++) {
		for (int j = 0; j<pow(2, i+1); j++) {
			cout<<comp[i][j].X() << "  ";
			cout<<comp[i][j].Y() << endl;
		}
		cout << "------------"<<endl;
	}
	cout << sin(glm::pi<GLfloat>());
	cout << a;
	return 0;
}
