//
//  main.cpp
//  Ocean
//
//  Created by Sam MAO on 2020-03-08.
//  Copyright © 2020 Sam MAO. All rights reserved.
//

#include <iostream>
#include "ocean.hpp"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

#define TEST_MATHUTILS 0
#define TEST_OCEAN 1
#define TEST_PHILLIPS 1
#define TEST_GUASSIANRANDOM 1
#define TEST_OPENCV 1

int main(int argc, const char * argv[]) {
	// Test code
#if TEST_MATHUTILS
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
#endif
	
#if TEST_OCEAN
	Ocean* ocean = new Ocean();
	glm::ivec2 dim = glm::ivec2(100, 150);
	glm::vec2 size = glm::vec2(200.0f, 300.0f);
	glm::vec2 wind = glm::vec2(20.0f, 10.0f);
	ocean->initialize(dim, size, wind, 2, 2);
	
	glm::vec2 k(0.5, 2);
	math_utils::Complex h = ocean->calAmplitudeAtTime(k, 2);
	
	cout << ocean->getDimension().x << endl;
	cout << ocean->getSize().x << endl;
	cout << h.X() << endl;
	cout << glm::length(wind) << endl;
#endif
	
#if TEST_PHILLIPS
	cout << ocean->calPhillips(glm::vec2(60, 70)) << endl;
	math_utils::Complex random_1 = math_utils::getGaussRandomNum();
	cout << random_1.X() << "  " << random_1.Y() << endl;
	math_utils::Complex random_2 = math_utils::getGaussRandomNum();
	cout << random_2.X() << "  " << random_2.Y() << endl;
	math_utils::Complex random_3 = math_utils::getGaussRandomNum();
	cout << random_3.X() << "  " << random_3.Y() << endl;
#endif
	
#if TEST_OPENCV
	cv::Mat img(500, 500, CV_8UC1, cv::Scalar::all(0));
	
	cv::namedWindow("Display window", cv::WINDOW_AUTOSIZE);
    cv::imshow("Display window", img);
	cv::waitKey(0);
#endif
	
	return 0;
}
