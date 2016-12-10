////==--------------------------------------------------------------------====//
// ECKERT EXCEPTION - BAD SCALAR
// [ Update ]
// Jan 27, 2016
//====--------------------------------------------------------------------==////

#ifndef _BAD_SCALAR_H_
#define _BAD_SCALAR_H_

#include "BadArgument.h"

namespace engine{
	class BadScalar : public BadArgument {
		public:
			BadScalar()
			 : BadArgument() {}
			BadScalar(const char *str)
			 : BadArgument(str) {}
			BadScalar(const char *str, const char *place)
			 : BadArgument(str, place) {}
			BadScalar(const BadArgument &obj)
			 : BadArgument(obj) {}
	};
} // namespace engine

#endif // ifndef _BAD_SCALAR_H_
