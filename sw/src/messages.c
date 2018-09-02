/*
 * uw_messages.c
 *
 *  Created on: Feb 19, 2015
 *      Author: usenius
 */


#include "main.h"
#include "messages.h"
#include "can_esb.h"
#include "can_fsb.h"
#include "can_csb.h"
#include "can_ccu.h"
#include "pin_mappings.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <uv_timer.h>
#include <uv_utilities.h>

extern dev_st dev;
#define this (&dev)




canopen_object_st obj_dict[] = {
		{
				.main_index = CCU_TOTAL_CURRENT_INDEX,
				.sub_index = CCU_TOTAL_CURRENT_SUBINDEX,
				.type = CCU_TOTAL_CURRENT_TYPE,
				.permissions = CCU_TOTAL_CURRENT_PERMISSIONS,
				.data_ptr = &this->total_current
		},
		{
				.main_index = CCU_STEER_REQ_INDEX,
				.sub_index = CCU_STEER_REQ_SUBINDEX,
				.type = CCU_STEER_REQ_TYPE,
				.permissions = CCU_STEER_REQ_PERMISSIONS,
				.data_ptr = &this->steer.input.request
		},
		{
				.main_index = CCU_STEER_PARAM_INDEX,
				.sub_index = CCU_STEER_PARAM_ARRAY_MAX_SIZE,
				.type = CCU_STEER_PARAM_TYPE,
				.permissions = CCU_STEER_PARAM_PERMISSIONS,
				.data_ptr = &this->steer_conf
		},
		{
				.main_index = CCU_STEER_CURRENT_INDEX,
				.sub_index = CCU_STEER_CURRENT_SUBINDEX,
				.type = CCU_STEER_CURRENT_TYPE,
				.permissions = CCU_STEER_CURRENT_PERMISSIONS,
				.data_ptr = &this->steer.out.current_ma
		},
		{
				.main_index = CCU_DRIVE_REQ_INDEX,
				.sub_index = CCU_DRIVE_REQ_SUBINDEX,
				.type = CCU_DRIVE_REQ_TYPE,
				.permissions = CCU_DRIVE_REQ_PERMISSIONS,
				.data_ptr = &this->drive.input.request
		},
		{
				.main_index = CCU_DRIVE_PARAM_INDEX,
				.sub_index = CCU_DRIVE_PARAM_ARRAY_MAX_SIZE,
				.type = CCU_DRIVE_PARAM_TYPE,
				.permissions = CCU_DRIVE_PARAM_PERMISSIONS,
				.data_ptr = &this->drive_conf
		},
		{
				.main_index = CCU_DRIVE_CURRENT1_INDEX,
				.sub_index = CCU_DRIVE_CURRENT1_SUBINDEX,
				.type = CCU_DRIVE_CURRENT1_TYPE,
				.permissions = CCU_DRIVE_CURRENT1_PERMISSIONS,
				.data_ptr = &this->drive.out1.current_ma
		},
		{
				.main_index = CCU_DRIVE_CURRENT2_INDEX,
				.sub_index = CCU_DRIVE_CURRENT2_SUBINDEX,
				.type = CCU_DRIVE_CURRENT2_TYPE,
				.permissions = CCU_DRIVE_CURRENT2_PERMISSIONS,
				.data_ptr = &this->drive.out2.current_ma
		},
		{
				.main_index = CCU_DRIVE_CURRENT3_INDEX,
				.sub_index = CCU_DRIVE_CURRENT3_SUBINDEX,
				.type = CCU_DRIVE_CURRENT3_TYPE,
				.permissions = CCU_DRIVE_CURRENT3_PERMISSIONS,
				.data_ptr = &this->drive.out3.current_ma
		},
		{
				.main_index = CCU_GEAR_INDEX,
				.sub_index = CCU_GEAR_SUBINDEX,
				.type = CCU_GEAR_TYPE,
				.permissions = CCU_GEAR_PERMISSIONS,
				.data_ptr = &this->drive.gear
		},
		{
				.main_index = CCU_GEAR_REQ_INDEX,
				.sub_index = CCU_GEAR_REQ_SUBINDEX,
				.type = CCU_GEAR_REQ_TYPE,
				.permissions = CCU_GEAR_REQ_PERMISSIONS,
				.data_ptr = &this->drive.gear_req.request
		},
		{
				.main_index = CCU_D4WD_REQ_INDEX,
				.sub_index = CCU_D4WD_REQ_SUBINDEX,
				.type = CCU_D4WD_REQ_TYPE,
				.permissions = CCU_D4WD_REQ_PERMISSIONS,
				.data_ptr = &this->drive.d4wd_req
		},
		{
				.main_index = CCU_CABROT_REQ_INDEX,
				.sub_index = CCU_CABROT_REQ_SUBINDEX,
				.type = CCU_CABROT_REQ_TYPE,
				.permissions = CCU_CABROT_REQ_PERMISSIONS,
				.data_ptr = &this->cabrot.input.request
		},
		{
				.main_index = CCU_CABROT_PARAM_INDEX,
				.sub_index = CCU_CABROT_PARAM_ARRAY_MAX_SIZE,
				.type = CCU_CABROT_PARAM_TYPE,
				.permissions = CCU_CABROT_PARAM_PERMISSIONS,
				.data_ptr = &this->cabrot_conf
		},
		{
				.main_index = CCU_CABROT_CURRENT_INDEX,
				.sub_index = CCU_CABROT_CURRENT_SUBINDEX,
				.type = CCU_CABROT_CURRENT_TYPE,
				.permissions = CCU_CABROT_CURRENT_PERMISSIONS,
				.data_ptr = &this->cabrot.out.current_ma
		},
		{
				.main_index = CCU_CABROT_DIR_INDEX,
				.sub_index = CCU_CABROT_DIR_SUBINDEX,
				.type = CCU_CABROT_DIR_TYPE,
				.permissions = CCU_CABROT_DIR_PERMISSIONS,
				.data_ptr = &this->cabrot.dir
		},
		{
				.main_index = CCU_TELESCOPE_REQ_INDEX,
				.sub_index = CCU_TELESCOPE_REQ_SUBINDEX,
				.type = CCU_TELESCOPE_REQ_TYPE,
				.permissions = CCU_TELESCOPE_REQ_PERMISSIONS,
				.data_ptr = &this->telescope.input.request
		},
		{
				.main_index = CCU_TELESCOPE_PARAM_INDEX,
				.sub_index = CCU_TELESCOPE_PARAM_ARRAY_MAX_SIZE,
				.type = CCU_TELESCOPE_PARAM_TYPE,
				.permissions = CCU_TELESCOPE_PARAM_PERMISSIONS,
				.data_ptr = &this->telescope_conf
		},
		{
				.main_index = CCU_TELESCOPE_CURRENT_INDEX,
				.sub_index = CCU_TELESCOPE_CURRENT_SUBINDEX,
				.type = CCU_TELESCOPE_CURRENT_TYPE,
				.permissions = CCU_TELESCOPE_CURRENT_PERMISSIONS,
				.data_ptr = &this->telescope.out.current_ma
		},


		{
				.main_index = CCU_FSB_INDEX_OFFSET + FSB_IGNKEY_INDEX,
				.sub_index = FSB_IGNKEY_SUBINDEX,
				.type = FSB_IGNKEY_TYPE,
				.permissions = FSB_IGNKEY_PERMISSIONS,
				.data_ptr = &this->fsb.ignkey_state
		},
		{
				.main_index = CCU_FSB_INDEX_OFFSET + FSB_EMCY_INDEX,
				.sub_index = FSB_EMCY_SUBINDEX,
				.type = FSB_EMCY_TYPE,
				.permissions = FSB_EMCY_PERMISSIONS,
				.data_ptr = &this->fsb.emcy
		},
		{
				.main_index = CCU_FSB_INDEX_OFFSET + FSB_DOORSW1_INDEX,
				.sub_index = FSB_DOORSW1_SUBINDEX,
				.type = FSB_DOORSW1_TYPE,
				.permissions = FSB_DOORSW1_PERMISSIONS,
				.data_ptr = &this->fsb.door_sw1
		},
		{
				.main_index = CCU_FSB_INDEX_OFFSET + FSB_DOORSW2_INDEX,
				.sub_index = FSB_DOORSW2_SUBINDEX,
				.type = FSB_DOORSW2_TYPE,
				.permissions = FSB_DOORSW2_PERMISSIONS,
				.data_ptr = &this->fsb.door_sw2
		},
		{
				.main_index = CCU_FSB_INDEX_OFFSET + FSB_SEATSW_INDEX,
				.sub_index = FSB_SEATSW_SUBINDEX,
				.type = FSB_SEATSW_TYPE,
				.permissions = FSB_SEATSW_PERMISSIONS,
				.data_ptr = &this->fsb.seat_sw
		},
		{
				.main_index = CCU_PEDAL_RAW_INDEX,
				.array_max_size = CCU_PEDAL_RAW_ARRAY_MAX_SIZE,
				.type = CCU_PEDAL_RAW_TYPE,
				.permissions = CCU_PEDAL_RAW_PERMISSIONS,
				.data_ptr = &this->pedal.hal[0]
		},
		{
				.main_index = CCU_HCU_INDEX_OFFSET + HCU_LEFT_FOOT_STATE_INDEX,
				.sub_index = HCU_LEFT_FOOT_STATE_SUBINDEX,
				.type = HCU_LEFT_FOOT_STATE_TYPE,
				.permissions = HCU_LEFT_FOOT_STATE_PERMISSIONS,
				.data_ptr = &this->hcu.left_foot_state
		},
		{
				.main_index = CCU_HCU_INDEX_OFFSET + HCU_RIGHT_FOOT_STATE_INDEX,
				.sub_index = HCU_RIGHT_FOOT_STATE_SUBINDEX,
				.type = HCU_RIGHT_FOOT_STATE_TYPE,
				.permissions = HCU_RIGHT_FOOT_STATE_PERMISSIONS,
				.data_ptr = &this->hcu.right_foot_state
		}
};

int obj_dict_len() {
	return sizeof(obj_dict) / sizeof(canopen_object_st);
}

void stat_callb(void* me, unsigned int cmd, unsigned int args, argument_st *argv);
void set_callb(void* me, unsigned int cmd, unsigned int args, argument_st *argv);
void can2_callb(void* me, unsigned int cmd, unsigned int args, argument_st *argv);


const uv_command_st terminal_commands[] = {
		{
				.id = CMD_STAT,
				.str = "stat",
				.instructions = "Displays the system status information.\n"
						"Usage: stat",
				.callback = &stat_callb
		},
		{
				.id = CMD_SET,
				.str = "set",
				.instructions = "Sets the configurations for output modules.\n"
						"Usage: set <\"str\"/\"g1\"/\"g2\"/\"g3\"/\"cabrot\"/\"telescope\"> "
						"<\"maxa\"/\"maxb\"/\"mina\"/\"minb\"/\"acc\"/\"dec\"/\"invert\">"
						"<value>",
				.callback = &set_callb
		},
		{
				.id = CMD_CAN2,
				.str = "can2",
				.instructions = "Does various operations to CAN2 (MCP2515 module). \n"
						"Usage: can2 <\"reset\"/\"hardreset\">",
				.callback = &can2_callb
		}
};




unsigned int commands_size(void) {
	return sizeof(terminal_commands) / sizeof(uv_command_st);
}




static void stat_output(uv_dual_solenoid_output_st *output, const char *name) {
	printf("%s solenoid states: %u %u, current: %i mA\n",
			name, uv_dual_solenoid_output_get_state(output, DUAL_OUTPUT_SOLENOID_A),
			uv_dual_solenoid_output_get_state(output, DUAL_OUTPUT_SOLENOID_B),
			uv_dual_solenoid_output_get_current(output));
}


void stat_callb(void* me, unsigned int cmd, unsigned int args, argument_st *argv) {
	printf("SYSTEM STATUS:\n");
	printf("Total current: %u mA\n", (unsigned int) this->total_current);
	printf("Gear: %u\n", this->drive.gear + 1);
	stat_output(&this->steer.out, "Steer");
	stat_output(&this->drive.out1, "Drive 1");
	stat_output(&this->drive.out2, "Drive 2");
	stat_output(&this->drive.out3, "Drive 3");
	printf("brake state: %u, current: %u mA\n",
			uv_output_get_state(&this->drive.brake),
			uv_output_get_current(&this->drive.brake));
	printf("Gear3 state: %u, current: %u mA\n",
			uv_output_get_state(&this->drive.gear3),
			uv_output_get_current(&this->drive.gear3));
	stat_output(&this->cabrot.out, "Cabin Rotate");
	printf("Cabin direction: %s\n",
			(cabrot_get_dir(&this->cabrot) == CCU_CABDIR_FORWARD) ? "FORWARD" : "BACKWARD");
	printf("Cab brake state: %u, current: %i mA\n",
			uv_output_get_state(&this->cabrot.cabbrake),
			uv_output_get_current(&this->cabrot.cabbrake));
	stat_output(&this->telescope.out, "Loading Space Telescope");
	printf("Pedal: state: %u, hal1: %i hal2: %i request: %i\n",
			this->pedal.state, this->pedal.req[0], this->pedal.req[1], this->pedal.request);
	printf("Boom VDD state: %u, current: %u mA\n",
			uv_output_get_state(&this->boom_vdd),
			uv_output_get_current(&this->boom_vdd));
	printf("emcy: %u, seat sw: %u, ignkey state: %u, fsb heartbeat expired: %u\n",
			this->fsb.emcy, this->fsb.seat_sw, this->fsb.ignkey_state,
			uv_canopen_heartbeat_producer_is_expired(FSB_NODE_ID));
}

void set_callb(void* me, unsigned int cmd, unsigned int args, argument_st *argv) {
	if ((args < 1) || (argv[0].type != ARG_STRING)) {
		printf("Give module name as an argument.\n");
	}
	else {
		uv_dual_solenoid_output_conf_st *conf = NULL;
		const char *str = argv[0].str;

		if (strcmp(str, "str") == 0) {
			conf = &this->steer_conf.out_conf;
		}
		else if (strcmp(str, "g1") == 0) {
			conf = &this->drive_conf.gear_conf[CCU_GEAR_1];
		}
		else if (strcmp(str, "g2") == 0) {
			conf = &this->drive_conf.gear_conf[CCU_GEAR_2];
		}
		else if (strcmp(str, "g3") == 0) {
			conf = &this->drive_conf.gear_conf[CCU_GEAR_3];
		}
		else if (strcmp(str, "cabrot") == 0) {
			conf = &this->cabrot_conf.out_conf;
		}
		else if (strcmp(str, "telescope") == 0) {
			conf = &this->telescope_conf.out_conf;
		}
		else {
			printf("Unknown module '%s'\n", str);
		}

		if (conf) {
			if (args > 2) {
				if ((argv[1].type == ARG_STRING) &&
					(argv[2].type == ARG_INTEGER)) {
					const char *s = argv[1].str;
					int16_t value = argv[2].number;
					if (strcmp(s, "maxa") == 0) {
						conf->solenoid_conf[DUAL_OUTPUT_SOLENOID_A].max_ma = value;
					}
					else if (strcmp(s, "mina") == 0) {
						conf->solenoid_conf[DUAL_OUTPUT_SOLENOID_A].min_ma = value;
					}
					else if (strcmp(s, "maxb") == 0) {
						conf->solenoid_conf[DUAL_OUTPUT_SOLENOID_B].max_ma = value;
					}
					else if (strcmp(s, "minb") == 0) {
						conf->solenoid_conf[DUAL_OUTPUT_SOLENOID_B].min_ma = value;
					}
					else if (strcmp(s, "acc") == 0) {
						conf->acc = value;
					}
					else if (strcmp(s, "dec") == 0) {
						conf->dec = value;
					}
					else if (strcmp(s, "invert") == 0) {
						conf->invert = (bool) value;
					}
					else if (strcmp(s, "assinv") == 0) {
						conf->assembly_invert = (bool) value;
					}
					else {
						printf("Unknown parameter '%s'\n", s);
					}
				}
				else {
					printf("Wrong type of arguments. Arguments has to be:\n"
							"   String, string and integer.\n");
				}
			}
			printf("%s parameters:\n"
					"   Max Speed A: %u\n"
					"   Min Speed A: %u\n"
					"   Max Speed B: %u\n"
					"   Min Speed B: %u\n"
					"   Acceleration: %u\n"
					"   Deceleration: %u\n"
					"   Invert: %u\n"
					"   Assembly Invert: %u\n",
					str,
					conf->solenoid_conf[DUAL_OUTPUT_SOLENOID_A].max_ma,
					conf->solenoid_conf[DUAL_OUTPUT_SOLENOID_A].min_ma,
					conf->solenoid_conf[DUAL_OUTPUT_SOLENOID_B].max_ma,
					conf->solenoid_conf[DUAL_OUTPUT_SOLENOID_B].min_ma,
					conf->acc,
					conf->dec,
					conf->invert,
					conf->assembly_invert);
		}
	}
}

void can2_callb(void* me, unsigned int cmd, unsigned int args, argument_st *argv) {
	if (args && argv[0].type == ARG_STRING) {
		char *str = argv[0].str;
		if (strcmp(str, "reset") == 0) {
			uv_mcp2515_init(&this->mcp2515, SPI0, SPI_SLAVE0, MCP2515_INT, uv_memory_get_can_baudrate());
			printf("can2 reset\n");
		}
		else if (strcmp(str, "hardreset") == 0) {
			printf("Hard reset\n");
			uv_output_set_state(&this->boom_vdd, OUTPUT_STATE_OFF);
			uv_output_step(&this->boom_vdd, 20);
			uv_rtos_task_delay(100);
		}
		else if (strcmp(str, "state") == 0) {
			uv_can_errors_e e = uv_mcp2515_get_error_state(&this->mcp2515);
			printf("MCP2515 error state: %u\n", e);
		}
		else {
			printf("unknown command %s\n", str);
		}
	}
}


