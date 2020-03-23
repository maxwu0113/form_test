/** 
 ** Copyright (c) 2002-2005 Leica Microsystems - All Rights Reserved
 ** 
 ** AHM Interop Types
 **
 **/

#ifndef AHM_IOP_H
#define AHM_IOP_H



#ifdef AHM_NEEDS_WINDOWS_STUFF
#define WIN32_LEAN_AND_MEAN		// Exclude rarely-used stuff from Windows headers
#include <windows.h>
#endif


#include <stddef.h> // wchar_t

#ifdef AHM_EXPORTS
#define AHM_API extern "C" __declspec(dllexport)
#else
#define AHM_API extern "C" __declspec(dllimport)
#endif



namespace iop {  // interoperability
	typedef const char * string;
	typedef const wchar_t *unicode_string;
	typedef int int32;
	typedef unsigned int uint32;
	typedef double float64;
	typedef unsigned char byte;
	typedef long long int64;


	const int32 MAX_INT32 = 0x7fffffff;
	const int64 MAX_INT64 = 0x7fffffffffffffff;
};


#endif
