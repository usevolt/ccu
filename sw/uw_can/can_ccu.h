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


#ifndef UW_CAN_CAN_CCU_H_
#define UW_CAN_CAN_CCU_H_




#include <stdint.h>






#define CCU_NODE_ID					0x9




/// @brief: Defines all ESB's EMCY message data values.
/// All EMCY messages belong to device specific EMCY error code category (0xFF00)
typedef enum {
	CCU_EMCY_STEER_OVERLOAD_A = (CCU_NODE_ID << 16),
	CCU_EMCY_STEER_FAULT_A,
	CCU_EMCY_STEER_OVERLOAD_B,
	CCU_EMCY_STEER_FAULT_B,
	CCU_EMCY_DRIVE1_OVERLOAD_A,
	CCU_EMCY_DRIVE1_FAULT_A,
	CCU_EMCY_DRIVE1_OVERLOAD_B,
	CCU_EMCY_DRIVE1_FAULT_B,
	CCU_EMCY_DRIVE2_OVERLOAD_A,
	CCU_EMCY_DRIVE2_FAULT_A,
	CCU_EMCY_DRIVE2_OVERLOAD_B,
	CCU_EMCY_DRIVE2_FAULT_B,
	CCU_EMCY_DRIVING_LEFT_FOOT_DOWN,
	CCU_EMCY_DRIVING_RIGHT_FOOT_DOWN,
	CCU_EMCY_BRAKE_OVERLOAD,
	CCU_EMCY_BRAKE_FAULT,

	CCU_EMCY_BOOM_VDD_OVERLOAD,
	CCU_EMCY_BOOM_VDD_FAULT,
	CCU_EMCY_PEDAL_FAULT,
	CCU_EMCY_COUNT
} ccu_emcy_e;


typedef enum {
	CCU_GEAR_1 = 0,
	CCU_GEAR_2,
	CCU_GEAR_3,
	CCU_GEAR_COUNT
} ccu_gear_e;


// CCU OBJECT DICTIONARY ENTRIES


#define CCU_TOTAL_CURRENT_INDEX					0x2000
#define CCU_TOTAL_CURRENT_SUBINDEX				0
#define CCU_TOTAL_CURRENT_TYPE					CANOPEN_UNSIGNED16
#define CCU_TOTAL_CURRENT_PERMISSIONS			CANOPEN_RO

#define CCU_STEER_REQ_INDEX						0x2100
#define CCU_STEER_REQ_SUBINDEX					0
#define CCU_STEER_REQ_TYPE						CANOPEN_UNSIGNED8
#define CCU_STEER_REQ_PERMISSIONS				CANOPEN_RW

#define CCU_STEER_PARAM_INDEX					0x2101
#define CCU_STEER_PARAM_ARRAY_MAX_SIZE			7
#define CCU_STEER_PARAM_TYPE					CANOPEN_ARRAY16
#define CCU_STEER_PARAM_PERMISSIONS				CANOPEN_RW

#define CCU_STEER_CURRENT_INDEX					0x2102
#define CCU_STEER_CURRENT_SUBINDEX				0
#define CCU_STEER_CURRENT_TYPE					CANOPEN_SIGNED16
#define CCU_STEER_CURRENT_PERMISSIONS			CANOPEN_RO

#define CCU_DRIVE_REQ_INDEX						0x2110
#define CCU_DRIVE_REQ_SUBINDEX					0
#define CCU_DRIVE_REQ_TYPE						CANOPEN_UNSIGNED8
#define CCU_DRIVE_REQ_PERMISSIONS				CANOPEN_RW

#define CCU_DRIVE_PARAM_INDEX					0x2111
#define CCU_DRIVE_PARAM_ARRAY_MAX_SIZE			7 * CCU_GEAR_COUNT
#define CCU_DRIVE_PARAM_TYPE					CANOPEN_ARRAY16
#define CCU_DRIVE_PARAM_PERMISSIONS				CANOPEN_RW

#define CCU_DRIVE_CURRENT1_INDEX				0x2112
#define CCU_DRIVE_CURRENT1_SUBINDEX				0
#define CCU_DRIVE_CURRENT1_TYPE					CANOPEN_SIGNED16
#define CCU_DRIVE_CURRENT1_PERMISSIONS			CANOPEN_RO

#define CCU_DRIVE_CURRENT2_INDEX				0x2113
#define CCU_DRIVE_CURRENT2_SUBINDEX				0
#define CCU_DRIVE_CURRENT2_TYPE					CANOPEN_SIGNED16
#define CCU_DRIVE_CURRENT2_PERMISSIONS			CANOPEN_RO

#define CCU_GEAR_INDEX							0x2114
#define CCU_GEAR_SUBINDEX						0
#define CCU_GEAR_TYPE							CANOPEN_UNSIGNED8
#define CCU_GEAR_PERMISSIONS					CANOPEN_RW


#define CCU_PEDAL_RAW_INDEX						0x2200
#define CCU_PEDAL_RAW_ARRAY_MAX_SIZE			2
#define CCU_PEDAL_RAW_TYPE						CANOPEN_ARRAY16
#define CCU_PEDAL_RAW_PERMISSIONS				CANOPEN_RW




#define CCU_FSB_INDEX_OFFSET					0x1000
#define CCU_HCU_INDEX_OFFSET					0x2000


#endif /* UW_CAN_CAN_CCU_H_ */
