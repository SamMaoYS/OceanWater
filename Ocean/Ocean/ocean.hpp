//
//  ocean.hpp
//  Ocean
//
//  Created by Sam MAO on 2020-03-08.
//  Copyright © 2020 Sam MAO. All rights reserved.
//

#ifndef ocean_hpp
#define ocean_hpp

#include "ocean_struct.h"
#include "math_utils.hpp"

class Ocean {
public:
	Ocean();
	Ocean(const glm::ivec2 dim, const glm::vec2 size, const glm::vec2 wind, GLfloat amplitude, GLint repeat);
	~Ocean();
	
	// Initialize the parameters of the ocean
	bool initialize(const glm::ivec2 dim, const glm::vec2 size, const glm::vec2 wind, GLfloat amplitude, GLint repeat);
	
	// Compute the phillips spectrum
	GLfloat getPhillips(GLint n, GLint m);
	
	inline glm::ivec2 getDimension() {
		return glm::ivec2(dim_x_, dim_z_);
	}
	
	inline glm::vec2 getSize() {
		return glm::vec2(len_x_, len_z_);
	}
	
private:
	// The dimensions of the ocean plane
	GLint dim_x_;
	GLint dim_z_;
	
	// The size of the ocean plane
	GLfloat len_x_;
	GLfloat len_z_;
	
	// Phillips spectrum simulate wind effect on wave movement
	GLfloat phillips_;
	// Vector of wind
	glm::vec2 wind_;
	// The amplitude of waves
	GLfloat ampl_a_;
	// Animation of water surface loops after a time t
	GLfloat cycle_t_;
	// The basic frequence w = 2*pi / t
	GLfloat freq_w_;
	// Accelerate the convergence of phillips spectrum when wave number is large
	GLfloat convergence_;
	
	// The number of ocean copies along one dimension
	GLint repeat_;
	
	// Thr gravity default 9.80665 m/s^2
	GLfloat gravity_;
	
	// Fourier amplitudes of the wave field
	vector<math_utils::Complex> h_;
	vector<math_utils::Complex> h_derivative_x_;
	vector<math_utils::Complex> h_derivative_z_;
	vector<math_utils::Complex> h_dx_;
	vector<math_utils::Complex> h_dz_;
	
	// Fast Fourier transform
	math_utils::FFT* fft_x_;
	math_utils::FFT* fft_z_;
	
	// The structure of ocean surface
	vector<ocean_struct::ocean_vector> ocean_vecotrs_;
	// Indices for vertices of ocean surface
	vector<GLuint> line_indices_;
	vector<GLuint> triang_indices_;
};

#endif /* ocean_hpp */
