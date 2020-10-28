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





#include "cabrot.h"
#include "can_ccu.h"
#include "main.h"
#include "pin_mappings.h"
#include "drive.h"
#include <uv_eeprom.h>


void cabrot_conf_reset(cabrot_conf_st *this) {

	this->out_conf.acc = 60;
	this->out_conf.dec = 60;
	this->out_conf.invert = false;
	this->out_conf.assembly_invert = true;
	this->out_conf.solenoid_conf[DUAL_OUTPUT_SOLENOID_A].min_ma = 600;
	this->out_conf.solenoid_conf[DUAL_OUTPUT_SOLENOID_A].max_ma = 900;
	this->out_conf.solenoid_conf[DUAL_OUTPUT_SOLENOID_B].min_ma = 600;
	this->out_conf.solenoid_conf[DUAL_OUTPUT_SOLENOID_B].max_ma = 900;
}


void cabrot_init(cabrot_st *this, cabrot_conf_st *conf_ptr) {
	input_init(&this->input);
	this->conf = conf_ptr;
	this->state = CABROT_STATE_OFF;
	uv_eeprom_read(&this->dir, sizeof(this->dir), CABDIR_EEPROM_ADDR);
	if (this->dir >= CCU_CABDIR_COUNT) {
		this->dir = CCU_CABDIR_BACKWARD;
	}

	uv_dual_solenoid_output_init(&this->out, &conf_ptr->out_conf, CABROT_PWMA,
			CABROT_PWMB, CABROT_SENSE, dev.dither_freq, dev.dither_ampl,
			VND5050_CURRENT_AMPL_UA, SOLENOID_MAX_CURRENT, SOLENOID_FAULT_CURRENT,
			CCU_EMCY_CABROT_OVERLOAD_A, CCU_EMCY_CABROT_OVERLOAD_B,
			CCU_EMCY_CABROT_FAULT_A, CCU_EMCY_CABROT_FAULT_B);

	uv_output_init(&this->cabbrake, CABBRAKE_SENSE, CABBRAKE_OUT, VND5050_CURRENT_AMPL_UA,
			4000, 6000, 20, 0, 0);
	uv_output_set_state(&this->cabbrake, OUTPUT_STATE_OFF);
}


void cabrot_step(cabrot_st *this, uint16_t step_ms) {
	if (dev.assembly.cabrot_installed) {
		input_step(&this->input, step_ms);

		int32_t req = input_get_request(&this->input);
		if (req == 0) {
			this->state = CABROT_STATE_NORMAL;
		}
		else {
			if (dev.hcu.pressure > CABROT_MAX_PRESSURE) {
				this->state = CABROT_STATE_OVERPRESSURE;
			}
		}
		if (this->state == CABROT_STATE_OVERPRESSURE) {
			req = 0;
		}

		uv_dual_solenoid_output_set(&this->out,
					input_get_request(&this->input, &this->conf->out_conf));

		ccu_cabdir_e new_dir = this->dir;
		if (uv_dual_solenoid_output_get_current(&this->out) > 0) {
			new_dir = CCU_CABDIR_FORWARD;
		}
		else if (uv_dual_solenoid_output_get_current(&this->out) < 0) {
			new_dir = CCU_CABDIR_BACKWARD;
		}
		else {

		}
		if (this->dir != new_dir) {
			uv_eeprom_write(&new_dir, sizeof(new_dir), CABDIR_EEPROM_ADDR);
			this->dir = new_dir;
		}

		uv_output_set_state(&this->cabbrake, uv_dual_solenoid_output_get_current(&this->out) ?
				OUTPUT_STATE_ON : OUTPUT_STATE_OFF);

	}
}

void cabrot_solenoid_step(cabrot_st *this, uint16_t step_ms) {
	if (dev.assembly.cabrot_installed) {
		uv_dual_solenoid_output_step(&this->out, step_ms);
		uv_output_step(&this->cabbrake, step_ms);
	}
}
