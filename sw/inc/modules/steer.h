/* 
 * This file is part of the uv_hal distribution (www.usevolt.fi).
 * Copyright (c) 2017 Usevolt Oy.
 * 
 * This program is free software: you can redistribute it and/or modify  
 * it under the terms of the GNU General Public License as published by  
 * the Free Software Foundation, version 3.
 *
 * This program is distributed in the hope that it will be useful, but 
 * WITHOUT ANY WARRANTY; without even the implied warranty of 
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU 
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License 
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
*/


#ifndef INC_MODULES_STEER_H_
#define INC_MODULES_STEER_H_

#include <uv_utilities.h>
#include <uv_dual_solenoid_output.h>
#include "input.h"

/// @brief: Boom fold configuration settings. Should be stored in non-volatile memory
typedef struct {
	uv_dual_solenoid_output_conf_st out_conf;
} steer_conf_st;

/// @brief: Resets the non-volatile settings to defaults
void steer_conf_reset(steer_conf_st *this);


typedef struct {
	// input module from the CAN-bus
	input_st input;

	uv_dual_solenoid_output_st out;

	steer_conf_st *conf;

} steer_st;


/// @brief: Initializes the module
void steer_init(steer_st *this, steer_conf_st *conf_ptr);


/// @brief: Step function
void steer_step(steer_st *this, uint16_t step_ms);


static inline int16_t steer_get_current(steer_st *this) {
	return uv_dual_solenoid_output_get_current(&this->out);
}

/// @brief: Step function for the solenoid driver module. Should be called
/// with a smaller step cycle from a higher priority thread than the main module.
static inline void steer_solenoid_step(steer_st *this, uint16_t step_ms) {
	uv_dual_solenoid_output_step(&this->out, step_ms);
}



static inline bool steer_get_active(steer_st *this) {
	return !!uv_dual_solenoid_output_get_target(&this->out);
}



/// @brief: Disables the boom fold module
static inline void steer_disable(steer_st *this) {
	uv_dual_solenoid_output_disable(&this->out);
	this->input.request = 0;
}


/// @brief: Enables the boom fold module
static inline void steer_enable(steer_st *this) {
	uv_dual_solenoid_output_enable(&this->out);
}



#endif /* INC_MODULES_STEER_H_ */
