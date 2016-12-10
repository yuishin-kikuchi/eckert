#include "GeneralOperator.h"

namespace engine {

GeneralProcessor GeneralOperator::_proc;

////==--------------------------------------------------------------------====//
// GENERAL OPERATOR / HAS ENOUGH ITEMS
// [ description ]
// Judge if the calculator has enough items.
// [ Update ]
// Nov 17, 2016
//====--------------------------------------------------------------------==////
bool GeneralOperator::hasEnoughItems(StackEngine &stackEngine) const {
	auto &stack = stackEngine.refStack();
	std::size_t currentItemCount = stack.size();
	if (currentItemCount >= this->getRequiredCount()) {
		return true;
	}
	else {
		stackEngine.setErrorMessage("FEW_ARG");
		return false;
	}
}

////==--------------------------------------------------------------------====//
// GENERAL OPERATOR / GET SIZE_T VALUE
// [ description ]
// Get size_t value from SpElement
// [ Update ]
// Nov 14, 2016
//====--------------------------------------------------------------------==////
bool GeneralOperator::getSizetValue(std::size_t &num, const SpElement &elem) {
	switch (elem->getType()) {
		case Element::INTEGER: {
			auto temp = GET_INTEGER_DATA(elem);
			if (temp < 0) {
				return true;
			}
			else {
				num = (std::size_t)temp;
			}
			break;
		}
		case Element::BINARY8: {
			num = (std::size_t)GET_BYTE_DATA(elem);
			break;
		}
		case Element::BINARY16: {
			num = (std::size_t)GET_WORD_DATA(elem);
			break;
		}
		case Element::BINARY32: {
			num = (std::size_t)GET_DWORD_DATA(elem);
			break;
		}
		case Element::BINARY64: {
			num = (std::size_t)GET_QWORD_DATA(elem);
			break;
		}
		default:
			return true;
	}
	return false;
}

} // namespace engine
