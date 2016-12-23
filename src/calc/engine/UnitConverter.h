#ifndef _UNIT_CONVERTER_H_
#define _UNIT_CONVERTER_H_

#include "proc/ElementMacros.h"
#include <map>
#include <string>

////==--------------------------------------------------------------------====//
// UNIT CONVERTER
// [ Update ]
// Dec 22, 2016
//====--------------------------------------------------------------------==////

namespace engine {

struct CoversionCriterion {
	std::string name;
	unsigned int type;
	SpElement step;
	SpElement zero;
};

class UnitConverter {
	public:
		#include "UnitConverter__units.h"
		static const std::map <std::string, unsigned int> unitKeywords;
		static const std::map <unsigned int, CoversionCriterion> criteria;
		static const std::string& getUnitName(const unsigned int &unit);
		static bool convert(SpElement &dst, const SpElement &src, const unsigned int &fromUnit, const unsigned int &toUnit);
};

} // namespace engine

#endif // _UNIT_CONVERTER_H_
