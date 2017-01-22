#include "EckertCui.h"
#include "ncheck/NumericCheck.h"
#include "ncheck/StringConverter.h"
#include "util/StringChecker.h"
#include "engine/JsonOut.h"
#include "engine/OperatorsRegister.h"
#include "engine/UnitConverter.h"
#include <cstdio>

#include <iostream>

////==--------------------------------------------------------------------====//
// ECKERT CUI / OPERATE
// [ Update ]
// Dec 23, 2016
//====--------------------------------------------------------------------==////
void EckertCui::operate(const std::string &str)
try {
	switch (getOperationMode()) {
		case OperationMode::VERSION_FROM_CONFIG: {
			auto &stackEngine = _engCalc.refStackEngine();
			_stat.resetWaitingState();
			stackEngine.setCommandMessage("CF_NOP");
			stackEngine.setErrorMessage("NO_ERROR");
			setOperationMode(OperationMode::CONFIG);
			return;
		}
		case OperationMode::VERSION_FROM_CALCULATOR: {
			auto &stackEngine = _engCalc.refStackEngine();
			_stat.resetWaitingState();
			stackEngine.setCommandMessage("H_NOP");
			stackEngine.setErrorMessage("NO_ERROR");
			setOperationMode(OperationMode::CALCULATOR);
			return;
		}
		case OperationMode::VIEW: {
			auto &stackEngine = _engCalc.refStackEngine();
			_stat.resetWaitingState();
			stackEngine.setCommandMessage("H_NOP");
			stackEngine.setErrorMessage("NO_ERROR");
			setOperationMode(OperationMode::CALCULATOR);
			return;
		}
		default:
			break;
	}
	auto tokens = StringUtility::split(str);
	std::size_t size = tokens.size();
	if (1 == size) {
		const std::string &token = tokens.at(0);
		if (StringChecker::isExit(token)) {
			setStateFlags(END_STATE);
			return;
		}
		else if (StringChecker::isHomura(token)) {
			auto &stackEngine = _engCalc.refStackEngine();
			_stat.resetWaitingState();
			stackEngine.setCommandMessage("H_NOP");
			stackEngine.setErrorMessage("NO_ERROR");
			setOperationMode(OperationMode::CALCULATOR);
			return;
		}
		else if (StringChecker::isConfig(token)) {
			auto &stackEngine = _engCalc.refStackEngine();
			_stat.resetWaitingState();
			stackEngine.setCommandMessage("CF_NOP");
			stackEngine.setErrorMessage("NO_ERROR");
			setOperationMode(OperationMode::CONFIG);
			return;
		}
		switch (getOperationMode()) {
			case OperationMode::CALCULATOR:
				if (StringChecker::isVersion(token)) {
					_stat.resetWaitingState();
					setOperationMode(OperationMode::VERSION_FROM_CALCULATOR);
					return;
				}
				else if (StringChecker::isView(token)) {
					_stat.resetWaitingState();
					setOperationMode(OperationMode::VIEW);
					return;
				}
				break;
			case OperationMode::CONFIG:
				if (StringChecker::isVersion(token)) {
					_stat.resetWaitingState();
					setOperationMode(OperationMode::VERSION_FROM_CONFIG);
					return;
				}
				break;
			default:
				break;
			
		}
	}
	switch (getOperationMode()) {
		case OperationMode::CALCULATOR:
			operateCalculator(str);
			break;
		case OperationMode::CONFIG:
			operateConfig(str);
			break;
		default:
			break;
	}
}
catch (std::exception &ex) {
	std::cout << ex.what() << std::endl;
	setStateFlags(FATAL_STATE);
	getchar();
}
catch (...) {
	std::cout << "Unknown exception!" << std::endl;
	setStateFlags(FATAL_STATE);
	getchar();
}

////==--------------------------------------------------------------------====//
// ECKERT CUI / OPERATE CONFIG
// [ Update ]
// Dec 18, 2016
//====--------------------------------------------------------------------==////
void EckertCui::operateConfig(const std::string &str) {
	auto &stackEngine = _engCalc.refStackEngine();
	auto tokens = StringUtility::split(str);
	std::size_t size = tokens.size();
	switch (size) {
		case 0:
			stackEngine.setCommandMessage("CF_NOP");
			stackEngine.setErrorMessage("NO_ERROR");
			_stat.resetWaitingState();
			return;
		case 1: {
			const auto &token = tokens.at(0);
			auto lower_token = StringUtility::genLowerString(token);
			if (!lower_token.compare("load")) {
				stackEngine.setCommandMessage("CF_LOAD");
				if (!loadConfig()) {
					stackEngine.setErrorMessage("LOADED");
				}
				else {
					stackEngine.setErrorMessage("LD_ERR");
				}
				return;
			}
			else if (!lower_token.compare("save")) {
				stackEngine.setCommandMessage("CF_SAVE");
				if (!saveConfig()) {
					stackEngine.setErrorMessage("SAVED");
				}
				else {
					stackEngine.setErrorMessage("SV_ERR");
				}
				return;
			}
			else if (StringChecker::isReset(lower_token)) {
				stackEngine.setCommandMessage("CF_REST");
				stackEngine.setErrorMessage("CNFM");
				_stat.setWaitingState(EckertStates::RESET_CONFIRM);
				return;
			}
			break;
		}
		default:
			break;
	}
	operateConfig(tokens);
}

////==--------------------------------------------------------------------====//
// ECKERT CUI / OPERATE CONFIG (vector)
// [ Update ]
// Dec 18, 2016
//====--------------------------------------------------------------------==////
void EckertCui::operateConfig(const std::vector<std::string> &tokens)
try {
	auto &stackEngine = _engCalc.refStackEngine();
	std::size_t size = tokens.size();
	for (std::size_t ucnt = 0; ucnt < size; ++ucnt) {
		auto waiting = _stat.getWaitingState();
		const auto &token = tokens.at(ucnt);
		std::string lower_token = StringUtility::genLowerString(token);
		if (!lower_token.compare("hist")) {
			stackEngine.setCommandMessage("CF_HIST");
			stackEngine.setErrorMessage("WAIT_INT");
			_stat.setWaitingState(EckertStates::HISTORY_SIZE);
		}
		else if (!lower_token.compare("width")) {
			stackEngine.setCommandMessage("CF_WIDT");
			stackEngine.setErrorMessage("WAIT_INT");
			_stat.setWaitingState(EckertStates::DISPLAY_WIDTH);
		}
		else if (!lower_token.compare("lines")) {
			stackEngine.setCommandMessage("CF_LINE");
			stackEngine.setErrorMessage("WAIT_INT");
			_stat.setWaitingState(EckertStates::DISPLAY_LINE);
		}
		else if (EckertStates::NONE != waiting) {
			switch (waiting) {
				case EckertStates::HISTORY_SIZE:
					stackEngine.setCommandMessage("CF_HIST");
					if (NumericCheck::isUnsigned(token)) {
						std::size_t temp = StringConverter::convert<std::size_t>(token);
						if (0 != temp) {
							stackEngine.setErrorMessage("S_NRM");
						}
						else {
							stackEngine.setErrorMessage("S_MIN");
						}
						_hist.setMaxSize(temp);
					}
					else {
						stackEngine.setErrorMessage("NOT_NUM");
					}
					break;
				case EckertStates::DISPLAY_LINE:
					stackEngine.setCommandMessage("CF_LINE");
					if (NumericCheck::isUnsigned(token)) {
						std::size_t temp = StringConverter::convert<std::size_t>(token);
						if (temp < EckertPaginator::LEAST_DISPLAY_LINE) {
							temp = EckertPaginator::LEAST_DISPLAY_LINE;
							stackEngine.setErrorMessage("S_MIN");
						}
						else {
							stackEngine.setErrorMessage("S_NRM");
						}
						_paginator.setDisplayLine(temp);
					}
					else {
						stackEngine.setErrorMessage("NOT_NUM");
					}
					break;
				case EckertStates::DISPLAY_WIDTH:
					stackEngine.setCommandMessage("CF_WIDT");
					if (NumericCheck::isUnsigned(token)) {
						int temp = StringConverter::convert<int>(token);
						if (temp < EckertPaginator::LEAST_DISPLAY_WIDTH) {
							temp = EckertPaginator::LEAST_DISPLAY_WIDTH;
							stackEngine.setErrorMessage("S_MIN");
						}
						else {
							stackEngine.setErrorMessage("S_NRM");
						}
						_paginator.setDisplayWidth(temp);
					}
					else {
						stackEngine.setErrorMessage("NOT_NUM");
					}
					break;
				case EckertStates::RESET_CONFIRM:
					stackEngine.setCommandMessage("CF_REST");
					if (StringChecker::isYes(lower_token)) {
						resetConfig();
						stackEngine.setErrorMessage("DONE");
					}
					else if (StringChecker::isNo(lower_token)) {
						stackEngine.setErrorMessage("CNCL");
					}
					else {
						stackEngine.setErrorMessage("INV_IN");
					}
					_stat.setWaitingState(EckertStates::NONE);
					goto LOOP_END;
				default:
					break;
			}
			_stat.setWaitingState(EckertStates::NONE);
		}
		else {
			stackEngine.setCommandMessage("ERROR");
			stackEngine.setErrorMessage("KW_ERR");
			_stat.setWaitingState(EckertStates::NONE);
			break;
		}
	}
LOOP_END:
	return;
}
catch (StringConverter::Failure &) {
	auto &stackEngine = _engCalc.refStackEngine();
	stackEngine.setCommandMessage("ERROR");
	stackEngine.setErrorMessage("ERR_IN");
	return;
}
catch (std::exception &ex) {
	std::cout << ex.what() << std::endl;
	setStateFlags(FATAL_STATE);
	getchar();
}
catch (...) {
	std::cout << "Unknown exception!" << std::endl;
	setStateFlags(FATAL_STATE);
	getchar();
}

////==--------------------------------------------------------------------====//
// ECKERT CUI / OPERATE CALCULATOR
// [ Update ]
// Dec 18, 2016
//====--------------------------------------------------------------------==////
void EckertCui::operateCalculator(const std::string &str) {
	auto &stackEngine = _engCalc.refStackEngine();
	//==  Check if empty  ==//
	if (str.empty()) {
		auto waiting = _stat.getWaitingState();
		if (EckertStates::NONE != waiting) {
			_stat.resetWaitingState();
			stackEngine.setCommandMessage("H_NOP");
			stackEngine.setErrorMessage("NO_ERROR");
			return;
		}
		else {
			_stat.resetWaitingState();
			_stat.startRec();
			if (!_engCalc.operate("dup")) {
				_hist.manage(stackEngine);
				_paginator.resetStackOffset();
			}
			_stat.stopRec();
			return;
		}
	}
	auto tokens = StringUtility::split(str);
	if (tokens.empty()) {
		_stat.resetWaitingState();
		stackEngine.setCommandMessage("ERROR");
		stackEngine.setErrorMessage("EMP_IN");
		return;
	}
	operateCalculator(tokens);
}

////==--------------------------------------------------------------------====//
// ECKERT CUI / OPERATE CALCULATOR (vector)
// [ Update ]
// Jan 18, 2017
//====--------------------------------------------------------------------==////
void EckertCui::operateCalculator(const std::vector<std::string> &tokens)
try {
	auto &stackEngine = _engCalc.refStackEngine();
	//==  Operated flag  ==//
	bool operated = false;
	//==  Check tokens  ==//
	std::size_t items = tokens.size();
	//==  One keyword operation  ==//
	if (1 == items) {
		bool is_waiting = (EckertStates::NONE != _stat.getWaitingState());
		if (!is_waiting) {
			const std::string &token = tokens.at(0);
			std::string lower_token = StringUtility::genLowerString(token);
			switch (operateCalculatorOneKeyword(lower_token)) {
				case ReturnCode::SUCCESS:
					// fall through
				case ReturnCode::FAILURE:
					return;
				case ReturnCode::NOT_FOUND:
					// fall through
				default:
					break;
			}
		}
	}
	//==  Operate with each string  ==//
	for (std::size_t ucnt = 0; ucnt < items; ++ucnt) {
		stackEngine.setErrorMessage("NO_ERROR");
		//==  Token operation  ==//
		const std::string &token = tokens.at(ucnt);
		std::string lower_token = StringUtility::genLowerString(token);
		//==  Start operation  ==//
		_stat.startRec();
		switch (operateUnitConversion(lower_token)) {
			case ReturnCode::SUCCESS: {
				bool is_waiting = (EckertStates::NONE != _stat.getWaitingState());
				if (is_waiting) {
					continue;
				}
				else {
					operated = true;
					continue;
				}
				break;
			}
			case ReturnCode::FAILURE:
				goto LOOP_END;
			case ReturnCode::NOT_FOUND:
				break;
			default:
				break;
		}
		auto &fcfg = _strEngine.refFloatingDisplayConfig();
		switch (_parser.manageConfig(stackEngine, fcfg, _stat, token)) {
			case EckertParser::ReturnCode::SUCCESS: {
				bool is_waiting = (EckertStates::NONE != _stat.getWaitingState());
				if (is_waiting) {
					continue;
				}
				else {
					goto LOOP_END;
				}
			}
			case EckertParser::ReturnCode::MUST_CLEAR:
				_engCalc.init();
				_cfg.init();
				_strEngine.init();
				_hist.init(stackEngine);
				_paginator.init();
				return;
			case EckertParser::ReturnCode::WAIT_USER:
				// fall through
			case EckertParser::ReturnCode::FAILURE:
				goto LOOP_END;
			case EckertParser::ReturnCode::NOT_FOUND:
				// fall through
			default:
				break;
		}
		_stat.resetWaitingState();
		switch (_parser.pushElementByString(token, stackEngine, _stat)) {
			case EckertParser::ReturnCode::SUCCESS:
				operated = true;
				_stat.stopRec();
				continue;
			case EckertParser::ReturnCode::FAILURE:
				goto LOOP_END;
			case EckertParser::ReturnCode::NOT_FOUND:
				// fall through
			default:
				break;
		}
		switch (operateGeneralCalculation(lower_token)) {
			case ReturnCode::SUCCESS:
				operated = true;
				_stat.stopRec();
				continue;
			case ReturnCode::FAILURE:
				goto LOOP_END;
			case ReturnCode::NOT_FOUND:
				// fall through
			default:
				break;
		}
		switch (operateRegister(lower_token)) {
			case ReturnCode::SUCCESS:
				operated = true;
				_stat.stopRec();
				continue;
			case ReturnCode::FAILURE:
				goto LOOP_END;
			case ReturnCode::NOT_FOUND:
				// fall through
			default:
				break;
		}
		switch (runMacro(lower_token)) {
			case ReturnCode::SUCCESS:
				operated = true;
				_stat.stopRec();
				continue;
			case ReturnCode::FAILURE:
				operated = true;
				_stat.stopRec();
				goto LOOP_END;
			case ReturnCode::NOT_FOUND:
				// fall through
			default:
				break;
		}
		stackEngine.setCommandMessage("ERROR");
		stackEngine.setErrorMessage("KW_ERR");
		break;
	}
LOOP_END:
	//==  Manage history  ==//
	if (operated) {
		_hist.manage(stackEngine);
		_paginator.resetStackOffset();
	}
	return;
}
catch (engine::EckertException &ee) {
	std::cout << ee.what() << std::endl;
	std::cout << "From: " << ee.where() << std::endl;
	std::getchar();
	throw;
}

////==--------------------------------------------------------------------====//
// ECKERT CUI / OPERATE CALCULATOR ONE KEYWORD
// [ Update ]
// Dec 10, 2016
//====--------------------------------------------------------------------==////
EckertCui::ReturnCode
EckertCui::operateCalculatorOneKeyword(const std::string &token) {
	auto &stackEngine = _engCalc.refStackEngine();
	stackEngine.setErrorMessage("NO_ERROR");
	_stat.startRec();
	if (StringChecker::isUndo(token)) {
		//=  Undo  =//
		stackEngine.setCommandMessage("HS_UNDO");
		if (0 == _hist.getMaxSize()) {
			stackEngine.setErrorMessage("H_OFF");
		}
		else if (0 == _hist.getCurrentSize()) {
			stackEngine.setErrorMessage("H_EMP");
		}
		else if (_hist.undo(stackEngine)) {
			stackEngine.setErrorMessage("H_OLD");
		}
		else {
			_paginator.resetStackOffset();
		}
		_stat.stopRec();
		_stat.resetWaitingState();
		return ReturnCode::SUCCESS;
	}
	else if (StringChecker::isRedo(token)) {
		//=  Redo  =//
		stackEngine.setCommandMessage("HS_REDO");
		if (0 == _hist.getMaxSize()) {
			stackEngine.setErrorMessage("H_OFF");
		}
		else if (0 == _hist.getCurrentSize()) {
			stackEngine.setErrorMessage("H_EMP");
		}
		else if (_hist.redo(stackEngine)) {
			stackEngine.setErrorMessage("H_NEW");
		}
		else {
			_paginator.resetStackOffset();
		}
		_stat.stopRec();
		_stat.resetWaitingState();
		return ReturnCode::SUCCESS;
	}
	else if (StringChecker::isJson(token)) {
		//=  Json output  =//
		stackEngine.setCommandMessage("H_JSON");
		std::string filename = genJsonFileName();
		setJsonFilename(filename);
		if (!engine::JsonOut::outputFile(stackEngine, _strEngine, _cfg, filename)) {
			stackEngine.setAdditionalMessage(filename);
		}
		else {
			stackEngine.setErrorMessage("OUT_ERR");
		}
		_stat.resetWaitingState();
		return ReturnCode::SUCCESS;
	}
	switch (changeCalculatorMode(token)) {
		case ReturnCode::SUCCESS:
			_stat.resetWaitingState();
			return ReturnCode::SUCCESS;
		case ReturnCode::NOT_FOUND:
			// fall through
		default:
			break;
	}
	switch (changeCalculatorPages(token)) {
		case ReturnCode::SUCCESS:
			_stat.resetWaitingState();
			return ReturnCode::SUCCESS;
		case ReturnCode::FAILURE:
			_stat.resetWaitingState();
			return ReturnCode::FAILURE;
		case ReturnCode::NOT_FOUND:
			// fall through
		default:
			break;
	}
	return ReturnCode::NOT_FOUND;
}

////==--------------------------------------------------------------------====//
// ECKERT CUI / OPERATE UNIT CONVERSION
// [ Update ]
// Dec 25, 2016
//====--------------------------------------------------------------------==////
EckertCui::ReturnCode
EckertCui::operateUnitConversion(const std::string &token) {
	auto &stackEngine = _engCalc.refStackEngine();
	auto state = _stat.getWaitingState();
	switch (state) {
		case EckertStates::NONE: {
			if (!token.compare("conv") || !token.compare("cv")) {
				_paginator.resetStackOffset();
				stackEngine.setCommandMessage("H_CONV");
				auto &exStack = stackEngine.refExStack();
				if (exStack.empty()) {
					stackEngine.setErrorMessage("FEW_ARG");
					return ReturnCode::FAILURE;
				}
				else {
					auto elm = exStack.fetch(0);
					if (!elm->isKindOf(engine::Element::SCALAR_TYPE)) {
						stackEngine.setErrorMessage("BAD_TYPE");
						return ReturnCode::FAILURE;
					}
				}
				stackEngine.setErrorMessage("UNIT");
				_stat.setWaitingState(EckertStates::FIRST_UNIT);
				return ReturnCode::SUCCESS;
			}
			else if (!token.compare("rec")) {
				_paginator.resetStackOffset();
				stackEngine.setCommandMessage("H_REC");
				auto &exStack = stackEngine.refExStack();
				if (exStack.empty()) {
					stackEngine.setErrorMessage("FEW_ARG");
					return ReturnCode::FAILURE;
				}
				else {
					auto elm = exStack.fetch(0);
					if (!elm->isKindOf(engine::Element::SCALAR_TYPE)) {
						stackEngine.setErrorMessage("BAD_TYPE");
						return ReturnCode::FAILURE;
					}
				}
				auto fromUnit = _stat.getPrevFromUnit();
				auto toUnit = _stat.getPrevToUnit();
				if ((0 == fromUnit) || (0 == toUnit)) {
					stackEngine.setErrorMessage("CNV_ERR");
					return ReturnCode::FAILURE;
				}
				auto src = exStack.fetch(0);
				engine::SpElement dest;
				if (engine::UnitConverter::convert(dest, src, fromUnit, toUnit)) {
					stackEngine.setErrorMessage("CNV_ERR");
					return ReturnCode::FAILURE;
				}
				else {
					exStack.drop(1);
					exStack.push(dest);
				}
				return ReturnCode::SUCCESS;
			}
			break;
		}
		case EckertStates::FIRST_UNIT: {
			const auto &unitKeywords = engine::UnitConverter::unitKeywords;
			stackEngine.setCommandMessage("H_CONV");
			if (unitKeywords.find(token) != unitKeywords.end()) {
				_stat.setFromUnit(unitKeywords.at(token));
				_stat.setWaitingState(EckertStates::SECOND_UNIT);
				stackEngine.setErrorMessage("UNIT");
				return ReturnCode::SUCCESS;
			}
			else {
				stackEngine.setErrorMessage("INV_IN");
				_stat.setWaitingState(EckertStates::NONE);
				return ReturnCode::FAILURE;
			}
			break;
		}
		case EckertStates::SECOND_UNIT: {
			const auto &unitKeywords = engine::UnitConverter::unitKeywords;
			stackEngine.setCommandMessage("H_CONV");
			_stat.setWaitingState(EckertStates::NONE);
			if (unitKeywords.find(token) != unitKeywords.end()) {
				_stat.setToUnit(unitKeywords.at(token));
			}
			else {
				stackEngine.setErrorMessage("INV_IN");
				return ReturnCode::FAILURE;
			}
			auto fromUnit = _stat.getFromUnit();
			auto toUnit = _stat.getToUnit();
			auto &exStack = stackEngine.refExStack();
			if (exStack.empty()) {
				stackEngine.setErrorMessage("FEW_ARG");
				return ReturnCode::FAILURE;
			}
			else {
				auto elm = exStack.fetch(0);
				if (!elm->isKindOf(engine::Element::SCALAR_TYPE)) {
					stackEngine.setErrorMessage("BAD_TYPE");
					return ReturnCode::FAILURE;
				}
			}
			auto src = exStack.fetch(0);
			engine::SpElement dest;
			if (engine::UnitConverter::convert(dest, src, fromUnit, toUnit)) {
				stackEngine.setErrorMessage("CNV_ERR");
				return ReturnCode::FAILURE;
			}
			else {
				_stat.setPrevFromUnit(fromUnit);
				_stat.setPrevToUnit(toUnit);
				exStack.drop(1);
				exStack.push(dest);
			}
			return ReturnCode::SUCCESS;
		}
		default:
			break;
	}
	return ReturnCode::NOT_FOUND;
}

////==--------------------------------------------------------------------====//
// ECKERT CUI / OPERATE GENERAL CALCULATION
// [ Update ]
// Dec 10, 2016
//====--------------------------------------------------------------------==////
EckertCui::ReturnCode
EckertCui::operateGeneralCalculation(const std::string &token) {
	//==  Make lower token  ==//
	auto &stackEngine = _engCalc.refStackEngine();
	stackEngine.setErrorMessage("NO_ERROR");
	if (_engCalc.doesCommandExist(token)) {
		if (_engCalc.operate(token)) {
			return ReturnCode::FAILURE;
		}
		else {
			return ReturnCode::SUCCESS;
		}
	}
	else if (_drgOperators.find(token) != _drgOperators.end()) {
		const auto &set = _drgOperators.at(token);
		switch (_cfg.getAngleMode()) {
			case engine::CalculationConfig::AngleMode::DEGREE: {
				const auto &op = set.degree;
				if (stackEngine.acceptOperator(op)) {
					return ReturnCode::FAILURE;
				}
				else {
					return ReturnCode::SUCCESS;
				}
				break;
			}
			case engine::CalculationConfig::AngleMode::RADIAN: {
				const auto &op = set.radian;
				if (stackEngine.acceptOperator(op)) {
					return ReturnCode::FAILURE;
				}
				else {
					return ReturnCode::SUCCESS;
				}
				break;
			}
			case engine::CalculationConfig::AngleMode::GRADE: {
				const auto &op = set.grade;
				if (stackEngine.acceptOperator(op)) {
					return ReturnCode::FAILURE;
				}
				else {
					return ReturnCode::SUCCESS;
				}
				break;
			}
			default:
				break;
		}
	}
	return ReturnCode::NOT_FOUND;
}

////==--------------------------------------------------------------------====//
// ECKERT CUI / OPERATE REGISTER
// [ Update ]
// Dec 18, 2016
//====--------------------------------------------------------------------==////
EckertCui::ReturnCode
EckertCui::operateRegister(const std::string &token) {
	auto &stackEngine = _engCalc.refStackEngine();
	stackEngine.setErrorMessage("NO_ERROR");
	std::size_t pos = StringChecker::getRegisterPos(token);
	if (StringChecker::isRegisterStore(token)) {
		auto op = engine::RegStoreOperator(pos);
		if (stackEngine.acceptOperator(&op)) {
			return EckertCui::ReturnCode::FAILURE;
		}
		else {
			return EckertCui::ReturnCode::SUCCESS;
		}
	}
	else if (StringChecker::isRegisterLoad(token)) {
		auto op = engine::RegLoadOperator(pos);
		if (stackEngine.acceptOperator(&op)) {
			return EckertCui::ReturnCode::FAILURE;
		}
		else {
			return EckertCui::ReturnCode::SUCCESS;
		}
	}
	else if (StringChecker::isRegisterDel(token)) {
		auto op = engine::RegDelOperator(pos);
		if (stackEngine.acceptOperator(&op)) {
			return EckertCui::ReturnCode::FAILURE;
		}
		else {
			return EckertCui::ReturnCode::SUCCESS;
		}
	}
	else if (StringChecker::isRegisterInc(token)) {
		auto op = engine::RegIncOperator(pos);
		if (stackEngine.acceptOperator(&op)) {
			return EckertCui::ReturnCode::FAILURE;
		}
		else {
			return EckertCui::ReturnCode::SUCCESS;
		}
	}
	else if (StringChecker::isRegisterDec(token)) {
		auto op = engine::RegDecOperator(pos);
		if (stackEngine.acceptOperator(&op)) {
			return EckertCui::ReturnCode::FAILURE;
		}
		else {
			return EckertCui::ReturnCode::SUCCESS;
		}
	}
	else if (StringChecker::isRegisterAdd(token)) {
		auto op = engine::RegAddOperator(pos);
		if (stackEngine.acceptOperator(&op)) {
			return EckertCui::ReturnCode::FAILURE;
		}
		else {
			return EckertCui::ReturnCode::SUCCESS;
		}
	}
	else if (StringChecker::isRegisterSub(token)) {
		auto op = engine::RegSubOperator(pos);
		if (stackEngine.acceptOperator(&op)) {
			return EckertCui::ReturnCode::FAILURE;
		}
		else {
			return EckertCui::ReturnCode::SUCCESS;
		}
	}
	else if (StringChecker::isRegisterMul(token)) {
		auto op = engine::RegMulOperator(pos);
		if (stackEngine.acceptOperator(&op)) {
			return EckertCui::ReturnCode::FAILURE;
		}
		else {
			return EckertCui::ReturnCode::SUCCESS;
		}
	}
	else if (StringChecker::isRegisterDiv(token)) {
		auto op = engine::RegDivOperator(pos);
		if (stackEngine.acceptOperator(&op)) {
			return EckertCui::ReturnCode::FAILURE;
		}
		else {
			return EckertCui::ReturnCode::SUCCESS;
		}
	}
	else {
		return EckertCui::ReturnCode::NOT_FOUND;
	}
}

////==--------------------------------------------------------------------====//
// ECKERT CUI / CHANGE CALCULATOR MODE
// [ Update ]
// Dec 18, 2016
//====--------------------------------------------------------------------==////
EckertCui::ReturnCode
EckertCui::changeCalculatorMode(const std::string &token) {
	//==  Make lower token  ==//
	auto &stackEngine = _engCalc.refStackEngine();
	//==  Try to change mode  ==//
	stackEngine.setErrorMessage("NO_ERROR");
	if (!token.compare("ad")) {
		_strEngine.setDecimalDisplayMode(engine::StringEngine::DecimalDisplayMode::AUTO_DECIMAL);
		stackEngine.setCommandMessage("M_AD");
		return ReturnCode::SUCCESS;
	}
	else if (!token.compare("fd")) {
		_strEngine.setDecimalDisplayMode(engine::StringEngine::DecimalDisplayMode::FORCE_DECIMAL);
		stackEngine.setCommandMessage("M_FD");
		return ReturnCode::SUCCESS;
	}
	else if (!token.compare("ff")) {
		_strEngine.setDecimalDisplayMode(engine::StringEngine::DecimalDisplayMode::FORCE_FRACTIONAL);
		stackEngine.setCommandMessage("M_FF");
		return ReturnCode::SUCCESS;
	}
	else if (!token.compare("deg")) {
		_cfg.setAngleMode(engine::CalculationConfig::AngleMode::DEGREE);
		stackEngine.setCommandMessage("M_ADEG");
		return ReturnCode::SUCCESS;
	}
	else if (!token.compare("rad")) {
		_cfg.setAngleMode(engine::CalculationConfig::AngleMode::RADIAN);
		stackEngine.setCommandMessage("M_ARAD");
		return ReturnCode::SUCCESS;
	}
	else if (!token.compare("gra") || !token.compare("grad")) {
		_cfg.setAngleMode(engine::CalculationConfig::AngleMode::GRADE);
		stackEngine.setCommandMessage("M_AGRA");
		return ReturnCode::SUCCESS;
	}
	else if (!token.compare("std")) {
		auto &fcfg = _strEngine.refFloatingDisplayConfig();
		fcfg.setDisplayMode(engine::FloatingDisplayConfig::STANDARD);
		stackEngine.setCommandMessage("M_FSTD");
		return ReturnCode::SUCCESS;
	}
	else if (!token.compare("fix")) {
		auto &fcfg = _strEngine.refFloatingDisplayConfig();
		fcfg.setDisplayMode(engine::FloatingDisplayConfig::FIXED);
		stackEngine.setCommandMessage("M_FFIX");
		return ReturnCode::SUCCESS;
	}
	else if (!token.compare("sci")) {
		auto &fcfg = _strEngine.refFloatingDisplayConfig();
		fcfg.setDisplayMode(engine::FloatingDisplayConfig::SCIENTIFIC);
		stackEngine.setCommandMessage("M_FSCI");
		return ReturnCode::SUCCESS;
	}
	else if (!token.compare("eng")) {
		auto &fcfg = _strEngine.refFloatingDisplayConfig();
		fcfg.setDisplayMode(engine::FloatingDisplayConfig::ENGINEERING);
		stackEngine.setCommandMessage("M_FENG");
		return ReturnCode::SUCCESS;
	}
	else if (!token.compare("type")) {
		switch (_strEngine.getTypeDisplayMode()) {
			case engine::StringEngine::TypeDisplayMode::LONG:
				_strEngine.setTypeDisplayMode(engine::StringEngine::TypeDisplayMode::NO_DISPLAY);
				stackEngine.setCommandMessage("M_TOFF");
				// stackEngine.setCommandMessage("M_TSHT");
				break;
			case engine::StringEngine::TypeDisplayMode::SHORT:
				_strEngine.setTypeDisplayMode(engine::StringEngine::TypeDisplayMode::NO_DISPLAY);
				stackEngine.setCommandMessage("M_TOFF");
				break;
			case engine::StringEngine::TypeDisplayMode::NO_DISPLAY:
				_strEngine.setTypeDisplayMode(engine::StringEngine::TypeDisplayMode::LONG);
				stackEngine.setCommandMessage("M_TLNG");
				break;
			default:
				break;
		}
		return ReturnCode::SUCCESS;
	}
	else if (!token.compare("register") || !token.compare("reg")) {
		if (_paginator.getRegisterDisplayFlag()) {
			_paginator.setRegisterDisplayFlag(false);
			stackEngine.setCommandMessage("M_ROFF");
		}
		else {
			_paginator.setRegisterDisplayFlag(true);
			stackEngine.setCommandMessage("M_RON");
		}
		return ReturnCode::SUCCESS;
	}
	else if (!token.compare("euler") || !token.compare("eul")) {
		if (_strEngine.getEulerFlag()) {
			_strEngine.setEulerFlag(false);
			stackEngine.setCommandMessage("M_EOFF");
		}
		else {
			_strEngine.setEulerFlag(true);
			stackEngine.setCommandMessage("M_EON");
		}
		return ReturnCode::SUCCESS;
	}
	else if (!token.compare("fraction") || !token.compare("frac")) {
		switch (_strEngine.getFractionalDisplayMode()) {
			case engine::StringEngine::FractionalDisplayMode::MIXED:
				_strEngine.setFractionalDisplayMode(engine::StringEngine::FractionalDisplayMode::PROVISIONAL);
				stackEngine.setCommandMessage("M_PROV");
				break;
			case engine::StringEngine::FractionalDisplayMode::PROVISIONAL:
				_strEngine.setFractionalDisplayMode(engine::StringEngine::FractionalDisplayMode::MIXED);
				stackEngine.setCommandMessage("M_MIX");
				break;
			default:
				break;
		}
		return ReturnCode::SUCCESS;
	}
	else if (!token.compare("bin")) {
		_strEngine.setNumberBaseMode(engine::StringEngine::NumberBaseMode::BINARY);
		stackEngine.setCommandMessage("M_BIN");
		return ReturnCode::SUCCESS;
	}
	else if (!token.compare("oct")) {
		_strEngine.setNumberBaseMode(engine::StringEngine::NumberBaseMode::OCTAL);
		stackEngine.setCommandMessage("M_OCT");
		return ReturnCode::SUCCESS;
	}
	else if (!token.compare("sdec")) {
		_strEngine.setNumberBaseMode(engine::StringEngine::NumberBaseMode::SIGNED_DECIMAL);
		stackEngine.setCommandMessage("M_DEC");
		return ReturnCode::SUCCESS;
	}
	else if (!token.compare("udec")) {
		_strEngine.setNumberBaseMode(engine::StringEngine::NumberBaseMode::UNSIGNED_DECIMAL);
		stackEngine.setCommandMessage("M_UDEC");
		return ReturnCode::SUCCESS;
	}
	else if (!token.compare("hex")) {
		_strEngine.setNumberBaseMode(engine::StringEngine::NumberBaseMode::HEXADECIMAL);
		stackEngine.setCommandMessage("M_HEX");
		return ReturnCode::SUCCESS;
	}
	else if (!token.compare("byte")) {
		_parser.setBinarySize(EckertParser::BinarySize::BYTE);
		stackEngine.setCommandMessage("M_BYT");
		return ReturnCode::SUCCESS;
	}
	else if (!token.compare("word")) {
		_parser.setBinarySize(EckertParser::BinarySize::WORD);
		stackEngine.setCommandMessage("M_WRD");
		return ReturnCode::SUCCESS;
	}
	else if (!token.compare("dword")) {
		_parser.setBinarySize(EckertParser::BinarySize::DWORD);
		stackEngine.setCommandMessage("M_DWD");
		return ReturnCode::SUCCESS;
	}
	else if (!token.compare("qword")) {
		_parser.setBinarySize(EckertParser::BinarySize::QWORD);
		stackEngine.setCommandMessage("M_QWD");
		return ReturnCode::SUCCESS;
	}
	return ReturnCode::NOT_FOUND;
}

////==--------------------------------------------------------------------====//
// ECKERT CUI / OPERATE REGISTER
// [ Update ]
// Feb 03, 2016
//====--------------------------------------------------------------------==////
EckertCui::ReturnCode
EckertCui::changeCalculatorPages(const std::string &token) {
	//==  Make lower token  ==//
	auto &stackEngine = _engCalc.refStackEngine();
	const auto stackItems = stackEngine.refStack().size();
	const auto registerSize = stackEngine.refRegister().size();
	//==  Try to change mode  ==//
	stackEngine.setErrorMessage("NO_ERROR");
	if (!token.compare("next") || !token.compare("n")) {
		stackEngine.setCommandMessage("SP_NXT");
		if (_paginator.stackNext(stackItems, registerSize)) {
			stackEngine.setErrorMessage("S_FNL");
			return ReturnCode::FAILURE;
		}
		else {
			return ReturnCode::SUCCESS;
		}
	}
	else if (!token.compare("prev") || !token.compare("p")) {
		stackEngine.setCommandMessage("SP_PRV");
		if (_paginator.stackPrev(stackItems, registerSize)) {
			stackEngine.setErrorMessage("S_FST");
			return ReturnCode::FAILURE;
		}
		else {
			return ReturnCode::SUCCESS;
		}
	}
	else if (!token.compare("first") || !token.compare("fst")) {
		stackEngine.setCommandMessage("SP_FST");
		if (_paginator.stackFirst(stackItems, registerSize)) {
			return ReturnCode::FAILURE;
		}
		else {
			return ReturnCode::SUCCESS;
		}
	}
	else if (!token.compare("regnext") || !token.compare("rn")) {
		stackEngine.setCommandMessage("RP_NXT");
		if (_paginator.registerNext(registerSize)) {
			stackEngine.setCommandMessage("R_FNL");
			return ReturnCode::FAILURE;
		}
		else {
			return ReturnCode::SUCCESS;
		}
	}
	else if (!token.compare("regprev") || !token.compare("rp")) {
		stackEngine.setCommandMessage("RP_PRV");
		if (_paginator.registerPrev(registerSize)) {
			stackEngine.setCommandMessage("R_FST");
			return ReturnCode::FAILURE;
		}
		else {
			return ReturnCode::SUCCESS;
		}
	}
	else if (!token.compare("regprev") || !token.compare("rp")) {
		stackEngine.setCommandMessage("RP_FST");
		if (_paginator.registerFirst(registerSize)) {
			return ReturnCode::FAILURE;
		}
		else {
			return ReturnCode::SUCCESS;
		}
	}
	return ReturnCode::NOT_FOUND;
}

////==--------------------------------------------------------------------====//
// ECKERT CUI / RUN MACRO
// [ Update ]
// Feb 03, 2016
//====--------------------------------------------------------------------==////
EckertCui::ReturnCode
EckertCui::runMacro(const std::string &token) {
	if (!StringChecker::isMacro(token)) {
		return ReturnCode::NOT_FOUND;
	}
	//==  Refer stack  ==//
	auto &stackEngine = _engCalc.refStackEngine();
	auto &stk = stackEngine.refStack();
	//==  String for macro  ==//
	std::string macro_string;
	//==  Try to run macro  ==//
	std::size_t items = stk.size();
	stackEngine.setCommandMessage("H_MACRO");
	stackEngine.setErrorMessage("NO_ERROR");
	if (items < 1) {
		stackEngine.setErrorMessage("FEW_ARG");
		return ReturnCode::NOT_FOUND;
	}
	else {
		auto &p_ex = *stk.rbegin();
		if (!p_ex->isType(engine::Element::ESTRING)) {
			stackEngine.setErrorMessage("BAD_TYPE");
			return ReturnCode::NOT_FOUND;
		}
		macro_string = GET_ESTRING_DATA(p_ex);
		stk.pop_back();
	}
	auto tokens = StringUtility::split(macro_string);
	items = tokens.size();
	if (0 == items) {
		stackEngine.setCommandMessage("H_MACRO");
		stackEngine.setErrorMessage("EMP_IN");
		return ReturnCode::NOT_FOUND;
	}
	for (std::size_t ucnt = 0; ucnt < items; ++ucnt) {
		//==  Operate token  ==//
		const std::string &token = tokens.at(ucnt);
		std::string lower_token = StringUtility::genLowerString(token);
		_stat.startRec();
		switch (_parser.pushElementByString(token, stackEngine, _stat)) {
			case EckertParser::ReturnCode::SUCCESS:
				_stat.stopRec();
				continue;
			case EckertParser::ReturnCode::FAILURE:
				_stat.stopRec();
				stackEngine.setCommandMessage("H_MACRO");
				return ReturnCode::FAILURE;
			case EckertParser::ReturnCode::NOT_FOUND:
				// fall through
			default:
				break;
		}
		switch (operateGeneralCalculation(lower_token)) {
			case ReturnCode::SUCCESS:
				_stat.stopRec();
				continue;
			case ReturnCode::FAILURE:
				_stat.stopRec();
				stackEngine.setCommandMessage("H_MACRO");
				return ReturnCode::FAILURE;
			case ReturnCode::NOT_FOUND:
				// fall through
			default:
				break;
		}
		switch (operateRegister(lower_token)) {
			case ReturnCode::SUCCESS:
				_stat.stopRec();
				continue;
			case ReturnCode::FAILURE:
				_stat.stopRec();
				stackEngine.setCommandMessage("H_MACRO");
				return ReturnCode::FAILURE;
			case ReturnCode::NOT_FOUND:
				// fall through
			default:
				break;
		}
		stackEngine.setErrorMessage("KW_ERR");
		return ReturnCode::FAILURE;
	}
	stackEngine.setCommandMessage("H_MACRO");
	stackEngine.setErrorMessage("NO_ERROR");
	return ReturnCode::SUCCESS;
}
