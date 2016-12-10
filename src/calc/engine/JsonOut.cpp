#include "JsonOut.h"
#include "proc/base/core/StackEngine.h"
#include "StringEngine.h"
#include "CalculationConfig.h"
#include <fstream>
#include <iomanip>

namespace engine {

////==--------------------------------------------------------------------====//
// JSON OUT / OUTPUT FILE
// [ Update ]
// Nov 19, 2016
//====--------------------------------------------------------------------==////
bool JsonOut::outputFile(
	const StackEngine &stackEngine,
	const StringEngine &stringEngine,
	const CalculationConfig &config,
	const std::string &filename)
try {
	std::ofstream output;
	output.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	output.open(filename, std::ios::out | std::ios::trunc);
	return outputStream(stackEngine, stringEngine, config, output);
}
catch (std::ofstream::failure &) {
	return true;
}

////==--------------------------------------------------------------------====//
// JSON OUT / OUTPUT STREAM
// [ Update ]
// Nov 19, 2016
//====--------------------------------------------------------------------==////
bool JsonOut::outputStream(
	const StackEngine &stackEngine,
	const StringEngine &stringEngine,
	const CalculationConfig &config,
	std::ostream &output)
{
	const auto &stk = stackEngine.refStack();
	const auto &reg = stackEngine.refRegister();
	output << '{' << std::endl;
	//==  Register  ==//
	output << "  \"register\": [" << std::endl;
	for (std::size_t i = 0; i < reg.size(); ++i) {
		auto elm = reg.at(i);
		if (nullptr != elm) {
			output << "    {";
			output << "\"type\": \"";
			output << stringEngine.typeToLongString(elm) << "\", ";
			output << "\"value\": \"";
			output << stringEngine.elementToString(config, elm) << "\"}";
		}
		else {
			output << "    {\"type\": null, \"value\": null}";
		}
		if (i + 1 != reg.size()) {
			output << ',';
		}
		output << std::endl;
	}
	output << "  ]," << std::endl;
	//==  Stack  ==//
	output << "  \"stack\": [" << std::endl;
	for (std::size_t i = 0; i < stk.size(); ++i) {
		auto elm = stk.at(i);
		if (nullptr == elm) {
			break;
		}
		output << "    {";
		output << "\"type\": \"";
		output << stringEngine.typeToLongString(elm) << "\", ";
		output << "\"value\": \"";
		output << stringEngine.elementToString(config, elm) << "\"}";
		if (i + 1 != stk.size() && stk.at(i + 1)) {
			output << ',';
		}
		output << std::endl;
	}
	output << "  ]" << std::endl;
	output << '}' << std::endl;
	return false;
}

} // namespace engine
