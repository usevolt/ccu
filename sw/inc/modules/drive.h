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


#ifndef INC_MODULES_DRIVE_H_
#define INC_MODULES_DRIVE_H_

#include <uv_utilities.h>
#include <uv_dual_solenoid_output.h>
#include "input.h"
#include "can_ccu.h"

/// @brief: Boom fold configuration settings. Should be stored in non-volatile memory
typedef struct {
	uv_dual_solenoid_output_conf_st gear_conf[CCU_GEAR_COUNT];
} drive_conf_st;

/// @brief: Resets the non-volatile settings to defaults
void drive_conf_reset(drive_conf_st *this);


#define DRIVE_FOOT_DOWN_DELAY_MS		1000

typedef struct {
	// input module from the CAN-bus
	input_st input;

	// output for only 1st gear
	uv_dual_solenoid_output_st out1;

	// output for all other gears
	uv_dual_solenoid_output_st out2;

	// inhibit delay for sending emcy messages when driving foot down
	uv_delay_st foot_down_emcy_delay;

	// output for brake
	uv_output_st brake;

	ccu_gear_e gear;

	drive_conf_st *conf;

} drive_st;


/// @brief: Initializes the module
void drive_init(drive_st *this, drive_conf_st *conf_ptr);


/// @brief: Step function
void drive_step(drive_st *this, uint16_t step_ms);


static inline int16_t drive_get_current1(drive_st *this) {
	return uv_dual_solenoid_output_get_current(&this->out1);
}

static inline int16_t drive_get_current2(drive_st *this) {
	return uv_dual_solenoid_output_get_current(&this->out2);
}

/// @brief: Step function for the solenoid driver module. Should be called
/// with a smaller step cycle from a higher priority thread than the main module.
static inline void drive_solenoid_step(drive_st *this, uint16_t step_ms) {
	uv_dual_solenoid_output_step(&this->out1, step_ms);
	uv_dual_solenoid_output_step(&this->out2, step_ms);
	uv_output_step(&this->brake, step_ms);
}


static inline void drive_set_request(drive_st *this, int8_t value) {
	this->input.request = value;
}


/// @brief: Disables the boom fold module
static inline void drive_disable(drive_st *this) {
	uv_dual_solenoid_output_disable(&this->out1);
	uv_dual_solenoid_output_disable(&this->out2);
}


/// @brief: Enables the boom fold module
static inline void drive_enable(drive_st *this) {
	uv_dual_solenoid_output_enable(&this->out1);
	uv_dual_solenoid_output_enable(&this->out2);
}



#endif /* INC_MODULES_DRIVE_H_ */
