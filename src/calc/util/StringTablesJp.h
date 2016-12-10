#ifndef _STRING_TABLES_JP_H_
#define _STRING_TABLES_JP_H_

#include <string>
#include <map>

////==--------------------------------------------------------------------====//
// STRING TABLES (Japanese)
//====--------------------------------------------------------------------==////

class StringTablesJp {
	public:
		static const std::map <std::string, std::string> errorMessage;
		static const std::map <std::string, std::string> noticeMessage;
		static const std::map <std::string, std::string> confirmMessage;
		static const std::map <std::string, std::string> pushMessage;
		static const std::map <std::string, std::string> prefixMessage;
		static const std::map <std::string, std::string> instructionMessage;
};

#endif // _STRING_TABLES_JP_H_
