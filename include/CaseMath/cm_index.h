/**

    @file      cm_index.h
    @brief     
    @details   ~
    @author    Viola Case
    @date      11.12.2025
    @copyright © Viola Case, 2025.

**/
#pragma once

#include <cstdint>
#include "cm_typetraits.h"
#include "cm_enum.h"

namespace CaseMath {
	template <typename T> requires std::is_convertible_v<T, long long>
	constexpr bool KDelta(T _a, T _b) {
		return (_a == _b);
	}

	template <typename... Args> requires (std::is_convertible_v<Args, size_t> && ...)
	constexpr Sign LeviCivita(Args... args) {
		constexpr size_t N = sizeof...(Args);  //!< @TODO make sure this is not size-dependent
		size_t arr[N] = { args... };

		size_t maxval = 0;
		for (size_t i = 0; i < N; ++i) {
			if (arr[i] > maxval) maxval = arr[i];
		}
		if (maxval != N - 1) return Sign::Zero;

		int sign = 1;
		for (size_t i = 0; i < N; ++i) {
			for (size_t j = i + 1; j < N; ++j) {
				if (arr[i] > arr[j]) sign = -sign;
			}
		}

		return (sign == 1 ? Sign::Positive : Sign::Negative);
	}
}