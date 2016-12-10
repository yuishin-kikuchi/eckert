#ifndef _ECKERT_PARSER_H_
#define _ECKERT_PARSER_H_

#include "engine/EngineeringCalculator.h"
#include "engine/FloatingDisplayConfig.h"
#include "util/EckertStates.h"
#include "ncheck/NumericCheck.h"

////==--------------------------------------------------------------------====//
// ECKERT PARSER
// [ Update ]
// Nov 20, 2016
//====--------------------------------------------------------------------==////

class EckertParser {
	public:
		enum class ReturnCode : int {
			SUCCESS = 0,
			FAILURE,
			NOT_FOUND,
			MUST_CLEAR,
			WAIT_USER,
		};
		enum class BinarySize : int {
			BYTE,
			WORD,
			DWORD,
			QWORD,
		};
	private:
		BinarySize _size;
		engine::SpElement multiplyByPrefix(const engine::SpElement &elm, const NumericCheck::MetricPrefix &prefix);
		void setPrefixMessage(engine::StackEngine &stackEngine, const NumericCheck::MetricPrefix &prefix);
	public:
		EckertParser();
		void init();
		ReturnCode manageConfig(
			engine::StackEngine &stackEngine,
			engine::FloatingDisplayConfig &fcfg,
			EckertStates &stat,
			const std::string &str);
		ReturnCode pushElementByString(
			const std::string &str,
			engine::StackEngine &stackEngine,
			EckertStates &stat);
		ReturnCode genSpElement(
			engine::SpElement &r_set,
			const std::string &str,
			engine::StackEngine &stackEngine,
			EckertStates &stat);
		ReturnCode genSpElementString(
			engine::SpElement &r_set,
			const std::string &str,
			engine::StackEngine &stackEngine,
			EckertStates &stat);
		ReturnCode genSpElementNumeric(
			engine::SpElement &r_set,
			const std::string &str,
			engine::StackEngine &stackEngine,
			EckertStates &stat);
		ReturnCode genSpElementBinary(
			engine::SpElement &r_set,
			const std::string &str,
			engine::StackEngine &stackEngine,
			EckertStates &stat);
		ReturnCode genSpElementConstant(
			engine::SpElement &r_set,
			const std::string &str,
			engine::StackEngine &stackEngine,
			EckertStates &stat);
		void setBinarySize(const BinarySize &size) {
			_size = size;
		}
		BinarySize getBinarySize() const{
			return _size;
		}
};

#endif // _ECKERT_PARSER_H_
