/* 
 * Published Abstract Hardware Model Interfaces and Definitions 
 * applying to microscopes
 *
 * Copyright 2002, 2003, 2009 (c) Leica Microsystems - All Rights Reserved.
 *
 */

#ifndef PUBLIC_AHM_PROPERTY_IDS_H
#define PUBLIC_AHM_PROPERTY_IDS_H


namespace ahm {

	typedef enum eReservedPropertyIdRanges {
		/* Property Ids reserved for core internal and common hardware properties */
		RESERVED_PROPID_CORE_FIRST = 0x0,
		RESERVED_PROPID_CORE_LAST = 0x0fff,

		/* Property Ids reserved for microscopic hardware */
		RESERVED_PROPID_MICROSCOPE_FIRST = 0x1000,
		RESERVED_PROPID_MICROSCOPE_LAST  = 0x1fff,

		/* Property Ids reserved for image source hardware */
		RESERVED_PROPID_IMAGE_SOURCE_FIRST = 0x2000,
		RESERVED_PROPID_IMAGE_SOURCE_LAST  = 0x2fff,

		/* Property Ids reserved for autofocus hardware */
		RESERVED_PROPID_AUTOFOCUS_FIRST = 0x3100,
		RESERVED_PROPID_AUTOFOCUS_LAST  = 0x31ff,
		/* Property Ids reserved for autofocus hardware */
		RESERVED_PROPID_WIDEFIELD_FIRST = 0x3200,
		RESERVED_PROPID_WIDEFIELD_LAST  = 0x32ff,

		RESERVED_PROPID_UCAPI_FIRST = 0x4000,
		RESERVED_PROPID_UCAPI_LAST  = 0x4fff,

		/* GAP */
		/* Property Ids reserved to map TWAIN capabilities */
		RESERVED_PROPID_TWAIN_FIRST = 0x10000,
		RESERVED_PROPID_TWAIN_LAST  = 0x1ffff,
		__RESERVED_PROPID_MAX
		/* GAP */

	} EReservedPropertyIdRanges;
};

#endif // PUBLIC_AHM_PROPERTY_IDS_H

