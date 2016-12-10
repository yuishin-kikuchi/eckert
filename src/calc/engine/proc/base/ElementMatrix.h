////==--------------------------------------------------------------------====//
// ECKERT ELEMENT - MATRIX
// [ Update ]
// Nov 13, 2016
//====--------------------------------------------------------------------==////

#ifndef _ECKERT_MATRIX_H_
#define _ECKERT_MATRIX_H_

#include "Element.h"
#include <vector>

namespace engine {

class Matrix : public Element {
	public:
		virtual unsigned int getType() const {
			return MATRIX;
		}
	private:
		std::size_t _size_m;
		std::size_t _size_n;
		std::vector<std::vector<SpElement>> _mat;
	public:
		Matrix() = delete;
		Matrix(const std::vector<std::vector<SpElement>> &mat);
		virtual SpElement clone() const;
		virtual bool hasError() const {
			return (((0 == _size_m) || (0 == _size_n)) ? true : false);
		}
		SpElement get(
			const std::size_t &pos_i,
			const std::size_t &pos_j) const {
			return _mat.at(pos_i).at(pos_j);
		}
		const std::vector<SpElement>& getVector(const std::size_t &i) const {
			return _mat.at(i);
		}
		const std::vector<std::vector<SpElement>>& getMatrix() const {
			return _mat;
		}
		std::size_t getM() const {
			return _size_m;
		}
		std::size_t getN() const {
			return _size_n;
		}
		bool isSquareMatrix() const {
			if (_size_m == _size_n) {
				if (0 != _size_m) {
					return true;
				}
			}
			return false;
		}
};

} // namespace engine

#endif // ifndef _ECKERT_MATRIX_H_
