#include "GeneralProcessor.h"

namespace engine {

////==--------------------------------------------------------------------====//
// ECKERT PROCESSOR / SHIFT LOGICAL LEFT
// [ description ]
// Calculate SHIFT LOGICAL LEFT
// [ Update ]
// Nov 17, 2016
//====--------------------------------------------------------------------==////
SpElement GeneralProcessor::shiftLeft(const SpElement &p_ex) {
	//==  NULL POINTER CHECK  ==//
	if (nullptr == p_ex) {
		throw TechnicalError("NULLPTR", __FUNCTION__);
	}
	SpElement p_etemp;
	switch (p_ex->getType()) {
		case Element::BINARY8: {
			//==  shl(BINARY8)  ==//
			uint8_t byte_x = GET_BYTE_DATA(p_ex);
			p_etemp = GEN_BYTE(byte_x << 1);
			break;
		}
		case Element::BINARY16: {
			//==  shl(BINARY16)  ==//
			uint16_t word_x = GET_WORD_DATA(p_ex);
			p_etemp = GEN_WORD(word_x << 1);
			break;
		}
		case Element::BINARY32: {
			//==  shl(BINARY32)  ==//
			uint32_t dword_x = GET_DWORD_DATA(p_ex);
			p_etemp = GEN_DWORD(dword_x << 1);
			break;
		}
		case Element::BINARY64: {
			//==  shl(BINARY64)  ==//
			uint64_t qword_x = GET_QWORD_DATA(p_ex);
			p_etemp = GEN_QWORD(qword_x << 1);
			break;
		}
		default:
			//==  shl(Unexpected)  ==//
			throw BadArgument("BAD_TYPE", __FUNCTION__);
	}
	return p_etemp;
}

////==--------------------------------------------------------------------====//
// ECKERT PROCESSOR / SHIFT LOGICAL RIGHT
// [ description ]
// Calculate SHIFT LOGICAL RIGHT
// [ Update ]
// Nov 17, 2016
//====--------------------------------------------------------------------==////
SpElement GeneralProcessor::shiftRight(const SpElement &p_ex) {
	//==  NULL POINTER CHECK  ==//
	if (nullptr == p_ex) {
		throw TechnicalError("NULLPTR", __FUNCTION__);
	}
	SpElement p_etemp;
	switch (p_ex->getType()) {
		case Element::BINARY8: {
			//==  shr(BINARY8)  ==//
			uint8_t byte_x = GET_BYTE_DATA(p_ex);
			p_etemp = GEN_BYTE(byte_x >> 1);
			break;
		}
		case Element::BINARY16: {
			//==  shr(BINARY16)  ==//
			uint16_t word_x = GET_WORD_DATA(p_ex);
			p_etemp = GEN_WORD(word_x >> 1);
			break;
		}
		case Element::BINARY32: {
			//==  shr(BINARY32)  ==//
			uint32_t dword_x = GET_DWORD_DATA(p_ex);
			p_etemp = GEN_DWORD(dword_x >> 1);
			break;
		}
		case Element::BINARY64: {
			//==  shr(BINARY64)  ==//
			uint64_t qword_x = GET_QWORD_DATA(p_ex);
			p_etemp = GEN_QWORD(qword_x >> 1);
			break;
		}
		default:
			//==  shr(Unexpected)  ==//
			throw BadArgument("BAD_TYPE", __FUNCTION__);
	}
	return p_etemp;
}

////==--------------------------------------------------------------------====//
// ECKERT PROCESSOR / SHIFT ARITHMETIC RIGHT
// [ description ]
// Calculate SHIFT ARITHMETIC RIGHT
// [ Update ]
// Nov 17, 2016
//====--------------------------------------------------------------------==////
SpElement GeneralProcessor::shiftArithmeticRight(const SpElement &p_ex) {
	//==  NULL POINTER CHECK  ==//
	if (nullptr == p_ex) {
		throw TechnicalError("NULLPTR", __FUNCTION__);
	}
	SpElement p_etemp;
	switch (p_ex->getType()) {
		case Element::BINARY8: {
			//==  sar(BINARY8)  ==//
			uint8_t byte_x = GET_BYTE_DATA(p_ex);
			uint8_t pos = 1u << (sizeof(pos) * 8 - 1);
			if (pos & byte_x) {
				p_etemp = GEN_BYTE((byte_x >> 1) | pos);
			}
			else {
				p_etemp = GEN_BYTE(byte_x >> 1);
			}
			break;
		}
		case Element::BINARY16: {
			//==  sar(BINARY16)  ==//
			uint16_t word_x = GET_WORD_DATA(p_ex);
			uint16_t pos = 1u << (sizeof(pos) * 8 - 1);
			if (pos & word_x) {
				p_etemp = GEN_WORD((word_x >> 1) | pos);
			}
			else {
				p_etemp = GEN_WORD(word_x >> 1);
			}
			break;
		}
		case Element::BINARY32: {
			//==  sar(BINARY32)  ==//
			uint32_t dword_x = GET_DWORD_DATA(p_ex);
			uint32_t pos = 1u << (sizeof(pos) * 8 - 1);
			if (pos & dword_x) {
				p_etemp = GEN_DWORD((dword_x >> 1) | pos);
			}
			else {
				p_etemp = GEN_DWORD(dword_x >> 1);
			}
			break;
		}
		case Element::BINARY64: {
			//==  sar(BINARY64)  ==//
			uint64_t qword_x = GET_QWORD_DATA(p_ex);
			uint64_t pos = 1u;
			pos <<= (sizeof(pos) * 8 - 1);
			if (pos & qword_x) {
				p_etemp = GEN_QWORD((qword_x >> 1) | pos);
			}
			else {
				p_etemp = GEN_QWORD(qword_x >> 1);
			}
			break;
		}
		default:
			//==  sar(Unexpected)  ==//
			throw BadArgument("BAD_TYPE", __FUNCTION__);
	}
	return p_etemp;
}

////==--------------------------------------------------------------------====//
// ECKERT PROCESSOR / SHIFT NIBBLE LEFT
// [ description ]
// Calculate SHIFT NIBBLE LEFT
// [ Update ]
// Nov 17, 2016
//====--------------------------------------------------------------------==////
SpElement GeneralProcessor::shiftNibbleLeft(const SpElement &p_ex) {
	//==  NULL POINTER CHECK  ==//
	if (nullptr == p_ex) {
		throw TechnicalError("NULLPTR", __FUNCTION__);
	}
	SpElement p_etemp;
	switch (p_ex->getType()) {
		case Element::BINARY8: {
			//==  snl(BINARY8)  ==//
			uint8_t byte_x = GET_BYTE_DATA(p_ex);
			p_etemp = GEN_BYTE(byte_x << 4);
			break;
		}
		case Element::BINARY16: {
			//==  snl(BINARY16)  ==//
			uint16_t word_x = GET_WORD_DATA(p_ex);
			p_etemp = GEN_WORD(word_x << 4);
			break;
		}
		case Element::BINARY32: {
			//==  snl(BINARY32)  ==//
			uint32_t dword_x = GET_DWORD_DATA(p_ex);
			p_etemp = GEN_DWORD(dword_x << 4);
			break;
		}
		case Element::BINARY64: {
			//==  snl(BINARY64)  ==//
			uint64_t qword_x = GET_QWORD_DATA(p_ex);
			p_etemp = GEN_QWORD(qword_x << 4);
			break;
		}
		default:
			//==  snl(Unexpected)  ==//
			throw BadArgument("BAD_TYPE", __FUNCTION__);
	}
	return p_etemp;
}

////==--------------------------------------------------------------------====//
// ECKERT PROCESSOR / SHIFT NIBBLE RIGHT
// [ description ]
// Calculate SHIFT NIBBLE RIGHT
// [ Update ]
// Nov 17, 2016
//====--------------------------------------------------------------------==////
SpElement GeneralProcessor::shiftNibbleRight(const SpElement &p_ex) {
	//==  NULL POINTER CHECK  ==//
	if (nullptr == p_ex) {
		throw TechnicalError("NULLPTR", __FUNCTION__);
	}
	SpElement p_etemp;
	switch (p_ex->getType()) {
		case Element::BINARY8: {
			//==  snr(BINARY8)  ==//
			uint8_t byte_x = GET_BYTE_DATA(p_ex);
			p_etemp = GEN_BYTE(byte_x >> 4);
			break;
		}
		case Element::BINARY16: {
			//==  snr(BINARY16)  ==//
			uint16_t word_x = GET_WORD_DATA(p_ex);
			p_etemp = GEN_WORD(word_x >> 4);
			break;
		}
		case Element::BINARY32: {
			//==  snr(BINARY32)  ==//
			uint32_t dword_x = GET_DWORD_DATA(p_ex);
			p_etemp = GEN_DWORD(dword_x >> 4);
			break;
		}
		case Element::BINARY64: {
			//==  snr(BINARY64)  ==//
			uint64_t qword_x = GET_QWORD_DATA(p_ex);
			p_etemp = GEN_QWORD(qword_x >> 4);
			break;
		}
		default:
			//==  snr(Unexpected)  ==//
			throw BadArgument("BAD_TYPE", __FUNCTION__);
	}
	return p_etemp;
}

////==--------------------------------------------------------------------====//
// ECKERT PROCESSOR / SHIFT BYTE LEFT
// [ description ]
// Calculate SHIFT BYTE LEFT
// [ Update ]
// Nov 17, 2016
//====--------------------------------------------------------------------==////
SpElement GeneralProcessor::shiftByteLeft(const SpElement &p_ex) {
	//==  NULL POINTER CHECK  ==//
	if (nullptr == p_ex) {
		throw TechnicalError("NULLPTR", __FUNCTION__);
	}
	SpElement p_etemp;
	switch (p_ex->getType()) {
		case Element::BINARY8: {
			//==  sbl(BINARY8)  ==//
			p_etemp = GEN_BYTE(0);
			break;
		}
		case Element::BINARY16: {
			//==  sbl(BINARY16)  ==//
			uint16_t word_x = GET_WORD_DATA(p_ex);
			p_etemp = GEN_WORD(word_x << 8);
			break;
		}
		case Element::BINARY32: {
			//==  sbl(BINARY32)  ==//
			uint32_t dword_x = GET_DWORD_DATA(p_ex);
			p_etemp = GEN_DWORD(dword_x << 8);
			break;
		}
		case Element::BINARY64: {
			//==  sbl(BINARY64)  ==//
			uint64_t qword_x = GET_QWORD_DATA(p_ex);
			p_etemp = GEN_QWORD(qword_x << 8);
			break;
		}
		default:
			//==  sbl(Unexpected)  ==//
			throw BadArgument("BAD_TYPE", __FUNCTION__);
	}
	return p_etemp;
}

////==--------------------------------------------------------------------====//
// ECKERT PROCESSOR / SHIFT BYTE RIGHT
// [ description ]
// Calculate SHIFT BYTE RIGHT
// [ Update ]
// Nov 17, 2016
//====--------------------------------------------------------------------==////
SpElement GeneralProcessor::shiftByteRight(const SpElement &p_ex) {
	//==  NULL POINTER CHECK  ==//
	if (nullptr == p_ex) {
		throw TechnicalError("NULLPTR", __FUNCTION__);
	}
	SpElement p_etemp;
	switch (p_ex->getType()) {
		case Element::BINARY8: {
			//==  sbr(BINARY8)  ==//
			p_etemp = GEN_BYTE(0);
			break;
		}
		case Element::BINARY16: {
			//==  sbr(BINARY16)  ==//
			uint16_t word_x = GET_WORD_DATA(p_ex);
			p_etemp = GEN_WORD(word_x >> 8);
			break;
		}
		case Element::BINARY32: {
			//==  sbr(BINARY32)  ==//
			uint32_t dword_x = GET_DWORD_DATA(p_ex);
			p_etemp = GEN_DWORD(dword_x >> 8);
			break;
		}
		case Element::BINARY64: {
			//==  sbr(BINARY64)  ==//
			uint64_t qword_x = GET_QWORD_DATA(p_ex);
			p_etemp = GEN_QWORD(qword_x >> 8);
			break;
		}
		default:
			//==  sbr(Unexpected)  ==//
			throw BadArgument("BAD_TYPE", __FUNCTION__);
	}
	return p_etemp;
}

////==--------------------------------------------------------------------====//
// ECKERT PROCESSOR / ROTATE LEFT
// [ description ]
// Calculate ROTATE LEFT
// [ Update ]
// Nov 17, 2016
//====--------------------------------------------------------------------==////
SpElement GeneralProcessor::rotateLeft(const SpElement &p_ex) {
	//==  NULL POINTER CHECK  ==//
	if (nullptr == p_ex) {
		throw TechnicalError("NULLPTR", __FUNCTION__);
	}
	SpElement p_etemp;
	switch (p_ex->getType()) {
		case Element::BINARY8: {
			//==  rol(BINARY8)  ==//
			uint8_t byte_x = GET_BYTE_DATA(p_ex);
			uint8_t pos = 1u << (sizeof(pos) * 8 - 1);
			if (pos & byte_x) {
				p_etemp = GEN_BYTE((byte_x << 1) | 0x01);
			}
			else {
				p_etemp = GEN_BYTE(byte_x << 1);
			}
			break;
		}
		case Element::BINARY16: {
			//==  rol(BINARY16)  ==//
			uint16_t word_x = GET_WORD_DATA(p_ex);
			uint16_t pos = 1u << (sizeof(pos) * 8 - 1);
			if (pos & word_x) {
				p_etemp = GEN_WORD((word_x << 1) | 0x01);
			}
			else {
				p_etemp = GEN_WORD(word_x << 1);
			}
			break;
		}
		case Element::BINARY32: {
			//==  rol(BINARY32)  ==//
			uint32_t dword_x = GET_DWORD_DATA(p_ex);
			uint32_t pos = 1u << (sizeof(pos) * 8 - 1);
			if (pos & dword_x) {
				p_etemp = GEN_DWORD((dword_x << 1) | 0x01);
			}
			else {
				p_etemp = GEN_DWORD(dword_x << 1);
			}
			break;
		}
		case Element::BINARY64: {
			//==  rol(BINARY64)  ==//
			uint64_t qword_x = GET_QWORD_DATA(p_ex);
			uint64_t pos = 1u;
			pos <<= (sizeof(pos) * 8 - 1);
			if (pos & qword_x) {
				p_etemp = GEN_QWORD((qword_x << 1) | 0x01);
			}
			else {
				p_etemp = GEN_QWORD(qword_x << 1);
			}
			break;
		}
		default:
			//==  rol(Unexpected)  ==//
			throw BadArgument("BAD_TYPE", __FUNCTION__);
	}
	return p_etemp;
}

////==--------------------------------------------------------------------====//
// ECKERT PROCESSOR / ROTATE RIGHT
// [ description ]
// Calculate ROTATE RIGHT
// [ Update ]
// Nov 17, 2016
//====--------------------------------------------------------------------==////
SpElement GeneralProcessor::rotateRight(const SpElement &p_ex) {
	//==  NULL POINTER CHECK  ==//
	if (nullptr == p_ex) {
		throw TechnicalError("NULLPTR", __FUNCTION__);
	}
	SpElement p_etemp;
	switch (p_ex->getType()) {
		case Element::BINARY8: {
			//==  ror(BINARY8)  ==//
			uint8_t byte_x = GET_BYTE_DATA(p_ex);
			uint8_t pos = 1u << (sizeof(pos) * 8 - 1);
			if (0x01 & byte_x) {
				p_etemp = GEN_BYTE((byte_x >> 1) | pos);
			}
			else {
				p_etemp = GEN_BYTE(byte_x >> 1);
			}
			break;
		}
		case Element::BINARY16: {
			//==  ror(BINARY16)  ==//
			uint16_t word_x = GET_WORD_DATA(p_ex);
			uint16_t pos = 1u << (sizeof(pos) * 8 - 1);
			if (0x01 & word_x) {
				p_etemp = GEN_WORD((word_x >> 1) | pos);
			}
			else {
				p_etemp = GEN_WORD(word_x >> 1);
			}
			break;
		}
		case Element::BINARY32: {
			//==  ror(BINARY32)  ==//
			uint32_t dword_x = GET_DWORD_DATA(p_ex);
			uint32_t pos = 1u << (sizeof(pos) * 8 - 1);
			if (0x01 & dword_x) {
				p_etemp = GEN_DWORD((dword_x >> 1) | pos);
			}
			else {
				p_etemp = GEN_DWORD(dword_x >> 1);
			}
			break;
		}
		case Element::BINARY64: {
			//==  ror(BINARY64)  ==//
			uint64_t qword_x = GET_QWORD_DATA(p_ex);
			uint64_t pos = 1u;
			pos <<= (sizeof(pos) * 8 - 1);
			if (0x01 & qword_x) {
				p_etemp = GEN_QWORD((qword_x >> 1) | pos);
			}
			else {
				p_etemp = GEN_QWORD(qword_x >> 1);
			}
			break;
		}
		default:
			//==  ror(Unexpected)  ==//
			throw BadArgument("BAD_TYPE", __FUNCTION__);
	}
	return p_etemp;
}

} // namespace engine
