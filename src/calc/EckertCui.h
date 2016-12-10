#ifndef _ECKERT_CUI_H_
#define _ECKERT_CUI_H_

#include <vector>
#include <map>
#include "engine/proc/base/core/HistoryManager.h"
#include "engine/EngineeringCalculator.h"
#include "engine/StringEngine.h"
#include "engine/CalculationConfig.h"
#include "util/EckertStates.h"
#include "EckertPaginator.h"
#include "EckertParser.h"

////==--------------------------------------------------------------------====//
// ECKERT CUI
// [ Update ]
// Nov 21, 2016
//====--------------------------------------------------------------------==////

class EckertCui {
	public:
		static const char *const NAME;
		static const char *const AUTHOR;
		static const char *const VERSION;
		//==  inner class  ==//
		class DisplayHint;
		enum class ReturnCode : int {
			SUCCESS = 0,
			FAILURE,
			NOT_FOUND,
		};
		enum class MessageType : int {
			UNKNOWN,
			NO_ERROR,
			ERROR,
			NOTICE,
			CONFIRM,
		};
		enum class OperationMode : int {
			CALCULATOR,
			VIEW,
			CONFIG,
			VERSION_FROM_CALCULATOR,
			VERSION_FROM_CONFIG,
		};
	private:
		//==  END FLAGS  ==//
		enum : unsigned int {
			END_FLAG    = 1,
			FATAL_FLAG  = 2,
			END_STATE   = 1,
			FATAL_STATE = 3,
		};
		//==  static map  ==//
		struct OperatorsDRG {
			engine::StackOperatorPtr degree;
			engine::StackOperatorPtr radian;
			engine::StackOperatorPtr grade;
		};
		std::map<std::string, OperatorsDRG> _drgOperators;
		void initOperatorsDRG();
		//==  CALCULATOR  ==//
		engine::EngineeringCalculator _engCalc;
		engine::CalculationConfig _cfg;
		engine::StringEngine _strEngine;
		engine::HistoryManager _hist;
		EckertStates _stat;
		EckertPaginator _paginator;
		EckertParser _parser;
		OperationMode _opmode;
		//==  Display and operate  ==//
		void putline(const int &len, const char &c);
		void showContinuing(const char &c, const DisplayHint &dh);
		void showHeader(const DisplayHint &dh);
		void showColumn(const DisplayHint &dh);
		void showRegister(const DisplayHint &dh);
		void showStack(const DisplayHint &dh);
		void showCalculatorAdditionalInformation();
		void showConfigAdditionalInformation();
		MessageType checkErrorMessage(const std::string &token);
		void operateConfig(const std::string &str);
		void operateConfig(const std::vector<std::string> &tokens);
		void operateCalculator(const std::string &str);
		void operateCalculator(const std::vector<std::string> &tokens);
		ReturnCode operateCalculatorOneKeyword(const std::string &token);
		ReturnCode operateGeneralCalculation(const std::string &token);
		ReturnCode operateRegister(const std::string &token);
		ReturnCode changeCalculatorMode(const std::string &token);
		ReturnCode changeCalculatorPages(const std::string &token);
		ReturnCode runMacro(const std::string &token);
		static std::string genJsonFileName();
		unsigned int _stateFlags;
		void setStateFlags(const unsigned int &flags) {
			_stateFlags = flags;
		}
		std::string _jsonFileName;
		void setJsonFilename(const std::string &name) {
			_jsonFileName = name;
		}
		void setOperationMode(const OperationMode &mode) {
			_opmode = mode;
		}
		OperationMode getOperationMode() const {
			return _opmode;
		}
		EckertParser& refEckertParser() {
			return _parser;
		}
	public:
		//==  Constructor and initializer  ==//
		EckertCui();
		void init();
		void resetStates();
		void resetConfig();
		//==  Check whether end or fatal  ==//
		bool isEnd() const {
			return ((_stateFlags & END_FLAG) ? true : false);
		}
		bool isFatal() const {
			return ((_stateFlags & FATAL_FLAG) ? true : false);
		}
		//==  Display and operate  ==//
		void showConfig();
		void display();
		void displayVersion();
		void displayCalculator();
		void displayFullData();
		void displayConfig();
		void operate(const std::string &str);
		//==  CONFIG  ==//
		bool loadConfig();
		bool saveConfig();
		//==  JSON output  ==//
		void displayAsJson();
		bool outputJson();
		std::string getJsonFilename() const {
			return _jsonFileName;
		}
		class DisplayHint {
			public:
				DisplayHint();
				DisplayHint(
					const engine::StackEngine &stackEngine,
					const engine::StringEngine &stringEngine,
					const EckertPaginator &paginator);
				void init();
				void init(
					const engine::StackEngine &stackEngine,
					const engine::StringEngine &stringEngine,
					const EckertPaginator &paginator);
				bool registerFlag;
				bool eulerFlag;
				bool approxFlag;
				std::size_t displayLine;
				std::size_t stackLine;
				std::size_t registerLine;
				std::size_t stackOffset;
				std::size_t registerOffset;
				std::size_t stackItems;
				std::size_t registerSize;
				int displayWidth;
				int numWidth;
				int typeWidth;
				int valueWidth;
		};
};

#endif // _ECKERT_CUI_H_
