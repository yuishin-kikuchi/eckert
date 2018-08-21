#include "EckertCui.h"
#include "engine/proc/except/Exceptions.h"
#include "engine/EckertConstants.h"
#include "engine/UnitConverter.h"
#include "util/StringTables.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <cstdio>

static const char *indent = " ";
static const char *indent_deep = "   ";

////==--------------------------------------------------------------------====//
// ECKERT CUI / PUT LINE
// [ Update ]
// Feb 03, 2016
//====--------------------------------------------------------------------==////
void EckertCui::putline(const int &len, const char &c) {
	for (int cnt = 0; cnt < len; ++cnt) {
		std::cout << c;
	}
	std::cout << std::endl;
}

////==--------------------------------------------------------------------====//
// ECKERT CUI / DISPLAY
// [ Update ]
// Nov 25, 2016
//====--------------------------------------------------------------------==////
void EckertCui::display()
try {
	//==  Display app info  ==//
	std::cout << indent << NAME << std::endl; // Display application name
	std::cout << indent << AUTHOR << std::endl; // Display author
	auto display_width = _paginator.getDisplayWidth();
	putline(display_width, '-');
	switch (getOperationMode()) {
		case OperationMode::VERSION_FROM_CALCULATOR:
			// fall through
		case OperationMode::VERSION_FROM_CONFIG:
			displayVersion();
			putline(display_width, '-');
			std::cout << "(Press Return or Enter)" << std::endl;
			break;
		case OperationMode::CONFIG:
			displayConfig();
			break;
		case OperationMode::VIEW:
			displayFullData();
			putline(display_width, '-');
			std::cout << "(Press Return or Enter)" << std::endl;
			break;
		case OperationMode::CALCULATOR:
			displayCalculator();
			break;
		default:
			std::cerr
				<< indent
				<< "Technical error: type \"exit\"" << std::endl;
			putline(display_width, '-');
			break;
	}
}
catch (...) {
	setStateFlags(FATAL_STATE);
}

////==--------------------------------------------------------------------====//
// ECKERT CUI / DISPLAY VERSION
// [ Update ]
// Dec 16, 2016
//====--------------------------------------------------------------------==////
void EckertCui::displayVersion() {
	const auto &constantTable = engine::EckertConstants::scientificConstantValues;
	const auto &unitTable = engine::UnitConverter::criteria;
	auto display_width = _paginator.getDisplayWidth();
	std::cout << indent << "VERSION DISPLAY" << std::endl;
	putline(display_width, '=');
	// eckert cui
	std::cout << indent << VERSION << std::endl;
	// info
	const auto opSize = _engCalc.refOperators().size();
	const auto drgSize = _drgOperators.size();
	const auto constSize = constantTable.size();
	const auto unitSize = unitTable.size();
	putline(display_width, '-');
	std::cout << indent_deep << "   Stack functions: " << opSize + drgSize * 3 << std::endl;
	std::cout << indent_deep << "Register functions: " << 9 << std::endl;
	std::cout << indent_deep << "Math/Sci constants: " << constSize << std::endl;
	std::cout << indent_deep << "  Supporting units: " << unitSize << std::endl;
}

////==--------------------------------------------------------------------====//
// ECKERT CUI / DISPLAY CONFIG
// [ Update ]
// Nov 25, 2016
//====--------------------------------------------------------------------==////
void EckertCui::displayConfig()
try {
	const std::ios::fmtflags format = std::cout.flags();
	auto &stackEngine = _engCalc.refStackEngine();
	auto display_width = _paginator.getDisplayWidth();
	auto display_line = _paginator.getDisplayLine();
	auto history_size = _hist.getMaxSize();
	std::cout << " CONFIGURATION MODE" << std::endl;
	putline(display_width, '=');
	std::cout << indent << "Interface" << std::endl;
	std::cout << indent_deep << "History size   (hist): ";
	if (0 != history_size) {
		std::cout << history_size << std::endl;
	}
	else {
		std::cout << "OFF" << std::endl;
	}
	std::cout << indent_deep << "Display width (width): " << display_width << std::endl;
	std::cout << indent_deep << "Display lines (lines): " << display_line << std::endl;
	std::cout << indent << "Management" << std::endl;
	std::cout << indent_deep << "Load config   (load)" << std::endl;
	std::cout << indent_deep << "Save config   (save)" << std::endl;
	std::cout << indent_deep << "Reset config  (reset)" << std::endl;
	putline(display_width, '-');
	showConfigAdditionalInformation();
	putline(display_width, '-');
	stackEngine.setCommandMessage("CF_NOP");
	stackEngine.setErrorMessage("NO_ERROR");
	std::cout.setf(format);
}
catch (engine::EckertException &ee) {
	std::cout << ee.what() << std::endl;
	std::cout << "From: " << ee.where() << std::endl;
	setStateFlags(FATAL_STATE);
	getchar();
}
catch (std::exception &ex) {
	std::cout << ex.what() << std::endl;
	setStateFlags(FATAL_STATE);
	getchar();
}

////==--------------------------------------------------------------------====//
// ECKERT CUI / SHOW CONFIG INFORMATION
// [ Update ]
// May 22, 2018
//====--------------------------------------------------------------------==////
void EckertCui::showConfigAdditionalInformation() {
	//==  Backup cout flags  ==//
	const std::ios::fmtflags format = std::cout.flags();
	auto &stackEngine = _engCalc.refStackEngine();
	const auto &errorMessageTable = StringTables::errorMessage;
	const auto &noticeMessageTable = StringTables::noticeMessage;
	const auto &confirmMessageTable = StringTables::confirmMessage;
	const auto &instructionMessageTable = StringTables::instructionMessage;
	const auto opcode = stackEngine.getCommandMessage();
	const auto errcode = stackEngine.getErrorMessage();
	const auto msg_type = checkErrorMessage(errcode);
	bool inst_found = false;
	if (instructionMessageTable.find(opcode) != instructionMessageTable.end()) {
		inst_found = true;
	}
	std::cout << indent;
	switch (msg_type) {
		case MessageType::NO_ERROR:
			break;
		case MessageType::UNKNOWN:
			std::cout << "[?] ";
			break;
		case MessageType::ERROR:
			std::cout << "[!] ";
			break;
		case MessageType::NOTICE:
			std::cout << "[i] ";
			break;
		case MessageType::CONFIRM:
			std::cout << "[C] ";
			break;
		default:
			break;
	}
	if (inst_found) {
		std::cout << instructionMessageTable.at(opcode);
	}
	else {
		std::cout << "Operation code: " << opcode;
	}
	std::cout << std::endl;
	std::cout << indent;
	switch (msg_type) {
		case MessageType::NO_ERROR:
			std::cout << "Type \"calc\" or \"homura\" to quit config";
			break;
		case MessageType::UNKNOWN:
			std::cout << "Error code: " << errcode;
			break;
		case MessageType::ERROR:
			std::cout << "Error: " << errorMessageTable.at(errcode);
			break;
		case MessageType::NOTICE:
			std::cout << "Notice: " << noticeMessageTable.at(errcode);
			break;
		case MessageType::CONFIRM:
			std::cout << "Confirm: " << confirmMessageTable.at(errcode);
			break;
		default:
			break;
	}
	std::cout << std::endl;
	//==  Restore cout flag  ==//
	std::cout.setf(format);
}

////==--------------------------------------------------------------------====//
// ECKERT CUI / DISPLAY
// [ Update ]
// Feb 03, 2016
//====--------------------------------------------------------------------==////
void EckertCui::displayCalculator()
try {
	//==  Backup cout flags  ==//
	const std::ios::fmtflags format = std::cout.flags();
	//==  Calculate parameters  ==//
	auto stackEngine = _engCalc.refStackEngine();
	DisplayHint dh(stackEngine, _strEngine, _paginator);
	//==  Head information  ==//
	showHeader(dh);
	//==  Header of stack and register area  ==//
	putline(dh.displayWidth, '=');
	showColumn(dh);
	//==  Display register  ==//
	if (dh.registerFlag) {
		showRegister(dh);
		//=  Top of register area  =//
		if (dh.registerLine + dh.stackItems <= dh.displayLine + dh.stackOffset) {
			putline(dh.displayWidth, '_');
		}
		else {
			showContinuing('^', dh);
		}
	}
	else {
		//=  Top of stack area  =//
		if (dh.stackItems > dh.displayLine + dh.stackOffset) {
			showContinuing('^', dh);
		}
		else {
			putline(dh.displayWidth, '_');
		}
	}
	//==  Display stack  ==//
	showStack(dh);
	//==  Bottom of stack and register area  ==//
	if (dh.stackOffset > 0) {
		showContinuing('v', dh);
	}
	else {
		putline(dh.displayWidth, '-');
	}
	//==  Display last operation and other info  ==//
	showCalculatorAdditionalInformation();
	putline(dh.displayWidth, '-');
	//==  Reset messages  ==//
	stackEngine.setCommandMessage("H_NOP");
	stackEngine.setErrorMessage("NO_ERROR");
	_stat.startRec();
	//==  Restore cout flag  ==//
	std::cout.setf(format);
}
catch (engine::EckertException &ee) {
	std::cout << ee.what() << std::endl;
	std::cout << "From: " << ee.where() << std::endl;
	getchar();
	throw;
}
catch (std::exception &ex) {
	std::cout << ex.what() << std::endl;
	getchar();
	throw;
}

////==--------------------------------------------------------------------====//
// ECKERT CUI - HOMURA FRONT END / SHOW STACK
// [ Update ]
// Feb 03, 2016
//====--------------------------------------------------------------------==////
void EckertCui::showStack(const DisplayHint &dh) {
	//==  Backup cout flags  ==//
	const std::ios::fmtflags format = std::cout.flags();
	//==  Initialize cout  ==//
	std::cout << std::setfill(' ');
	//==  Stack reference  ==//
	const auto &stackEngine = _engCalc.refStackEngine();
	const auto &stk = stackEngine.refStack();
	//==  Display stack  ==//
	for (std::size_t ucnt = dh.stackLine; 0 != ucnt; --ucnt) {
		//=  Item number  =//
		if (ucnt + dh.stackOffset < 4) {
			// display X, Y, Z anytime
			std::cout
				<< std::setw(dh.numWidth)
				<< std::right
				<< (char)('X' + ucnt - 1);
		}
		else if (ucnt + dh.stackOffset > dh.stackItems) {
			// display '-' when the item is not available
			std::cout
				<< std::setw(dh.numWidth)
				<< std::right
				<< '-';
		}
		else {
			// display 4, 5, 6... when the item is available
			std::cout
				<< std::setw(dh.numWidth)
				<< std::right
				<< ucnt + dh.stackOffset;
		}
		std::cout << ": ";
		if (ucnt + dh.stackOffset < dh.stackItems + 1) {
			//=  Item is available  =//
			const auto &elm = stk.at(dh.stackItems - ucnt - dh.stackOffset);
			//=  Element type  =//
			switch (_strEngine.getTypeDisplayMode()) {
				case engine::StringEngine::TypeDisplayMode::LONG:
					std::cout
						<< std::setw(dh.typeWidth)
						<< std::left
						<< _strEngine.typeToLongString(elm)
						<< " : ";
					break;
				case engine::StringEngine::TypeDisplayMode::SHORT:
					std::cout
						<< std::setw(dh.typeWidth)
						<< std::left
						<< _strEngine.typeToShortString(elm)
						<< " : ";
					break;
				case engine::StringEngine::TypeDisplayMode::NO_DISPLAY:
					break;
				default:
					break;
			}
			//=  Element value  =//
			std::cout
				<< std::setw(dh.valueWidth)
				<< std::right
				<< _strEngine.elementToString(_cfg, elm, dh.valueWidth);
		}
		else {
			//=  Item is not available  =//
			switch (_strEngine.getTypeDisplayMode()) {
				case engine::StringEngine::TypeDisplayMode::LONG:
					// fall through
				case engine::StringEngine::TypeDisplayMode::SHORT:
					std::cout
						<< std::setw(dh.typeWidth)
						<< std::right
						<< ""
						<< " :";
					break;
				case engine::StringEngine::TypeDisplayMode::NO_DISPLAY:
					break;
				default:
					break;
			}
		}
		std::cout << std::endl;
	}
	//==  Restore cout flag  ==//
	std::cout.setf(format);
}

////==--------------------------------------------------------------------====//
// ECKERT CUI / SHOW REGISTER
// [ Update ]
// Feb 03, 2016
//====--------------------------------------------------------------------==////
void EckertCui::showRegister(const DisplayHint &dh) {
	//==  Backup cout flags  ==//
	const std::ios::fmtflags format = std::cout.flags();
	//==  Register reference  ==//
	const auto &stackEngine = _engCalc.refStackEngine();
	const auto &reg = stackEngine.refRegister();
	//==  Initialize cout  ==//
	std::cout << std::setfill(' ');
	//==  Display register  ==//
	std::size_t scanning = dh.registerOffset;
	for (std::size_t ucnt = 0; ucnt < dh.registerLine; ++ucnt) {
		if (scanning < dh.registerSize) {
			// check range of register
			const auto &elm = reg.at(scanning);
			//=  Item number  =//
			std::cout
				<< std::setw(dh.numWidth - 1)
				<< std::right
				<< "R"
				<< (char)('A' + scanning)
				<< ": ";
			if (elm) {
				// if elm is not null, data is available
				//=  Element type  =//
				switch (_strEngine.getTypeDisplayMode()) {
					case engine::StringEngine::TypeDisplayMode::LONG:
						std::cout
							<< std::setw(dh.typeWidth)
							<< std::left
							<< _strEngine.typeToLongString(elm)
							<< " : ";
						break;
					case engine::StringEngine::TypeDisplayMode::SHORT:
						std::cout
							<< std::setw(dh.typeWidth)
							<< std::left
							<< _strEngine.typeToShortString(elm)
							<< " : ";
						break;
					case engine::StringEngine::TypeDisplayMode::NO_DISPLAY:
						break;
					default:
						break;
				}
				//=  engine::Element value  =//
				std::cout
					<< std::setw(dh.valueWidth)
					<< std::right
					<< _strEngine.elementToString(_cfg, elm, dh.valueWidth);
			}
			else {
				// if elm is null, show empty line
				switch (_strEngine.getTypeDisplayMode()) {
					case engine::StringEngine::TypeDisplayMode::LONG:
						// fall through
					case engine::StringEngine::TypeDisplayMode::SHORT:
						std::cout
							<< std::setw(dh.typeWidth)
							<< std::left
							<< ""
							<< " :";
						break;
					case engine::StringEngine::TypeDisplayMode::NO_DISPLAY:
						break;
					default:
						break;
				}
			}
		}
		else {
			// out of range of register
			//=  Item number  =//
			std::cout
				<< std::setw(dh.numWidth)
				<< std::right
				<< "--"
				<< ": ";
			switch (_strEngine.getTypeDisplayMode()) {
				case engine::StringEngine::TypeDisplayMode::LONG:
					// fall through
				case engine::StringEngine::TypeDisplayMode::SHORT:
					std::cout
						<< std::setw(dh.typeWidth)
						<< std::left
						<< ""
						<< " :";
					break;
				case engine::StringEngine::TypeDisplayMode::NO_DISPLAY:
					break;
				default:
					break;
			}
		}
		++scanning;
		std::cout << std::endl;
	}
	//==  Restore cout flag  ==//
	std::cout.setf(format);
}

////==--------------------------------------------------------------------====//
// ECKERT CUI / SHOW HEADER
// [ Update ]
// Jul 10, 2017
//====--------------------------------------------------------------------==////
void EckertCui::showHeader(const EckertCui::DisplayHint &dh) {
	const char *head_splitter = ",  ";
	//==  Backup cout flags  ==//
	const std::ios::fmtflags format = std::cout.flags();
	// Display mode of Homura
	std::cout << indent;
	std::cout << "HOMURA: ";
	switch (_strEngine.getDecimalDisplayMode()) {
		case engine::StringEngine::DecimalDisplayMode::AUTO_DECIMAL:
			std::cout << "(AD) ";
			break;
		case engine::StringEngine::DecimalDisplayMode::FORCE_DECIMAL:
			std::cout << "(FD) ";
			break;
		case engine::StringEngine::DecimalDisplayMode::FORCE_FRACTIONAL:
			std::cout << "(FF) ";
			break;
		default:
			std::cout << "!ERROR!";
			break;
	}
	switch (_cfg.getAngleMode()) {
		case engine::CalculationConfig::AngleMode::DEGREE:
			std::cout << "(Deg) ";
			break;
		case engine::CalculationConfig::AngleMode::RADIAN:
			std::cout << "(Rad) ";
			break;
		case engine::CalculationConfig::AngleMode::GRADE:
			std::cout << "(Gra) ";
			break;
		default:
			std::cout << "!ERROR!";
			break;
	}
	switch (_strEngine.getNumberBaseMode()) {
		case engine::StringEngine::NumberBaseMode::BINARY:
			std::cout << "(Bin) ";
			break;
		case engine::StringEngine::NumberBaseMode::OCTAL:
			std::cout << "(Oct) ";
			break;
		case engine::StringEngine::NumberBaseMode::SIGNED_DECIMAL:
			std::cout << "(Sdec) ";
			break;
		case engine::StringEngine::NumberBaseMode::UNSIGNED_DECIMAL:
			std::cout << "(Udec) ";
			break;
		case engine::StringEngine::NumberBaseMode::HEXADECIMAL:
			std::cout << "(Hex) ";
			break;
		default:
			std::cout << "!ERROR!";
			break;
	}
	switch (_parser.getBinarySize()) {
		case EckertParser::BinarySize::BYTE:
			std::cout << "(Byte) ";
			break;
		case EckertParser::BinarySize::WORD:
			std::cout << "(Word) ";
			break;
		case EckertParser::BinarySize::DWORD:
			std::cout << "(Dword) ";
			break;
		case EckertParser::BinarySize::QWORD:
			std::cout << "(Qword) ";
			break;
		default:
			std::cout << "!ERROR!";
			break;
	}
	if (dh.registerFlag) {
		std::cout << "[Reg] ";
	}
	if (_strEngine.getEulerFlag()) {
		std::cout << "[Eul";
		if (_strEngine.getPiRadianFlag()) {
			std::cout << "(Pi)";
		}
		std::cout << "] ";
	}
	switch (_strEngine.getFractionalDisplayMode()) {
		case engine::StringEngine::FractionalDisplayMode::MIXED:
			std::cout << "[i.a/b] ";
			break;
		case engine::StringEngine::FractionalDisplayMode::PROVISIONAL:
			break;
		default:
			break;
	}
	std::cout << std::endl;
	// Display digits
	std::cout << indent;
	const auto &fdisp = _strEngine.refFloatingDisplayConfig();
	std::cout << std::setfill(' ');
	switch (fdisp.getDisplayMode()) {
		case engine::FloatingDisplayConfig::STANDARD:
			std::cout
				<< "Std: "
				<< std::setw(2) << fdisp.getStdDigits() << '/'
				<< std::setw(2) << fdisp.getStdMax();
			break;
		case engine::FloatingDisplayConfig::FIXED:
			std::cout
				<< "Fix: "
				<< std::setw(2) << fdisp.getFixDigits() << '/'
				<< std::setw(2) << fdisp.getFixMax();
			break;
		case engine::FloatingDisplayConfig::SCIENTIFIC:
			std::cout
				<< "Sci: "
				<< std::setw(2) << fdisp.getSciDigits() << '/'
				<< std::setw(2) << fdisp.getSciMax();
			break;
		case engine::FloatingDisplayConfig::ENGINEERING:
			std::cout
				<< "Eng: "
				<< std::setw(2) << fdisp.getEngDigits() << '/'
				<< std::setw(2) << fdisp.getEngMax();
			break;
		default:
			std::cout << "!ERROR!";
			break;
	}
	// Stack items
	std::cout << head_splitter;
	std::cout << "Stack: ";
	if (0 == dh.stackItems) {
		std::cout << "Empty";
	}
	else {
		std::cout << dh.stackItems;
	}
	// History items
	std::size_t history_items = _hist.getCurrentSize();
	std::cout << head_splitter;
	std::cout << "History: ";
	if (0 == _hist.getMaxSize()) {
		std::cout << "OFF";
	}
	else if (0 == history_items) {
		std::cout << "Init";
	}
	else {
		std::cout << _hist.getCurrentPos() << '/' << history_items;
	}
	std::cout << std::endl;
	//==  Restore cout flag  ==//
	std::cout.setf(format);
}

////==--------------------------------------------------------------------====//
// ECKERT CUI / SHOW LEGEND
// [ Update ]
// Feb 03, 2016
//====--------------------------------------------------------------------==////
void EckertCui::showColumn(const EckertCui::DisplayHint &dh) {
	//==  Backup cout flags  ==//
	const std::ios::fmtflags format = std::cout.flags();
	//==  Column  ==//
	std::cout
		<< std::setw(dh.numWidth)
		<< std::right
		<< "#"
		<< "  ";
	if (0 != dh.typeWidth) {
		std::cout
			<< std::setw(dh.typeWidth)
			<< std::left
			<< "TYPE"
			<< " : ";
	}
	std::cout
		<< std::setw(dh.valueWidth)
		<< std::right
		<< "VALUE"
		<< std::endl;
	//==  Restore cout flag  ==//
	std::cout.setf(format);
}

////==--------------------------------------------------------------------====//
// ECKERT CUI / SHOW CALCULATOR INFORMATION
// [ Update ]
// Aug 22, 2018
//====--------------------------------------------------------------------==////
void EckertCui::showCalculatorAdditionalInformation() {
	const char *DEFAULT_MESSAGE = "Ready to operate";
	//==  Backup cout flags  ==//
	const std::ios::fmtflags format = std::cout.flags();
	//==  Messages reference  ==//
	auto &stackEngine = _engCalc.refStackEngine();
	const auto &constantKeywordTable = engine::EckertConstants::scientificConstantKeywords;
	const auto &constantValueTable = engine::EckertConstants::scientificConstantValues;
	const auto &errorMessageTable = StringTables::errorMessage;
	const auto &noticeMessageTable = StringTables::noticeMessage;
	const auto &confirmMessageTable = StringTables::confirmMessage;
	const auto &instructionMessageTable = StringTables::instructionMessage;
	const auto &pushMessageTable = StringTables::pushMessage;
	const auto &prefixMessageTable = StringTables::prefixMessage;
	const auto opcode = stackEngine.getCommandMessage();
	const auto errcode = stackEngine.getErrorMessage();
	const auto additional = stackEngine.getAdditionalMessage();
	const auto msg_type = checkErrorMessage(errcode);
	//==  Other definition  ==//
	const auto waiting = _stat.getWaitingState();
	double duration = _stat.getDuration();
	//==  Operate information  ==//
	std::cout << indent;
	if (!opcode.compare("PUSH_N")) {
		// push operation
		std::cout << instructionMessageTable.at(opcode) << ' ';
		if (pushMessageTable.find(errcode) != pushMessageTable.end()) {
			std::cout << pushMessageTable.at(errcode);
			if (prefixMessageTable.find(additional) != prefixMessageTable.end()) {
				std::cout << " with " << prefixMessageTable.at(additional);
			}
			std::cout << std::endl;
			std::cout << indent << DEFAULT_MESSAGE << std::endl;
		}
		else {
			std::cout << "Unknown" << std::endl;
			std::cout << indent << DEFAULT_MESSAGE << std::endl;
		}
	}
	else if (!opcode.compare("PUSH_B")) {
		std::cout << instructionMessageTable.at(opcode) << ' ';
		std::cout << pushMessageTable.at(errcode) << std::endl;
		std::cout << indent << DEFAULT_MESSAGE << std::endl;
	}
	else if (!opcode.compare("PUSH_S")) {
		std::cout << instructionMessageTable.at(opcode) << ' ';
		std::cout << pushMessageTable.at(errcode) << std::endl;
		std::cout << indent << DEFAULT_MESSAGE << std::endl;
	}
	else if (!opcode.compare("PUSH_C")) {
		std::cout << instructionMessageTable.at(opcode) << std::endl;
		if (constantKeywordTable.find(additional) != constantKeywordTable.end()) {
			const auto &constId = constantKeywordTable.at(additional);
			if (constantValueTable.find(constId) != constantValueTable.end()) {
				const auto &pair = constantValueTable.at(constId);
				std::cout << indent << pair.name << std::endl;
			}
			else {
				std::cout << "code: " << additional << std::endl;
			}
		}
		else {
			std::cout << "code: " << additional << std::endl;
		}
	}
	else {
		// operations without push
		bool inst_found = false;
		if (instructionMessageTable.find(opcode) != instructionMessageTable.end()) {
			inst_found = true;
		}
		switch (msg_type) {
			case EckertCui::MessageType::NO_ERROR:
				break;
			case EckertCui::MessageType::ERROR:
				std::cout << "[!] ";
				break;
			case EckertCui::MessageType::NOTICE:
				std::cout << "[i] ";
				break;
			case EckertCui::MessageType::CONFIRM:
				std::cout << "[C] ";
				break;
			default:
				std::cout << "[?] ";
				break;
		}
		if (inst_found) {
			std::cout << instructionMessageTable.at(opcode);
		}
		else {
			std::cout << "Operation code: " << opcode;
		}
		// time display
		if (duration >= 1.0) {
			std::cout << " (" << duration << " sec)";
		}
		else if (duration >= 1.0E-1) {
			std::cout << " (" << duration * 1.0E+3 << " msec)";
		}
		std::cout << std::endl;
		std::cout << indent;
		// information
		if (!opcode.compare("H_JSON")) {
			if (!errcode.compare("OUT_ERR")) {
				std::cout << "Error: " << errorMessageTable.at(errcode) << std::endl;
			}
			else {
				std::cout << "out: " << getJsonFilename() << std::endl;
			}
		}
		else if (!opcode.compare("H_CONV")) {
			auto fromUnit = _stat.getFromUnit();
			auto toUnit = _stat.getToUnit();
			switch (_stat.getWaitingState()) {
				case EckertStates::FIRST_UNIT:
					std::cout << "Confirm: From ______" << std::endl;
					break;
				case EckertStates::SECOND_UNIT:
					std::cout
					<< "Confirm: From ["
					<< engine::UnitConverter::getUnitName(fromUnit)
					<< "] to ______"
					<< std::endl;
					break;
				default:
					switch (msg_type) {
						case EckertCui::MessageType::NO_ERROR:
							std::cout
								<< "From ["
								<< engine::UnitConverter::getUnitName(fromUnit)
								<< "] to ["
								<< engine::UnitConverter::getUnitName(toUnit)
								<< ']'
								<< std::endl;
							break;
						case EckertCui::MessageType::ERROR: {
							if (!errcode.compare("CNV_ERR")) {
								std::cout
									<< "Error: From ["
									<< engine::UnitConverter::getUnitName(fromUnit)
									<< "] to ["
									<< engine::UnitConverter::getUnitName(toUnit)
									<< "] : INVALID"
									<< std::endl;
							}
							else {
								std::cout << "Error: " << errorMessageTable.at(errcode) << std::endl;
							}
							break;
						}
						default:
							std::cout << "Error code: " << errcode << std::endl;
							break;
					}
					break;
			}
		}
		else if (!opcode.compare("H_REC")) {
			auto fromUnit = _stat.getPrevFromUnit();
			auto toUnit = _stat.getPrevToUnit();
			if (msg_type == EckertCui::MessageType::ERROR) {
				std::cout
					<< "Error: "
					<< errorMessageTable.at(errcode)
					<< std::endl;
			}
			else {
				std::cout
					<< "From ["
					<< engine::UnitConverter::getUnitName(fromUnit)
					<< "] to ["
					<< engine::UnitConverter::getUnitName(toUnit)
					<< ']'
					<< std::endl;
			}
		}
		else {
			switch (msg_type) {
				case EckertCui::MessageType::NO_ERROR:
					std::cout << DEFAULT_MESSAGE << std::endl;
					break;
				case EckertCui::MessageType::ERROR:
					std::cout << "Error: " << errorMessageTable.at(errcode) << std::endl;
					break;
				case EckertCui::MessageType::NOTICE:
					std::cout << "Notice: " << noticeMessageTable.at(errcode) << std::endl;
					break;
				case EckertCui::MessageType::CONFIRM:
					std::cout << "Confirm: ";
					switch (waiting) {
						case EckertStates::WaitingState::RESET_CONFIRM:
							std::cout
								<< "OK?  Y/N"
								<< std::endl;
							break;
						default:
							std::cout << confirmMessageTable.at(errcode) << std::endl;
							break;
					}
					break;
				default:
					std::cout << "Error code: " << errcode << std::endl;
			}
		}
	}
	//==  Restore cout flag  ==//
	std::cout.setf(format);
}

////==--------------------------------------------------------------------====//
// ECKERT CUI / SHOW CONTINUING
// [ Update ]
// Feb 03, 2016
//====--------------------------------------------------------------------==////
void EckertCui::showContinuing(const char &c, const EckertCui::DisplayHint &dh) {
	//==  Backup cout flags  ==//
	const std::ios::fmtflags format = std::cout.flags();
	//==  Continuing  ==//
	std::cout
		<< std::setfill(' ') << std::setw(dh.numWidth) << std::right
		<< c
		<< "  ......"
		<< std::setw(dh.displayWidth - dh.numWidth - 10) << std::right
		<< "......  "
		<< c
		<< std::endl;
	//==  Restore cout flag  ==//
	std::cout.setf(format);
}

////==--------------------------------------------------------------------====//
// ECKERT CUI / DISPLAY FULL DATA (VIEW MODE)
// [ Update ]
// May 20, 2018
//====--------------------------------------------------------------------==////
void EckertCui::displayFullData()
try {
	//==  Backup cout flags  ==//
	const std::ios::fmtflags format = std::cout.flags();
	//==  Stack and register reference  ==//
	auto &stackEngine = _engCalc.refStackEngine();
	const auto &stk = stackEngine.refStack();
	const auto &reg = stackEngine.refRegister();
	//==  Calculate display parameters  ==//
	DisplayHint dh(stackEngine, _strEngine, _paginator);
	//==  Initialize cout  ==//
	std::cout << std::setfill(' ');
	//==  Display register  ==//
	if (dh.registerFlag) {
		bool reg_nodata = true;
		std::cout << "----------------" << std::endl;
		std::cout << " REGISTERS VIEW " << std::endl;
		std::cout << "================" << std::endl;
		std::size_t scanning = dh.registerOffset;
		for (std::size_t ucnt = 0; ucnt < dh.registerLine; ++ucnt) {
			if (scanning < dh.registerSize) {
				const auto &elm = reg.at(scanning);
				if (elm) {
					// if elm is not null, data is available
					//=  Item number  =//
					std::cout
						<< 'R'
						<< (char)('A' + scanning)
						<< ": ";
					//=  engine::Element type  =//
					std::cout
						<< _strEngine.typeToLongString(elm)
						<< ':'
						<< std::endl;
					//=  engine::Element value  =//
					std::cout
						<< _strEngine.elementToString(_cfg, elm)
						<< std::endl;
					reg_nodata = false;
				}
			}
			++scanning;
		}
		if (reg_nodata) {
			std::cout << " [!] NO DATA TO SHOW IN REGISTERS" << std::endl;
		}
		std::cout << std::endl;
	}
	//==  Display stack  ==//
	bool stk_nodata = true;
	std::cout << "------------" << std::endl;
	std::cout << " STACK VIEW " << std::endl;
	std::cout << "============" << std::endl;
	for (std::size_t ucnt = dh.stackLine; 0 != ucnt; --ucnt) {
		if (ucnt + dh.stackOffset < dh.stackItems + 1) {
			const auto &elm = stk.at(dh.stackItems - ucnt - dh.stackOffset);
			//=  Item number  =//
			if (ucnt + dh.stackOffset < 4) {
				std::cout
					<< (char)('X' + ucnt - 1)
					<< ": ";
			}
			else {
				std::cout
					<< ucnt + dh.stackOffset
					<< ": ";
			}
			//=  engine::Element type  =//
			std::cout
				<< _strEngine.typeToLongString(elm)
				<< ':'
				<< std::endl;
			//=  engine::Element value  =//
			std::cout
				<< _strEngine.elementToString(_cfg, elm)
				<< std::endl;
			stk_nodata = false;
		}
	}
	if (stk_nodata) {
		std::cout << " [!] NO DATA TO SHOW IN STACK" << std::endl;
	}
	std::cout << std::endl;
	//==  Reset messages  ==//
	stackEngine.setCommandMessage("H_NOP");
	stackEngine.setErrorMessage("NO_ERROR");
	//==  Restore cout flag  ==//
	std::cout.setf(format);
}
catch (engine::EckertException &ee) {
	std::cout << ee.what() << std::endl;
	std::cout << "From: " << ee.where() << std::endl;
	getchar();
	throw;
}
catch (std::exception &ex) {
	std::cout << ex.what() << std::endl;
	getchar();
	throw;
}
