#include "StringChecker.h"
#include <cctype>

////==--------------------------------------------------------------------====//
// STRING CHECKER / IS DOUBLE QUOTED
// [ Update ]
// Feb 02, 2016
//====--------------------------------------------------------------------==////
bool StringChecker::isDoubleQuoted(const std::string &token) {
	if (token.size() < 2u) {
		return false;
	}
	if (('\"' == *token.rbegin()) && ('\"' == *token.begin())) {
		return true;
	}
	else {
		return false;
	}
}

////==--------------------------------------------------------------------====//
// STRING CHECKER / GET REGISTER POSITION
// [ Update ]
// Feb 02, 2016
//====--------------------------------------------------------------------==////
std::size_t StringChecker::getRegisterPos(const std::string &token) {
	if (token.size() > 1) {
		char ch = *token.rbegin();
		if (std::isupper(ch)) {
			return (ch - 'A');
		}
		else if (std::islower(ch)) {
			return (ch - 'a');
		}
		else {
			return (std::size_t)(-1);
		}
	}
	else {
		return (std::size_t)(-1);
	}
}

////==--------------------------------------------------------------------====//
// STRING CHECKER / IS STORE STRING
// [ Update ]
// Feb 02, 2016
//====--------------------------------------------------------------------==////
bool StringChecker::isRegisterStore(const std::string &token) {
	if (4 != token.size()) {
		return false;
	}
	else {
		std::string::size_type pos = 0;
		std::string lower_token = genLowerString(token);
		pos = lower_token.find("str", 0);
		if ((0 != pos) || (std::string::npos == pos)) {
			return false; // not found
		}
		if (std::islower(lower_token.at(3))) {
			return true; // stra to strz
		}
		else {
			return false;
		}
	}
}

////==--------------------------------------------------------------------====//
// STRING CHECKER / IS LOAD STRING
// [ Update ]
// Feb 02, 2016
//====--------------------------------------------------------------------==////
bool StringChecker::isRegisterLoad(const std::string &token) {
	if (4 != token.size()) {
		return false;
	}
	else {
		std::string::size_type pos = 0;
		std::string lower_token = genLowerString(token);
		pos = lower_token.find("ldr", 0);
		if ((0 != pos) || (std::string::npos == pos)) {
			return false; // not found
		}
		if (std::islower(token.at(3))) {
			return true; // ldra to ldrz
		}
		else {
			return false;
		}
	}
}

////==--------------------------------------------------------------------====//
// STRING CHECKER / IS DELETE STRING
// [ Update ]
// Feb 02, 2016
//====--------------------------------------------------------------------==////
bool StringChecker::isRegisterDel(const std::string &token) {
	if (5 != token.size()) {
		return false;
	}
	else {
		std::string::size_type pos = 0;
		std::string lower_token = genLowerString(token);
		pos = lower_token.find("delr", 0);
		if ((0 != pos) || (std::string::npos == pos)) {
			return false; // not found
		}
		if (std::islower(token.at(4))) {
			return true; // delra to delrz
		}
		else {
			return false;
		}
	}
}

////==--------------------------------------------------------------------====//
// STRING CHECKER / IS REGISTER INCREMENT STRING
// [ Update ]
// Feb 02, 2016
//====--------------------------------------------------------------------==////
bool StringChecker::isRegisterInc(const std::string &token) {
	std::string::size_type pos = 0;
	switch (token.size()) {
	case 3: {
		pos = token.find("ir", 0);
		if ((0 != pos) || (std::string::npos == pos)) {
			return false; // not found
		}
		if (std::islower(token.at(2))) {
			return true; // ira to irz
		}
		break;
	}
	case 4: {
		pos = token.find("++r", 0);
		if ((0 != pos) || (std::string::npos == pos)) {
			return false; // not found
		}
		if (std::islower(token.at(3))) {
			return true; // ++ra to ++rz
		}
		break;
	}
	default:
		return false;
	}
	return false;
}

////==--------------------------------------------------------------------====//
// STRING CHECKER / IS REGISTER DECREMENT STRING
// [ Update ]
// Feb 02, 2016
//====--------------------------------------------------------------------==////
bool StringChecker::isRegisterDec(const std::string &token) {
	std::string::size_type pos = 0;
	std::string lower_token = genLowerString(token);
	switch (token.size()) {
	case 3: {
		pos = lower_token.find("dr", 0);
		if ((0 != pos) || (std::string::npos == pos)) {
			return false; // not found
		}
		if (std::islower(token.at(2))) {
			return true; // dra to drz
		}
		break;
	}
	case 4: {
		pos = lower_token.find("--r", 0);
		if ((0 != pos) || (std::string::npos == pos)) {
			return false; // not found
		}
		if (std::islower(token.at(3))) {
			return true; // --ra to --rz
		}
		break;
	}
	default:
		return false;
	}
	return false;
}

////==--------------------------------------------------------------------====//
// STRING CHECKER / IS REGISTER ADDITION STRING
// [ Update ]
// Feb 02, 2016
//====--------------------------------------------------------------------==////
bool StringChecker::isRegisterAdd(const std::string &token) {
	std::string::size_type pos = 0;
	std::string lower_token = genLowerString(token);
	switch (token.size()) {
	case 5: {
		pos = lower_token.find("addr", 0);
		if ((0 != pos) || (std::string::npos == pos)) {
			return false; // not found
		}
		if (std::islower(token.at(4))) {
			return true; // addra to addrz
		}
		break;
	}
	case 3: {
		pos = lower_token.find("+r", 0);
		if ((0 != pos) || (std::string::npos == pos)) {
			return false; // not found
		}
		if (std::islower(token.at(2))) {
			return true; // +ra to +rz
		}
		break;
	}
	default:
		return false;
	}
	return false;
}

////==--------------------------------------------------------------------====//
// STRING CHECKER / IS REGISTER SUBTRACTION STRING
// [ Update ]
// Feb 02, 2016
//====--------------------------------------------------------------------==////
bool StringChecker::isRegisterSub(const std::string &token) {
	std::string::size_type pos = 0;
	std::string lower_token = genLowerString(token);
	switch (token.size()) {
	case 5: {
		pos = lower_token.find("subr", 0);
		if ((0 != pos) || (std::string::npos == pos)) {
			return false; // not found
		}
		if (std::islower(token.at(4))) {
			return true; // subra to subrz
		}
		break;
	}
	case 3: {
		pos = lower_token.find("-r", 0);
		if ((0 != pos) || (std::string::npos == pos)) {
			return false; // not found
		}
		if (std::islower(token.at(2))) {
			return true; // -ra to -rz
		}
		break;
	}
	default:
		return false;
	}
	return false;
}

////==--------------------------------------------------------------------====//
// STRING CHECKER / IS REGISTER MULTIPLICATION STRING
// [ Update ]
// Feb 02, 2016
//====--------------------------------------------------------------------==////
bool StringChecker::isRegisterMul(const std::string &token) {
	std::string::size_type pos = 0;
	std::string lower_token = genLowerString(token);
	switch (token.size()) {
	case 5: {
		pos = lower_token.find("mulr", 0);
		if ((0 != pos) || (std::string::npos == pos)) {
			return false; // not found
		}
		if (std::islower(token.at(4))) {
			return true; // mulra to mulrz
		}
		break;
	}
	case 3: {
		pos = lower_token.find("*r", 0);
		if ((0 != pos) || (std::string::npos == pos)) {
			return false; // not found
		}
		if (std::islower(token.at(2))) {
			return true; // *ra to *rz
		}
		break;
	}
	default:
		return false;
	}
	return false;
}

////==--------------------------------------------------------------------====//
// STRING CHECKER / IS REGISTER DIVISION STRING
// [ Update ]
// Feb 02, 2016
//====--------------------------------------------------------------------==////
bool StringChecker::isRegisterDiv(const std::string &token) {
	std::string::size_type pos = 0;
	std::string lower_token = genLowerString(token);
	switch (token.size()) {
	case 5: {
		pos = lower_token.find("divr", 0);
		if ((0 != pos) || (std::string::npos == pos)) {
			return false; // not found
		}
		if (std::islower(token.at(4))) {
			return true; // mulra to mulrz
		}
		break;
	}
	case 3: {
		pos = lower_token.find("/r", 0);
		if ((0 != pos) || (std::string::npos == pos)) {
			return false; // not found
		}
		if (std::islower(token.at(2))) {
			return true; // /ra to /rz
		}
		break;
	}
	default:
		return false;
	}
	return false;
}

////==--------------------------------------------------------------------====//
// STRING CHECKER / IS YES STRING
// [ Update ]
// Feb 02, 2016
//====--------------------------------------------------------------------==////
bool StringChecker::isYes(const std::string &token) {
	std::string lower_token = genLowerString(token);
	return (
		(!lower_token.compare("yes")) ||
		(!lower_token.compare("y"))
	);
}

////==--------------------------------------------------------------------====//
// STRING CHECKER / IS NO STRING
// [ Update ]
// Feb 02, 2016
//====--------------------------------------------------------------------==////
bool StringChecker::isNo(const std::string &token) {
	std::string lower_token = genLowerString(token);
	return (
		(!lower_token.compare("no")) ||
		(!lower_token.compare("n"))
	);
}

////==--------------------------------------------------------------------====//
// STRING CHECKER / IS RESET STRING
// [ Update ]
// Feb 02, 2016
//====--------------------------------------------------------------------==////
bool StringChecker::isReset(const std::string &token) {
	std::string lower_token = genLowerString(token);
	return (
		(!lower_token.compare("reset")) ||
		(!lower_token.compare("rst"))
	);
}

////==--------------------------------------------------------------------====//
// STRING CHECKER / IS DISP DIGIT STRING
// [ Update ]
// Feb 02, 2016
//====--------------------------------------------------------------------==////
bool StringChecker::isDisplayDigit(const std::string &token) {
	std::string lower_token = genLowerString(token);
	return (
		(!lower_token.compare("digit")) ||
		(!lower_token.compare("disp"))
	);
}

////==--------------------------------------------------------------------====//
// STRING CHECKER / IS UNDO STRING
// [ Update ]
// Feb 02, 2016
//====--------------------------------------------------------------------==////
bool StringChecker::isUndo(const std::string &token) {
	std::string lower_token = genLowerString(token);
	return (
		(!lower_token.compare("undo")) ||
		(!lower_token.compare("u"))
	);
}

////==--------------------------------------------------------------------====//
// STRING CHECKER / IS REDO STRING
// [ Update ]
// Feb 02, 2016
//====--------------------------------------------------------------------==////
bool StringChecker::isRedo(const std::string &token) {
	std::string lower_token = genLowerString(token);
	return (
		(!lower_token.compare("redo")) ||
		(!lower_token.compare("r"))
	);
}

////==--------------------------------------------------------------------====//
// STRING CHECKER / IS JSON STRING
// [ Update ]
// Feb 02, 2016
//====--------------------------------------------------------------------==////
bool StringChecker::isJson(const std::string &token) {
	std::string lower_token = genLowerString(token);
	return (
		(!lower_token.compare("json")) ||
		(!lower_token.compare("out"))
	);
}

////==--------------------------------------------------------------------====//
// STRING CHECKER / IS MACRO STRING
// [ Update ]
// Feb 02, 2016
//====--------------------------------------------------------------------==////
bool StringChecker::isMacro(const std::string &token) {
	std::string lower_token = genLowerString(token);
	return (!lower_token.compare("run"));
}

////==--------------------------------------------------------------------====//
// STRING CHECKER / IS EXIT STRING
// [ Update ]
// Feb 16, 2016
//====--------------------------------------------------------------------==////
bool StringChecker::isExit(const std::string &token) {
	std::string lower_token = genLowerString(token);
	return (
		(!lower_token.compare("exit")) ||
		(!lower_token.compare("quit")) ||
		(!lower_token.compare("q"))
	);
}

////==--------------------------------------------------------------------====//
// STRING CHECKER / IS VERSION STRING
// [ Update ]
// Feb 16, 2016
//====--------------------------------------------------------------------==////
bool StringChecker::isVersion(const std::string &token) {
	std::string lower_token = genLowerString(token);
	return (
		(!lower_token.compare("version")) ||
		(!lower_token.compare("ver"))
	);
}

////==--------------------------------------------------------------------====//
// STRING CHECKER / IS VIEW STRING
// [ Update ]
// Feb 16, 2016
//====--------------------------------------------------------------------==////
bool StringChecker::isView(const std::string &token) {
	std::string lower_token = genLowerString(token);
	return (
		(!lower_token.compare("view")) ||
		(!lower_token.compare("v"))
	);
}

////==--------------------------------------------------------------------====//
// STRING CHECKER / IS CONFIG STRING
// [ Update ]
// Feb 16, 2016
//====--------------------------------------------------------------------==////
bool StringChecker::isConfig(const std::string &token) {
	std::string lower_token = genLowerString(token);
	return (
		(!lower_token.compare("config")) ||
		(!lower_token.compare("cfg"))
	);
}

////==--------------------------------------------------------------------====//
// STRING CHECKER / IS HOMURA STRING
// [ Update ]
// Feb 16, 2016
//====--------------------------------------------------------------------==////
bool StringChecker::isHomura(const std::string &token) {
	std::string lower_token = genLowerString(token);
	return (
		(!lower_token.compare("homura")) ||
		(!lower_token.compare("calc"))
	);
}
