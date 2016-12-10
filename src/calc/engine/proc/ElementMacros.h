////==--------------------------------------------------------------------====//
// ECKERT ELEMENT MACROS
//====--------------------------------------------------------------------==////

#ifndef _ELEMENT_MACROS_H_
#define _ELEMENT_MACROS_H_

#include "base/Element.h"

#define IS_NUMERIC(ptr) \
  (ptr->isKindOf(engine::Element::NUMERIC_TYPE))
#define IS_SCALAR(ptr) \
  (ptr->isKindOf(engine::Element::SCALAR_TYPE))
#define IS_SET(ptr) \
  (ptr->isKindOf(engine::Element::SET_TYPE))
#define IS_BINARY(ptr) \
  (ptr->isKindOf(engine::Element::BINARY_TYPE))

#include "base/ElementError.h"
#include "base/ElementEString.h"

// Caster
#define CAST_INTO_ERROR(ptr) \
  (std::dynamic_pointer_cast<engine::Error>(ptr))
#define CAST_INTO_ESTRING(ptr) \
  (std::dynamic_pointer_cast<engine::EString>(ptr))

// Getter
#define GET_ERROR_DATA(ptr) \
  (CAST_INTO_ERROR(ptr)->get())
#define GET_ESTRING_DATA(ptr) \
  (CAST_INTO_ESTRING(ptr)->get())

// Generator
#define GEN_ERROR(str) \
	(engine::SpElement(new engine::Error(str)))
#define GEN_ESTRING(str) \
	(engine::SpElement(new engine::EString(str)))

#include "base/ElementInteger.h"
#include "base/ElementUInteger.h"
#include "base/ElementFloating.h"
#include "base/ElementRational.h"
#include "base/ElementEInfinity.h"
#include "base/ElementComplex.h"

// Caster
#define CAST_INTO_INTEGER(ptr) \
  (std::dynamic_pointer_cast<engine::Integer>(ptr))
#define CAST_INTO_FLOATING(ptr) \
  (std::dynamic_pointer_cast<engine::Floating>(ptr))
#define CAST_INTO_RATIONAL(ptr) \
  (std::dynamic_pointer_cast<engine::Rational>(ptr))
#define CAST_INTO_EINFINITY(ptr) \
  (std::dynamic_pointer_cast<engine::EInfinity>(ptr))
#define CAST_INTO_COMPLEX(ptr) \
  (std::dynamic_pointer_cast<engine::Complex>(ptr))

// Getter
#define GET_INTEGER_DATA(ptr) \
  (CAST_INTO_INTEGER(ptr)->get())
#define GET_FLOATING_DATA(ptr) \
  (CAST_INTO_FLOATING(ptr)->get())
#define GET_RATIONAL_DATA(ptr) \
  (CAST_INTO_RATIONAL(ptr)->get())
#define GET_EINFINITY_DATA(ptr) \
  (CAST_INTO_EINFINITY(ptr)->get())
#define GET_COMPLEX_RE(ptr) \
  (CAST_INTO_COMPLEX(ptr)->getRe())
#define GET_COMPLEX_IM(ptr) \
  (CAST_INTO_COMPLEX(ptr)->getIm())

// Generator
#define GEN_INTEGER(num) \
  (engine::SpElement(new engine::Integer(num)))
#define GEN_FLOATING(num) \
  (engine::SpElement(new engine::Floating(num)))
#define GEN_RATIONAL(num) \
  (engine::SpElement(new engine::Rational(num)))
#define GEN_RATIONAL2(num, den) \
  (engine::SpElement(new engine::Rational(num, den)))
#define GEN_EINFINITY(num)\
  (engine::SpElement(new engine::EInfinity(num)))
#define GEN_COMPLEX(re, im) \
  (engine::SpElement(new engine::Complex(re, im)))
#define POS_IMAGINARY \
  (engine::SpElement(new engine::Complex(GEN_INTEGER(0), GEN_INTEGER(+1))))
#define NEG_IMAGINARY \
  (engine::SpElement(new engine::Complex(GEN_INTEGER(0), GEN_INTEGER(-1))))

#include "base/ElementETuple.h"
#include "base/ElementMatrix.h"

// Caster
#define CAST_INTO_ETUPLE(ptr) \
  (std::dynamic_pointer_cast<engine::ETuple>(ptr))
#define CAST_INTO_MATRIX(ptr) \
  (std::dynamic_pointer_cast<engine::Matrix>(ptr))

// Getter
#define GET_ETUPLE_RAW(ptr) \
  (CAST_INTO_ETUPLE(ptr)->getVector())
#define GET_ETUPLE_DATA(ptr, i) \
  (CAST_INTO_ETUPLE(ptr)->get(i))
#define GET_ETUPLE_SIZE(ptr) \
  (CAST_INTO_ETUPLE(ptr)->getSize())
#define GET_ETUPLE_TYPE(ptr) \
  (CAST_INTO_ETUPLE(ptr)->getTupleType())
#define GET_MATRIX_RAW(ptr) \
  (CAST_INTO_MATRIX(ptr)->getMatrix())
#define GET_MATRIX_DATA(ptr, i, j) \
  (CAST_INTO_MATRIX(ptr)->get(i, j))
#define GET_MATRIX_SIZE_M(ptr) \
  (CAST_INTO_MATRIX(ptr)->getM())
#define GET_MATRIX_SIZE_N(ptr) \
  (CAST_INTO_MATRIX(ptr)->getN())

// Generator
#define GEN_ETUPLE(set) \
  (engine::SpElement(new engine::ETuple(set, engine::ETuple::TupleType::ROW)))
#define GEN_ETUPLE2(set, type) \
  (engine::SpElement(new engine::ETuple(set, type)))
#define GEN_MATRIX(mat) \
  (engine::SpElement(new engine::Matrix(mat)))

#include "base/ElementBoolean.h"
#include "base/ElementBinary8.h"
#include "base/ElementBinary16.h"
#include "base/ElementBinary32.h"
#include "base/ElementBinary64.h"

// Caster
#define CAST_INTO_BOOLEAN(ptr) \
  (std::dynamic_pointer_cast<engine::Boolean>(ptr))
#define CAST_INTO_BYTE(ptr) \
  (std::dynamic_pointer_cast<engine::Binary8>(ptr))
#define CAST_INTO_WORD(ptr) \
  (std::dynamic_pointer_cast<engine::Binary16>(ptr))
#define CAST_INTO_DWORD(ptr) \
  (std::dynamic_pointer_cast<engine::Binary32>(ptr))
#define CAST_INTO_QWORD(ptr) \
  (std::dynamic_pointer_cast<engine::Binary64>(ptr))

// Getter
#define GET_BOOLEAN_DATA(ptr) \
  (CAST_INTO_BOOLEAN(ptr)->get())
#define GET_BYTE_DATA(ptr) \
  (CAST_INTO_BYTE(ptr)->get())
#define GET_WORD_DATA(ptr) \
  (CAST_INTO_WORD(ptr)->get())
#define GET_DWORD_DATA(ptr) \
  (CAST_INTO_DWORD(ptr)->get())
#define GET_QWORD_DATA(ptr) \
  (CAST_INTO_QWORD(ptr)->get())

// Generator
#define GEN_BOOLEAN(flag) \
	(engine::SpElement(new engine::Boolean(flag)))
#define GEN_BYTE(num) \
	(engine::SpElement(new engine::Binary8(num)))
#define GEN_WORD(num) \
	(engine::SpElement(new engine::Binary16(num)))
#define GEN_DWORD(num) \
	(engine::SpElement(new engine::Binary32(num)))
#define GEN_QWORD(num) \
	(engine::SpElement(new engine::Binary64(num)))

#endif // ifndef _ELEMENT_MACROS_H_
