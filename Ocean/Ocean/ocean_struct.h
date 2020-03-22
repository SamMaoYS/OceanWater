//
//  ocean_struct.h
//  Ocean
//
//  Created by Sam MAO on 2020-03-08.
//  Copyright © 2020 Sam MAO. All rights reserved.
//

#ifndef ocean_struct_h
#define ocean_struct_h

#include "ocean_lib.h"
#include "math_utils.hpp"

namespace ocean_struct {
struct ocean_vector {
	glm::vec3 curr_pos;
	glm::vec3 orig_pos;
	glm::vec3 normal;
	math_utils::Complex height_ampl;
	math_utils::Complex height_conj;
};
}

#endif /* ocean_struct_h */
