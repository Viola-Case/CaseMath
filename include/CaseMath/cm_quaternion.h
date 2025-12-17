/**

    @file      cm_quaternion.h
    @brief     
    @details   ~
    @author    Viola Case
    @date      13.12.2025
    @copyright © Viola Case, 2025.

**/
#pragma once
#include "cm_complex.h"
#include "cm_vector.h"
#include "cm_index.h"
namespace CaseMath {
	template <StdScalar T>
		requires std::is_signed_v<T>
	struct Quat {
		union {
			struct {
				T w, x, y, z;
			};
			struct {
				Comp<T> c;
				T y, z;
			};
			Vec4<T> vec;
			T data[4];
		};
		
		constexpr Quat() noexcept : w(T{1}), x(T{}), y(T{}), z(T{}) {}
		constexpr Quat(T _w, T _x = T{}, T _y = T{}, T _z = T{}) noexcept : w(_w), x(_x), y(_y), z(_z) {}
		constexpr Quat(Comp<T> _c, T _y = T{}, T _z = T{}) noexcept : c(_c), y(_y), z(_z) {}

		constexpr Quat& operator*=(const Quat &rhs) noexcept {
			T a[4]{ w, x, y, z };
			T b[4]{ rhs.w, rhs.x, rhs.y, rhs.z };

			w = a[0] * b[0];
			for (int i = 1; i <= 3; ++i)
				for (int j = 1; j <= 3; ++j)
					w -= a[i] * b[j] * KDelta(i, j);

			for (int k = 1; k <= 3; ++k) {
				data[k] = a[0] * b[k] + b[0] * a[k];

				for (int i = 1; i <= 3; ++i)
					for (int j = 1; j <= 3; ++j)
						data[k] += LeviCivita(k, i, j) * a[i] * b[j];
			}

			return *this;
		}

		template<StdScalar U>
			requires std::is_signed_v<U> && !(std::is_same_v<T, U>)
		constexpr operator Quat() const noexcept {
			return Quat<U>(static_cast<U>(w), static_cast<U>(x), static_cast<U>(y), static_cast<U>(z));
		}

		constexpr operator Comp() const noexcept {
			return c;
		}

		constexpr Quat operator*(const Quat &rhs) const noexcept {
			return (Quat(*this) *= rhs);
		}

	};


	constexpr Quat<long double> operator"" _j(long double v) noexcept {
		return { 0, 0, v, 0 };
	}
	constexpr Quat<long double> operator"" _k(long double v) noexcept {
		return { 0, 0, 0, v };
	}

	using Quati = Quat<int>;
	using Quatf = Quat<float>;
	using Quatd = Quat<double>;
}