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


#ifndef CAN_ICU_H_
#define CAN_ICU_H_


/// @file: Defines the UW ceiling supply board CANopen interface.

#include <stdint.h>






#define ICU_NODE_ID					0xA






/// @brief: Defines all ICU's EMCY message data values.
/// All EMCY messages belong to device specific EMCY error code category (0xFF00)
typedef enum {
	ICU_EMCY_BLADEOPEN_OVERCURRENT = (ICU_NODE_ID << 16),
	ICU_EMCY_BLADEOPEN_FAULT,
	ICU_EMCY_FEEDOPEN_OVERCURRENT,
	ICU_EMCY_FEEDOPEN_FAULT,
	ICU_EMCY_SAW_OVERCURRENT,
	ICU_EMCY_SAW_FAULT,
	ICU_EMCY_TILT_OVERCURRENT,
	ICU_EMCY_TILT_FAULT,
	ICU_EMCY_FEEDSERIES_OVERCURRENT,
	ICU_EMCY_FEEDSERIES_FAULT,
	ICU_EMCY_COUNT
} icu_emcy_e;




// ICU OBJECT DICTIONARY ENTRIES


#define ICU_TOTAL_CURRENT_INDEX					0x2000
#define ICU_TOTAL_CURRENT_SUBINDEX				0
#define ICU_TOTAL_CURRENT_TYPE					CANOPEN_UNSIGNED16
#define ICU_TOTAL_CURRENT_PERMISSIONS			CANOPEN_RO

#define ICU_IMPL1_REQ_INDEX						0x2100
#define ICU_IMPL1_REQ_SUBINDEX					0
#define ICU_IMPL1_REQ_TYPE						CANOPEN_SIGNED8
#define ICU_IMPL1_REQ_PERMISSIONS				CANOPEN_RO

#define ICU_IMPL2_REQ_INDEX						0x2101
#define ICU_IMPL2_REQ_SUBINDEX					0
#define ICU_IMPL2_REQ_TYPE						CANOPEN_SIGNED8
#define ICU_IMPL2_REQ_PERMISSIONS				CANOPEN_RO

#define ICU_BLADEOPEN_REQ_INDEX					0x2200
#define ICU_BLADEOPEN_REQ_SUBINDEX				0
#define ICU_BLADEOPEN_REQ_TYPE					CANOPEN_SIGNED8
#define ICU_BLADEOPEN_REQ_PERMISSIONS			CANOPEN_RW

#define ICU_BLADEOPEN_PARAM_INDEX				0x2201
#define ICU_BLADEOPEN_PARAM_ARRAY_MAX_SIZE		5
#define ICU_BLADEOPEN_PARAM_TYPE				CANOPEN_ARRAY16
#define ICU_BLADEOPEN_PARAM_PERMISSIONS			CANOPEN_RW

#define ICU_BLADEOPEN_CURRENT_INDEX				0x2202
#define ICU_BLADEOPEN_CURRENT_SUBINDEX			0
#define ICU_BLADEOPEN_CURRENT_TYPE				CANOPEN_UNSIGNED16
#define ICU_BLADEOPEN_CURRENT_PERMISSIONS		CANOPEN_RO

#define ICU_FEEDOPEN_REQ_INDEX					0x2210
#define ICU_FEEDOPEN_REQ_SUBINDEX				0
#define ICU_FEEDOPEN_REQ_TYPE					CANOPEN_SIGNED8
#define ICU_FEEDOPEN_REQ_PERMISSIONS			CANOPEN_RW

#define ICU_FEEDOPEN_PARAM_INDEX				0x2211
#define ICU_FEEDOPEN_PARAM_ARRAY_MAX_SIZE		5
#define ICU_FEEDOPEN_PARAM_TYPE					CANOPEN_ARRAY16
#define ICU_FEEDOPEN_PARAM_PERMISSIONS			CANOPEN_RW

#define ICU_FEEDOPEN_CURRENT_INDEX				0x2212
#define ICU_FEEDOPEN_CURRENT_SUBINDEX			0
#define ICU_FEEDOPEN_CURRENT_TYPE				CANOPEN_UNSIGNED16
#define ICU_FEEDOPEN_CURRENT_PERMISSIONS		CANOPEN_RO

#define ICU_SAW_REQ_INDEX						0x2220
#define ICU_SAW_REQ_SUBINDEX					0
#define ICU_SAW_REQ_TYPE						CANOPEN_SIGNED8
#define ICU_SAW_REQ_PERMISSIONS					CANOPEN_RW

#define ICU_SAW_PARAM_INDEX						0x2221
#define ICU_SAW_PARAM_ARRAY_MAX_SIZE			6
#define ICU_SAW_PARAM_TYPE						CANOPEN_ARRAY16
#define ICU_SAW_PARAM_PERMISSIONS				CANOPEN_RW

#define ICU_SAW_CURRENT_INDEX					0x2222
#define ICU_SAW_CURRENT_SUBINDEX				0
#define ICU_SAW_CURRENT_TYPE					CANOPEN_UNSIGNED16
#define ICU_SAW_CURRENT_PERMISSIONS				CANOPEN_RO

#define ICU_TILT_REQ_INDEX						0x2230
#define ICU_TILT_REQ_SUBINDEX					0
#define ICU_TILT_REQ_TYPE						CANOPEN_SIGNED8
#define ICU_TILT_REQ_PERMISSIONS				CANOPEN_RW

#define ICU_TILT_PARAM_INDEX					0x2231
#define ICU_TILT_PARAM_ARRAY_MAX_SIZE			5
#define ICU_TILT_PARAM_TYPE						CANOPEN_ARRAY16
#define ICU_TILT_PARAM_PERMISSIONS				CANOPEN_RW

#define ICU_TILT_CURRENT_INDEX					0x2232
#define ICU_TILT_CURRENT_SUBINDEX				0
#define ICU_TILT_CURRENT_TYPE					CANOPEN_UNSIGNED16
#define ICU_TILT_CURRENT_PERMISSIONS			CANOPEN_RO

#define ICU_FEED_REQ_INDEX						0x2240
#define ICU_FEED_REQ_SUBINDEX					0
#define ICU_FEED_REQ_TYPE						CANOPEN_SIGNED8
#define ICU_FEED_REQ_PERMISSIONS				CANOPEN_RW

#define ICU_FEED_PARAM_INDEX					0x2241
#define ICU_FEED_PARAM_ARRAY_MAX_SIZE			5
#define ICU_FEED_PARAM_TYPE						CANOPEN_ARRAY16
#define ICU_FEED_PARAM_PERMISSIONS				CANOPEN_RW

#define ICU_FEED_CURRENT_INDEX					0x2242
#define ICU_FEED_CURRENT_SUBINDEX				0
#define ICU_FEED_CURRENT_TYPE					CANOPEN_UNSIGNED16
#define ICU_FEED_CURRENT_PERMISSIONS			CANOPEN_RO

#define ICU_ALLOPEN_REQ_INDEX					0x2250
#define ICU_ALLOPEN_REQ_SUBINDEX				0
#define ICU_ALLOPEN_REQ_TYPE					CANOPEN_SIGNED8
#define ICU_ALLOPEN_REQ_PERMISSIONS				CANOPEN_RW

#define ICU_ALLOPEN_PARAM_INDEX					0x2251
#define ICU_ALLOPEN_PARAM_ARRAY_MAX_SIZE		7
#define ICU_ALLOPEN_PARAM_TYPE					CANOPEN_ARRAY16
#define ICU_ALLOPEN_PARAM_PERMISSIONS			CANOPEN_RW



#define ICU_FSB_INDEX_OFFSET					0x1000



#endif /* CAN_ICU_H_ */
