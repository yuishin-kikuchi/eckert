////==--------------------------------------------------------------------====//
// ECKERT EXCEPTION - TECHNICAL ERROR
// [ Update ]
// Nov 13, 2016
//====--------------------------------------------------------------------==////

#ifndef _TECHNICAL_ERROR_H_
#define _TECHNICAL_ERROR_H_

#include "EckertException.h"

namespace engine {
	class TechnicalError : public EckertException {
		public:
			TechnicalError()
			 : EckertException() {}
			TechnicalError(const char *str)
			 : EckertException(str){}
			TechnicalError(const char *str, const char *place)
			 : EckertException(str, place) {}
			TechnicalError(const TechnicalError &obj)
			 : EckertException(obj) {}
	};
} // namespace engine

#endif // ifndef _TECHNICAL_ERROR_H_
