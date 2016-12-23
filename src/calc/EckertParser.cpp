#include "EckertParser.h"
#include "engine/proc/GeneralProcessor.h"
#include "engine/EckertConstants.h"
#include "util/StringChecker.h"
#include "ncheck/StringConverter.h"
#include "engine/proc/base/math/floatToRational.h"

////==--------------------------------------------------------------------====//
// ECKERT PARSER / CONSTRUCTOR
// [ Update ]
// Dec 03, 2016
//====--------------------------------------------------------------------==////
EckertParser::EckertParser() {
	init();
}

////==--------------------------------------------------------------------====//
// ECKERT PARSER / INITIALIZER
// [ Update ]
// Dec 03, 2016
//====--------------------------------------------------------------------==////
void EckertParser::init() {
	_size = BinarySize::DWORD;
}

////==--------------------------------------------------------------------====//
// ECKERT PARSER / MANAGE CONFIG
// [ Update ]
// Dec 03, 2016
//====--------------------------------------------------------------------==////
EckertParser::ReturnCode EckertParser::manageConfig(
	engine::StackEngine &stackEngine,
	engine::FloatingDisplayConfig &fcfg,
	EckertStates &stat,
	const std::string &str)
try {
	auto waiting = stat.getWaitingState();
	if (StringChecker::isReset(str)) {
		stat.setWaitingState(EckertStates::RESET_CONFIRM);
		stackEngine.setCommandMessage("H_REST");
		stackEngine.setErrorMessage("CNFM");
		return EckertParser::ReturnCode::WAIT_USER;
	}
	else if (StringChecker::isDisplayDigit(str)) {
		switch (fcfg.getDisplayMode()) {
			case engine::FloatingDisplayConfig::STANDARD:
				stat.setWaitingState(EckertStates::STD_DIGITS);
				stackEngine.setCommandMessage("D_STD");
				stackEngine.setErrorMessage("WAIT_INT");
				return EckertParser::ReturnCode::SUCCESS;
			case engine::FloatingDisplayConfig::FIXED:
				stat.setWaitingState(EckertStates::FIX_DIGITS);
				stackEngine.setCommandMessage("D_FIX");
				stackEngine.setErrorMessage("WAIT_INT");
				return EckertParser::ReturnCode::SUCCESS;
			case engine::FloatingDisplayConfig::SCIENTIFIC:
				stat.setWaitingState(EckertStates::SCI_DIGITS);
				stackEngine.setCommandMessage("D_SCI");
				stackEngine.setErrorMessage("WAIT_INT");
				return EckertParser::ReturnCode::SUCCESS;
			case engine::FloatingDisplayConfig::ENGINEERING:
				stat.setWaitingState(EckertStates::ENG_DIGITS);
				stackEngine.setCommandMessage("D_ENG");
				stackEngine.setErrorMessage("WAIT_INT");
				return EckertParser::ReturnCode::SUCCESS;
			default:
				break;
		}
		return EckertParser::ReturnCode::FAILURE;
	}
	else {
		stat.resetWaitingState();
		switch (waiting) {
			case EckertStates::WaitingState::RESET_CONFIRM:
				stackEngine.setCommandMessage("H_REST");
				if (StringChecker::isYes(str)) {
					stackEngine.setErrorMessage("DONE");
					return EckertParser::ReturnCode::MUST_CLEAR;
				}
				else if (StringChecker::isNo(str)) {
					stackEngine.setErrorMessage("CNCL");
					return EckertParser::ReturnCode::SUCCESS;
				}
				else {
					stackEngine.setErrorMessage("INV_IN");
					return EckertParser::ReturnCode::FAILURE;
				}
			case EckertStates::WaitingState::STD_DIGITS:
				stackEngine.setCommandMessage("D_STD");
				if (!NumericCheck::isUnsigned(str)) {
					stackEngine.setErrorMessage("INV_IN");
					return EckertParser::ReturnCode::FAILURE;
				}
				else {
					int temp = StringConverter::convert<int>(str);
					if (temp < fcfg.getStdMin()) {
						temp = fcfg.getStdMin();
						stackEngine.setErrorMessage("S_MIN");
					}
					else if (temp > fcfg.getStdMax()) {
						temp = fcfg.getStdMax();
						stackEngine.setErrorMessage("S_MAX");
					}
					else {
						stackEngine.setErrorMessage("S_NRM");
					}
					fcfg.setStdDigits(temp);
					return EckertParser::ReturnCode::SUCCESS;
				}
			case EckertStates::WaitingState::FIX_DIGITS:
				stackEngine.setCommandMessage("D_FIX");
				if (!NumericCheck::isUnsigned(str)) {
					stackEngine.setErrorMessage("INV_IN");
					return EckertParser::ReturnCode::FAILURE;
				}
				else {
					int temp = StringConverter::convert<int>(str);
					if (temp < fcfg.getFixMin()) {
						temp = fcfg.getFixMin();
						stackEngine.setErrorMessage("S_MIN");
					}
					else if (temp > fcfg.getFixMax()) {
						temp = fcfg.getFixMax();
						stackEngine.setErrorMessage("S_MAX");
					}
					else {
						stackEngine.setErrorMessage("S_NRM");
					}
					fcfg.setFixDigits(temp);
					return EckertParser::ReturnCode::SUCCESS;
				}
			case EckertStates::WaitingState::SCI_DIGITS:
				stackEngine.setCommandMessage("D_SCI");
				if (!NumericCheck::isUnsigned(str)) {
					stackEngine.setErrorMessage("INV_IN");
					return EckertParser::ReturnCode::FAILURE;
				}
				else {
					int temp = StringConverter::convert<int>(str);
					if (temp < fcfg.getSciMin()) {
						temp = fcfg.getSciMin();
						stackEngine.setErrorMessage("S_MIN");
					}
					else if (temp > fcfg.getSciMax()) {
						temp = fcfg.getSciMax();
						stackEngine.setErrorMessage("S_MAX");
					}
					else {
						stackEngine.setErrorMessage("S_NRM");
					}
					fcfg.setSciDigits(temp);
					return EckertParser::ReturnCode::SUCCESS;
				}
			case EckertStates::WaitingState::ENG_DIGITS:
				stackEngine.setCommandMessage("D_ENG");
				if (!NumericCheck::isUnsigned(str)) {
					stackEngine.setErrorMessage("INV_IN");
					return EckertParser::ReturnCode::FAILURE;
				}
				else {
					int temp = StringConverter::convert<int>(str);
					if (temp < fcfg.getEngMin()) {
						temp = fcfg.getEngMin();
						stackEngine.setErrorMessage("S_MIN");
					}
					else if (temp > fcfg.getEngMax()) {
						temp = fcfg.getEngMax();
						stackEngine.setErrorMessage("S_MAX");
					}
					else {
						stackEngine.setErrorMessage("S_NRM");
					}
					fcfg.setEngDigits(temp);
					return EckertParser::ReturnCode::SUCCESS;
				}
			case EckertStates::WaitingState::NONE:
				break;
			default:
				break;
		}
	}
	return EckertParser::ReturnCode::NOT_FOUND;
}
catch (StringConverter::Failure &) {
	stackEngine.setCommandMessage("ERROR");
	stackEngine.setErrorMessage("ERR_IN");
	stat.resetWaitingState();
	return EckertParser::ReturnCode::FAILURE;
}

////==--------------------------------------------------------------------====//
// ECKERT PARSER / GENERATE ELEMENT FROM STRING
// [ Update ]
// Dec 03, 2016
//====--------------------------------------------------------------------==////
EckertParser::ReturnCode
EckertParser::pushElementByString(
	const std::string &str,
	engine::StackEngine &stackEngine,
	EckertStates &stat)
{
	auto &stack = stackEngine.refExStack();
	engine::SpElement r_set;
	switch (genSpElement(r_set, str, stackEngine, stat)) {
		case EckertParser::ReturnCode::SUCCESS:
			stack.push(r_set);
			return EckertParser::ReturnCode::SUCCESS;
		case EckertParser::ReturnCode::FAILURE:
			stackEngine.setCommandMessage("ERROR");
			stackEngine.setErrorMessage("ERR_IN");
			return EckertParser::ReturnCode::FAILURE;
		case EckertParser::ReturnCode::NOT_FOUND:
			// fall through
		default:
			break;
	}
	return EckertParser::ReturnCode::NOT_FOUND;
}

////==--------------------------------------------------------------------====//
// ECKERT PARSER / GENERATE ELEMENT FROM STRING
// [ Update ]
// Dec 03, 2016
//====--------------------------------------------------------------------==////
EckertParser::ReturnCode
EckertParser::genSpElement(
	engine::SpElement &r_set,
	const std::string &str,
	engine::StackEngine &stackEngine,
	EckertStates &stat)
{
	switch (genSpElementNumeric(r_set, str, stackEngine, stat)) {
		case EckertParser::ReturnCode::SUCCESS:
			return EckertParser::ReturnCode::SUCCESS;
		case EckertParser::ReturnCode::FAILURE:
			return EckertParser::ReturnCode::FAILURE;
		case EckertParser::ReturnCode::NOT_FOUND:
			// fall through
		default:
			break;
	}
	switch (genSpElementBinary(r_set, str, stackEngine, stat)) {
		case EckertParser::ReturnCode::SUCCESS:
			return EckertParser::ReturnCode::SUCCESS;
		case EckertParser::ReturnCode::FAILURE:
			return EckertParser::ReturnCode::FAILURE;
		case EckertParser::ReturnCode::NOT_FOUND:
			// fall through
		default:
			break;
	}
	switch (genSpElementConstant(r_set, str, stackEngine, stat)) {
		case EckertParser::ReturnCode::SUCCESS:
			return EckertParser::ReturnCode::SUCCESS;
		case EckertParser::ReturnCode::FAILURE:
			// fall through
		case EckertParser::ReturnCode::NOT_FOUND:
			// fall through
		default:
			break;
	}
	switch (genSpElementString(r_set, str, stackEngine, stat)) {
		case EckertParser::ReturnCode::SUCCESS:
			return EckertParser::ReturnCode::SUCCESS;
		case EckertParser::ReturnCode::FAILURE:
			return EckertParser::ReturnCode::FAILURE;
		case EckertParser::ReturnCode::NOT_FOUND:
			// fall through
		default:
			break;
	}
	return EckertParser::ReturnCode::NOT_FOUND;
}

////==--------------------------------------------------------------------====//
// ECKERT PARSER / GENERATE STRING ELEMENT FROM STRING
// [ Update ]
// Dec 03, 2016
//====--------------------------------------------------------------------==////
EckertParser::ReturnCode
EckertParser::genSpElementString(
	engine::SpElement &r_set,
	const std::string &str,
	engine::StackEngine &stackEngine,
	EckertStates &stat)
{
	if (StringChecker::isDoubleQuoted(str)) {
		auto temp = str;
		temp.erase(0, 1);
		temp.erase(temp.size() - 1, 1);
		r_set = GEN_ESTRING(temp);
		stackEngine.setCommandMessage("PUSH_S");
		stackEngine.setErrorMessage("STR");
		stackEngine.setAdditionalMessage("ONE");
		return EckertParser::ReturnCode::SUCCESS;
	}
	else {
		return EckertParser::ReturnCode::NOT_FOUND;
	}
}

////==--------------------------------------------------------------------====//
// ECKERT PARSER / GENERATE NUMERIC ELEMENT FROM STRING
// [ Update ]
// Dec 20, 2016
//====--------------------------------------------------------------------==////
EckertParser::ReturnCode
EckertParser::genSpElementNumeric(
	engine::SpElement &r_set,
	const std::string &str,
	engine::StackEngine &stackEngine,
	EckertStates &stat)
try {
	auto lower_token = StringUtility::genLowerString(str);
	NumericCheck::MetricPrefix mp;
	NumericCheck::NumberType input_type;
	engine::GeneralProcessor calc;
	input_type = NumericCheck::whatNumber(str, mp);
	switch (input_type) {
		case NumericCheck::NumberType::T_INFINITY: {
			if ('-' == str.at(0)) {
				r_set = GEN_EINFINITY(engine::GeneralProcessor::NEGATIVE);
			}
			else {
				r_set = GEN_EINFINITY(engine::GeneralProcessor::POSITIVE);
			}
			stackEngine.setCommandMessage("PUSH_N");
			stackEngine.setErrorMessage("INF");
			stackEngine.setAdditionalMessage("ONE");
			return EckertParser::ReturnCode::SUCCESS;
		}
		case NumericCheck::NumberType::INTEGER: {
			NumericCheck::erasePrefix(lower_token, input_type, mp);
			auto temp = StringConverter::convert<engine::integer_t>(lower_token);
			r_set = GEN_INTEGER(temp);
			r_set = multiplyByPrefix(r_set, mp);
			stackEngine.setCommandMessage("PUSH_N");
			stackEngine.setErrorMessage("INT");
			setPrefixMessage(stackEngine, mp);
			return EckertParser::ReturnCode::SUCCESS;
		}
		case NumericCheck::NumberType::DECIMAL: {
			NumericCheck::erasePrefix(lower_token, input_type, mp);
			auto temp = StringConverter::convert<engine::floating_t>(lower_token);
			r_set = GEN_FLOATING(temp);
			r_set = multiplyByPrefix(r_set, mp);
			stackEngine.setCommandMessage("PUSH_N");
			stackEngine.setErrorMessage("DEC");
			setPrefixMessage(stackEngine, mp);
			return EckertParser::ReturnCode::SUCCESS;
		}
		case NumericCheck::NumberType::EXPONENTIAL: {
			NumericCheck::erasePrefix(lower_token, input_type, mp);
			auto temp = StringConverter::convert<engine::floating_t>(lower_token);
			r_set = GEN_FLOATING(temp);
			r_set = multiplyByPrefix(r_set, mp);
			stackEngine.setCommandMessage("PUSH_N");
			stackEngine.setErrorMessage("EXP");
			setPrefixMessage(stackEngine, mp);
			return EckertParser::ReturnCode::SUCCESS;
		}
		case NumericCheck::NumberType::IMAG_INTEGER: {
			if ((!lower_token.compare("i")) || (!lower_token.compare("+i"))) {
				r_set = POS_IMAGINARY;
			}
			else if (!lower_token.compare("-i")) {
				r_set = NEG_IMAGINARY;
			}
			else {
				NumericCheck::erasePrefix(lower_token, input_type, mp);
				NumericCheck::removeImag(lower_token);
				auto temp = StringConverter::convert<engine::integer_t>(lower_token);
				auto imag = multiplyByPrefix(GEN_INTEGER(temp), mp);
				r_set = GEN_COMPLEX(GEN_INTEGER(0), imag);
			}
			stackEngine.setCommandMessage("PUSH_N");
			stackEngine.setErrorMessage("IINT");
			setPrefixMessage(stackEngine, mp);
			return EckertParser::ReturnCode::SUCCESS;
		}
		case NumericCheck::NumberType::IMAG_DECIMAL: {
			NumericCheck::erasePrefix(lower_token, input_type, mp);
			NumericCheck::removeImag(lower_token);
			auto temp = StringConverter::convert<engine::floating_t>(lower_token);
			auto imag = multiplyByPrefix(GEN_FLOATING(temp), mp);
			r_set = GEN_COMPLEX(GEN_INTEGER(0), imag);
			stackEngine.setCommandMessage("PUSH_N");
			stackEngine.setErrorMessage("IDEC");
			setPrefixMessage(stackEngine, mp);
			return EckertParser::ReturnCode::SUCCESS;
		}
		case NumericCheck::NumberType::IMAG_EXPONENTIAL: {
			NumericCheck::erasePrefix(lower_token, input_type, mp);
			NumericCheck::removeImag(lower_token);
			auto temp = StringConverter::convert<engine::floating_t>(lower_token);
			auto imag = multiplyByPrefix(GEN_FLOATING(temp), mp);
			r_set = GEN_COMPLEX(GEN_INTEGER(0), imag);
			stackEngine.setCommandMessage("PUSH_N");
			stackEngine.setErrorMessage("IEXP");
			setPrefixMessage(stackEngine, mp);
			return EckertParser::ReturnCode::SUCCESS;
		}
		case NumericCheck::NumberType::NOT_NUMBER:
			break;
		default:
			break;
	}
	return EckertParser::ReturnCode::NOT_FOUND;
}
catch (StringConverter::Failure &) {
	return EckertParser::ReturnCode::FAILURE;
}

////==--------------------------------------------------------------------====//
// ECKERT PARSER / MULTIPLY BY PREFIX
// [ Update ]
// Dec 03, 2016
//====--------------------------------------------------------------------==////
engine::SpElement EckertParser::multiplyByPrefix(const engine::SpElement &elm, const NumericCheck::MetricPrefix &prefix) {
	engine::GeneralProcessor calc;
	engine::SpElement to_multiply;
	switch (prefix) {
		case NumericCheck::MetricPrefix::YOCTO:
			to_multiply = engine::EckertConstants::prefixValue.at("y");
			break;
		case NumericCheck::MetricPrefix::ZEPTO:
			to_multiply = engine::EckertConstants::prefixValue.at("z");
			break;
		case NumericCheck::MetricPrefix::ATTO:
			to_multiply = engine::EckertConstants::prefixValue.at("a");
			break;
		case NumericCheck::MetricPrefix::FEMTO:
			to_multiply = engine::EckertConstants::prefixValue.at("f");
			break;
		case NumericCheck::MetricPrefix::PICO:
			to_multiply = engine::EckertConstants::prefixValue.at("p");
			break;
		case NumericCheck::MetricPrefix::NANO:
			to_multiply = engine::EckertConstants::prefixValue.at("n");
			break;
		case NumericCheck::MetricPrefix::MICRO:
			to_multiply = engine::EckertConstants::prefixValue.at("u");
			break;
		case NumericCheck::MetricPrefix::MILLI:
			to_multiply = engine::EckertConstants::prefixValue.at("m");
			break;
		case NumericCheck::MetricPrefix::CENTI:
			to_multiply = engine::EckertConstants::prefixValue.at("c");
			break;
		case NumericCheck::MetricPrefix::DECI:
			to_multiply = engine::EckertConstants::prefixValue.at("d");
			break;
		case NumericCheck::MetricPrefix::ONE:
			to_multiply = GEN_INTEGER(1);
			break;
		case NumericCheck::MetricPrefix::DECA:
			to_multiply = engine::EckertConstants::prefixValue.at("da");
			break;
		case NumericCheck::MetricPrefix::HECTO:
			to_multiply = engine::EckertConstants::prefixValue.at("h");
			break;
		case NumericCheck::MetricPrefix::KILO:
			to_multiply = engine::EckertConstants::prefixValue.at("k");
			break;
		case NumericCheck::MetricPrefix::MEGA:
			to_multiply = engine::EckertConstants::prefixValue.at("M");
			break;
		case NumericCheck::MetricPrefix::GIGA:
			to_multiply = engine::EckertConstants::prefixValue.at("G");
			break;
		case NumericCheck::MetricPrefix::TERA:
			to_multiply = engine::EckertConstants::prefixValue.at("T");
			break;
		case NumericCheck::MetricPrefix::PETA:
			to_multiply = engine::EckertConstants::prefixValue.at("P");
			break;
		case NumericCheck::MetricPrefix::EXA:
			to_multiply = engine::EckertConstants::prefixValue.at("E");
			break;
		case NumericCheck::MetricPrefix::ZETTA:
			to_multiply = engine::EckertConstants::prefixValue.at("Z");
			break;
		case NumericCheck::MetricPrefix::YOTTA:
			to_multiply = engine::EckertConstants::prefixValue.at("Y");
			break;
		case NumericCheck::MetricPrefix::KIBI:
			to_multiply = engine::EckertConstants::prefixValue.at("Ki");
			break;
		case NumericCheck::MetricPrefix::MEBI:
			to_multiply = engine::EckertConstants::prefixValue.at("Mi");
			break;
		case NumericCheck::MetricPrefix::GIBI:
			to_multiply = engine::EckertConstants::prefixValue.at("Gi");
			break;
		case NumericCheck::MetricPrefix::TEBI:
			to_multiply = engine::EckertConstants::prefixValue.at("Ti");
			break;
		case NumericCheck::MetricPrefix::PEBI:
			to_multiply = engine::EckertConstants::prefixValue.at("Pi");
			break;
		case NumericCheck::MetricPrefix::EXBI:
			to_multiply = engine::EckertConstants::prefixValue.at("Ei");
			break;
		case NumericCheck::MetricPrefix::ZEBI:
			to_multiply = engine::EckertConstants::prefixValue.at("Zi");
			break;
		case NumericCheck::MetricPrefix::YOBI:
			to_multiply = engine::EckertConstants::prefixValue.at("Yi");
			break;
		default:
			to_multiply = GEN_INTEGER(1);
			break;
	}
	return calc.mul(elm, to_multiply);
}

////==--------------------------------------------------------------------====//
// ECKERT PARSER / SET PREFIX MESSAGE
// [ Update ]
// Dec 03, 2016
//====--------------------------------------------------------------------==////
void EckertParser::setPrefixMessage(engine::StackEngine &stackEngine, const NumericCheck::MetricPrefix &prefix) {
	switch (prefix) {
		case NumericCheck::MetricPrefix::YOCTO:
			stackEngine.setAdditionalMessage("YOCTO");
			break;
		case NumericCheck::MetricPrefix::ZEPTO:
			stackEngine.setAdditionalMessage("ZEPTO");
			break;
		case NumericCheck::MetricPrefix::ATTO:
			stackEngine.setAdditionalMessage("ATTO");
			break;
		case NumericCheck::MetricPrefix::FEMTO:
			stackEngine.setAdditionalMessage("FEMTO");
			break;
		case NumericCheck::MetricPrefix::PICO:
			stackEngine.setAdditionalMessage("PICO");
			break;
		case NumericCheck::MetricPrefix::NANO:
			stackEngine.setAdditionalMessage("NANO");
			break;
		case NumericCheck::MetricPrefix::MICRO:
			stackEngine.setAdditionalMessage("MICRO");
			break;
		case NumericCheck::MetricPrefix::MILLI:
			stackEngine.setAdditionalMessage("MILLI");
			break;
		case NumericCheck::MetricPrefix::CENTI:
			stackEngine.setAdditionalMessage("CENTI");
			break;
		case NumericCheck::MetricPrefix::DECI:
			stackEngine.setAdditionalMessage("DECI");
			break;
		case NumericCheck::MetricPrefix::ONE:
			stackEngine.setAdditionalMessage("ONE");
			break;
		case NumericCheck::MetricPrefix::DECA:
			stackEngine.setAdditionalMessage("DECA");
			break;
		case NumericCheck::MetricPrefix::HECTO:
			stackEngine.setAdditionalMessage("HECTO");
			break;
		case NumericCheck::MetricPrefix::KILO:
			stackEngine.setAdditionalMessage("KILO");
			break;
		case NumericCheck::MetricPrefix::MEGA:
			stackEngine.setAdditionalMessage("MEGA");
			break;
		case NumericCheck::MetricPrefix::GIGA:
			stackEngine.setAdditionalMessage("GIGA");
			break;
		case NumericCheck::MetricPrefix::TERA:
			stackEngine.setAdditionalMessage("TERA");
			break;
		case NumericCheck::MetricPrefix::PETA:
			stackEngine.setAdditionalMessage("PETA");
			break;
		case NumericCheck::MetricPrefix::EXA:
			stackEngine.setAdditionalMessage("EXA");
			break;
		case NumericCheck::MetricPrefix::ZETTA:
			stackEngine.setAdditionalMessage("ZETTA");
			break;
		case NumericCheck::MetricPrefix::YOTTA:
			stackEngine.setAdditionalMessage("YOTTA");
			break;
		case NumericCheck::MetricPrefix::KIBI:
			stackEngine.setAdditionalMessage("KIBI");
			break;
		case NumericCheck::MetricPrefix::MEBI:
			stackEngine.setAdditionalMessage("MEBI");
			break;
		case NumericCheck::MetricPrefix::GIBI:
			stackEngine.setAdditionalMessage("GIBI");
			break;
		case NumericCheck::MetricPrefix::TEBI:
			stackEngine.setAdditionalMessage("TEBI");
			break;
		case NumericCheck::MetricPrefix::PEBI:
			stackEngine.setAdditionalMessage("PEBI");
			break;
		case NumericCheck::MetricPrefix::EXBI:
			stackEngine.setAdditionalMessage("EXBI");
			break;
		case NumericCheck::MetricPrefix::ZEBI:
			stackEngine.setAdditionalMessage("ZEBI");
			break;
		case NumericCheck::MetricPrefix::YOBI:
			stackEngine.setAdditionalMessage("YOBI");
			break;
		default:
			stackEngine.setAdditionalMessage("_");
			break;
	}
}

////==--------------------------------------------------------------------====//
// ECKERT PARSER / GENERATE BINARY ELEMENT FROM STRING
// [ Update ]
// Dec 03, 2016
//====--------------------------------------------------------------------==////
EckertParser::ReturnCode
EckertParser::genSpElementBinary(
	engine::SpElement &r_set,
	const std::string &str,
	engine::StackEngine &stackEngine,
	EckertStates &stat)
try {
	NumericCheck::DataType input_type;
	std::string lower_token = StringUtility::genLowerString(str);
	input_type = NumericCheck::whatData(str);
	switch (input_type) {
		case NumericCheck::DataType::DECIMAL:
			stackEngine.setCommandMessage("PUSH_B");
			stackEngine.setErrorMessage("DEC");
			switch (_size) {
				case EckertParser::BinarySize::BYTE: {
					uint8_t temp = (uint8_t)StringConverter::convertDecimalString<uint64_t>(lower_token);
					r_set = GEN_BYTE(temp);
					return EckertParser::ReturnCode::SUCCESS;
				}
				case EckertParser::BinarySize::WORD: {
					uint16_t temp = (uint16_t)StringConverter::convertDecimalString<uint64_t>(lower_token);
					r_set = GEN_WORD(temp);
					return EckertParser::ReturnCode::SUCCESS;
				}
				case EckertParser::BinarySize::DWORD: {
					uint32_t temp = (uint32_t)StringConverter::convertDecimalString<uint64_t>(lower_token);
					r_set = GEN_DWORD(temp);
					return EckertParser::ReturnCode::SUCCESS;
				}
				case EckertParser::BinarySize::QWORD: {
					uint64_t temp = (uint64_t)StringConverter::convertDecimalString<uint64_t>(lower_token);
					r_set = GEN_QWORD(temp);
					return EckertParser::ReturnCode::SUCCESS;
				}
				default:
					break;
			}
			break;
		case NumericCheck::DataType::UNSIGNED:
			stackEngine.setCommandMessage("PUSH_B");
			stackEngine.setErrorMessage("UDEC");
			switch (_size) {
				case EckertParser::BinarySize::BYTE: {
					uint8_t temp = (uint8_t)StringConverter::convertUnsignedDecimalString<uint64_t>(lower_token);
					r_set = GEN_BYTE(temp);
					return EckertParser::ReturnCode::SUCCESS;
				}
				case EckertParser::BinarySize::WORD: {
					uint16_t temp = (uint16_t)StringConverter::convertUnsignedDecimalString<uint64_t>(lower_token);
					r_set = GEN_WORD(temp);
					return EckertParser::ReturnCode::SUCCESS;
				}
				case EckertParser::BinarySize::DWORD: {
					uint32_t temp = (uint32_t)StringConverter::convertUnsignedDecimalString<uint64_t>(lower_token);
					r_set = GEN_DWORD(temp);
					return EckertParser::ReturnCode::SUCCESS;
				}
				case EckertParser::BinarySize::QWORD: {
					uint64_t temp = StringConverter::convertUnsignedDecimalString<uint64_t>(lower_token);
					r_set = GEN_QWORD(temp);
					return EckertParser::ReturnCode::SUCCESS;
				}
				default:
					break;
			}
			break;
		case NumericCheck::DataType::BINARY:
			stackEngine.setCommandMessage("PUSH_B");
			stackEngine.setErrorMessage("BIN");
			switch (_size) {
				case EckertParser::BinarySize::BYTE: {
					uint8_t temp = (uint8_t)StringConverter::convertBinaryString<uint64_t>(lower_token);
					r_set = GEN_BYTE(temp);
					return EckertParser::ReturnCode::SUCCESS;
				}
				case EckertParser::BinarySize::WORD: {
					uint16_t temp = (uint16_t)StringConverter::convertBinaryString<uint64_t>(lower_token);
					r_set = GEN_WORD(temp);
					return EckertParser::ReturnCode::SUCCESS;
				}
				case EckertParser::BinarySize::DWORD: {
					uint32_t temp = (uint32_t)StringConverter::convertBinaryString<uint64_t>(lower_token);
					r_set = GEN_DWORD(temp);
					return EckertParser::ReturnCode::SUCCESS;
				}
				case EckertParser::BinarySize::QWORD: {
					uint64_t temp = StringConverter::convertBinaryString<uint64_t>(lower_token);
					r_set = GEN_QWORD(temp);
					return EckertParser::ReturnCode::SUCCESS;
				}
				default:
					break;
			}
			break;
		case NumericCheck::DataType::OCTAL:
			stackEngine.setCommandMessage("PUSH_B");
			stackEngine.setErrorMessage("OCT");
			switch (_size) {
				case EckertParser::BinarySize::BYTE: {
					uint8_t temp = (uint8_t)StringConverter::convertOctalString<uint64_t>(lower_token);
					r_set = GEN_BYTE(temp);
					return EckertParser::ReturnCode::SUCCESS;
				}
				case EckertParser::BinarySize::WORD: {
					uint16_t temp = (uint16_t)StringConverter::convertOctalString<uint64_t>(lower_token);
					r_set = GEN_WORD(temp);
					return EckertParser::ReturnCode::SUCCESS;
				}
				case EckertParser::BinarySize::DWORD: {
					uint32_t temp = (uint32_t)StringConverter::convertOctalString<uint64_t>(lower_token);
					r_set = GEN_DWORD(temp);
					return EckertParser::ReturnCode::SUCCESS;
				}
				case EckertParser::BinarySize::QWORD: {
					uint64_t temp = (uint64_t)StringConverter::convertOctalString<uint64_t>(lower_token);
					r_set = GEN_QWORD(temp);
					return EckertParser::ReturnCode::SUCCESS;
				}
				default:
					break;
			}
			break;
		case NumericCheck::DataType::ZERO_OCTAL:
			stackEngine.setCommandMessage("PUSH_B");
			stackEngine.setErrorMessage("ZOCT");
			switch (_size) {
				case EckertParser::BinarySize::BYTE: {
					uint8_t temp = (uint8_t)StringConverter::convertZeroOctalString<uint64_t>(lower_token);
					r_set = GEN_BYTE(temp);
					return EckertParser::ReturnCode::SUCCESS;
				}
				case EckertParser::BinarySize::WORD: {
					uint16_t temp = (uint16_t)StringConverter::convertZeroOctalString<uint64_t>(lower_token);
					r_set = GEN_WORD(temp);
					return EckertParser::ReturnCode::SUCCESS;
				}
				case EckertParser::BinarySize::DWORD: {
					uint32_t temp = (uint32_t)StringConverter::convertZeroOctalString<uint64_t>(lower_token);
					r_set = GEN_DWORD(temp);
					return EckertParser::ReturnCode::SUCCESS;
				}
				case EckertParser::BinarySize::QWORD: {
					uint64_t temp = StringConverter::convertZeroOctalString<uint64_t>(lower_token);
					r_set = GEN_QWORD(temp);
					return EckertParser::ReturnCode::SUCCESS;
				}
				default:
					break;
			}
			break;
		case NumericCheck::DataType::HEXADECIMAL:
			stackEngine.setCommandMessage("PUSH_B");
			stackEngine.setErrorMessage("HEX");
			switch (_size) {
				case EckertParser::BinarySize::BYTE: {
					uint8_t temp = (uint8_t)StringConverter::convertHexadecimalString<uint64_t>(lower_token);
					r_set = GEN_BYTE(temp);
					return EckertParser::ReturnCode::SUCCESS;
				}
				case EckertParser::BinarySize::WORD: {
					uint16_t temp = (uint16_t)StringConverter::convertHexadecimalString<uint64_t>(lower_token);
					r_set = GEN_WORD(temp);
					return EckertParser::ReturnCode::SUCCESS;
				}
				case EckertParser::BinarySize::DWORD: {
					uint32_t temp = (uint32_t)StringConverter::convertHexadecimalString<uint64_t>(lower_token);
					r_set = GEN_DWORD(temp);
					return EckertParser::ReturnCode::SUCCESS;
				}
				case EckertParser::BinarySize::QWORD: {
					uint64_t temp = StringConverter::convertHexadecimalString<uint64_t>(lower_token);
					r_set = GEN_QWORD(temp);
					return EckertParser::ReturnCode::SUCCESS;
				}
				default:
					break;
			}
			break;
		case NumericCheck::DataType::TRUE:
			stackEngine.setCommandMessage("PUSH_B");
			stackEngine.setErrorMessage("BOL");
			r_set = GEN_BOOLEAN(true);
			return EckertParser::ReturnCode::SUCCESS;
		case NumericCheck::DataType::FALSE:
			stackEngine.setCommandMessage("PUSH_B");
			stackEngine.setErrorMessage("BOL");
			r_set = GEN_BOOLEAN(false);
			return EckertParser::ReturnCode::SUCCESS;
		default:
			break;
	}
	return EckertParser::ReturnCode::NOT_FOUND;
}
catch (StringConverter::Failure &) {
	return EckertParser::ReturnCode::FAILURE;
}

////==--------------------------------------------------------------------====//
// ECKERT PARSER / GENERATE CONSTANT ELEMENT FROM STRING
// [ Update ]
// Dec 03, 2016
//====--------------------------------------------------------------------==////
EckertParser::ReturnCode
EckertParser::genSpElementConstant(
	engine::SpElement &r_set,
	const std::string &str,
	engine::StackEngine &stackEngine,
	EckertStates &stat)
{
	const auto &constantTable = engine::EckertConstants::scientificConstants;
	std::string lower_token = StringUtility::genLowerString(str);
	if (constantTable.find(lower_token) != constantTable.end()) {
		const auto &pair = constantTable.at(lower_token);
		r_set = pair.elm;
		stackEngine.setCommandMessage("PUSH_C");
		stackEngine.setAdditionalMessage(str);
		return EckertParser::ReturnCode::SUCCESS;
	}
	else {
		return EckertParser::ReturnCode::NOT_FOUND;
	}
}
