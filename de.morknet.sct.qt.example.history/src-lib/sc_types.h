/* Copyright (C) GIRA Giersiepen GmbH & Co. KG */

#ifndef SC_TYPES_H_
#define SC_TYPES_H_

/* As <cstdint> is not available on all platforms we choose to include <stdint.h>. You can switch to <cstdint> by commenting and uncommenting the lines below.*/
// #include <cstdint>
#include <stdint.h>

#ifndef sc_string
#define sc_string      char*
#endif

#ifndef sc_integer
#define sc_integer int
#endif

#ifndef sc_real
#define sc_real double
#endif

#ifndef sc_boolean
#define sc_boolean bool
#endif


typedef int_fast16_t   sc_short;
typedef uint_fast16_t  sc_ushort;
typedef int16_t		   sc_errorCode;

typedef intptr_t       sc_eventid;

#ifndef sc_null
#define sc_null 0
#endif

#endif /* SC_TYPES_H_ */
