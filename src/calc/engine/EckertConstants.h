#ifndef _ECKERT_CONSTANTS_H_
#define _ECKERT_CONSTANTS_H_

#include "proc/ElementMacros.h"
#include <map>
#include <string>

////==--------------------------------------------------------------------====//
// ECKERT CONSTANTS
// [ Update ]
// Nov 17, 2016
//====--------------------------------------------------------------------==////

namespace engine {

struct SpElementNamePair {
	SpElement elm;
	std::string name;
};

class EckertConstants {
	public:
		static const std::map <std::string, SpElement> prefixValue;
		static const std::map <std::string, SpElementNamePair> scientificConstants;
};

} // namespace engine

#endif // _ECKERT_CONSTANTS_H_
