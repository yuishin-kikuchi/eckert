////==--------------------------------------------------------------------====//
// ECKERT ELEMENT
// [ Update ]
// Nov 18, 2016
//====--------------------------------------------------------------------==////

#ifndef _ECKERT_ELEMENT_H_
#define _ECKERT_ELEMENT_H_

#include "EckertTypedef.h"
#include "core/BaseElement.h"

namespace engine {

class Element : public BaseElement {
	public:
		enum : unsigned int {
			// KIND
			NUMERIC_TYPE = 32,  // 0b 0010 0000
			SCALAR_TYPE  = 48,  // 0b 0011 0000
			BINARY_TYPE  = 64,  // 0b 0100 0000
			SET_TYPE     = 128, // 0b 1000 0000
			// TYPE
			ERROR        = 0,
			ESTRING      = 1,
			EINFINITY    = 2,
			UINTEGER     = 3,
			INTEGER      = 0 | SCALAR_TYPE,
			FLOATING     = 1 | SCALAR_TYPE,
			RATIONAL     = 2 | SCALAR_TYPE,
			COMPLEX      = 0 | NUMERIC_TYPE,
			ETUPLE       = 0 | SET_TYPE,
			MATRIX       = 1 | SET_TYPE,
			BOOLEAN      = 0 | BINARY_TYPE,
			BINARY8      = 1 | BINARY_TYPE,
			BINARY16     = 2 | BINARY_TYPE,
			BINARY32     = 3 | BINARY_TYPE,
			BINARY64     = 4 | BINARY_TYPE,
		};
	public:
		virtual unsigned int getType() const = 0;
		virtual SpElement clone() const = 0;
		virtual bool isType(const unsigned int &type) const {
			return ((type == this->getType()) ? true : false);
		}
		virtual bool isKindOf(const unsigned int &type) const {
			return ((type & this->getType()) ? true : false);
		}
		virtual bool hasError() const {
			return false;
		}
};

} // namespace engine

#endif // ifndef _ECKERT_ELEMENT_H_
