#ifndef _FLOATING_DISPLAY_CONFIG_H_
#define _FLOATING_DISPLAY_CONFIG_H_

////==--------------------------------------------------------------------====//
// FLOATING DISPLAY CONFIG
// [ Update ]
// Nov 21, 2016
//====--------------------------------------------------------------------==////

namespace engine {

class FloatingDisplayConfig {
	public:
		static const int DEFAULT_STD_DIGITS;
		static const int DEFAULT_FIX_DIGITS;
		static const int DEFAULT_SCI_DIGITS;
		static const int DEFAULT_ENG_DIGITS;
		enum DisplayMode : int {
			STANDARD,
			FIXED,
			SCIENTIFIC,
			ENGINEERING,
		};
	private:
		int _stdDigits;
		int _fixDigits;
		int _sciDigits;
		int _engDigits;
		DisplayMode _mode;
	public:
		//==  default constructor  ==//
		FloatingDisplayConfig();
		void init();
		//==  mode  ==//
		void setDisplayMode(const DisplayMode &mode) {
			_mode = mode;
		}
		DisplayMode getDisplayMode() const {
			return _mode;
		}
		//==  digit setter  ==//
		void setStdDigits(const int &digits) {
			_stdDigits = digits;
		}
		void setFixDigits(const int &digits) {
			_fixDigits = digits;
		}
		void setSciDigits(const int &digits) {
			_sciDigits = digits;
		}
		void setEngDigits(const int &digits) {
			_engDigits = digits;
		}
		//==  digit getter  ==//
		int getStdDigits() const {
			return _stdDigits;
		}
		int getFixDigits() const {
			return _fixDigits;
		}
		int getSciDigits() const {
			return _sciDigits;
		}
		int getEngDigits() const {
			return _engDigits;
		}
		// min
		int getStdMin() const;
		int getFixMin() const;
		int getSciMin() const;
		int getEngMin() const;
		// max
		int getStdMax() const;
		int getFixMax() const;
		int getSciMax() const;
		int getEngMax() const;
};

} // namespace engine

#endif // _FLOATING_DISPLAY_CONFIG_H_
