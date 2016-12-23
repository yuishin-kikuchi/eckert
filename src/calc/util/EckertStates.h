#ifndef _ECKERT_STATES_H_
#define _ECKERT_STATES_H_

#include <string>
#include <chrono>

////==--------------------------------------------------------------------====//
// ECKERT STATES
// [ Update ]
// Dec 22, 2016
//====--------------------------------------------------------------------==////

class EckertStates {
	public:
		enum WaitingState : int {
			NONE,
			RESET_CONFIRM,
			STD_DIGITS,
			FIX_DIGITS,
			SCI_DIGITS,
			ENG_DIGITS,
			FIRST_UNIT,
			SECOND_UNIT,
			DISPLAY_LINE,
			DISPLAY_WIDTH,
			HISTORY_SIZE,
		};
	private:
		WaitingState _waiting;
		std::chrono::high_resolution_clock::time_point _startPoint;
		std::chrono::high_resolution_clock::time_point _endPoint;
		unsigned int _prev_from_unit;
		unsigned int _prev_to_unit;
		unsigned int _from_unit;
		unsigned int _to_unit;
	public:
		EckertStates();
		void init();
		void resetWaitingState();
		void setWaitingState(const WaitingState &stat) {
			_waiting = stat;
		}
		const WaitingState& getWaitingState() const {
			return _waiting;
		}
		void startRec();
		void stopRec();
		double getDuration() const;
		void setPrevFromUnit(const unsigned int &unit) {
			_prev_from_unit = unit;
		}
		void setPrevToUnit(const unsigned int &unit) {
			_prev_to_unit = unit;
		}
		void setFromUnit(const unsigned int &unit) {
			_from_unit = unit;
		}
		void setToUnit(const unsigned int &unit) {
			_to_unit = unit;
		}
		void resetPrevUnits() {
			_prev_from_unit = 0;
			_prev_to_unit = 0;
		}
		void resetUnits() {
			_from_unit = 0;
			_to_unit = 0;
		}
		unsigned int getPrevFromUnit() const {
			return _prev_from_unit;
		}
		unsigned int getPrevToUnit() const {
			return _prev_to_unit;
		}
		unsigned int getFromUnit() const {
			return _from_unit;
		}
		unsigned int getToUnit() const {
			return _to_unit;
		}
};

#endif // _ECKERT_STATES_H_
