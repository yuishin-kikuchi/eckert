#include "GeneralProcessor.h"

namespace engine {

////==--------------------------------------------------------------------====//
// ECKERT PROCESSOR / AND
// [ description ]
// Calculate AND
// [ Update ]
// Feb 11, 2016
//====--------------------------------------------------------------------==////
SpElement GeneralProcessor::bitwiseAnd(const SpElement &p_ey, const SpElement &p_ex) {
	//==  NULL POINTER CHECK  ==//
	if ((nullptr == p_ey) || (nullptr == p_ex)) {
		throw TechnicalError("NULLPTR", __FUNCTION__);
	}
	SpElement p_etemp;
	auto y_type = p_ey->getType();
	auto x_type = p_ex->getType();
	switch (y_type) {
		case Element::BOOLEAN:
			//===  BOOLEAN & ???  ===//
			switch (x_type) {
				case Element::BOOLEAN: {
					//==  BOOLEAN & BOOLEAN  ==//
					bool bool_y = GET_BOOLEAN_DATA(p_ey);
					bool bool_x = GET_BOOLEAN_DATA(p_ex);
					p_etemp = GEN_BOOLEAN(bool_y & bool_x);
					break;
				}
				default:
					throw BadArgument("BAD_TYPE", __FUNCTION__);
			}
			break;
		case Element::BINARY8:
			//===  BINARY8 & ???  ===//
			switch (x_type) {
				case Element::BINARY8: {
					//==  BINARY8 & BINARY8  ==//
					uint8_t byte_y = GET_BYTE_DATA(p_ey);
					uint8_t byte_x = GET_BYTE_DATA(p_ex);
					p_etemp = GEN_BYTE(byte_y & byte_x);
					break;
				}
				case Element::BINARY16: {
					//==  BINARY8 & BINARY16  ==//
					uint8_t byte_y = GET_BYTE_DATA(p_ey);
					uint16_t word_x = GET_WORD_DATA(p_ex);
					p_etemp = GEN_BYTE(static_cast<uint8_t>(byte_y & word_x));
					break;
				}
				case Element::BINARY32: {
					//==  BINARY8 & BINARY32  ==//
					uint8_t byte_y = GET_BYTE_DATA(p_ey);
					uint32_t dword_x = GET_DWORD_DATA(p_ex);
					p_etemp = GEN_BYTE(static_cast<uint8_t>(byte_y & dword_x));
					break;
				}
				case Element::BINARY64: {
					//==  BINARY8 & BINARY64  ==//
					uint8_t byte_y = GET_BYTE_DATA(p_ey);
					uint64_t qword_x = GET_QWORD_DATA(p_ex);
					p_etemp = GEN_BYTE(static_cast<uint8_t>(byte_y & qword_x));
					break;
				}
				default:
					//==  BINARY8 & Unexpected  ==//
					throw BadArgument("BAD_TYPE", __FUNCTION__);
			}
			break;
		case Element::BINARY16:
			//===  BINARY16 & ???  ===//
			switch (x_type) {
				case Element::BINARY8: {
					//==  BINARY16 & BINARY8  ==//
					uint16_t word_y = GET_WORD_DATA(p_ey);
					uint8_t byte_x = GET_BYTE_DATA(p_ex);
					p_etemp = GEN_BYTE(static_cast<uint8_t>(word_y & byte_x));
					break;
				}
				case Element::BINARY16: {
					//==  BINARY16 & BINARY16  ==//
					uint16_t word_y = GET_WORD_DATA(p_ey);
					uint16_t word_x = GET_WORD_DATA(p_ex);
					p_etemp = GEN_WORD(word_y & word_x);
					break;
				}
				case Element::BINARY32: {
					//==  BINARY16 & BINARY32  ==//
					uint16_t word_y = GET_WORD_DATA(p_ey);
					uint32_t dword_x = GET_DWORD_DATA(p_ex);
					p_etemp = GEN_WORD(static_cast<uint16_t>(word_y & dword_x));
					break;
				}
				case Element::BINARY64: {
					//==  BINARY16 & BINARY64  ==//
					uint16_t word_y = GET_WORD_DATA(p_ey);
					uint64_t qword_x = GET_QWORD_DATA(p_ex);
					p_etemp = GEN_WORD(static_cast<uint16_t>(word_y & qword_x));
					break;
				}
				default:
					//==  BINARY16 & Unexpected  ==//
					throw BadArgument("BAD_TYPE", __FUNCTION__);
			}
			break;
		case Element::BINARY32:
			//===  BINARY32 & ???  ===//
			switch (x_type) {
				case Element::BINARY8: {
					//==  BINARY32 & BINARY8  ==//
					uint32_t dword_y = GET_DWORD_DATA(p_ey);
					uint8_t byte_x = GET_BYTE_DATA(p_ex);
					p_etemp = GEN_BYTE(static_cast<uint8_t>(dword_y & byte_x));
					break;
				}
				case Element::BINARY16: {
					//==  BINARY32 & BINARY16  ==//
					uint32_t dword_y = GET_DWORD_DATA(p_ey);
					uint16_t word_x = GET_WORD_DATA(p_ex);
					p_etemp = GEN_WORD(static_cast<uint16_t>(dword_y & word_x));
					break;
				}
				case Element::BINARY32: {
					//==  BINARY32 & BINARY32  ==//
					uint32_t dword_y = GET_DWORD_DATA(p_ey);
					uint32_t dword_x = GET_DWORD_DATA(p_ex);
					p_etemp = GEN_DWORD(dword_y & dword_x);
					break;
				}
				case Element::BINARY64: {
					//==  BINARY32 & BINARY64 ==//
					uint32_t dword_y = GET_DWORD_DATA(p_ey);
					uint64_t qword_x = GET_QWORD_DATA(p_ex);
					p_etemp = GEN_DWORD(static_cast<uint32_t>(dword_y & qword_x));
					break;
				}
				default:
					//==  BINARY32 & Unexpected  ==//
					throw BadArgument("BAD_TYPE", __FUNCTION__);
			}
			break;
		case Element::BINARY64:
			//===  BINARY64 & ???  ===//
			switch (x_type) {
				case Element::BINARY8: {
					//==  BINARY64 & BINARY8  ==//
					uint64_t qword_y = GET_QWORD_DATA(p_ey);
					uint8_t byte_x = GET_BYTE_DATA(p_ex);
					p_etemp = GEN_BYTE(static_cast<uint8_t>(qword_y & byte_x));
					break;
				}
				case Element::BINARY16: {
					//==  BINARY64 & BINARY16  ==//
					uint64_t qword_y = GET_QWORD_DATA(p_ey);
					uint16_t word_x = GET_WORD_DATA(p_ex);
					p_etemp = GEN_WORD(static_cast<uint16_t>(qword_y & word_x));
					break;
				}
				case Element::BINARY32: {
					//==  BINARY64 & BINARY32  ==//
					uint64_t qword_y = GET_QWORD_DATA(p_ey);
					uint32_t dword_x = GET_DWORD_DATA(p_ex);
					p_etemp = GEN_DWORD(static_cast<uint32_t>(qword_y & dword_x));
					break;
				}
				case Element::BINARY64: {
					//==  BINARY64 & BINARY64  ==//
					uint64_t qword_y = GET_QWORD_DATA(p_ey);
					uint64_t qword_x = GET_QWORD_DATA(p_ex);
					p_etemp = GEN_QWORD(qword_y & qword_x);
					break;
				}
				default:
					//==  BINARY64 & Unexpected  ==//
					throw BadArgument("BAD_TYPE", __FUNCTION__);
			}
			break;
		default:
			//===  Unexpected & ANY  ===//
			throw BadArgument("BAD_TYPE", __FUNCTION__);
	}
	return p_etemp;
}

////==--------------------------------------------------------------------====//
// ECKERT PROCESSOR / BITWISE OR
// [ description ]
// Calculate OR.
// [ Update ]
// Feb 11, 2016
//====--------------------------------------------------------------------==////
SpElement GeneralProcessor::bitwiseOr(const SpElement &p_ey, const SpElement &p_ex) {
	//==  NULL POINTER CHECK  ==//
	if ((nullptr == p_ey) || (nullptr == p_ex)) {
		throw TechnicalError("NULLPTR", __FUNCTION__);
	}
	SpElement p_etemp;
	auto y_type = p_ey->getType();
	auto x_type = p_ex->getType();
	switch (y_type) {
		case Element::BOOLEAN:
			//===  BOOLEAN | ???  ===//
			switch (x_type) {
				case Element::BOOLEAN: {
					//==  BOOLEAN | BOOLEAN  ==//
					bool bool_y = GET_BOOLEAN_DATA(p_ey);
					bool bool_x = GET_BOOLEAN_DATA(p_ex);
					p_etemp = GEN_BOOLEAN(bool_y | bool_x);
					break;
				}
				default:
					throw BadArgument("BAD_TYPE", __FUNCTION__);
			}
			break;
		case Element::BINARY8:
			//===  BINARY8 | ???  ===//
			switch (x_type) {
				case Element::BINARY8: {
					//==  BINARY8 | BINARY8  ==//
					uint8_t byte_y = GET_BYTE_DATA(p_ey);
					uint8_t byte_x = GET_BYTE_DATA(p_ex);
					p_etemp = GEN_BYTE(byte_y | byte_x);
					break;
				}
				case Element::BINARY16: {
					//==  BINARY8 | BINARY16  ==//
					uint8_t byte_y = GET_BYTE_DATA(p_ey);
					uint16_t word_x = GET_WORD_DATA(p_ex);
					p_etemp = GEN_WORD(byte_y | word_x);
					break;
				}
				case Element::BINARY32: {
					//==  BINARY8 | BINARY32  ==//
					uint8_t byte_y = GET_BYTE_DATA(p_ey);
					uint32_t dword_x = GET_DWORD_DATA(p_ex);
					p_etemp = GEN_DWORD(byte_y | dword_x);
					break;
				}
				case Element::BINARY64: {
					//==  BINARY8 | BINARY64  ==//
					uint8_t byte_y = GET_BYTE_DATA(p_ey);
					uint64_t qword_x = GET_QWORD_DATA(p_ex);
					p_etemp = GEN_QWORD(byte_y | qword_x);
					break;
				}
				default:
					//==  BINARY8 | Unexpected  ==//
					throw BadArgument("BAD_TYPE", __FUNCTION__);
			}
			break;
		case Element::BINARY16:
			//===  BINARY16 | ???  ===//
			switch (x_type) {
				case Element::BINARY8: {
					//==  BINARY16 | BINARY8  ==//
					uint16_t word_y = GET_WORD_DATA(p_ey);
					uint8_t byte_x = GET_BYTE_DATA(p_ex);
					p_etemp = GEN_WORD(word_y | byte_x);
					break;
				}
				case Element::BINARY16: {
					//==  BINARY16 | BINARY16  ==//
					uint16_t word_y = GET_WORD_DATA(p_ey);
					uint16_t word_x = GET_WORD_DATA(p_ex);
					p_etemp = GEN_WORD(word_y | word_x);
					break;
				}
				case Element::BINARY32: {
					//==  BINARY16 | BINARY32  ==//
					uint16_t word_y = GET_WORD_DATA(p_ey);
					uint32_t dword_x = GET_DWORD_DATA(p_ex);
					p_etemp = GEN_DWORD(word_y | dword_x);
					break;
				}
				case Element::BINARY64: {
					//==  BINARY16 | BINARY64  ==//
					uint16_t word_y = GET_WORD_DATA(p_ey);
					uint64_t qword_x = GET_QWORD_DATA(p_ex);
					p_etemp = GEN_QWORD(word_y | qword_x);
					break;
				}
				default:
					//==  BINARY16 | Unexpected  ==//
					throw BadArgument("BAD_TYPE", __FUNCTION__);
			}
			break;
		case Element::BINARY32:
			//===  BINARY32 | ???  ===//
			switch (x_type) {
				case Element::BINARY8: {
					//==  BINARY32 | BINARY8  ==//
					uint32_t dword_y = GET_DWORD_DATA(p_ey);
					uint8_t byte_x = GET_BYTE_DATA(p_ex);
					p_etemp = GEN_DWORD(dword_y | byte_x);
					break;
				}
				case Element::BINARY16: {
					//==  BINARY32 | BINARY16  ==//
					uint32_t dword_y = GET_DWORD_DATA(p_ey);
					uint16_t word_x = GET_WORD_DATA(p_ex);
					p_etemp = GEN_DWORD(dword_y | word_x);
					break;
				}
				case Element::BINARY32: {
					//==  BINARY32 | BINARY32  ==//
					uint32_t dword_y = GET_DWORD_DATA(p_ey);
					uint32_t dword_x = GET_DWORD_DATA(p_ex);
					p_etemp = GEN_DWORD(dword_y | dword_x);
					break;
				}
				case Element::BINARY64: {
					//==  BINARY32 | BINARY64  ==//
					uint32_t dword_y = GET_DWORD_DATA(p_ey);
					uint64_t qword_x = GET_QWORD_DATA(p_ex);
					p_etemp = GEN_QWORD(dword_y | qword_x);
					break;
				}
				default:
					//==  BINARY32 | Unexpected  ==//
					throw BadArgument("BAD_TYPE", __FUNCTION__);
			}
			break;
		case Element::BINARY64:
			//===  BINARY64 | ???  ===//
			switch (x_type) {
				case Element::BINARY8: {
					//==  BINARY64 | BINARY8  ==//
					uint64_t qword_y = GET_QWORD_DATA(p_ey);
					uint8_t byte_x = GET_BYTE_DATA(p_ex);
					p_etemp = GEN_QWORD(qword_y | byte_x);
					break;
				}
				case Element::BINARY16: {
					//==  BINARY64 | BINARY16  ==//
					uint64_t qword_y = GET_QWORD_DATA(p_ey);
					uint16_t word_x = GET_WORD_DATA(p_ex);
					p_etemp = GEN_QWORD(qword_y | word_x);
					break;
				}
				case Element::BINARY32: {
					//==  BINARY64 | BINARY32  ==//
					uint64_t qword_y = GET_QWORD_DATA(p_ey);
					uint32_t dword_x = GET_DWORD_DATA(p_ex);
					p_etemp = GEN_QWORD(qword_y | dword_x);
					break;
				}
				case Element::BINARY64: {
					//==  BINARY64 | BINARY64  ==//
					uint64_t qword_y = GET_QWORD_DATA(p_ey);
					uint64_t qword_x = GET_QWORD_DATA(p_ex);
					p_etemp = GEN_QWORD(qword_y | qword_x);
					break;
				}
				default:
					//==  BINARY64 | Unexpected  ==//
					throw BadArgument("BAD_TYPE", __FUNCTION__);
			}
			break;
		default:
			//===  Unexpected | ANY  ===//
			throw BadArgument("BAD_TYPE", __FUNCTION__);
	}
	return p_etemp;
}

////==--------------------------------------------------------------------====//
// ECKERT PROCESSOR / NAND
// [ description ]
// Calculate NAND
// [ Update ]
// Feb 11, 2016
//====--------------------------------------------------------------------==////
SpElement GeneralProcessor::bitwiseNand(const SpElement &p_ey, const SpElement &p_ex) {
	//==  NULL POINTER CHECK  ==//
	if ((nullptr == p_ey) || (nullptr == p_ex)) {
		throw TechnicalError("NULLPTR", __FUNCTION__);
	}
	SpElement p_etemp;
	auto y_type = p_ey->getType();
	auto x_type = p_ex->getType();
	switch (y_type) {
		case Element::BOOLEAN:
			//===  BOOLEAN & ???  ===//
			switch (x_type) {
				case Element::BOOLEAN: {
					//==  BOOLEAN & BOOLEAN  ==//
					bool bool_y = GET_BOOLEAN_DATA(p_ey);
					bool bool_x = GET_BOOLEAN_DATA(p_ex);
					p_etemp = GEN_BOOLEAN(bool_y & bool_x);
					break;
				}
				default:
					throw BadArgument("BAD_TYPE", __FUNCTION__);
			}
			break;
		case Element::BINARY8:
			//===  BINARY8 & ???  ===//
			switch (x_type) {
				case Element::BINARY8: {
					//==  BINARY8 & BINARY8  ==//
					uint8_t byte_y = GET_BYTE_DATA(p_ey);
					uint8_t byte_x = GET_BYTE_DATA(p_ex);
					p_etemp = GEN_BYTE(~(byte_y & byte_x));
					break;
				}
				case Element::BINARY16: {
					//==  BINARY8 & BINARY16  ==//
					uint8_t byte_y = GET_BYTE_DATA(p_ey);
					uint16_t word_x = GET_WORD_DATA(p_ex);
					p_etemp = GEN_BYTE(~(static_cast<uint8_t>(byte_y & word_x)));
					break;
				}
				case Element::BINARY32: {
					//==  BINARY8 & BINARY32  ==//
					uint8_t byte_y = GET_BYTE_DATA(p_ey);
					uint32_t dword_x = GET_DWORD_DATA(p_ex);
					p_etemp = GEN_BYTE(~(static_cast<uint8_t>(byte_y & dword_x)));
					break;
				}
				case Element::BINARY64: {
					//==  BINARY8 & BINARY64  ==//
					uint8_t byte_y = GET_BYTE_DATA(p_ey);
					uint64_t qword_x = GET_QWORD_DATA(p_ex);
					p_etemp = GEN_BYTE(~(static_cast<uint8_t>(byte_y & qword_x)));
					break;
				}
				default:
					//==  BINARY8 & Unexpected  ==//
					throw BadArgument("BAD_TYPE", __FUNCTION__);
			}
			break;
		case Element::BINARY16:
			//===  BINARY16 & ???  ===//
			switch (x_type) {
				case Element::BINARY8: {
					//==  BINARY16 & BINARY8  ==//
					uint16_t word_y = GET_WORD_DATA(p_ey);
					uint8_t byte_x = GET_BYTE_DATA(p_ex);
					p_etemp = GEN_BYTE(~(static_cast<uint8_t>(word_y & byte_x)));
					break;
				}
				case Element::BINARY16: {
					//==  BINARY16 & BINARY16  ==//
					uint16_t word_y = GET_WORD_DATA(p_ey);
					uint16_t word_x = GET_WORD_DATA(p_ex);
					p_etemp = GEN_WORD(~(word_y & word_x));
					break;
				}
				case Element::BINARY32: {
					//==  BINARY16 & BINARY32  ==//
					uint16_t word_y = GET_WORD_DATA(p_ey);
					uint32_t dword_x = GET_DWORD_DATA(p_ex);
					p_etemp = GEN_WORD(~(static_cast<uint16_t>(word_y & dword_x)));
					break;
				}
				case Element::BINARY64: {
					//==  BINARY16 & BINARY64  ==//
					uint16_t word_y = GET_WORD_DATA(p_ey);
					uint64_t qword_x = GET_QWORD_DATA(p_ex);
					p_etemp = GEN_WORD(~(static_cast<uint16_t>(word_y & qword_x)));
					break;
				}
				default:
					//==  BINARY16 & Unexpected  ==//
					throw BadArgument("BAD_TYPE", __FUNCTION__);
			}
			break;
		case Element::BINARY32:
			//===  BINARY32 & ???  ===//
			switch (x_type) {
				case Element::BINARY8: {
					//==  BINARY32 & BINARY8  ==//
					uint32_t dword_y = GET_DWORD_DATA(p_ey);
					uint8_t byte_x = GET_BYTE_DATA(p_ex);
					p_etemp = GEN_BYTE(~(static_cast<uint8_t>(dword_y & byte_x)));
					break;
				}
				case Element::BINARY16: {
					//==  BINARY32 & BINARY16  ==//
					uint32_t dword_y = GET_DWORD_DATA(p_ey);
					uint16_t word_x = GET_WORD_DATA(p_ex);
					p_etemp = GEN_WORD(~(static_cast<uint16_t>(dword_y & word_x)));
					break;
				}
				case Element::BINARY32: {
					//==  BINARY32 & BINARY32  ==//
					uint32_t dword_y = GET_DWORD_DATA(p_ey);
					uint32_t dword_x = GET_DWORD_DATA(p_ex);
					p_etemp = GEN_DWORD(~(dword_y & dword_x));
					break;
				}
				case Element::BINARY64: {
					//==  BINARY32 & BINARY64  ==//
					uint32_t dword_y = GET_DWORD_DATA(p_ey);
					uint64_t qword_x = GET_QWORD_DATA(p_ex);
					p_etemp = GEN_DWORD(~(static_cast<uint32_t>(dword_y & qword_x)));
					break;
				}
				default:
					//==  BINARY32 & Unexpected  ==//
					throw BadArgument("BAD_TYPE", __FUNCTION__);
			}
			break;
		case Element::BINARY64:
			//===  BINARY64 & ???  ===//
			switch (x_type) {
				case Element::BINARY8: {
					//==  BINARY64 & BINARY8  ==//
					uint64_t qword_y = GET_QWORD_DATA(p_ey);
					uint8_t byte_x = GET_BYTE_DATA(p_ex);
					p_etemp = GEN_BYTE(~(static_cast<uint8_t>(qword_y & byte_x)));
					break;
				}
				case Element::BINARY16: {
					//==  BINARY64 & BINARY16  ==//
					uint64_t qword_y = GET_QWORD_DATA(p_ey);
					uint16_t word_x = GET_WORD_DATA(p_ex);
					p_etemp = GEN_WORD(~(static_cast<uint16_t>(qword_y & word_x)));
					break;
				}
				case Element::BINARY32: {
					//==  BINARY64 & BINARY32  ==//
					uint64_t qword_y = GET_QWORD_DATA(p_ey);
					uint32_t dword_x = GET_DWORD_DATA(p_ex);
					p_etemp = GEN_DWORD(~(static_cast<uint32_t>(qword_y & dword_x)));
					break;
				}
				case Element::BINARY64: {
					//==  BINARY64 & BINARY64 ==//
					uint64_t qword_y = GET_QWORD_DATA(p_ey);
					uint64_t qword_x = GET_QWORD_DATA(p_ex);
					p_etemp = GEN_QWORD(~(qword_y & qword_x));
					break;
				}
				default:
					//==  BINARY64 & Unexpected  ==//
					throw BadArgument("BAD_TYPE", __FUNCTION__);
			}
			break;
		default:
			//===  Unexpected & ANY  ===//
			throw BadArgument("BAD_TYPE", __FUNCTION__);
	}
	return p_etemp;
}

////==--------------------------------------------------------------------====//
// ECKERT PROCESSOR / NOR
// [ description ]
// Calculate NOR
// [ Update ]
// Feb 11, 2016
//====--------------------------------------------------------------------==////
SpElement GeneralProcessor::bitwiseNor(const SpElement &p_ey, const SpElement &p_ex) {
	//==  NULL POINTER CHECK  ==//
	if ((nullptr == p_ey) || (nullptr == p_ex)) {
		throw TechnicalError("NULLPTR", __FUNCTION__);
	}
	SpElement p_etemp;
	auto y_type = p_ey->getType();
	auto x_type = p_ex->getType();
	switch (y_type) {
		case Element::BOOLEAN:
			//===  BOOLEAN nor ???  ===//
			switch (x_type) {
				case Element::BOOLEAN: {
					//==  BOOLEAN nor BOOLEAN  ==//
					bool bool_y = GET_BOOLEAN_DATA(p_ey);
					bool bool_x = GET_BOOLEAN_DATA(p_ex);
					p_etemp = GEN_BOOLEAN(!(bool_y | bool_x));
					break;
				}
				default:
					throw BadArgument("BAD_TYPE", __FUNCTION__);
			}
			break;
		case Element::BINARY8:
			//===  BINARY8 nor ???  ===//
			switch (x_type) {
				case Element::BINARY8: {
					//==  BINARY8 nor BINARY8  ==//
					uint8_t byte_y = GET_BYTE_DATA(p_ey);
					uint8_t byte_x = GET_BYTE_DATA(p_ex);
					p_etemp = GEN_BYTE(~(byte_y | byte_x));
					break;
				}
				case Element::BINARY16: {
					//==  BINARY8 nor BINARY16  ==//
					uint8_t byte_y = GET_BYTE_DATA(p_ey);
					uint16_t word_x = GET_WORD_DATA(p_ex);
					p_etemp = GEN_WORD(~(byte_y | word_x));
					break;
				}
				case Element::BINARY32: {
					//==  BINARY8 nor BINARY32  ==//
					uint8_t byte_y = GET_BYTE_DATA(p_ey);
					uint32_t dword_x = GET_DWORD_DATA(p_ex);
					p_etemp = GEN_DWORD(~(byte_y | dword_x));
					break;
				}
				case Element::BINARY64: {
					//==  BINARY8 nor BINARY64  ==//
					uint8_t byte_y = GET_BYTE_DATA(p_ey);
					uint64_t qword_x = GET_QWORD_DATA(p_ex);
					p_etemp = GEN_QWORD(~(byte_y | qword_x));
					break;
				}
				default:
					//==  BINARY8 nor Unexpected  ==//
					throw BadArgument("BAD_TYPE", __FUNCTION__);
			}
			break;
		case Element::BINARY16:
			//===  BINARY16 nor ???  ===//
			switch (x_type) {
				case Element::BINARY8: {
					//==  BINARY16 nor BINARY8  ==//
					uint16_t word_y = GET_WORD_DATA(p_ey);
					uint8_t byte_x = GET_BYTE_DATA(p_ex);
					p_etemp = GEN_WORD(~(word_y | byte_x));
					break;
				}
				case Element::BINARY16: {
					//==  BINARY16 nor BINARY16  ==//
					uint16_t word_y = GET_WORD_DATA(p_ey);
					uint16_t word_x = GET_WORD_DATA(p_ex);
					p_etemp = GEN_WORD(~(word_y | word_x));
					break;
				}
				case Element::BINARY32: {
					//==  BINARY16 nor BINARY32  ==//
					uint16_t word_y = GET_WORD_DATA(p_ey);
					uint32_t dword_x = GET_DWORD_DATA(p_ex);
					p_etemp = GEN_DWORD(~(word_y | dword_x));
					break;
				}
				case Element::BINARY64: {
					//==  BINARY16 nor BINARY64  ==//
					uint16_t word_y = GET_WORD_DATA(p_ey);
					uint64_t qword_x = GET_QWORD_DATA(p_ex);
					p_etemp = GEN_QWORD(~(word_y | qword_x));
					break;
				}
				default:
					//==  BINARY16 nor Unexpected  ==//
					throw BadArgument("BAD_TYPE", __FUNCTION__);
			}
			break;
		case Element::BINARY32:
			//===  BINARY32 nor ???  ===//
			switch (x_type) {
				case Element::BINARY8: {
					//==  BINARY32 nor BINARY8  ==//
					uint32_t dword_y = GET_DWORD_DATA(p_ey);
					uint8_t byte_x = GET_BYTE_DATA(p_ex);
					p_etemp = GEN_DWORD(~(dword_y | byte_x));
					break;
				}
				case Element::BINARY16: {
					//==  BINARY32 nor BINARY16  ==//
					uint32_t dword_y = GET_DWORD_DATA(p_ey);
					uint16_t word_x = GET_WORD_DATA(p_ex);
					p_etemp = GEN_DWORD(~(dword_y | word_x));
					break;
				}
				case Element::BINARY32: {
					//==  BINARY32 nor BINARY32  ==//
					uint32_t dword_y = GET_DWORD_DATA(p_ey);
					uint32_t dword_x = GET_DWORD_DATA(p_ex);
					p_etemp = GEN_DWORD(~(dword_y | dword_x));
					break;
				}
				case Element::BINARY64: {
					//==  BINARY32 nor BINARY64  ==//
					uint32_t dword_y = GET_DWORD_DATA(p_ey);
					uint64_t qword_x = GET_QWORD_DATA(p_ex);
					p_etemp = GEN_QWORD(~(dword_y | qword_x));
					break;
				}
				default:
					//==  BINARY32 nor Unexpected  ==//
					throw BadArgument("BAD_TYPE", __FUNCTION__);
			}
			break;
		case Element::BINARY64:
			//===  BINARY64 nor ???  ===//
			switch (x_type) {
				case Element::BINARY8: {
					//==  BINARY64 nor BINARY8  ==//
					uint64_t qword_y = GET_QWORD_DATA(p_ey);
					uint8_t byte_x = GET_BYTE_DATA(p_ex);
					p_etemp = GEN_QWORD(~(qword_y | byte_x));
					break;
				}
				case Element::BINARY16: {
					//==  BINARY64 nor BINARY16  ==//
					uint64_t qword_y = GET_QWORD_DATA(p_ey);
					uint16_t word_x = GET_WORD_DATA(p_ex);
					p_etemp = GEN_QWORD(~(qword_y | word_x));
					break;
				}
				case Element::BINARY32: {
					//==  BINARY64 nor BINARY32  ==//
					uint64_t qword_y = GET_QWORD_DATA(p_ey);
					uint32_t dword_x = GET_DWORD_DATA(p_ex);
					p_etemp = GEN_QWORD(~(qword_y | dword_x));
					break;
				}
				case Element::BINARY64: {
					//==  BINARY64 nor BINARY64  ==//
					uint64_t qword_y = GET_QWORD_DATA(p_ey);
					uint64_t qword_x = GET_QWORD_DATA(p_ex);
					p_etemp = GEN_QWORD(~(qword_y | qword_x));
					break;
				}
				default:
					//==  BINARY64 nor Unexpected  ==//
					throw BadArgument("BAD_TYPE", __FUNCTION__);
			}
			break;
		default:
			//===  Unexpected | ANY  ===//
			throw BadArgument("BAD_TYPE", __FUNCTION__);
	}
	return p_etemp;
}

////==--------------------------------------------------------------------====//
// ECKERT PROCESSOR / BITWISE NOT
// [ description ]
// Calculate NOT
// [ Update ]
// Feb 11, 2016
//====--------------------------------------------------------------------==////
SpElement GeneralProcessor::bitwiseNot(const SpElement &p_ex) {
	//==  NULL POINTER CHECK  ==//
	if (nullptr == p_ex) {
		throw TechnicalError("NULLPTR", __FUNCTION__);
	}
	SpElement p_etemp;
	switch (p_ex->getType()) {
		case Element::BOOLEAN: {
			//==  not(BINARY8)  ==//
			bool bool_x = GET_BOOLEAN_DATA(p_ex);
			p_etemp = GEN_BOOLEAN(!bool_x);
			break;
		}
		case Element::BINARY8: {
			//==  not(BINARY8)  ==//
			uint8_t byte_x = GET_BYTE_DATA(p_ex);
			p_etemp = GEN_BYTE(~byte_x);
			break;
		}
		case Element::BINARY16: {
			//==  not(BINARY16)  ==//
			uint16_t word_x = GET_WORD_DATA(p_ex);
			p_etemp = GEN_WORD(~word_x);
			break;
		}
		case Element::BINARY32: {
			//==  not(BINARY32)  ==//
			uint32_t dword_x = GET_DWORD_DATA(p_ex);
			p_etemp = GEN_DWORD(~dword_x);
			break;
		}
		case Element::BINARY64: {
			//==  not(BINARY64)  ==//
			uint64_t qword_x = GET_QWORD_DATA(p_ex);
			p_etemp = GEN_QWORD(~qword_x);
			break;
		}
		default:
			//==  neg(Unexpected)  ==//
			throw TechnicalError("neg(Unexpected)", __FUNCTION__);
	}
	return p_etemp;
}

////==--------------------------------------------------------------------====//
// ECKERT PROCESSOR / XOR
// [ description ]
// Calculate NEGATE
// [ Update ]
// Feb 11, 2016
//====--------------------------------------------------------------------==////
SpElement GeneralProcessor::bitwiseXor(const SpElement &p_ey, const SpElement &p_ex) {
	//==  NULL POINTER CHECK  ==//
	if ((nullptr == p_ey) || (nullptr == p_ex)) {
		throw TechnicalError("NULLPTR", __FUNCTION__);
	}
	SpElement p_etemp;
	auto y_type = p_ey->getType();
	auto x_type = p_ex->getType();
	switch (y_type) {
		case Element::BOOLEAN:
			//===  BOOLEAN ^ ???  ===//
			switch (x_type) {
				case Element::BOOLEAN: {
					//==  BOOLEAN ^ BOOLEAN  ==//
					bool bool_y = GET_BOOLEAN_DATA(p_ey);
					bool bool_x = GET_BOOLEAN_DATA(p_ex);
					p_etemp = GEN_BOOLEAN(bool_y ^ bool_x);
					break;
				}
				default:
					throw BadArgument("BAD_TYPE", __FUNCTION__);
			}
			break;
		case Element::BINARY8:
			//===  BINARY8 ^ ???  ===//
			switch (x_type) {
				case Element::BINARY8: {
					//==  BINARY8 ^ BINARY8  ==//
					uint8_t byte_y = GET_BYTE_DATA(p_ey);
					uint8_t byte_x = GET_BYTE_DATA(p_ex);
					p_etemp = GEN_BYTE(byte_y ^ byte_x);
					break;
				}
				case Element::BINARY16: {
					//==  BINARY8 ^ BINARY16  ==//
					uint8_t byte_y = GET_BYTE_DATA(p_ey);
					uint16_t word_x = GET_WORD_DATA(p_ex);
					p_etemp = GEN_WORD(byte_y ^ word_x);
					break;
				}
				case Element::BINARY32: {
					//==  BINARY8 ^ BINARY32  ==//
					uint8_t byte_y = GET_BYTE_DATA(p_ey);
					uint32_t dword_x = GET_DWORD_DATA(p_ex);
					p_etemp = GEN_DWORD(byte_y ^ dword_x);
					break;
				}
				case Element::BINARY64: {
					//==  BINARY8 ^ BINARY64  ==//
					uint8_t byte_y = GET_BYTE_DATA(p_ey);
					uint64_t qword_x = GET_QWORD_DATA(p_ex);
					p_etemp = GEN_QWORD(byte_y ^ qword_x);
					break;
				}
				default:
					//==  BINARY8 ^ Unexpected  ==//
					throw BadArgument("BAD_TYPE", __FUNCTION__);
			}
			break;
		case Element::BINARY16:
			//===  BINARY16 ^ ???  ===//
			switch (x_type) {
				case Element::BINARY8: {
					//==  BINARY16 ^ BINARY8  ==//
					uint16_t word_y = GET_WORD_DATA(p_ey);
					uint8_t byte_x = GET_BYTE_DATA(p_ex);
					p_etemp = GEN_WORD(word_y ^ byte_x);
					break;
				}
				case Element::BINARY16: {
					//==  BINARY16 ^ BINARY16  ==//
					uint16_t word_y = GET_WORD_DATA(p_ey);
					uint16_t word_x = GET_WORD_DATA(p_ex);
					p_etemp = GEN_WORD(word_y ^ word_x);
					break;
				}
				case Element::BINARY32: {
					//==  BINARY16 ^ BINARY32  ==//
					uint16_t word_y = GET_WORD_DATA(p_ey);
					uint32_t dword_x = GET_DWORD_DATA(p_ex);
					p_etemp = GEN_WORD(word_y ^ dword_x);
					break;
				}
				case Element::BINARY64: {
					//==  BINARY16 ^ BINARY64  ==//
					uint16_t word_y = GET_WORD_DATA(p_ey);
					uint64_t qword_x = GET_QWORD_DATA(p_ex);
					p_etemp = GEN_QWORD(word_y ^ qword_x);
					break;
				}
				default:
					//==  BINARY16 ^ Unexpected  ==//
					throw BadArgument("BAD_TYPE", __FUNCTION__);
			}
			break;
		case Element::BINARY32:
			//===  BINARY32 ^ ???  ===//
			switch (x_type) {
				case Element::BINARY8: {
					//==  BINARY32 ^ BINARY8  ==//
					uint32_t dword_y = GET_DWORD_DATA(p_ey);
					uint8_t byte_x = GET_BYTE_DATA(p_ex);
					p_etemp = GEN_DWORD(dword_y ^ byte_x);
					break;
				}
				case Element::BINARY16: {
					//==  BINARY32 ^ BINARY16  ==//
					uint32_t dword_y = GET_DWORD_DATA(p_ey);
					uint16_t word_x = GET_WORD_DATA(p_ex);
					p_etemp = GEN_DWORD(dword_y ^ word_x);
					break;
				}
				case Element::BINARY32: {
					//==  BINARY32 ^ BINARY32  ==//
					uint32_t dword_y = GET_DWORD_DATA(p_ey);
					uint32_t dword_x = GET_DWORD_DATA(p_ex);
					p_etemp = GEN_DWORD(dword_y ^ dword_x);
					break;
				}
				case Element::BINARY64: {
					//==  BINARY32 ^ BINARY64  ==//
					uint32_t dword_y = GET_DWORD_DATA(p_ey);
					uint64_t qword_x = GET_QWORD_DATA(p_ex);
					p_etemp = GEN_QWORD(dword_y ^ qword_x);
					break;
				}
				default:
					//==  BINARY32 ^ Unexpected  ==//
					throw BadArgument("BAD_TYPE", __FUNCTION__);
			}
			break;
		case Element::BINARY64:
			//===  BINARY64 ^ ???  ===//
			switch (x_type) {
				case Element::BINARY8: {
					//==  BINARY64 ^ BINARY8  ==//
					uint64_t qword_y = GET_QWORD_DATA(p_ey);
					uint8_t byte_x = GET_BYTE_DATA(p_ex);
					p_etemp = GEN_QWORD(qword_y ^ byte_x);
					break;
				}
				case Element::BINARY16: {
					//==  BINARY64 ^ BINARY16  ==//
					uint64_t qword_y = GET_QWORD_DATA(p_ey);
					uint16_t word_x = GET_WORD_DATA(p_ex);
					p_etemp = GEN_QWORD(qword_y ^ word_x);
					break;
				}
				case Element::BINARY32: {
					//==  BINARY64 ^ BINARY32  ==//
					uint64_t qword_y = GET_QWORD_DATA(p_ey);
					uint32_t dword_x = GET_DWORD_DATA(p_ex);
					p_etemp = GEN_QWORD(qword_y ^ dword_x);
					break;
				}
				case Element::BINARY64: {
					//==  BINARY64 ^ BINARY64  ==//
					uint64_t qword_y = GET_QWORD_DATA(p_ey);
					uint64_t qword_x = GET_QWORD_DATA(p_ex);
					p_etemp = GEN_QWORD(qword_y ^ qword_x);
					break;
				}
				default:
					//==  BINARY64 ^ Unexpected  ==//
					throw BadArgument("BAD_TYPE", __FUNCTION__);
			}
			break;
		default:
			//===  Unexpected ^ ANY  ===//
			throw BadArgument("BAD_TYPE", __FUNCTION__);
	}
	return p_etemp;
}

} // namespace engine
