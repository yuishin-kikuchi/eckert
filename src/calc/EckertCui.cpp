#define _CRT_SECURE_NO_WARNINGS

#include "EckertCui.h"
#include "engine/JsonOut.h"
#include "util/StringTables.h"
#include "ncheck/NumericCheck.h"
#include "ncheck/StringConverter.h"
#include "engine/OperatorsTrigonometric.h"
#include "engine/OperatorsComplex.h"
#include "engine/OperatorsAngleConversion.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>

////==--------------------------------------------------------------------====//
// ECKERT CUI / STATIC MEMBERS
//====--------------------------------------------------------------------==////
const char *const EckertCui::NAME
 = "Engineering Calculator with KEyboard and Refined Tools";
const char *const EckertCui::AUTHOR
 = "(C) 2014-2017  Yuishin Kikuchi";
const char *const EckertCui::VERSION
 = "Version Jan 26, 2017";

////==--------------------------------------------------------------------====//
// ECKERT CUI / CONSTRUCTER
//====--------------------------------------------------------------------==////
EckertCui::EckertCui() {
	_stateFlags = 0;
	resetConfig();
	resetStates();
	initOperatorsDRG();
}

////==--------------------------------------------------------------------====//
// ECKERT CUI / INITIALIZE ALL
// [ Update ]
// Feb 03, 2016
//====--------------------------------------------------------------------==////
void EckertCui::init() {
	resetConfig();
	resetStates();
}

////==--------------------------------------------------------------------====//
// ECKERT CUI / INITIALIZE DRG TABLE
// [ Update ]
// Feb 03, 2016
//====--------------------------------------------------------------------==////
void EckertCui::initOperatorsDRG() {
	_drgOperators.insert(std::map<std::string, OperatorsDRG>::value_type(
		"sin",
		OperatorsDRG {
			engine::StackOperatorPtr(new engine::SinDegreeOperator()),
			engine::StackOperatorPtr(new engine::SinRadianOperator()),
			engine::StackOperatorPtr(new engine::SinGradeOperator())
		}
	));
	_drgOperators.insert(std::map<std::string, OperatorsDRG>::value_type(
		"cos",
		OperatorsDRG {
			engine::StackOperatorPtr(new engine::CosDegreeOperator()),
			engine::StackOperatorPtr(new engine::CosRadianOperator()),
			engine::StackOperatorPtr(new engine::CosGradeOperator())
		}
	));
	_drgOperators.insert(std::map<std::string, OperatorsDRG>::value_type(
		"tan",
		OperatorsDRG {
			engine::StackOperatorPtr(new engine::TanDegreeOperator()),
			engine::StackOperatorPtr(new engine::TanRadianOperator()),
				engine::StackOperatorPtr(new engine::TanGradeOperator())
		}
	));
	_drgOperators.insert(std::map<std::string, OperatorsDRG>::value_type(
		"asin",
		OperatorsDRG {
			engine::StackOperatorPtr(new engine::AsinDegreeOperator()),
			engine::StackOperatorPtr(new engine::AsinRadianOperator()),
			engine::StackOperatorPtr(new engine::AsinGradeOperator())
		}
	));
	_drgOperators.insert(std::map<std::string, OperatorsDRG>::value_type(
		"acos",
		OperatorsDRG {
			engine::StackOperatorPtr(new engine::AcosDegreeOperator()),
			engine::StackOperatorPtr(new engine::AcosRadianOperator()),
			engine::StackOperatorPtr(new engine::AcosGradeOperator())
		}
	));
	_drgOperators.insert(std::map<std::string, OperatorsDRG>::value_type(
		"atan",
		OperatorsDRG {
			engine::StackOperatorPtr(new engine::AtanDegreeOperator()),
			engine::StackOperatorPtr(new engine::AtanRadianOperator()),
			engine::StackOperatorPtr(new engine::AtanGradeOperator())
		}
	));
	_drgOperators.insert(std::map<std::string, OperatorsDRG>::value_type(
		"arg",
		OperatorsDRG {
			engine::StackOperatorPtr(new engine::ArgDegreeOperator()),
			engine::StackOperatorPtr(new engine::ArgRadianOperator()),
			engine::StackOperatorPtr(new engine::ArgGradeOperator())
		}
	));
	_drgOperators.insert(std::map<std::string, OperatorsDRG>::value_type(
		"mke",
		OperatorsDRG {
			engine::StackOperatorPtr(new engine::MakeComplexPolDegreeOperator()),
			engine::StackOperatorPtr(new engine::MakeComplexPolRadianOperator()),
			engine::StackOperatorPtr(new engine::MakeComplexPolGradeOperator())
		}
	));
	_drgOperators.insert(std::map<std::string, OperatorsDRG>::value_type(
		"maga",
		OperatorsDRG {
			engine::StackOperatorPtr(new engine::MagArgDegreeOperator()),
			engine::StackOperatorPtr(new engine::MagArgRadianOperator()),
			engine::StackOperatorPtr(new engine::MagArgGradeOperator())
		}
	));
	_drgOperators.insert(std::map<std::string, OperatorsDRG>::value_type(
		"cang",
		OperatorsDRG {
			engine::StackOperatorPtr(new engine::ComplementaryAngleDegree()),
			engine::StackOperatorPtr(new engine::ComplementaryAngleRadian()),
			engine::StackOperatorPtr(new engine::ComplementaryAngleGrade())
		}
	));
	_drgOperators.insert(std::map<std::string, OperatorsDRG>::value_type(
		"sang",
		OperatorsDRG {
			engine::StackOperatorPtr(new engine::SupplementaryAngleDegree()),
			engine::StackOperatorPtr(new engine::SupplementaryAngleRadian()),
			engine::StackOperatorPtr(new engine::SupplementaryAngleGrade())
		}
	));
}

////==--------------------------------------------------------------------====//
// ECKERT CUI / SHOW CONFIG
//====--------------------------------------------------------------------==////
void EckertCui::showConfig() {
	std::cerr << "  HISTORY SIZE: " << _hist.getMaxSize() << std::endl;
	std::cerr << " DISPLAY WIDTH: " << _paginator.getDisplayWidth() << std::endl;
	std::cerr << " DISPLAY LINES: " << _paginator.getDisplayLine() << std::endl;
}

////==--------------------------------------------------------------------====//
// ECKERT CUI / LOAD CONFIG
//====--------------------------------------------------------------------==////
bool EckertCui::loadConfig()
try {
	std::ifstream input("config", std::ios::in);
	std::string buffer;
	if (input.fail()) {
		return false;
	}
	while (std::getline(input, buffer)) {
		if ('#' == buffer.at(0)) {
			continue;
		}
		else if (buffer.size() < 5) {
			return true;
		}
		else if (!buffer.compare(0, 5, "hist,")) {
			buffer.erase(0, 5);
			if (NumericCheck::isUnsigned(buffer)) {
				std::size_t temp = StringConverter::convert<std::size_t>(buffer);
				_hist.setMaxSize(temp);
			}
			else {
				return true;
			}
		}
		else if (!buffer.compare(0, 5, "widt,")) {
			buffer.erase(0, 5);
			if (NumericCheck::isUnsigned(buffer)) {
				int temp = StringConverter::convert<int>(buffer);
				_paginator.setDisplayWidth(temp);
			}
			else {
				return true;
			}
		}
		else if (!buffer.compare(0, 5, "line,")) {
			buffer.erase(0, 5);
			if (NumericCheck::isUnsigned(buffer)) {
				std::size_t temp = StringConverter::convert<std::size_t>(buffer);
				_paginator.setDisplayLine(temp);
			}
			else {
				return true;
			}
		}
		else {
			return true;
		}
	}
	return false;
}
catch (StringConverter::Failure &) {
	return true;
}

////==--------------------------------------------------------------------====//
// ECKERT CUI / SAVE CONFIG
//====--------------------------------------------------------------------==////
bool EckertCui::saveConfig()
try {
	std::ofstream output;
	output.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	output.open("config", std::ios::out | std::ios::trunc);
	output << "#ECKERT CONFIG" << std::endl;
	output << "#DO NOT CHANGE" << std::endl;
	output << "hist," << _hist.getMaxSize() << std::endl;
	output << "widt," << _paginator.getDisplayWidth() << std::endl;
	output << "line," << _paginator.getDisplayLine() << std::endl;
	return false;
}
catch (std::ofstream::failure &) {
	return true;
}

////==--------------------------------------------------------------------====//
// ECKERT CUI / RESET CONFIG
//====--------------------------------------------------------------------==////
void EckertCui::resetConfig() {
	const std::size_t DEFAULT_HISTORY_SIZE = 10;
	const std::size_t DEFAULT_DISPLAY_LINE = 11;
	const int DEFAULT_DISPLAY_WIDTH = 79;
	_hist.setMaxSize(DEFAULT_HISTORY_SIZE);
	_paginator.setDisplayLine(DEFAULT_DISPLAY_LINE);
	_paginator.setDisplayWidth(DEFAULT_DISPLAY_WIDTH);
}

////==--------------------------------------------------------------------====//
// ECKERT CUI / RESET STATES
// [ Update ]
// Feb 03, 2016
//====--------------------------------------------------------------------==////
void EckertCui::resetStates() {
	auto &stackEngine = _engCalc.refStackEngine();
	_stat.init();
	_hist.init(stackEngine);
	stackEngine.setCommandMessage("INIT");
	stackEngine.setErrorMessage("NO_ERROR");
	stackEngine.setAdditionalMessage("_");
	_paginator.init();
	_opmode = OperationMode::CALCULATOR;
}

////==--------------------------------------------------------------------====//
// ECKERT CUI / CHECK ERROR MESSAGE
// [ Update ]
// Feb 02, 2016
//====--------------------------------------------------------------------==////
EckertCui::MessageType EckertCui::checkErrorMessage(const std::string &token) {
	const auto &errorMessageTable = StringTables::errorMessage;
	const auto &noticeMessageTable = StringTables::noticeMessage;
	const auto &confirmMessageTable = StringTables::confirmMessage;
	MessageType type = MessageType::UNKNOWN;
	if (!token.compare("NO_ERROR")) {
		type = MessageType::NO_ERROR;
	}
	else if (errorMessageTable.find(token) != errorMessageTable.end()) {
		type = MessageType::ERROR;
	}
	else if (noticeMessageTable.find(token) != noticeMessageTable.end()) {
		type = MessageType::NOTICE;
	}
	else if (confirmMessageTable.find(token) != confirmMessageTable.end()) {
		type = MessageType::CONFIRM;
	}
	return type;
}

////==--------------------------------------------------------------------====//
// ECKERT CUI / GENERATE FILENAME
// [ Update ]
// Feb 02, 2016
//====--------------------------------------------------------------------==////
std::string EckertCui::genJsonFileName() {
	const tm *p_tmlocal = nullptr;
	time_t rawtime;
	time(&rawtime);
	p_tmlocal = std::localtime(&rawtime);
	if (nullptr == p_tmlocal) {
		return std::string("eckert.json");
	}
	// 20:00:00 Mar 21, 2015 -> eckert_2015_0321_200000.json
	std::ostringstream os;
	os << std::setfill('0');
	os << "eckert_";
	os << std::setw(4) << p_tmlocal->tm_year + 1900;
	os << '_';
	os << std::setw(2) << p_tmlocal->tm_mon + 1;
	os << std::setw(2) << p_tmlocal->tm_mday;
	os << '_';
	os << std::setw(2) << p_tmlocal->tm_hour;
	os << std::setw(2) << p_tmlocal->tm_min;
	os << std::setw(2) << p_tmlocal->tm_sec;
	os << ".json";
	return os.str();
}

////==--------------------------------------------------------------------====//
// ECKERT CUI / OUTPUT JSON
// [ Update ]
// Feb 16, 2016
//====--------------------------------------------------------------------==////
bool EckertCui::outputJson()
try {
	auto &calc = _engCalc.refStackEngine();
	std::string filename = genJsonFileName();
	setJsonFilename(filename);
	return engine::JsonOut::outputFile(calc, _strEngine, _cfg, filename);
}
catch (...) {
	setStateFlags(FATAL_STATE);
	return true;
}

////==--------------------------------------------------------------------====//
// ECKERT CUI / DISPLAY AS JSON
// [ Update ]
// Feb 16, 2016
//====--------------------------------------------------------------------==////
void EckertCui::displayAsJson()
try {
	auto &calc = _engCalc.refStackEngine();
	engine::JsonOut::outputStream(calc, _strEngine, _cfg, std::cerr);
}
catch (...) {
	setStateFlags(FATAL_STATE);
}

////==--------------------------------------------------------------------====//
// DISPLAY HINT
//====--------------------------------------------------------------------==////
EckertCui::DisplayHint::DisplayHint() {
	init();
}

EckertCui::DisplayHint::DisplayHint(
	const engine::StackEngine &stackEngine,
	const engine::StringEngine &stringEngine,
	const EckertPaginator &paginator)
{
	init(stackEngine, stringEngine, paginator);
}

void EckertCui::DisplayHint::init() {
	std::memset(this, 0x00, sizeof(*this));
}

void EckertCui::DisplayHint::init(
	const engine::StackEngine &stackEngine,
	const engine::StringEngine &stringEngine,
	const EckertPaginator &paginator)
{
	const auto &stack = stackEngine.refStack();
	const auto &reg = stackEngine.refRegister();
	stackItems = stack.size();
	registerSize = reg.size();
	registerFlag = paginator.getRegisterDisplayFlag();
	displayLine = paginator.getDisplayLine();
	displayWidth = paginator.getDisplayWidth();
	stackLine = paginator.calcStackLine(registerSize);
	registerLine = paginator.calcRegisterLine(registerSize);
	stackOffset = paginator.getStackOffset();
	registerOffset = paginator.getRegisterOffset();
	int digits = 1;
	std::size_t num = stackItems;
	while (num /= 10) {
		++digits;
	}
	if (digits < 3) {
		digits = 3;
	}
	numWidth = digits;
	valueWidth = displayWidth - 3 - numWidth;
	switch (stringEngine.getTypeDisplayMode()) {
		case engine::StringEngine::TypeDisplayMode::LONG:
			typeWidth = engine::StringEngine::LONG_TYPE_WIDTH;
			valueWidth -= typeWidth + 3;
			break;
		case engine::StringEngine::TypeDisplayMode::SHORT:
			typeWidth = engine::StringEngine::SHORT_TYPE_WIDTH;
			valueWidth -= typeWidth + 3;
			break;
		case engine::StringEngine::TypeDisplayMode::NO_DISPLAY:
			typeWidth = 0;
			break;
		default:
			break;
	}
}
