#ifndef _STRING_CHECKER_H_
#define _STRING_CHECKER_H_

#include "StringUtility.h"

////==--------------------------------------------------------------------====//
// STRING CHECKER
// [ Update ]
// Feb 16, 2016
//====--------------------------------------------------------------------==////

class StringChecker : public StringUtility {
	public:
		static bool isDoubleQuoted(const std::string &str);
		static std::size_t getRegisterPos(const std::string &str);
		static bool isRegisterStore(const std::string &str);
		static bool isRegisterLoad(const std::string &str);
		static bool isRegisterDel(const std::string &str);
		static bool isRegisterInc(const std::string &str);
		static bool isRegisterDec(const std::string &str);
		static bool isRegisterAdd(const std::string &str);
		static bool isRegisterSub(const std::string &str);
		static bool isRegisterMul(const std::string &str);
		static bool isRegisterDiv(const std::string &str);
		static bool isYes(const std::string &str);
		static bool isNo(const std::string &str);
		static bool isReset(const std::string &str);
		static bool isDisplayDigit(const std::string &str);
		static bool isUndo(const std::string &str);
		static bool isRedo(const std::string &str);
		static bool isJson(const std::string &str);
		static bool isMacro(const std::string &str);
		static bool isExit(const std::string &str);
		static bool isVersion(const std::string &str);
		static bool isView(const std::string &str);
		static bool isConfig(const std::string &str);
		static bool isHomura(const std::string &str);
};

#endif // _STRING_CHECKER_H_
