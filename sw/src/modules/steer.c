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





#include "steer.h"
#include "can_ccu.h"
#include "main.h"
#include "pin_mappings.h"
#include "drive.h"


void steer_conf_reset(steer_conf_st *this) {
	this->out_conf.acc = DUAL_SOLENOID_ACC_MAX;
	this->out_conf.dec = DUAL_SOLENOID_DEC_MAX;
	this->out_conf.invert = false;
	this->out_conf.assembly_invert = false;
	this->out_conf.solenoid_conf[DUAL_OUTPUT_SOLENOID_A].max_ma = 1000;
	this->out_conf.solenoid_conf[DUAL_OUTPUT_SOLENOID_A].min_ma = 80;
	this->out_conf.solenoid_conf[DUAL_OUTPUT_SOLENOID_B].max_ma = 1000;
	this->out_conf.solenoid_conf[DUAL_OUTPUT_SOLENOID_B].min_ma = 80;
}


void steer_init(steer_st *this, steer_conf_st *conf_ptr) {
	input_init(&this->input);
	this->conf = conf_ptr;

	uv_dual_solenoid_output_init(&this->out, &conf_ptr->out_conf, STEER_PWMA,
			STEER_PWMB, STEER_SENSE, dev.dither_freq, dev.dither_ampl,
			VND5050_CURRENT_AMPL_UA, SOLENOID_MAX_CURRENT, SOLENOID_FAULT_CURRENT,
			CCU_EMCY_STEER_OVERLOAD_A, CCU_EMCY_STEER_OVERLOAD_B,
			CCU_EMCY_STEER_FAULT_A, CCU_EMCY_STEER_FAULT_B);
}


void steer_step(steer_st *this, uint16_t step_ms) {
	input_step(&this->input, step_ms);

	int16_t req = input_get_request(&this->input, &this->conf->out_conf);
	if (cabrot_get_dir(&dev.cabrot) == CCU_CABDIR_BACKWARD) {
		req *= -1;
	}

	// steering enabled only when driving
	uv_dual_solenoid_output_set(&this->out,
			(input_get_request(&dev.drive.input, &this->conf->out_conf)) ? req : 0);

}

