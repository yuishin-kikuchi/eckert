////==--------------------------------------------------------------------====//
// ECKERT ELEMENT - INTEGER
// [ Update ]
// Nov 13, 2016
//====--------------------------------------------------------------------==////

#ifndef _ECKERT_INTEGER_H_
#define _ECKERT_INTEGER_H_

#include "Element.h"

namespace engine {

class Integer : public Element {
	public:
		virtual unsigned int getType() const {
			return INTEGER;
		}
	private:
		integer_t _data;
	public:
		Integer() = delete;
		Integer(const integer_t &num);
		virtual SpElement clone() const;
		integer_t get() const{
			return _data;
		}
};

} // namespace engine

#endif // ifndef _ECKERT_INTEGER_H_
