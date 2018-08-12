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





#include "drive.h"
#include "can_ccu.h"
#include "main.h"
#include "pin_mappings.h"


void drive_conf_reset(drive_conf_st *this) {
	this->gear_conf[CCU_GEAR_1].acc = DUAL_SOLENOID_ACC_MAX;
	this->gear_conf[CCU_GEAR_1].dec = DUAL_SOLENOID_DEC_MAX;
	this->gear_conf[CCU_GEAR_1].invert = false;
	this->gear_conf[CCU_GEAR_1].solenoid_conf[DUAL_OUTPUT_SOLENOID_A].max_ma = 1000;
	this->gear_conf[CCU_GEAR_1].solenoid_conf[DUAL_OUTPUT_SOLENOID_A].min_ma = 250;
	this->gear_conf[CCU_GEAR_1].solenoid_conf[DUAL_OUTPUT_SOLENOID_B].max_ma = 1000;
	this->gear_conf[CCU_GEAR_1].solenoid_conf[DUAL_OUTPUT_SOLENOID_B].min_ma = 250;

	this->gear_conf[CCU_GEAR_2].acc = 30;
	this->gear_conf[CCU_GEAR_2].dec = 0;
	this->gear_conf[CCU_GEAR_2].invert = false;
	this->gear_conf[CCU_GEAR_2].solenoid_conf[DUAL_OUTPUT_SOLENOID_A].max_ma = 1800;
	this->gear_conf[CCU_GEAR_2].solenoid_conf[DUAL_OUTPUT_SOLENOID_A].min_ma = 200;
	this->gear_conf[CCU_GEAR_2].solenoid_conf[DUAL_OUTPUT_SOLENOID_B].max_ma = 1800;
	this->gear_conf[CCU_GEAR_2].solenoid_conf[DUAL_OUTPUT_SOLENOID_B].min_ma = 250;

	this->gear_conf[CCU_GEAR_3].acc = 30;
	this->gear_conf[CCU_GEAR_3].dec = 0;
	this->gear_conf[CCU_GEAR_3].invert = false;
	this->gear_conf[CCU_GEAR_3].solenoid_conf[DUAL_OUTPUT_SOLENOID_A].max_ma = 1000;
	this->gear_conf[CCU_GEAR_3].solenoid_conf[DUAL_OUTPUT_SOLENOID_A].min_ma = 150;
	this->gear_conf[CCU_GEAR_3].solenoid_conf[DUAL_OUTPUT_SOLENOID_B].max_ma = 1000;
	this->gear_conf[CCU_GEAR_3].solenoid_conf[DUAL_OUTPUT_SOLENOID_B].min_ma = 80;
}


void drive_init(drive_st *this, drive_conf_st *conf_ptr) {
	input_init(&this->input);
	this->conf = conf_ptr;
	this->gear = CCU_GEAR_2;
	uv_delay_init(&this->foot_down_emcy_delay, DRIVE_FOOT_DOWN_DELAY_MS);

	uv_dual_solenoid_output_init(&this->out1, &this->conf->gear_conf[this->gear], DRIVE1_PWMA,
			DRIVE1_PWMB, DRIVE1_SENSE, dev.dither_freq, dev.dither_ampl,
			VND5050_CURRENT_AMPL_UA, SOLENOID_MAX_CURRENT, SOLENOID_FAULT_CURRENT,
			CCU_EMCY_DRIVE1_OVERLOAD_A, CCU_EMCY_DRIVE1_OVERLOAD_B,
			CCU_EMCY_DRIVE1_FAULT_A, CCU_EMCY_DRIVE1_FAULT_B);
	uv_dual_solenoid_output_init(&this->out2, &this->conf->gear_conf[this->gear], DRIVE2_PWMA,
			DRIVE2_PWMB, DRIVE2_SENSE, dev.dither_freq, dev.dither_ampl,
			VND5050_CURRENT_AMPL_UA, SOLENOID_MAX_CURRENT, SOLENOID_FAULT_CURRENT,
			CCU_EMCY_DRIVE2_OVERLOAD_A, CCU_EMCY_DRIVE2_OVERLOAD_B,
			CCU_EMCY_DRIVE2_FAULT_A, CCU_EMCY_DRIVE2_FAULT_B);
	uv_output_init(&this->brake, BRAKE_SENSE, BRAKE_OUT, VND5050_CURRENT_AMPL_UA,
			5000, 15000, 50, CCU_EMCY_BRAKE_OVERLOAD, CCU_EMCY_BRAKE_FAULT);

}


void drive_step(drive_st *this, uint16_t step_ms) {
	input_step(&this->input, step_ms);

	uv_dual_solenoid_output_set_conf(&this->out1, &this->conf->gear_conf[this->gear]);
	uv_dual_solenoid_output_set_conf(&this->out2, &this->conf->gear_conf[this->gear]);

	uv_delay(&this->foot_down_emcy_delay, step_ms);

	// prevent driving when legs are down
	if ((dev.hcu.left_foot_state == HCU_FOOT_DOWN) ||
			(dev.hcu.right_foot_state == HCU_FOOT_DOWN)) {

		if (input_get_request(&this->input) &&
				uv_delay_has_ended(&this->foot_down_emcy_delay)) {

			uv_canopen_emcy_send(CANOPEN_EMCY_DEVICE_SPECIFIC,
					(dev.hcu.left_foot_state == HCU_FOOT_DOWN) ?
							CCU_EMCY_DRIVING_LEFT_FOOT_DOWN :
							CCU_EMCY_DRIVING_RIGHT_FOOT_DOWN);
			uv_delay_init(&this->foot_down_emcy_delay, DRIVE_FOOT_DOWN_DELAY_MS);
		}
		uv_dual_solenoid_output_set(&this->out1, 0);
	}
	else {
		// driving normally
		uv_dual_solenoid_output_set(&this->out1, input_get_request(&this->input));

		// 2nd output is used only with 2nd and 3rd gears
		uv_dual_solenoid_output_set(&this->out2,
				(this->gear == CCU_GEAR_1) ? 0 : input_get_request(&this->input));
	}


//		printf("%i %i %i %i\n", this->out2.solenoid[0].pwm, this->out2.solenoid[1].pwm,
//				uv_dual_solenoid_output_get_current(&this->out2),
//				uv_dual_solenoid_output_get_state(&this->out2, DUAL_OUTPUT_SOLENOID_A));

	uv_output_set_state(&this->brake,
			(uv_dual_solenoid_output_get_current(&this->out1) ||
					uv_dual_solenoid_output_get_current(&this->out2)) ?
							OUTPUT_STATE_ON : OUTPUT_STATE_OFF);
}

