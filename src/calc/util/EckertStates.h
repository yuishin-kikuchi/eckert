#ifndef _ECKERT_STATES_H_
#define _ECKERT_STATES_H_

#include <string>
#include <chrono>

////==--------------------------------------------------------------------====//
// ECKERT STATES
// [ Update ]
// Nov 30, 2016
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
			DISPLAY_LINE,
			DISPLAY_WIDTH,
			HISTORY_SIZE,
		};
	private:
		WaitingState _waiting;
		std::chrono::high_resolution_clock::time_point _startPoint;
		std::chrono::high_resolution_clock::time_point _endPoint;
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
};

#endif // _ECKERT_STATES_H_
