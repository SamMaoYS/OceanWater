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
	this->cycle_t_ = 200.0f;
	this->freq_w_ = glm::two_pi<GLfloat>() / this->cycle_t_;
	this->fft_x_ = nullptr;
	this->fft_z_ = nullptr;
}

Ocean::Ocean(const glm::ivec2 dim, const glm::vec2 size, const glm::vec2 wind, GLfloat amplitude, GLint repeat) {
	this->gravity_ = 9.80665f;
	this->convergence_ = 0.001f;
	this->cycle_t_ = 200.0f;
	this->freq_w_ = glm::two_pi<GLfloat>() / this->cycle_t_;
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
	this->ocean_vecotrs_.resize((dim_x_)*(dim_z_));
	this->line_indices_.resize((dim_x_)*(dim_z_)*10);
	this->triang_indices_.resize((dim_x_)*(dim_z_)*10);
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
	this->initAmplitude();
	return true;
}

GLfloat Ocean::calPhillips(const glm::vec2 k) {
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
	
	phillips_ = phillips;
	return phillips;
}

GLfloat Ocean::calDispersion(const glm::vec2 k) {
	return floor(sqrt(gravity_*glm::length(k)) / freq_w_) * freq_w_;
}

math_utils::Complex Ocean::calRandomAmplitude(const glm::vec2 k) {
	math_utils::Complex gaussion_random_num = math_utils::getGaussRandomNum();
	math_utils::Complex h0;
	h0 = gaussion_random_num * sqrt(1.0/2.0*calPhillips(k));
	
	return h0;
}

math_utils::Complex Ocean::calAmplitudeAtTime(const glm::vec2 k, GLfloat t) {
	GLfloat real = cos(calDispersion(k)*t);
	GLfloat imagine = sin(calDispersion(k)*t);
	
	math_utils::Complex propagate_left(real, imagine);
	math_utils::Complex propagate_right(real, -imagine);
	
	math_utils::Complex h, h0, h0_conj;
	h0 = calRandomAmplitude(k);
	h0_conj = calRandomAmplitude(-k);
	h = h0*propagate_left + h0_conj.conjugation()*propagate_right;
	
	return h;
}

ocean_struct::ocean_surface Ocean::calAmplitude(const glm::vec2 x, GLfloat t) {
	math_utils::Complex h(0.0f, 0.0f);
	glm::vec2 displace(0.0f);
	glm::vec3 normal(0.0f);
	
	for (GLint m = 0; m < dim_z_; m++) {
		for (GLint n = 0; n < dim_x_; n++) {
			glm::vec2 k(cvtN2Kx(n), cvtM2Kz(m));
			math_utils::Complex h_fourier = calAmplitudeAtTime(k, t) * math_utils::Complex(cos(glm::dot(k, x)), sin(glm::dot(k, x)));
			h += h_fourier;
			// slope of waves, mutiply ik to h for the adding part, since i*i = -1
			// therefore multiply the -1 * imaginary number
			normal += glm::vec3(-k.x*h_fourier.Y(), 0.0f, -k.y*h_fourier.Y());
			if ((glm::length(k) - numeric_limits<GLfloat>::epsilon()) > 0) {
				// displacement of waves, mutiply -ik/|k| to h for the adding part
				displace += glm::vec2(k.x/glm::length(k)*h_fourier.Y(), k.y/glm::length(k)*h_fourier.Y());
			}
		}
	}
	// add the difference to original normal vector
	normal = glm::normalize(glm::vec3(0.0f, 1.0f, 0.0f) - normal);
	ocean_struct::ocean_surface surface;
	surface.displace = displace;
	surface.normal = normal;
	surface.height = h;
	
	return surface;
}

bool Ocean::initAmplitude() {
	glm::vec3 up_norm(0.0f, 1.0f, 0.0f);
	this->ocean_vecotrs_.clear();
	for (GLint m = 0; m < dim_z_; m++) {
		for (GLint n = 0; n < dim_x_; n++) {
			ocean_struct::ocean_vector vertex;
			glm::vec2 k(cvtN2Kx(n), cvtM2Kz(m));
			glm::vec2 x = glm::vec2((n-dim_x_/2)*len_x_/dim_x_, (m-dim_z_/2)*len_z_/dim_z_);
			vertex.normal = up_norm;
			vertex.curr_pos = glm::vec3(x.x, 0.0f, x.y);
			vertex.orig_pos = glm::vec3(x.x, 0.0f, x.y);
			vertex.height_ampl = calRandomAmplitude(k);
			vertex.height_conj = calRandomAmplitude(-k).conjugation();
			this->ocean_vecotrs_.push_back(vertex);
		}
	}
	return true;
}

void Ocean::calOceanWaves(GLfloat t) { 
	GLfloat lamda = -1.0f;
	
	for (GLint m = 0; m < dim_z_; m++) {
		for (GLint n = 0; n < dim_x_; n++) {
			GLint idx = m*dim_x_ + n;
			glm::vec2 x = glm::vec2(ocean_vecotrs_[idx].curr_pos.x, ocean_vecotrs_[idx].curr_pos.z);
			ocean_struct::ocean_surface surface = calAmplitude(x, t);
			
			ocean_vecotrs_[idx].curr_pos.y = surface.height.X();
			ocean_vecotrs_[idx].curr_pos.x = ocean_vecotrs_[idx].orig_pos.x + lamda*surface.displace.x;
			ocean_vecotrs_[idx].curr_pos.z = ocean_vecotrs_[idx].orig_pos.z + lamda*surface.displace.y;
			
			ocean_vecotrs_[idx].normal = surface.normal;
		}
	}
}

void Ocean::calOceanWavesFFT(GLfloat t) { 
	return;
}


