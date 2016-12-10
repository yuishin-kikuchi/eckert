////==--------------------------------------------------------------------====//
// ECKERT EXCEPTION - INVALID VALUE
// [ Update ]
// Nov 13, 2016
//====--------------------------------------------------------------------==////

#ifndef _INVALID_VALUE_H_
#define _INVALID_VALUE_H_

#include "BadArgument.h"

namespace engine {
	class InvalidValue : public BadArgument {
	public:
		InvalidValue()
		 : BadArgument(){}
		InvalidValue(const char *str)
		 : BadArgument(str){}
		InvalidValue(const char *str, const char *place)
		 : BadArgument(str, place){}
		InvalidValue(const InvalidValue &obj)
		 : BadArgument(obj){}
	};
} // namespace engine

#endif // ifndef _INVALID_VALUE_H_
