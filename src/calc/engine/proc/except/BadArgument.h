////==--------------------------------------------------------------------====//
// ECKERT EXCEPTION - BAD ARGUMENT
// [ Update ]
// Nov 13, 2016
//====--------------------------------------------------------------------==////

#ifndef _BAD_ARGUMENT_H_
#define _BAD_ARGUMENT_H_

#include "EckertException.h"

namespace engine {
	class BadArgument : public EckertException {
		public:
			BadArgument()
			 : EckertException() {}
			BadArgument(const char *str)
			 : EckertException(str) {}
			BadArgument(const char *str, const char *place)
			 : EckertException(str, place) {}
			BadArgument(const BadArgument &obj)
			 : EckertException(obj) {}
	};
} // namespace engine

#endif // ifndef _BAD_ARGUMENT_H_
