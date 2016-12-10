#include "ElementETuple.h"

namespace engine {

////==--------------------------------------------------------------------====//
// ECKERT ELEMENT - ETUPLE / Constructor
// [ description ]
// Constructor using vector of pointer to shared pointers.
// [ Update ]
// Jan 25, 2016
//====--------------------------------------------------------------------==////
ETuple::ETuple(const std::vector<SpElement> &set, const ETuple::TupleType &type) {
	_size = 0;
	_ttype = ETuple::TupleType::COLUMN;
	std::size_t elements = set.size();
	if (0 != elements) {
		bool is_formal = true;
		for (std::size_t ucnt = 0; ucnt < elements; ++ucnt) {
			const auto &temp = set.at(ucnt);
			if (nullptr == temp) {
				is_formal = false;
				break;
			}
		}
		if (is_formal) {
			_set = set;
			_size = elements;
			_ttype = type;
		}
	}
}

////==--------------------------------------------------------------------====//
// ECKERT ELEMENT - ETUPLE / Clone
// [ description ]
// Generate its clone and return the shared pointer that points.
// [ Update ]
// Jan 25, 2016
//====--------------------------------------------------------------------==////
SpElement ETuple::clone() const {
	std::vector<SpElement> dst;
	dst.resize(_size);
	for (std::size_t ucnt = 0; ucnt < _size; ++ucnt) {
		dst.at(ucnt) = _set.at(ucnt)->clone();
	}
	return SpElement(new ETuple(dst, _ttype));
}

} // namespace engine
