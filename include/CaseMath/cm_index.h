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
#include <utility>
#include <array>
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
		std::array<size_t, N> arr{ static_cast<size_t>(args)... };

		for (size_t i = 0; i < N; ++i) {
			if (arr[i] >= N) return Sign::Zero;
			for (size_t j = i+1; j < N; ++j) {
				if (arr[i] == arr[j])
					return Sign::Zero;
			}
		}

		Sign sign = Sign::Positive;

		for (size_t i = 0; i < N; ++i) {
			for (size_t j = i+1; j < N; ++j) {
				if (arr[i] > arr[j]) sign.flip();
			}
		}

		return sign;
		
	}
}