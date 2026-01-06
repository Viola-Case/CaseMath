/**

    @file      cm_complex.h
    @brief     
    @details   ~
    @author    Viola Case
    @date      8.12.2025
    @copyright © Viola Case, 2025.

**/
#pragma once

#include "cm_typetraits.h"

namespace CaseMath {

	template<Scalar T, size_t N>
		requires std::is_signed_v<T> && (N > 0)
	struct Vec;

	template <StdScalar T>
		requires std::is_signed_v<T>
	struct Quat;

 /**
     @struct Comp
     @brief  Complex number, \f$a+b\mathrm{i}\f$
     @tparam T - t
 **/
	template<StdScalar T>
		requires std::is_signed_v<T>
	struct Comp {
		union {
			struct { T Re, Im; };
			T data[2];
			Vec<T, 2> vec;
		};

		// --- Constructors lol ---
		constexpr Comp() noexcept : 
			Re(T{}), Im(T{}) {};
		constexpr Comp(T re_, T im_) noexcept : 
			Re(re_), Im(im_) {} ;
		constexpr Comp(T re_) noexcept : 
			Re(re_), Im(T{}) {};

		// --- Compound operators ---
		constexpr Comp& operator+=(const Comp& rhs) noexcept {
			Re += rhs.Re;
			Im += rhs.Im;
			return *this;
		}

		constexpr Comp& operator-=(const Comp& rhs) noexcept {
			Re -= rhs.Re;
			Im -= rhs.Im;
			return *this;
		}

		constexpr Comp& operator*=(const Comp& rhs) noexcept {
			const T r = Re * rhs.Re - Im * rhs.Im;
			const T i = Re * rhs.Im + Im * rhs.Re;
			Re = r;
			Im = i;
			return *this;
		}

		constexpr Comp& operator/=(const Comp& rhs) noexcept {
			const T denom = rhs.Re * rhs.Re + rhs.Im * rhs.Im;
			// You can later assert/handle denom == 0 if desired
			const T r = (Re * rhs.Re + Im * rhs.Im) / denom;
			const T i = (Im * rhs.Re - Re * rhs.Im) / denom;
			Re = r;
			Im = i;
			return *this;
		}


		// --- Binary operators ---
		constexpr Comp operator+(const Comp& rhs) const noexcept {
			Comp result{ *this };
			return (result += rhs);
		}

		constexpr Comp operator-(const Comp& rhs) const noexcept {
			Comp result{ *this };
			return (result -= rhs);
		}

		constexpr Comp operator*(const Comp& rhs) const noexcept {
			Comp result{ *this };
			return (result *= rhs);
		}

		constexpr Comp operator/(const Comp& rhs) const noexcept {
			Comp result{ *this };
			return (result /= rhs);
		}


		// --- Unary operators ---
		constexpr Comp operator+() const noexcept {
			return *this;
		}

		constexpr Comp operator-() const noexcept {
			return Comp{ -Re, -Im };
		}


		// --- Comparisons (component-wise equality) ---
		constexpr bool operator==(const Comp& rhs) const noexcept {
			return Re == rhs.Re && Im == rhs.Im;
		}

		constexpr bool operator!=(const Comp& rhs) const noexcept {
			return !(*this == rhs);
		}


		// --- Optional: magnitude & conjugate helpers ---
		constexpr T mag2() const noexcept { return Re * Re + Im * Im; }
		constexpr T mag() const noexcept { return static_cast<T>(std::sqrt(mag2())); }

		constexpr Comp conj() const noexcept {
			return Comp{ Re, -Im };
		}

		constexpr operator Vec<T,2>() const noexcept {
			return vec;
		}

		constexpr operator Quat<T>() const noexcept {
			return { Re, Im, 0, 0 };
		}


		template<StdScalar U>
			requires std::is_signed_v<U> && !(std::is_same_v<T, U>)
		constexpr operator Comp() const noexcept {
			return Comp<U>(static_cast<U>(Re), static_cast<U>(im));
		}


	};

	// @TODO Figure out how to make the literals work nice
	/*constexpr Comp<long double> operator"" _i(long double v) noexcept {
		return { 0.0l, v };
	}

	constexpr Comp<long long> operator"" _i(unsigned long long v) noexcept {
		return { 0l, v };
	}*/

 /**
     @brief  Re[c]
 **/
	template<typename T>
	requires StdScalar<T> && std::is_signed_v<T>
	constexpr T Re(Comp<T> c) { return c.Re; }

	/**
	@brief  Im[c]
	**/
	template<typename T>
		requires StdScalar<T> && std::is_signed_v<T>
	constexpr T Im(Comp<T> c) { return c.Im; }


	template<typename T>
		//requires StdScalar<T> && std::is_signed_v<T>
	constexpr Comp<T> operator+(T lhs, const Comp<T>& rhs) noexcept {
		return Comp<T>{ lhs + rhs.Re, rhs.Im };
	}
	
	template<typename T>
		//requires StdScalar<T> && std::is_signed_v<T>
	constexpr Comp<T> operator-(T lhs, const Comp<T>& rhs) noexcept {
		return Comp<T>{ lhs - rhs.Re, -rhs.Im };
	}

	template<typename T>
		requires StdScalar<T> && std::is_signed_v<T>
	constexpr Comp<T> operator*(T lhs, const Comp<T>& rhs) noexcept {
		return Comp<T>{ lhs * rhs.Re, lhs * rhs.Im };
	}

	template<typename T>
		requires StdScalar<T> && std::is_signed_v<T>
	constexpr Comp<T> operator/(T lhs, const Comp<T>& rhs) noexcept {
		const T denom = rhs.Re * rhs.Re + rhs.Im * rhs.Im;
		return Comp<T>{
			(lhs * rhs.Re) / denom,
				(-lhs * rhs.Im) / denom
		};
	}

	//! @TODO allow for unsigned stuff, maybe actually just cast it 

	template<typename T, typename U>
		//requires StdScalar<T> && std::is_signed_v<T>
	constexpr Comp<T> operator+(const Comp<T>& lhs, T rhs) noexcept {
		return Comp<T>{ lhs.Re + rhs, lhs.Im };
	}

	template<typename T>
		//requires StdScalar<T> && std::is_signed_v<T>
	constexpr Comp<T> operator-(const Comp<T>& lhs, T rhs) noexcept {
		return Comp<T>{ lhs.Re - rhs, lhs.Im };
	}

	template<typename T>
		requires StdScalar<T> && std::is_signed_v<T>
	constexpr Comp<T> operator*(const Comp<T>& lhs, T rhs) noexcept {
		return Comp<T>{ lhs.Re * rhs, lhs.Im * rhs };
	}

	template<typename T>
		requires StdScalar<T> && std::is_signed_v<T>
	constexpr Comp<T> operator/(const Comp<T>& lhs, T rhs) noexcept {
		return Comp<T>{ lhs.Re / rhs, lhs.Im / rhs };
	}


	using Compf = Comp<float>;
	using Compd = Comp<double>;

	
	using Compi = Comp<int>;
	using Compl = Comp<long>;
	using Compll = Comp<long long>;


}