////==--------------------------------------------------------------------====//
// ECKERT ELEMENT - BINARY32
// [ Update ]
// Nov 18, 2016
//====--------------------------------------------------------------------==////

#ifndef _ECKERT_BINARY32_H_
#define _ECKERT_BINARY32_H_

#include "Element.h"

namespace engine {
	
class Binary32 : public Element {
	public:
		virtual unsigned int getType() const {
			return BINARY32;
		}
	private:
		uint32_t _data;
	public:
		Binary32() = delete;
		Binary32(const uint32_t &num);
		virtual SpElement clone() const;
		uint32_t get() const {
			return _data;
		}
};

} // namespace engine

#endif // ifndef _ECKERT_BINARY32_H_
