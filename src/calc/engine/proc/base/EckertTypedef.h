////==--------------------------------------------------------------------====//
// ECKERT TYPEDEF
// [ Update ]
// Nov 18, 2016
// ----
// [ NOTICE ]
// To change this file may affect whole ECKERT system
//====--------------------------------------------------------------------==////

#ifndef _ECKERT_TYPEDEF_H_
#define _ECKERT_TYPEDEF_H_

#include "math/SafetyRational.h"
#include <cstdint>

namespace engine {
	using integer_t = int64_t;
	using uinteger_t = uint64_t;
	using floating_t = long double;
	using rational_t = SafetyRational<integer_t, floating_t>;
} // namespace engine

#endif // ifndef _ECKERT_TYPEDEF_H_
