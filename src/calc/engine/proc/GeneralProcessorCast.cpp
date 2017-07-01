#include "GeneralProcessor.h"
#include "base/math/floatToRational.h"

namespace engine {

////==--------------------------------------------------------------------====//
// ECKERT PROCESSOR / CAST INTO INTEGER
// [ description ]
// Convert into Integer
// [ Update ]
// May 22, 2016
//====--------------------------------------------------------------------==////
SpElement GeneralProcessor::toInteger(const SpElement &p_ex) {
	//==  NULL POINTER CHECK  ==//
	if (nullptr == p_ex) {
		throw TechnicalError("NULLPTR", __FUNCTION__);
	}
	SpElement p_etemp;
	switch (p_ex->getType()) {
		case Element::INTEGER:
			//==  to_int(INTEGER)  ==//
			// fall through
		case Element::FLOATING:
			//==  to_int(FLOATING)  ==//
			// fall through
		case Element::RATIONAL: {
			//==  to_int(RATIONAL)  ==//
			return floor(p_ex);
		}
		case Element::BOOLEAN: {
			//==  to_int(BOOLEAN)  ==//
			bool bool_x = GET_BOOLEAN_DATA(p_ex);
			p_etemp = GEN_INTEGER(bool_x ? 1 : 0);
			break;
		}
		case Element::BINARY8: {
			//==  to_int(BINARY8)  ==//
			uint8_t byte_x = GET_BYTE_DATA(p_ex);
			p_etemp = GEN_INTEGER((integer_t)byte_x);
			break;
		}
		case Element::BINARY16: {
			//==  to_int(BINARY16)  ==//
			uint16_t word_x = GET_WORD_DATA(p_ex);
			p_etemp = GEN_INTEGER((integer_t)word_x);
			break;
		}
		case Element::BINARY32: {
			//==  to_int(BINARY32)  ==//
			uint32_t dword_x = GET_DWORD_DATA(p_ex);
			p_etemp = GEN_INTEGER((integer_t)dword_x);
			break;
		}
		case Element::BINARY64: {
			//==  to_int(BINARY64)  ==//
			uint64_t qword_x = GET_QWORD_DATA(p_ex);
			p_etemp = GEN_INTEGER((integer_t)qword_x);
			break;
		}
		default:
			//==  to_int(Unexpected)  ==//
			throw BadArgument("BAD_TYPE", __FUNCTION__);
	}
	return p_etemp;
}

////==--------------------------------------------------------------------====//
// ECKERT PROCESSOR / CAST INTO FLOATING
// [ description ]
// Convert into Floating
// [ Update ]
// May 22, 2016
//====--------------------------------------------------------------------==////
SpElement GeneralProcessor::toFloating(const SpElement &p_ex) {
	//==  NULL POINTER CHECK  ==//
	if (nullptr == p_ex) {
		throw TechnicalError("NULLPTR", __FUNCTION__);
	}
	SpElement p_etemp;
	switch (p_ex->getType()) {
		case Element::INTEGER: {
			//==  to_flt(INTEGER)  ==//
			p_etemp = GEN_FLOATING((floating_t)GET_INTEGER_DATA(p_ex));
			break;
		}
		case Element::FLOATING: {
			//==  to_flt(FLOATING)  ==//
			return p_ex;
		}
		case Element::RATIONAL: {
			//==  to_flt(RATIONAL)  ==//
			auto rat_x = GET_RATIONAL_DATA(p_ex);
			p_etemp = GEN_FLOATING(rat_x.getFloating());
			break;
		}
		case Element::BOOLEAN: {
			//==  to_flt(BOOLEAN)  ==//
			bool bool_x = GET_BOOLEAN_DATA(p_ex);
			p_etemp = GEN_FLOATING(bool_x ? 1.0 : 0.0);
			break;
		}
		case Element::BINARY8: {
			//==  to_flt(BINARY8)  ==//
			uint8_t byte_x = GET_BYTE_DATA(p_ex);
			p_etemp = GEN_FLOATING((floating_t)byte_x);
			break;
		}
		case Element::BINARY16: {
			//==  to_flt(BINARY16)  ==//
			uint16_t word_x = GET_WORD_DATA(p_ex);
			p_etemp = GEN_FLOATING((floating_t)word_x);
			break;
		}
		case Element::BINARY32: {
			//==  to_flt(BINARY32)  ==//
			uint32_t dword_x = GET_DWORD_DATA(p_ex);
			p_etemp = GEN_FLOATING((floating_t)dword_x);
			break;
		}
		case Element::BINARY64: {
			//==  to_flt(BINARY64)  ==//
			uint64_t qword_x = GET_QWORD_DATA(p_ex);
			p_etemp = GEN_FLOATING((floating_t)qword_x);
			break;
		}
		default:
			//==  to_flt(Unexpected)  ==//
			throw BadArgument("BAD_TYPE", __FUNCTION__);
	}
	return p_etemp;
}

////==--------------------------------------------------------------------====//
// ECKERT PROCESSOR / CAST INTO RATIONAL
// [ description ]
// Convert into Rational
// [ Update ]
// May 22, 2016
//====--------------------------------------------------------------------==////
SpElement GeneralProcessor::toRational(const SpElement &p_ex) {
	//==  NULL POINTER CHECK  ==//
	if (nullptr == p_ex) {
		throw TechnicalError("NULLPTR", __FUNCTION__);
	}
	SpElement p_etemp;
	switch (p_ex->getType()) {
		case Element::INTEGER: {
			//==  to_rat(INTEGER)  ==//
			return p_ex;
		}
		case Element::FLOATING: {
			//==  to_rat(FLOATING)  ==//
			auto flt_x = GET_FLOATING_DATA(p_ex);
			auto rat = approxRational<integer_t, floating_t>(flt_x);
			if (rat.isError()) {
				throw BadArgument("TOO_LRGE", __FUNCTION__);
			}
			else {
				setRational(p_etemp, rat);
			}
			break;
		}
		case Element::RATIONAL: {
			//==  to_rat(RATIONAL)  ==//
			return p_ex;
		}
		case Element::BOOLEAN:
			//==  to_rat(BOOLEAN)  ==//
			// fall through
		case Element::BINARY8:
			//==  to_rat(BINARY8)  ==//
			// fall through
		case Element::BINARY16:
			//==  to_rat(BINARY16)  ==//
			// fall through
		case Element::BINARY32:
			//==  to_rat(BINARY32)  ==//
			// fall through
		case Element::BINARY64: {
			//==  to_rat(BINARY64)  ==//
			return toInteger(p_ex);
		}
		default:
			//==  to_rat(Unexpected)  ==//
			throw BadArgument("BAD_TYPE", __FUNCTION__);
	}
	return p_etemp;
}

////==--------------------------------------------------------------------====//
// ECKERT PROCESSOR / CAST INTO BOOLEAN
// [ description ]
// Convert into Boolean
// [ Update ]
// May 22, 2016
//====--------------------------------------------------------------------==////
SpElement GeneralProcessor::toBoolean(const SpElement &p_ex) {
	//==  NULL POINTER CHECK  ==//
	if (nullptr == p_ex) {
		throw TechnicalError("NULLPTR", __FUNCTION__);
	}
	SpElement p_etemp;
	switch (p_ex->getType()) {
		case Element::INTEGER: {
			//==  to_bool(INTEGER)  ==//
			auto int_x = GET_INTEGER_DATA(p_ex);
			p_etemp = GEN_BOOLEAN((0 != int_x) ? true : false);
			break;
		}
		case Element::FLOATING: {
			//==  to_bool(FLOATING)  ==//
			auto flt_x = GET_FLOATING_DATA(p_ex);
			p_etemp = GEN_BOOLEAN((0.0 != flt_x) ? true : false);
			break;
		}
		case Element::RATIONAL: {
			//==  to_bool(RATIONAL)  ==//
			auto rat_x = GET_RATIONAL_DATA(p_ex);
			p_etemp = GEN_BOOLEAN((0 != rat_x.getNum()) ? true : false);
			break;
		}
		case Element::BOOLEAN: {
			//==  to_bool(BOOLEAN)  ==//
			return p_ex;
		}
		case Element::BINARY8: {
			//==  to_bool(BINARY8)  ==//
			uint8_t byte_x = GET_BYTE_DATA(p_ex);
			p_etemp = GEN_BOOLEAN((0 != byte_x) ? true : false);
			break;
		}
		case Element::BINARY16: {
			//==  to_bool(BINARY16)  ==//
			uint16_t word_x = GET_WORD_DATA(p_ex);
			p_etemp = GEN_BOOLEAN((0 != word_x) ? true : false);
			break;
		}
		case Element::BINARY32: {
			//==  to_bool(BINARY32)  ==//
			uint32_t dword_x = GET_DWORD_DATA(p_ex);
			p_etemp = GEN_BOOLEAN((0 != dword_x) ? true : false);
			break;
		}
		case Element::BINARY64: {
			//==  to_bool(BINARY64)  ==//
			uint64_t qword_x = GET_QWORD_DATA(p_ex);
			p_etemp = GEN_BOOLEAN((0 != qword_x) ? true : false);
			break;
		}
		default:
			//==  to_bool(Unexpected)  ==//
			throw BadArgument("BAD_TYPE", __FUNCTION__);
	}
	return p_etemp;
}

////==--------------------------------------------------------------------====//
// ECKERT PROCESSOR / CAST INTO BYTE
// [ description ]
// Convert into Byte
// [ Update ]
// May 22, 2016
//====--------------------------------------------------------------------==////
SpElement GeneralProcessor::toByte(const SpElement &p_ex) {
	//==  NULL POINTER CHECK  ==//
	if (nullptr == p_ex) {
		throw TechnicalError("NULLPTR", __FUNCTION__);
	}
	SpElement p_etemp;
	switch (p_ex->getType()) {
		case Element::INTEGER: {
			//==  to_byte(INTEGER)  ==//
			auto int_x = GET_INTEGER_DATA(p_ex);
			p_etemp = GEN_BYTE((int8_t)int_x);
			break;
		}
		case Element::BOOLEAN: {
			//==  to_byte(BOOLEAN)  ==//
			auto bool_x = GET_BOOLEAN_DATA(p_ex);
			p_etemp = GEN_BYTE(bool_x ? 1 : 0);
			break;
		}
		case Element::BINARY8: {
			//==  to_byte(BINARY8)  ==//
			return p_etemp;
		}
		case Element::BINARY16: {
			//==  to_byte(BINARY16)  ==//
			uint16_t word_x = GET_WORD_DATA(p_ex);
			p_etemp = GEN_BYTE((uint8_t)word_x);
			break;
		}
		case Element::BINARY32: {
			//==  to_byte(BINARY32)  ==//
			uint32_t dword_x = GET_DWORD_DATA(p_ex);
			p_etemp = GEN_BYTE((uint8_t)dword_x);
			break;
		}
		case Element::BINARY64: {
			//==  to_byte(BINARY64)  ==//
			uint64_t qword_x = GET_QWORD_DATA(p_ex);
			p_etemp = GEN_BYTE((uint8_t)qword_x);
			break;
		}
		default:
			//==  to_byte(Unexpected)  ==//
			throw BadArgument("BAD_TYPE", __FUNCTION__);
	}
	return p_etemp;
}

////==--------------------------------------------------------------------====//
// ECKERT PROCESSOR / CAST INTO WORD
// [ description ]
// Convert into Word
// [ Update ]
// May 22, 2016
//====--------------------------------------------------------------------==////
SpElement GeneralProcessor::toWord(const SpElement &p_ex) {
	//==  NULL POINTER CHECK  ==//
	if (nullptr == p_ex) {
		throw TechnicalError("NULLPTR", __FUNCTION__);
	}
	SpElement p_etemp;
	switch (p_ex->getType()) {
		case Element::INTEGER: {
			//==  to_word(INTEGER)  ==//
			auto int_x = GET_INTEGER_DATA(p_ex);
			p_etemp = GEN_WORD((int16_t)int_x);
			break;
		}
		case Element::BOOLEAN: {
			//==  to_word(BOOLEAN)  ==//
			auto bool_x = GET_BOOLEAN_DATA(p_ex);
			p_etemp = GEN_WORD(bool_x ? 1 : 0);
			break;
		}
		case Element::BINARY8: {
			//==  to_word(BINARY8)  ==//
			uint8_t byte_x = GET_BYTE_DATA(p_ex);
			p_etemp = GEN_WORD((uint16_t)byte_x);
			break;
		}
		case Element::BINARY16: {
			//==  to_word(BINARY16)  ==//
			return p_etemp;
		}
		case Element::BINARY32: {
			//==  to_word(BINARY32)  ==//
			uint32_t dword_x = GET_DWORD_DATA(p_ex);
			p_etemp = GEN_WORD((uint16_t)dword_x);
			break;
		}
		case Element::BINARY64: {
			//==  to_word(BINARY64)  ==//
			uint64_t qword_x = GET_QWORD_DATA(p_ex);
			p_etemp = GEN_WORD((uint16_t)qword_x);
			break;
		}
		default:
			//==  to_word(Unexpected)  ==//
			throw BadArgument("BAD_TYPE", __FUNCTION__);
	}
	return p_etemp;
}

////==--------------------------------------------------------------------====//
// ECKERT PROCESSOR / CAST INTO DWORD
// [ description ]
// Convert into Dword
// [ Update ]
// May 22, 2016
//====--------------------------------------------------------------------==////
SpElement GeneralProcessor::toDword(const SpElement &p_ex) {
	//==  NULL POINTER CHECK  ==//
	if (nullptr == p_ex) {
		throw TechnicalError("NULLPTR", __FUNCTION__);
	}
	SpElement p_etemp;
	switch (p_ex->getType()) {
		case Element::INTEGER: {
			//==  to_dword(INTEGER)  ==//
			auto int_x = GET_INTEGER_DATA(p_ex);
			p_etemp = GEN_DWORD((uint32_t)int_x);
			break;
		}
		case Element::BOOLEAN: {
			//==  to_dword(BOOLEAN)  ==//
			auto bool_x = GET_BOOLEAN_DATA(p_ex);
			p_etemp = GEN_DWORD(bool_x ? 1 : 0);
			break;
		}
		case Element::BINARY8: {
			//==  to_dword(BINARY8)  ==//
			uint8_t byte_x = GET_BYTE_DATA(p_ex);
			p_etemp = GEN_DWORD((uint32_t)byte_x);
			break;
		}
		case Element::BINARY16: {
			//==  to_dword(BINARY16)  ==//
			uint16_t word_x = GET_WORD_DATA(p_ex);
			p_etemp = GEN_DWORD((uint32_t)word_x);
			break;
		}
		case Element::BINARY32: {
			//==  to_dword(BINARY32)  ==//
			return p_etemp;
		}
		case Element::BINARY64: {
			//==  to_dword(BINARY64)  ==//
			uint64_t qword_x = GET_QWORD_DATA(p_ex);
			p_etemp = GEN_DWORD((uint32_t)qword_x);
			break;
		}
		default:
			//==  to_dword(Unexpected)  ==//
			throw BadArgument("BAD_TYPE", __FUNCTION__);
	}
	return p_etemp;
}

////==--------------------------------------------------------------------====//
// ECKERT PROCESSOR / CAST INTO QWORD
// [ description ]
// Convert into Qword
// [ Update ]
// May 22, 2016
//====--------------------------------------------------------------------==////
SpElement GeneralProcessor::toQword(const SpElement &p_ex) {
	//==  NULL POINTER CHECK  ==//
	if (nullptr == p_ex) {
		throw TechnicalError("NULLPTR", __FUNCTION__);
	}
	SpElement p_etemp;
	switch (p_ex->getType()) {
		case Element::INTEGER: {
			//==  to_qword(INTEGER)  ==//
			auto int_x = GET_INTEGER_DATA(p_ex);
			p_etemp = GEN_QWORD((int32_t)int_x);
			break;
		}
		case Element::BOOLEAN: {
			//==  to_qword(BOOLEAN)  ==//
			auto bool_x = GET_BOOLEAN_DATA(p_ex);
			p_etemp = GEN_QWORD(bool_x ? 1 : 0);
			break;
		}
		case Element::BINARY8: {
			//==  to_qword(BINARY8)  ==//
			uint8_t byte_x = GET_BYTE_DATA(p_ex);
			p_etemp = GEN_QWORD((uint64_t)byte_x);
			break;
		}
		case Element::BINARY16: {
			//==  to_qword(BINARY16)  ==//
			uint16_t word_x = GET_WORD_DATA(p_ex);
			p_etemp = GEN_QWORD((uint64_t)word_x);
			break;
		}
		case Element::BINARY32: {
			//==  to_qword(BINARY32)  ==//
			uint32_t dword_x = GET_DWORD_DATA(p_ex);
			p_etemp = GEN_QWORD((uint64_t)dword_x);
			break;
		}
		case Element::BINARY64: {
			//==  to_qword(BINARY64)  ==//
			return p_etemp;
		}
		default:
			//==  to_qword(Unexpected)  ==//
			throw BadArgument("BAD_TYPE", __FUNCTION__);
	}
	return p_etemp;
}

////==--------------------------------------------------------------------====//
// ECKERT PROCESSOR / CAST INTO WORD
// [ description ]
// Convert into Word (Sign extend)
// [ Update ]
// Jul 01, 2017
//====--------------------------------------------------------------------==////
SpElement GeneralProcessor::toSWord(const SpElement &p_ex) {
	//==  NULL POINTER CHECK  ==//
	if (nullptr == p_ex) {
		throw TechnicalError("NULLPTR", __FUNCTION__);
	}
	SpElement p_etemp;
	switch (p_ex->getType()) {
		case Element::INTEGER: {
			//==  to_signed_word(INTEGER)  ==//
			auto int_x = GET_INTEGER_DATA(p_ex);
			p_etemp = GEN_WORD((int16_t)int_x);
			break;
		}
		case Element::BOOLEAN: {
			//==  to_signed_word(BOOLEAN)  ==//
			auto bool_x = GET_BOOLEAN_DATA(p_ex);
			p_etemp = GEN_WORD(bool_x ? 1 : 0);
			break;
		}
		case Element::BINARY8: {
			//==  to_signed_word(BINARY8)  ==//
			uint8_t byte_x = GET_BYTE_DATA(p_ex);
			uint16_t dat = byte_x;
			if (dat & 0x80) {
				dat = 0xFF00 | dat;
			}
			p_etemp = GEN_WORD(dat);
			break;
		}
		case Element::BINARY16: {
			//==  to_signed_word(BINARY16)  ==//
			return p_etemp;
		}
		case Element::BINARY32: {
			//==  to_signed_word(BINARY32)  ==//
			uint32_t dword_x = GET_DWORD_DATA(p_ex);
			p_etemp = GEN_WORD((int16_t)dword_x);
			break;
		}
		case Element::BINARY64: {
			//==  to_signed_word(BINARY64)  ==//
			uint64_t qword_x = GET_QWORD_DATA(p_ex);
			p_etemp = GEN_WORD((uint16_t)qword_x);
			break;
		}
		default:
			//==  to_signed_word(Unexpected)  ==//
			throw BadArgument("BAD_TYPE", __FUNCTION__);
	}
	return p_etemp;
}

////==--------------------------------------------------------------------====//
// ECKERT PROCESSOR / CAST INTO DWORD
// [ description ]
// Convert into Dword (Sign extend)
// [ Update ]
// Jul 01, 2017
//====--------------------------------------------------------------------==////
SpElement GeneralProcessor::toSDword(const SpElement &p_ex) {
	//==  NULL POINTER CHECK  ==//
	if (nullptr == p_ex) {
		throw TechnicalError("NULLPTR", __FUNCTION__);
	}
	SpElement p_etemp;
	switch (p_ex->getType()) {
		case Element::INTEGER: {
			//==  to_signed_dword(INTEGER)  ==//
			auto int_x = GET_INTEGER_DATA(p_ex);
			p_etemp = GEN_DWORD((uint32_t)int_x);
			break;
		}
		case Element::BOOLEAN: {
			//==  to_signed_dword(BOOLEAN)  ==//
			auto bool_x = GET_BOOLEAN_DATA(p_ex);
			p_etemp = GEN_DWORD(bool_x ? 1 : 0);
			break;
		}
		case Element::BINARY8: {
			//==  to_signed_dword(BINARY8)  ==//
			uint8_t byte_x = GET_BYTE_DATA(p_ex);
			uint32_t dat = byte_x;
			if (dat & 0x80) {
				dat = 0xFFFFFF00 | dat;
			}
			p_etemp = GEN_DWORD(dat);
			break;
		}
		case Element::BINARY16: {
			//==  to_signed_dword(BINARY16)  ==//
			uint16_t word_x = GET_WORD_DATA(p_ex);
			uint32_t dat = word_x;
			if (dat & 0x8000) {
				dat = 0xFFFF0000 | dat;
			}
			p_etemp = GEN_DWORD(dat);
			break;
		}
		case Element::BINARY32: {
			//==  to_signed_dword(BINARY32)  ==//
			return p_etemp;
		}
		case Element::BINARY64: {
			//==  to_signed_dword(BINARY64)  ==//
			uint64_t qword_x = GET_QWORD_DATA(p_ex);
			p_etemp = GEN_DWORD((uint32_t)qword_x);
			break;
		}
		default:
			//==  to_signed_dword(Unexpected)  ==//
			throw BadArgument("BAD_TYPE", __FUNCTION__);
	}
	return p_etemp;
}

////==--------------------------------------------------------------------====//
// ECKERT PROCESSOR / CAST INTO QWORD
// [ description ]
// Convert into Qword (Sign extend)
// [ Update ]
// Jul 01, 2017
//====--------------------------------------------------------------------==////
SpElement GeneralProcessor::toSQword(const SpElement &p_ex) {
	//==  NULL POINTER CHECK  ==//
	if (nullptr == p_ex) {
		throw TechnicalError("NULLPTR", __FUNCTION__);
	}
	SpElement p_etemp;
	switch (p_ex->getType()) {
		case Element::INTEGER: {
			//==  to_signed_qword(INTEGER)  ==//
			auto int_x = GET_INTEGER_DATA(p_ex);
			p_etemp = GEN_QWORD((int32_t)int_x);
			break;
		}
		case Element::BOOLEAN: {
			//==  to_signed_qword(BOOLEAN)  ==//
			auto bool_x = GET_BOOLEAN_DATA(p_ex);
			p_etemp = GEN_QWORD(bool_x ? 1 : 0);
			break;
		}
		case Element::BINARY8: {
			//==  to_signed_qword(BINARY8)  ==//
			uint8_t byte_x = GET_BYTE_DATA(p_ex);
			uint64_t dat = byte_x;
			if (dat & 0x80) {
				dat = 0xFFFFFFFFFFFFFF00 | dat;
			}
			p_etemp = GEN_QWORD(dat);
			break;
		}
		case Element::BINARY16: {
			//==  to_signed_qword(BINARY16)  ==//
			uint16_t word_x = GET_WORD_DATA(p_ex);
			uint64_t dat = word_x;
			if (dat & 0x8000) {
				dat = 0xFFFFFFFFFFFF0000 | dat;
			}
			p_etemp = GEN_QWORD(dat);
			break;
		}
		case Element::BINARY32: {
			//==  to_signed_qword(BINARY32)  ==//
			uint32_t dword_x = GET_DWORD_DATA(p_ex);
			uint64_t dat = dword_x;
			if (dat & 0x80000000) {
				dat = 0xFFFFFFFF00000000 | dat;
			}
			p_etemp = GEN_QWORD(dat);
			break;
		}
		case Element::BINARY64: {
			//==  to_signed_qword(BINARY64)  ==//
			return p_etemp;
		}
		default:
			//==  to_signed_qword(Unexpected)  ==//
			throw BadArgument("BAD_TYPE", __FUNCTION__);
	}
	return p_etemp;
}

} // namespace engine
