/* Copyright (C) 2017 - Steffen A. Mork */

#ifndef SC_TYPES_H_
#define SC_TYPES_H_

#include <cstdint>


typedef int_fast16_t   sc_short;
typedef uint_fast16_t  sc_ushort;
typedef int32_t        sc_integer;
typedef double         sc_real;
typedef bool           sc_boolean;

#define sc_string      const char *
typedef intptr_t       sc_eventid;

#ifndef null
	#define null 0
#endif

#endif /* SC_TYPES_H_ */
