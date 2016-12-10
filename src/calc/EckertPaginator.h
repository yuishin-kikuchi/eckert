#ifndef _ECKERT_PAGINATOR_H_
#define _ECKERT_PAGINATOR_H_

#include <map>

////==--------------------------------------------------------------------====//
// PAGINATOR
// [ Update ]
// Feb 03, 2016
//====--------------------------------------------------------------------==////

class EckertPaginator {
	public:
		//==  Static constants  ==//
		static const std::size_t LEAST_DISPLAY_LINE;
		static const int LEAST_DISPLAY_WIDTH;
	private:
		//==  Display config  ==//
		bool _registerDisplayFlag;
		std::size_t _displayLine;
		int _displayWidth;
		std::size_t _stackOffset;
		std::size_t _registerOffset;
	public:
		//==  Constructor and initializer  ==//
		EckertPaginator();
		void init();
		//==  Setter  ==//
		void setDisplayLine(const std::size_t &line) {
			_displayLine = (line < LEAST_DISPLAY_LINE) ? LEAST_DISPLAY_LINE : line;
		}
		void setDisplayWidth(const int &width) {
			_displayWidth = (width < LEAST_DISPLAY_WIDTH) ? LEAST_DISPLAY_WIDTH : width;
		}
		void setRegisterDisplayFlag(const bool &flag) {
			_registerDisplayFlag = flag;
		}
		//==  Resetter  ==//
		void resetStackOffset() {
			_stackOffset = 0;
		}
		void resetRegisterOffset() {
			_registerOffset = 0;
		}
		//==  Getter  ==//
		std::size_t getDisplayLine() const {
			return _displayLine;
		}
		int getDisplayWidth() const {
			return _displayWidth;
		}
		bool getRegisterDisplayFlag() const {
			return _registerDisplayFlag;
		}
		std::size_t getRegisterOffset() const {
			return _registerOffset;
		}
		std::size_t getStackOffset() const {
			return _stackOffset;
		}
		//==  Size calculator  ==//
		std::size_t calcStackLine(const std::size_t &registerSize) const;
		std::size_t calcRegisterLine(const std::size_t &registerSize) const;
		//==  Page function  ==//
		bool stackNext(const std::size_t &stackItems, const std::size_t &registerSize);
		bool stackPrev(const std::size_t &stackItems, const std::size_t &registerSize);
		bool stackFirst(const std::size_t &stackItems, const std::size_t &registerSize);
		bool registerNext(const std::size_t &registerSize);
		bool registerPrev(const std::size_t &registerSize);
		bool registerFirst(const std::size_t &registerSize);
};

#endif // _ECKERT_PAGINATOR_H_
