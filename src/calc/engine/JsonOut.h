#ifndef _JSON_OUT_H_
#define _JSON_OUT_H_

#include <iostream>
#include <string>

////==--------------------------------------------------------------------====//
// HOMURA JSON OUT
// [ Update ]
// Nov 19, 2016
//====--------------------------------------------------------------------==////

namespace engine {

class StackEngine;
class StringEngine;
class CalculationConfig;

class JsonOut {
	public:
		static bool outputFile(
			const StackEngine &stackEngine,
			const StringEngine &stringEngine,
			const CalculationConfig &config,
			const std::string &filename);
		static bool outputStream(
			const StackEngine &stackEngine,
			const StringEngine &stringEngine,
			const CalculationConfig &config,
			std::ostream &output);
};

} // namespace engine

#endif // _JSON_OUT_H_
