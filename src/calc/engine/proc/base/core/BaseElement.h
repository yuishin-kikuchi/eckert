////==--------------------------------------------------------------------====//
// ECKERT ELEMENT
// [ Update ]
// Nov 13, 2016
//====--------------------------------------------------------------------==////

#ifndef _ECKERT_BASE_ELEMENT_H_
#define _ECKERT_BASE_ELEMENT_H_

#include <memory>

namespace engine {
	class BaseElement;
	using SpElement = std::shared_ptr<BaseElement>;
	class BaseElement {
		public:
			virtual unsigned int getType() const = 0;
			virtual SpElement clone() const = 0;
			virtual bool isType(const unsigned int &type) const = 0;
			virtual bool isKindOf(const unsigned int &type) const = 0;
			virtual bool hasError() const = 0;
	};
} // namespace engine

#endif // ifndef _ECKERT_BASE_ELEMENT_H_
