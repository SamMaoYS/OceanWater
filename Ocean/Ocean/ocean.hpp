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

class Ocean {
public:
	Ocean();
	Ocean(const glm::ivec2 dim, const glm::vec2 size, const glm::vec2 wind, GLfloat amplitude, GLint repeat);
	~Ocean();
	
	// Initialize the parameters of the ocean
	bool initialize(const glm::ivec2 dim, const glm::vec2 size, const glm::vec2 wind, GLfloat amplitude, GLint repeat);
	// Initialize the amplitude of the ocean
	bool initAmplitude();
	
	inline GLfloat cvtN2Kx(const GLint n) {
		return glm::two_pi<GLfloat>() * (GLfloat)(n - dim_x_/2.0) / len_x_;
	}
	
	inline GLfloat cvtM2Kz(const GLint m) {
		return glm::two_pi<GLfloat>() * (GLfloat)(m - dim_x_/2.0) / len_z_;
	}
	
	inline glm::vec2 cvtNM2K(const GLint n, const GLint m) {
		return glm::vec2(cvtN2Kx(n), cvtM2Kz(m));
	}
	
	// Calculate the phillips spectrum
	GLfloat calPhillips(const glm::vec2 k);
	
	// Calculate the dispersion relation for animating the waves
	GLfloat calDispersion(const glm::vec2 k);
	
	// Calculate the Fourier amplitudes of a wave height field
	math_utils::Complex calRandomAmplitude(const glm::vec2 k);
	// Calculate Fourier amplitudes of the wave field realization at time t with dispersion
	math_utils::Complex calAmplitudeAtTime(const glm::vec2 k, GLfloat t);
	// Calculate complex, time-dependent amplitudesn at horizontal position x = (x, z)
	ocean_struct::ocean_surface calAmplitude(const glm::vec2 x, GLfloat t);
	
	void calOceanWaves(GLfloat t);
	void calOceanWavesFFT(GLfloat t);
	
	inline void setCycleTime(const GLfloat t) {
		this->cycle_t_ = t;
	}
	
	inline glm::ivec2 getDimension() {
		return glm::ivec2(dim_x_, dim_z_);
	}
	
	inline glm::vec2 getSize() {
		return glm::vec2(len_x_, len_z_);
	}
	
	inline vector<ocean_struct::ocean_vector> getOceanVector() {
		return this->ocean_vecotrs_;
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
