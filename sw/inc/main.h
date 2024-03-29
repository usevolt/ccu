/*
 * main.h
 *
 *  Created on: Apr 26, 2015
 *      Author: usevolt
 */

#ifndef MAIN_H_
#define MAIN_H_


#include <uv_memory.h>
#include <uv_filters.h>
#include <uv_output.h>
#include <uv_dual_solenoid_output.h>
#include <uv_mcp2515.h>
#include "can_fsb.h"
#include "steer.h"
#include "drive.h"
#include "pedal.h"
#include "cabrot.h"
#include "telescope.h"


#define VND5050_CURRENT_AMPL_UA		1619
#define VN5E01_CURRENT_AMPL_UA		5600

#define DITHER_AMPL_DEF				0
#define DITHER_FREQ_DEF				50

#define SOLENOID_MAX_CURRENT		4000
#define SOLENOID_FAULT_CURRENT		5000

#define BOOM_VDD_MAX_CURRENT		15000
#define BOOM_VDD_FAULT_CURRENT		25000
#define BOOM_VDD_AVG_COUNT			10


#define WORK_DELAY_MS				5000
#define DRIVE_DELAY_MS				1000


#define ASSEMBLY_EEPROM_ADDR		0
#define CABDIR_EEPROM_ADDR			(ASSEMBLY_EEPROM_ADDR + sizeof(dev.assembly))

/// @brief: main data structure.
/// This struct can be save to non-volatile flash memory with
/// a terminal commmand 'save'.
typedef struct _dev_st {

	uint16_t total_current;
	uv_mcp2515_st mcp2515;

	steer_st steer;
	drive_st drive;
	cabrot_st cabrot;
	telescope_st telescope;

	uv_output_st boom_vdd;

	// assembly settings are stored in eeprom
	// Note: These variables are not initialized unless explicitly set.
	// They default to value 0 but this depends on the hardware.
	struct {
		uint8_t cabrot_installed;
		uint8_t telescope_installed;
		uint8_t gears_installed;
		uint8_t backsteer_installed;
	} assembly;
	uint8_t assembly_write;

	struct {
		fsb_ignkey_states_e ignkey_state;
		uint8_t emcy;
		uint8_t seat_sw;
		uint8_t door_sw1;
		uint8_t door_sw2;
	} fsb;
	struct {
		hcu_impls_e implement;
		hcu_foot_state_e left_foot_state;
		hcu_foot_state_e right_foot_state;
		uint16_t pressure;
	} hcu;
	pedal_st pedal;

	// the current oil req
	int8_t impl2_req;
	uint8_t work_active;
	uv_delay_st work_delay;
	uint8_t drive_active;
	uv_delay_st drive_delay;

	// non-volatile data start
	uv_data_start_t data_start;

	uint16_t dither_freq;
	int16_t dither_ampl;

	steer_conf_st steer_conf;
	drive_conf_st drive_conf;
	cabrot_conf_st cabrot_conf;
	telescope_conf_st telescope_conf;

	// the amount of oil request from impl2 when ain1 is high
	int8_t impl2_ain1_req;
	// the amount of oil request from impl2 when ain2 is high
	int8_t impl2_ain2_req;

	uv_data_end_t data_end;

} dev_st;



extern dev_st dev;


void step(void* me);

void init(dev_st* me);






#endif /* MAIN_H_ */
