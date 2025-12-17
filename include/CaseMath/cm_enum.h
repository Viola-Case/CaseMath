/**

    @file      cm_enum.h
    @brief     
    @details   ~
    @author    Viola Case
    @date      11.12.2025
    @copyright © Viola Case, 2025.

**/
#pragma once

#include <cstdint>

namespace CaseMath {
	struct Sign {
		enum Value : int8_t { Negative = -1, Zero = 0, Positive = 1 } value;
		constexpr Sign(Value v) : value(v) {}
		constexpr Sign(float i) : value((i == 0 ? Value::Zero : (i > 0 ? Value::Positive : Value::Negative))) {}
		constexpr operator int8_t() const noexcept { return static_cast<int8_t>(value); }
		constexpr Sign& flip() noexcept { 
			switch (value) {
			case Positive: value = Negative; break;
			case Negative: value = Positive; break;
			default: break; }
			return *this; 
		}
		constexpr Sign inverse() const noexcept {
			return Sign(*this).flip();
		}
	};

	constexpr Sign SignOf(float num) noexcept {
		return	(num > 0.f ? Sign::Positive :
			(num < 0.f ? Sign::Negative : Sign::Zero));
	}

	constexpr bool IsPositive(const Sign s, bool incZero = true) noexcept {
		return (s == Sign::Positive) || (incZero && s == Sign::Zero);
	}

	constexpr Sign Inverse(Sign _s) { return _s.inverse(); }
}