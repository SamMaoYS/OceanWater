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

namespace ocean_struct {
struct ocean_vector {
	glm::vec3 curr_pos;
	glm::vec3 normal;
	glm::vec3 height_ampl;
	glm::vec3 height_conj;
	glm::vec3 orig_pos;
};
}

#endif /* ocean_struct_h */
