//
//  ocean.cpp
//  Ocean
//
//  Created by Sam MAO on 2020-03-08.
//  Copyright © 2020 Sam MAO. All rights reserved.
//

#include "ocean.hpp"

Ocean::Ocean() {
	this->gravity_ = 9.80665f;
	this->convergence_ = 0.001f;
	this->fft_x_ = nullptr;
	this->fft_z_ = nullptr;
}

Ocean::Ocean(const glm::ivec2 dim, const glm::vec2 size, const glm::vec2 wind, GLfloat amplitude, GLint repeat) {
	this->gravity_ = 9.80665f;
	this->dim_x_ = dim.x;
	this->dim_z_ = dim.y;
	this->len_x_ = size.x;
	this->len_z_ = size.y;
	this->wind_ = wind;
	this->repeat_ = repeat;
	this->ampl_a_ = amplitude;
	this->h_.resize(dim_x_*dim_z_);
	this->h_derivative_x_.resize(dim_x_*dim_z_);
	this->h_derivative_z_.resize(dim_x_*dim_z_);
	this->h_dx_.resize(dim_x_*dim_z_);
	this->h_dz_.resize(dim_x_*dim_z_);
	this->fft_x_ = new math_utils::FFT(dim_x_);
	this->fft_z_ = new math_utils::FFT(dim_z_);
	this->ocean_vecotrs_.resize((dim_x_+1)*(dim_z_+1));
	this->line_indices_.resize((dim_x_+1)*(dim_z_+1)*10);
	this->triang_indices_.resize((dim_x_+1)*(dim_z_+1)*10);
}

Ocean::~Ocean() {
	if (!h_.empty()) {
		h_.clear();
	}
	
	if (!h_derivative_x_.empty()) {
		h_derivative_x_.clear();
	}
	
	if (!h_derivative_z_.empty()) {
		h_derivative_z_.clear();
	}
	
	if (!h_dx_.empty()) {
		h_dx_.clear();
	}
	
	if (!h_dz_.empty()) {
		h_dz_.clear();
	}
	
	if (fft_x_) {
		delete fft_x_;
		fft_x_ = nullptr;
	}
	
	if (fft_z_) {
		delete fft_z_;
		fft_z_ = nullptr;
	}
	
	if (!ocean_vecotrs_.empty()) {
		ocean_vecotrs_.clear();
	}
	
	if (!line_indices_.empty()) {
		line_indices_.clear();
	}
	
	if (!triang_indices_.empty()) {
		triang_indices_.clear();
	}
}

bool Ocean::initialize(const glm::ivec2 dim, const glm::vec2 size, const glm::vec2 wind, GLfloat amplitude, GLint repeat) {
	*this = Ocean(dim, size, wind, amplitude, repeat);
	return true;
}

GLfloat Ocean::getPhillips(GLint n, GLint m) { 
	glm::vec2 k = glm::vec2((GLfloat)n*glm::two_pi<GLfloat>()/len_x_,(GLfloat)m*glm::two_pi<GLfloat>()/len_z_);
	if (glm::length(k) < numeric_limits<GLfloat>::epsilon()) {
		return 0;
	}
	
	GLfloat k_dot_wind = glm::dot(glm::normalize(k), glm::normalize(wind_));
	GLfloat k_square = glm::dot(k, k);
	GLfloat k_quad = pow(k_square, 2.0);
	GLfloat speed = glm::length(wind_);
	GLfloat largest_height = pow(speed, 2.0) / gravity_;
	GLfloat largest_height_square = pow(largest_height, 2.0);
	GLfloat convergence_factor = exp(-k_square*largest_height_square*pow(convergence_, 2.0));
	GLfloat phillips = ampl_a_*exp(-1.0/(k_square*largest_height_square))/k_quad*pow(k_dot_wind, 2.0)*convergence_factor;
	
	return phillips;
}




