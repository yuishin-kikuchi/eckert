#ifndef _ECKERT_CONSTANTS_H_
#define _ECKERT_CONSTANTS_H_

#include "proc/ElementMacros.h"
#include <map>
#include <string>

////==--------------------------------------------------------------------====//
// ECKERT CONSTANTS
// [ Update ]
// Aug 22, 2018
//====--------------------------------------------------------------------==////

namespace engine {

struct SpElementNamePair {
	SpElement elm;
	std::string name;
};

class EckertConstants {
	public:
		#include "EckertConstants__enum.h"
		static const std::map <std::string, SpElement> prefixValues;
		static const std::map <std::string, unsigned int> scientificConstantKeywords;
		static const std::map <unsigned int, SpElementNamePair> scientificConstantValues;
};

} // namespace engine

#endif // _ECKERT_CONSTANTS_H_
