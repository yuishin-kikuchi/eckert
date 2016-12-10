#include "GeneralProcessor.h"

namespace engine {

////==--------------------------------------------------------------------====//
// ECKERT PROCESSOR / ADD (BINARY)
// [ description ]
// Calculate ADD
// [ Update ]
// Nov 14, 2016
//====--------------------------------------------------------------------==////
SpElement GeneralProcessor::addBinary(const SpElement &p_ey, const SpElement &p_ex) {
	//==  NULL POINTER CHECK  ==//
	if ((nullptr == p_ey) || (nullptr == p_ex)) {
		throw TechnicalError("NULLPTR", __FUNCTION__);
	}
	SpElement p_etemp;
	auto y_type = p_ey->getType();
	auto x_type = p_ex->getType();
	switch (y_type) {
		case Element::BOOLEAN:
			//===  BOOLEAN + ???  ===//
			switch (x_type) {
				case Element::BOOLEAN: {
					//==  BOOLEAN + BOOLEAN  ==//
					bool by = GET_BOOLEAN_DATA(p_ey);
					bool bx = GET_BOOLEAN_DATA(p_ex);
					p_etemp = GEN_BOOLEAN(by ^ bx); // BOOLEAN XOR BOOLEAN
					break;
				}
				default:
					//==  BOOLEAN + Unexpected  ==//
					throw BadArgument("BAD_TYPE", __FUNCTION__);
			}
			break;
		case Element::BINARY8:
			//===  BINARY8 + ???  ===//
			switch (x_type) {
				case Element::BINARY8: {
					//==  BINARY8 + BINARY8  ==//
					uint8_t byte_y = GET_BYTE_DATA(p_ey);
					uint8_t byte_x = GET_BYTE_DATA(p_ex);
					p_etemp = GEN_BYTE(byte_y + byte_x);
					break;
				}
				case Element::BINARY16: {
					//==  BINARY8 + BINARY16  ==//
					uint8_t byte_y = GET_BYTE_DATA(p_ey);
					uint16_t word_x = GET_WORD_DATA(p_ex);
					p_etemp = GEN_WORD(byte_y + word_x);
					break;
				}
				case Element::BINARY32: {
					//==  BINARY8 + BINARY32  ==//
					uint8_t byte_y = GET_BYTE_DATA(p_ey);
					uint32_t dword_x = GET_DWORD_DATA(p_ex);
					p_etemp = GEN_DWORD(byte_y + dword_x);
					break;
				}
				case Element::BINARY64: {
					//==  BINARY8 + BINARY64  ==//
					uint8_t byte_y = GET_BYTE_DATA(p_ey);
					uint64_t qword_x = GET_QWORD_DATA(p_ex);
					p_etemp = GEN_QWORD(byte_y + qword_x);
					break;
				}
				default:
					//==  BINARY8 + Unexpected  ==//
					throw BadArgument("BAD_TYPE", __FUNCTION__);
			}
			break;
		case Element::BINARY16:
			//===  BINARY16 + ???  ===//
			switch (x_type) {
				case Element::BINARY8: {
					//==  BINARY16 + BINARY8  ==//
					uint16_t word_y = GET_WORD_DATA(p_ey);
					uint8_t byte_x = GET_BYTE_DATA(p_ex);
					p_etemp = GEN_WORD(word_y + byte_x);
					break;
				}
				case Element::BINARY16: {
					//==  BINARY16 + BINARY16  ==//
					uint16_t word_y = GET_WORD_DATA(p_ey);
					uint16_t word_x = GET_WORD_DATA(p_ex);
					p_etemp = GEN_WORD(word_y + word_x);
					break;
				}
				case Element::BINARY32: {
					//==  BINARY16 + BINARY32  ==//
					uint16_t word_y = GET_WORD_DATA(p_ey);
					uint32_t dword_x = GET_DWORD_DATA(p_ex);
					p_etemp = GEN_DWORD(word_y + dword_x);
					break;
				}
				case Element::BINARY64: {
					//==  BINARY16 + BINARY64  ==//
					uint16_t word_y = GET_WORD_DATA(p_ey);
					uint64_t qword_x = GET_QWORD_DATA(p_ex);
					p_etemp = GEN_QWORD(word_y + qword_x);
					break;
				}
				default:
					//==  BINARY16 + Unexpected  ==//
					throw BadArgument("BAD_TYPE", __FUNCTION__);
			}
			break;
		case Element::BINARY32:
			//===  BINARY32 + ???  ===//
			switch (x_type) {
				case Element::BINARY8: {
					//==  BINARY32 + BINARY8  ==//
					uint32_t dword_y = GET_DWORD_DATA(p_ey);
					uint8_t byte_x = GET_BYTE_DATA(p_ex);
					p_etemp = GEN_DWORD(dword_y + byte_x);
					break;
				}
				case Element::BINARY16: {
					//==  BINARY32 + BINARY16  ==//
					uint32_t dword_y = GET_DWORD_DATA(p_ey);
					uint16_t word_x = GET_WORD_DATA(p_ex);
					p_etemp = GEN_DWORD(dword_y + word_x);
					break;
				}
				case Element::BINARY32: {
					//==  BINARY32 + BINARY32  ==//
					uint32_t dword_y = GET_DWORD_DATA(p_ey);
					uint32_t dword_x = GET_DWORD_DATA(p_ex);
					p_etemp = GEN_DWORD(dword_y + dword_x);
					break;
				}
				case Element::BINARY64: {
					//==  BINARY32 + BINARY64  ==//
					uint32_t dword_y = GET_DWORD_DATA(p_ey);
					uint64_t qword_x = GET_QWORD_DATA(p_ex);
					p_etemp = GEN_QWORD(dword_y + qword_x);
					break;
				}
				default:
					//==  BINARY32 + Unexpected  ==//
					throw BadArgument("BAD_TYPE", __FUNCTION__);
			}
			break;
		case Element::BINARY64:
			//===  BINARY64 + ???  ===//
			switch (x_type) {
				case Element::BINARY8: {
					//==  BINARY64 + BINARY8  ==//
					uint64_t qword_y = GET_QWORD_DATA(p_ey);
					uint8_t byte_x = GET_BYTE_DATA(p_ex);
					p_etemp = GEN_QWORD(qword_y + byte_x);
					break;
				}
				case Element::BINARY16: {
					//==  BINARY64 + BINARY16  ==//
					uint64_t qword_y = GET_QWORD_DATA(p_ey);
					uint16_t word_x = GET_WORD_DATA(p_ex);
					p_etemp = GEN_QWORD(qword_y + word_x);
					break;
				}
				case Element::BINARY32: {
					//==  BINARY64 + BINARY32  ==//
					uint64_t qword_y = GET_QWORD_DATA(p_ey);
					uint32_t dword_x = GET_DWORD_DATA(p_ex);
					p_etemp = GEN_QWORD(qword_y + dword_x);
					break;
				}
				case Element::BINARY64: {
					//==  BINARY64 + BINARY64  ==//
					uint64_t qword_y = GET_QWORD_DATA(p_ey);
					uint64_t qword_x = GET_QWORD_DATA(p_ex);
					p_etemp = GEN_QWORD(qword_y + qword_x);
					break;
				}
				default:
					//==  BINARY64 + Unexpected  ==//
					throw BadArgument("BAD_TYPE", __FUNCTION__);
			}
			break;
		default:
			//===  Unexpected + ANY  ===//
			throw BadArgument("BAD_TYPE", __FUNCTION__);
	}
	return p_etemp;
}

////==--------------------------------------------------------------------====//
// ECKERT PROCESSOR / SUBTRACT (BINARY)
// [ description ]
// Calculate SUBTRACT
// [ Update ]
// Nov 14, 2016
//====--------------------------------------------------------------------==////
SpElement GeneralProcessor::subBinary(const SpElement &p_ey, const SpElement &p_ex) {
	//==  NULL POINTER CHECK  ==//
	if ((nullptr == p_ey) || (nullptr == p_ex)) {
		throw TechnicalError("NULLPTR", __FUNCTION__);
	}
	SpElement p_etemp;
	auto y_type = p_ey->getType();
	auto x_type = p_ex->getType();
	switch (y_type) {
		case Element::BINARY8:
			//===  BINARY8 - ???  ===//
			switch (x_type) {
				case Element::BINARY8: {
					//==  BINARY8 - BINARY8  ==//
					uint8_t byte_y = GET_BYTE_DATA(p_ey);
					uint8_t byte_x = GET_BYTE_DATA(p_ex);
					p_etemp = GEN_BYTE(byte_y - byte_x);
					break;
				}
				case Element::BINARY16: {
					//==  BINARY8 - BINARY16  ==//
					uint8_t byte_y = GET_BYTE_DATA(p_ey);
					uint16_t word_x = GET_WORD_DATA(p_ex);
					p_etemp = GEN_WORD(byte_y - word_x);
					break;
				}
				case Element::BINARY32: {
					//==  BINARY8 - BINARY32  ==//
					uint8_t byte_y = GET_BYTE_DATA(p_ey);
					uint32_t dword_x = GET_DWORD_DATA(p_ex);
					p_etemp = GEN_DWORD(byte_y - dword_x);
					break;
				}
				case Element::BINARY64: {
					//==  BINARY8 - BINARY64  ==//
					uint8_t byte_y = GET_BYTE_DATA(p_ey);
					uint64_t qword_x = GET_QWORD_DATA(p_ex);
					p_etemp = GEN_QWORD(byte_y - qword_x);
					break;
				}
				default:
					//==  BINARY8 - Unexpected  ==//
					throw BadArgument("BAD_TYPE", __FUNCTION__);
			}
			break;
		case Element::BINARY16:
			//===  BINARY16 - ???  ===//
			switch (x_type) {
				case Element::BINARY8: {
					//==  BINARY16 - BINARY8  ==//
					uint16_t word_y = GET_WORD_DATA(p_ey);
					uint8_t byte_x = GET_BYTE_DATA(p_ex);
					p_etemp = GEN_WORD(word_y - byte_x);
					break;
				}
				case Element::BINARY16: {
					//==  BINARY16 - BINARY16  ==//
					uint16_t word_y = GET_WORD_DATA(p_ey);
					uint16_t word_x = GET_WORD_DATA(p_ex);
					p_etemp = GEN_WORD(word_y - word_x);
					break;
				}
				case Element::BINARY32: {
					//==  BINARY16 - BINARY32  ==//
					uint16_t word_y = GET_WORD_DATA(p_ey);
					uint32_t dword_x = GET_DWORD_DATA(p_ex);
					p_etemp = GEN_DWORD(word_y - dword_x);
					break;
				}
				case Element::BINARY64: {
					//==  BINARY16 - BINARY64  ==//
					uint16_t word_y = GET_WORD_DATA(p_ey);
					uint64_t qword_x = GET_QWORD_DATA(p_ex);
					p_etemp = GEN_QWORD(word_y - qword_x);
					break;
				}
				default:
					//==  BINARY16 - Unexpected  ==//
					throw BadArgument("BAD_TYPE", __FUNCTION__);
			}
			break;
		case Element::BINARY32:
			//===  BINARY32 - ???  ===//
			switch (x_type) {
				case Element::BINARY8: {
					//==  BINARY32 - BINARY8  ==//
					uint32_t dword_y = GET_DWORD_DATA(p_ey);
					uint8_t byte_x = GET_BYTE_DATA(p_ex);
					p_etemp = GEN_DWORD(dword_y - byte_x);
					break;
				}
				case Element::BINARY16: {
					//==  BINARY32 - BINARY16  ==//
					uint32_t dword_y = GET_DWORD_DATA(p_ey);
					uint16_t word_x = GET_WORD_DATA(p_ex);
					p_etemp = GEN_DWORD(dword_y - word_x);
					break;
				}
				case Element::BINARY32: {
					//==  BINARY32 - BINARY32  ==//
					uint32_t dword_y = GET_DWORD_DATA(p_ey);
					uint32_t dword_x = GET_DWORD_DATA(p_ex);
					p_etemp = GEN_DWORD(dword_y - dword_x);
					break;
				}
				case Element::BINARY64: {
					//==  BINARY32 - BINARY64  ==//
					uint32_t dword_y = GET_DWORD_DATA(p_ey);
					uint64_t qword_x = GET_QWORD_DATA(p_ex);
					p_etemp = GEN_QWORD(dword_y - qword_x);
					break;
				}
				default:
					//==  BINARY32 - Unexpected  ==//
					throw BadArgument("BAD_TYPE", __FUNCTION__);
			}
			break;
		case Element::BINARY64:
			//===  BINARY64 - ???  ===//
			switch (x_type) {
				case Element::BINARY8: {
					//==  BINARY64 - BINARY8  ==//
					uint64_t qword_y = GET_QWORD_DATA(p_ey);
					uint8_t byte_x = GET_BYTE_DATA(p_ex);
					p_etemp = GEN_QWORD(qword_y - byte_x);
					break;
				}
				case Element::BINARY16: {
					//==  BINARY64 - BINARY16  ==//
					uint64_t qword_y = GET_QWORD_DATA(p_ey);
					uint16_t word_x = GET_WORD_DATA(p_ex);
					p_etemp = GEN_QWORD(qword_y - word_x);
					break;
				}
				case Element::BINARY32: {
					//==  BINARY64 - BINARY32  ==//
					uint64_t qword_y = GET_QWORD_DATA(p_ey);
					uint32_t dword_x = GET_DWORD_DATA(p_ex);
					p_etemp = GEN_QWORD(qword_y - dword_x);
					break;
				}
				case Element::BINARY64: {
					//==  BINARY64 - BINARY64  ==//
					uint64_t qword_y = GET_QWORD_DATA(p_ey);
					uint64_t qword_x = GET_QWORD_DATA(p_ex);
					p_etemp = GEN_QWORD(qword_y - qword_x);
					break;
				}
				default:
					//==  BINARY64 - Unexpected  ==//
					throw BadArgument("BAD_TYPE", __FUNCTION__);
			}
			break;
		default:
			//===  Unexpected - ANY  ===//
			throw BadArgument("BAD_TYPE", __FUNCTION__);
	}
	return p_etemp;
}

////==--------------------------------------------------------------------====//
// ECKERT PROCESSOR / MULTIPLY (BINARY)
// [ description ]
// Calculate MULTIPLY
// [ Update ]
// Nov 14, 2016
//====--------------------------------------------------------------------==////
SpElement GeneralProcessor::mulBinary(const SpElement &p_ey, const SpElement &p_ex) {
	//==  NULL POINTER CHECK  ==//
	if ((nullptr == p_ey) || (nullptr == p_ex)) {
		throw TechnicalError("NULLPTR", __FUNCTION__);
	}
	SpElement p_etemp;
	auto y_type = p_ey->getType();
	auto x_type = p_ex->getType();
	switch (y_type) {
		case Element::BOOLEAN:
			//===  BOOLEAN * ???  ===//
			switch (x_type) {
				case Element::BOOLEAN: {
					//==  BOOLEAN * BOOLEAN  ==//
					bool by = GET_BOOLEAN_DATA(p_ey);
					bool bx = GET_BOOLEAN_DATA(p_ex);
					p_etemp = GEN_BOOLEAN(by & bx);
					break;
				}
				default:
					//==  BOOLEAN * Unexpected  ==//
					throw BadArgument("BAD_TYPE", __FUNCTION__);
			}
			break;
		case Element::BINARY8:
			//===  BINARY8 * ???  ===//
			switch (x_type) {
				case Element::BINARY8: {
					//==  BINARY8 * BINARY8  ==//
					uint8_t byte_y = GET_BYTE_DATA(p_ey);
					uint8_t byte_x = GET_BYTE_DATA(p_ex);
					p_etemp = GEN_BYTE(byte_y * byte_x);
					break;
				}
				case Element::BINARY16: {
					//==  BINARY8 * BINARY16  ==//
					uint8_t byte_y = GET_BYTE_DATA(p_ey);
					uint16_t word_x = GET_WORD_DATA(p_ex);
					p_etemp = GEN_WORD(byte_y * word_x);
					break;
				}
				case Element::BINARY32: {
					//==  BINARY8 * BINARY32  ==//
					uint8_t byte_y = GET_BYTE_DATA(p_ey);
					uint32_t dword_x = GET_DWORD_DATA(p_ex);
					p_etemp = GEN_DWORD(byte_y * dword_x);
					break;
				}
				case Element::BINARY64: {
					//==  BINARY8 * BINARY64  ==//
					uint8_t byte_y = GET_BYTE_DATA(p_ey);
					uint64_t qword_x = GET_QWORD_DATA(p_ex);
					p_etemp = GEN_QWORD(byte_y * qword_x);
					break;
				}
				default:
					//==  BINARY8 * Unexpected  ==//
					throw BadArgument("BAD_TYPE", __FUNCTION__);
			}
			break;
		case Element::BINARY16:
			//===  BINARY16 * ???  ===//
			switch (x_type) {
				case Element::BINARY8: {
					//==  BINARY16 * BINARY8  ==//
					uint16_t word_y = GET_WORD_DATA(p_ey);
					uint8_t byte_x = GET_BYTE_DATA(p_ex);
					p_etemp = GEN_WORD(word_y * byte_x);
					break;
				}
				case Element::BINARY16: {
					//==  BINARY16 * BINARY16  ==//
					uint16_t word_y = GET_WORD_DATA(p_ey);
					uint16_t word_x = GET_WORD_DATA(p_ex);
					p_etemp = GEN_WORD(word_y * word_x);
					break;
				}
				case Element::BINARY32: {
					//==  BINARY16 * BINARY32  ==//
					uint16_t word_y = GET_WORD_DATA(p_ey);
					uint32_t dword_x = GET_DWORD_DATA(p_ex);
					p_etemp = GEN_DWORD(word_y * dword_x);
					break;
				}
				case Element::BINARY64: {
					//==  BINARY16 * BINARY64  ==//
					uint16_t word_y = GET_WORD_DATA(p_ey);
					uint64_t qword_x = GET_QWORD_DATA(p_ex);
					p_etemp = GEN_QWORD(word_y * qword_x);
					break;
				}
				default:
					//==  BINARY16 * Unexpected  ==//
					throw BadArgument("BAD_TYPE", __FUNCTION__);
			}
			break;
		case Element::BINARY32:
			//===  BINARY32 * ???  ===//
			switch (x_type) {
				case Element::BINARY8: {
					//==  BINARY32 * BINARY8  ==//
					uint32_t dword_y = GET_DWORD_DATA(p_ey);
					uint8_t byte_x = GET_BYTE_DATA(p_ex);
					p_etemp = GEN_DWORD(dword_y * byte_x);
					break;
				}
				case Element::BINARY16: {
					//==  BINARY32 * BINARY16  ==//
					uint32_t dword_y = GET_DWORD_DATA(p_ey);
					uint16_t word_x = GET_WORD_DATA(p_ex);
					p_etemp = GEN_DWORD(dword_y * word_x);
					break;
				}
				case Element::BINARY32: {
					//==  BINARY32 * BINARY32  ==//
					uint32_t dword_y = GET_DWORD_DATA(p_ey);
					uint32_t dword_x = GET_DWORD_DATA(p_ex);
					p_etemp = GEN_DWORD(dword_y * dword_x);
					break;
				}
				case Element::BINARY64: {
					//==  BINARY32 * BINARY64  ==//
					uint32_t dword_y = GET_DWORD_DATA(p_ey);
					uint64_t qword_x = GET_QWORD_DATA(p_ex);
					p_etemp = GEN_QWORD(dword_y * qword_x);
					break;
				}
				default:
					//==  BINARY32 * Unexpected  ==//
					throw BadArgument("BAD_TYPE", __FUNCTION__);
			}
			break;
		case Element::BINARY64:
			//===  BINARY64 * ???  ===//
			switch (x_type) {
				case Element::BINARY8: {
					//==  BINARY64 * BINARY8  ==//
					uint64_t qword_y = GET_QWORD_DATA(p_ey);
					uint8_t byte_x = GET_BYTE_DATA(p_ex);
					p_etemp = GEN_QWORD(qword_y * byte_x);
					break;
				}
				case Element::BINARY16: {
					//==  BINARY64 * BINARY16  ==//
					uint64_t qword_y = GET_QWORD_DATA(p_ey);
					uint16_t word_x = GET_WORD_DATA(p_ex);
					p_etemp = GEN_QWORD(qword_y * word_x);
					break;
				}
				case Element::BINARY32: {
					//==  BINARY64 * BINARY32  ==//
					uint64_t qword_y = GET_QWORD_DATA(p_ey);
					uint32_t dword_x = GET_DWORD_DATA(p_ex);
					p_etemp = GEN_QWORD(qword_y * dword_x);
					break;
				}
				case Element::BINARY64: {
					//==  BINARY64 * BINARY64  ==//
					uint64_t qword_y = GET_QWORD_DATA(p_ey);
					uint64_t qword_x = GET_QWORD_DATA(p_ex);
					p_etemp = GEN_QWORD(qword_y * qword_x);
					break;
				}
				default:
					//==  BINARY64 * Unexpected  ==//
					throw BadArgument("BAD_TYPE", __FUNCTION__);
			}
			break;
		default:
			//===  Unexpected * ANY  ===//
			throw BadArgument("BAD_TYPE", __FUNCTION__);
	}
	return p_etemp;
}

////==--------------------------------------------------------------------====//
// ECKERT PROCESSOR / UNSIGNED DIVIDE
// [ description ]
// Calculate UNSIGNED DIVIDE
// [ Update ]
// Nov 14, 2016
//====--------------------------------------------------------------------==////
SpElement GeneralProcessor::divBinary(const SpElement &p_ey, const SpElement &p_ex) {
	//==  NULL POINTER CHECK  ==//
	if ((nullptr == p_ey) || (nullptr == p_ex)) {
		throw TechnicalError("NULLPTR", __FUNCTION__);
	}
	SpElement p_etemp;
	auto y_type = p_ey->getType();
	auto x_type = p_ex->getType();
	if (isZero(p_ex)) {
		throw BadArgument("DIV_ZERO", __FUNCTION__);
	}
	switch (y_type) {
		case Element::BINARY8:
			//===  BINARY8 / ???  ===//
			switch (x_type) {
				case Element::BINARY8: {
					//==  BINARY8 / BINARY8  ==//
					uint8_t byte_y = GET_BYTE_DATA(p_ey);
					uint8_t byte_x = GET_BYTE_DATA(p_ex);
					p_etemp = GEN_BYTE(byte_y / byte_x);
					break;
				}
				case Element::BINARY16: {
					//==  BINARY8 / BINARY16  ==//
					uint8_t byte_y = GET_BYTE_DATA(p_ey);
					uint16_t word_x = GET_WORD_DATA(p_ex);
					p_etemp = GEN_WORD(byte_y / word_x);
					break;
				}
				case Element::BINARY32: {
					//==  BINARY8 / BINARY32  ==//
					uint8_t byte_y = GET_BYTE_DATA(p_ey);
					uint32_t dword_x = GET_DWORD_DATA(p_ex);
					p_etemp = GEN_DWORD(byte_y / dword_x);
					break;
				}
				case Element::BINARY64: {
					//==  BINARY8 / BINARY64  ==//
					uint8_t byte_y = GET_BYTE_DATA(p_ey);
					uint64_t qword_x = GET_QWORD_DATA(p_ex);
					p_etemp = GEN_QWORD(byte_y / qword_x);
					break;
				}
				default:
					//==  BINARY8 / Unexpected  ==//
					throw BadArgument("BAD_TYPE", __FUNCTION__);
			}
			break;
		case Element::BINARY16:
			//===  BINARY16 / ???  ===//
			switch (x_type) {
				case Element::BINARY8: {
					//==  BINARY16 / BINARY8  ==//
					uint16_t word_y = GET_WORD_DATA(p_ey);
					uint8_t byte_x = GET_BYTE_DATA(p_ex);
					p_etemp = GEN_WORD(word_y / byte_x);
					break;
				}
				case Element::BINARY16: {
					//==  BINARY16 / BINARY16  ==//
					uint16_t word_y = GET_WORD_DATA(p_ey);
					uint16_t word_x = GET_WORD_DATA(p_ex);
					p_etemp = GEN_WORD(word_y / word_x);
					break;
				}
				case Element::BINARY32: {
					//==  BINARY16 / BINARY32  ==//
					uint16_t word_y = GET_WORD_DATA(p_ey);
					uint32_t dword_x = GET_DWORD_DATA(p_ex);
					p_etemp = GEN_DWORD(word_y / dword_x);
					break;
				}
				case Element::BINARY64: {
					//==  BINARY16 / BINARY64  ==//
					uint16_t word_y = GET_WORD_DATA(p_ey);
					uint64_t qword_x = GET_QWORD_DATA(p_ex);
					p_etemp = GEN_QWORD(word_y / qword_x);
					break;
				}
				default:
					//==  BINARY16 / Unexpected  ==// 
					throw BadArgument("BAD_TYPE", __FUNCTION__);
			}
			break;
		case Element::BINARY32:
			//===  BINARY32 / ???  ===//
			switch (x_type) {
				case Element::BINARY8: {
					//==  BINARY32 / BINARY8 ==//
					uint32_t dword_y = GET_DWORD_DATA(p_ey);
					uint8_t byte_x = GET_BYTE_DATA(p_ex);
					p_etemp = GEN_DWORD(dword_y / byte_x);
					break;
				}
				case Element::BINARY16: {
					//==  BINARY32 / BINARY16  ==//
					uint32_t dword_y = GET_DWORD_DATA(p_ey);
					uint16_t word_x = GET_WORD_DATA(p_ex);
					p_etemp = GEN_DWORD(dword_y / word_x);
					break;
				}
				case Element::BINARY32: {
					//==  BINARY32 / BINARY32  ==//
					uint32_t dword_y = GET_DWORD_DATA(p_ey);
					uint32_t dword_x = GET_DWORD_DATA(p_ex);
					p_etemp = GEN_DWORD(dword_y / dword_x);
					break;
				}
				case Element::BINARY64: {
					//==  BINARY32 / BINARY64  ==//
					uint32_t dword_y = GET_DWORD_DATA(p_ey);
					uint64_t qword_x = GET_QWORD_DATA(p_ex);
					p_etemp = GEN_QWORD(dword_y / qword_x);
					break;
				}
				default:
					//==  BINARY32 / Unexpected  ==//
					throw BadArgument("BAD_TYPE", __FUNCTION__);
			}
			break;
		case Element::BINARY64:
			//===  BINARY64 / ???  ===//
			switch (x_type) {
				case Element::BINARY8: {
					//==  BINARY64 / BINARY8  ==//
					uint64_t qword_y = GET_QWORD_DATA(p_ey);
					uint8_t byte_x = GET_BYTE_DATA(p_ex);
					p_etemp = GEN_QWORD(qword_y / byte_x);
					break;
				}
				case Element::BINARY16: {
					//==  BINARY64 / BINARY16  ==//
					uint64_t qword_y = GET_QWORD_DATA(p_ey);
					uint16_t word_x = GET_WORD_DATA(p_ex);
					p_etemp = GEN_QWORD(qword_y / word_x);
					break;
				}
				case Element::BINARY32: {
					//==  BINARY64 / BINARY32  ==//
					uint64_t qword_y = GET_QWORD_DATA(p_ey);
					uint32_t dword_x = GET_DWORD_DATA(p_ex);
					p_etemp = GEN_QWORD(qword_y / dword_x);
					break;
				}
				case Element::BINARY64: {
					//==  BINARY64 / BINARY64  ==//
					uint64_t qword_y = GET_QWORD_DATA(p_ey);
					uint64_t qword_x = GET_QWORD_DATA(p_ex);
					p_etemp = GEN_QWORD(qword_y / qword_x);
					break;
				}
				default:
					//==  BINARY64 / Unexpected  ==//
					throw BadArgument("BAD_TYPE", __FUNCTION__);
			}
			break;
		default:
			//===  Unexpected / ANY  ===//
			throw BadArgument("BAD_TYPE", __FUNCTION__);
	}
	return p_etemp;
}

} // namespace engine
