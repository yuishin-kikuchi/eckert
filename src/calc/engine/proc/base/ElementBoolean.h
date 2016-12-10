////==--------------------------------------------------------------------====//
// ECKERT ELEMENT - BOOLEAN
// [ Update ]
// Nov 13, 2016
//====--------------------------------------------------------------------==////

#ifndef _ECKERT_BOOLEAN_H_
#define _ECKERT_BOOLEAN_H_

#include "Element.h"

namespace engine {

class Boolean : public Element {
	public:
		virtual unsigned int getType() const {
			return BOOLEAN;
		}
	private:
		bool _flag;
	public:
		Boolean() = delete;
		Boolean(const bool &flag);
		virtual SpElement clone() const;
		bool get() const {
			return _flag;
		}
};

} // namespace engine

#endif // ifndef _ECKERT_BOOLEAN_H_
