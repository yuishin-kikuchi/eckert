////==--------------------------------------------------------------------====//
// ECKERT ELEMENT - ETUPLE
// [ Update ]
// Nov 13, 2016
//====--------------------------------------------------------------------==////

#ifndef _ECKERT_ETUPLE_H_
#define _ECKERT_ETUPLE_H_

#include "Element.h"
#include <vector>

namespace engine {

class ETuple : public Element {
	public:
		virtual unsigned int getType() const {
			return ETUPLE;
		}
		enum class TupleType : unsigned int {
			COLUMN,
			ROW,
		};
	private:
		size_t _size;
		TupleType _ttype;
		std::vector<SpElement> _set;
	public:
		ETuple() = delete;
		ETuple(const std::vector<SpElement> &set, const TupleType &type);
		virtual SpElement clone() const;
		bool hasError() const {
			return (0 == _size);
		}
		SpElement get(const std::size_t &i) const {
			return _set.at(i);
		}
		TupleType getTupleType() {
			return _ttype;
		}
		std::size_t getSize() const {
			return _size;
		}
		const std::vector<SpElement> getVector() const {
			return _set;
		}
};

} // namespace engine

#endif // ifndef _ELMSET_ETUPLE_H_
