#include "ElementMatrix.h"

namespace engine {

////==--------------------------------------------------------------------====//
// ECKERT ELEMENT - MATRIX / Constructor
// [ description ]
// Constructor using vector of vector of pointer to shared pointers.
// [ Update ]
// Nov 13, 2016
//====--------------------------------------------------------------------==////
Matrix::Matrix(const std::vector<std::vector<SpElement>> &mat) {
	_size_m = 0;
	_size_n = 0;
	std::size_t height = mat.size();
	if (0 != height) {
		// if the vector size is not 0
		// then check the vector
		bool is_formal = true;
		std::size_t width = mat.at(0).size();
		// all vectors must be the same size
		for (std::size_t i = 1; i < height; ++i) {
			auto &src_row = mat.at(i);
			if (width != src_row.size()) {
				// if the size is wrong, break
				is_formal = false;
				break;
			}
			for (std::size_t j = 0; j < width; ++j) {
				const auto &temp = src_row.at(j);
				if (nullptr == temp) {
					// if nullptr detected, break
					is_formal = false;
					break;
				}
			}
		}
		if (is_formal) {
			// if all done, set
			_mat = mat;
			_size_m = height;
			_size_n = width;
		}
	}
}

////==--------------------------------------------------------------------====//
// ECKERT ELEMENT - MATRIX / Clone
// [ description ]
// Generate its clone and return the shared pointer that points.
// [ Update ]
// Nov 13, 2016
//====--------------------------------------------------------------------==////
SpElement Matrix::clone() const {
	std::vector<std::vector<SpElement>> dst;
	dst.resize(_mat.size());
	for (std::size_t pos_i = 0; pos_i < _size_m; ++pos_i) {
		auto &src_row = _mat.at(pos_i);
		auto &dst_row = dst.at(pos_i);
		dst_row.resize(src_row.size());
		for (std::size_t pos_j = 0; pos_j < _size_n; ++pos_j) {
			dst_row.at(pos_j) = src_row.at(pos_j)->clone();
		}
	}
	return SpElement(new Matrix(dst));
}

} // namespace engine
