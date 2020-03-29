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
	glm::ivec2 dim = glm::ivec2(64, 64);
	glm::vec2 size = glm::vec2(320.0f, 320.0f);
	glm::vec2 wind = glm::vec2(0.0f, 12.8f);
	ocean->initialize(dim, size, wind, 0.005, 1);
	ocean->calOceanWaves(1.0);
	
#endif
	
#if TEST_OPENCV
	cv::Mat img(150, 150, CV_32FC1, cv::Scalar::all(0));
	vector<ocean_struct::ocean_vector> ocean_vector;
	ocean_vector = ocean->getOceanVector();
	float min = numeric_limits<float>::max();
	float max = -numeric_limits<float>::max();
	for (int i = 0; i<dim.x; i++) {
		for (int j=0; j<dim.y; j++) {
			int idx = i*dim.y+j;
			int x, y;
			
				x = (int) (ocean_vector[idx].curr_pos.x / 320.0 * 64 + 150/2);
			
			
				y = (int) (ocean_vector[idx].curr_pos.z / 320.0 * 64 + 150/2);
			
			float intensity = log(ocean_vector[idx].curr_pos.y);
			if (intensity < min) {
				min = intensity;
			}
			if (intensity > max) {
				max = intensity;
			}
			img.at<float>(x, y) = log(ocean_vector[idx].curr_pos.y);
		}
	}
	
	cv::Mat result;
	float scale = 255.0 / max - min;
	img.convertTo(result, CV_8UC1, scale, -min*scale);
	cv::namedWindow("Display window", cv::WINDOW_AUTOSIZE);
    cv::imshow("Display window", result);
	cv::waitKey(0);
#endif
	
	return 0;
}
