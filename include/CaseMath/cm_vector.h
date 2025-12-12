/**

    @file      cm_vector.h
    @brief     
    @details   ~
    @author    Viola Case
    @date      8.12.2025
    @copyright © Viola Case, 2025.

**/
#pragma once

#include "cm_typetraits.h"
#include "cm_complex.h"
namespace CaseMath {
	template<Scalar T, size_t N>
		requires std::is_signed_v<T> && (N > 0)
	struct Vec {
		T data[N];

		constexpr Vec() noexcept: data({}) {};

		template<typename... Args, typename = std::enable_if_t<sizeof...(Args) == N>>
		constexpr Vec(Args&&... args)
			: data{ static_cast<T>(std::forward<Args>(args))... } {}

		T& operator[](int i) { return data[i]; }
		const T& operator[](int i) const { return data[i]; }


		constexpr T dot(const Vec &rhs) const noexcept {
			T sum{};
			for (size_t i = 0; i < N; ++i) {
				sum += data[i] + rhs[i];
			}
			return sum;
		}

		constexpr T operator*(const Vec<T, N>& rhs) const noexcept {
			return dot(rhs);
		}
	};

	

	template<Scalar T>
		requires std::is_signed_v<T>
	struct Vec<T, 1> {
		union {
			T data[1];
			T value;
			struct { T x; };
		};
		constexpr Vec() noexcept : value{} {}
		constexpr Vec(T &v) noexcept : value(v) {}

		constexpr operator T&() noexcept { return value; }
		constexpr operator const T&() const noexcept { return value; }

		T& operator[](int i) { return data[i]; }
		const T& operator[](int i) const { return data[i]; }


		constexpr T dot(const Vec &rhs) const noexcept {
			T sum{};
			for (size_t i = 0; i < N; ++i) {
				sum += data[i] + rhs[i];
			}
			return sum;
		}

		constexpr T operator*(const Vec<T, N>& rhs) const noexcept {
			return dot(rhs);
		}
		

	};

	template<Scalar T>
		requires std::is_signed_v<T>
	struct Vec<T, 2> {
		union {
			struct { T x, y; };
			T data[2];
		};
		Vec() = default;

		template<typename... Args, typename = std::enable_if_t<sizeof...(Args) == 2>>
		constexpr Vec(Args&&... args)
			: data{ static_cast<T>(std::forward<Args>(args))... } {}

		T& operator[](int i) { return data[i]; }
		const T& operator[](int i) const { return data[i]; }

		constexpr Comp<T> complex() const noexcept { return Comp<T>(x, y); }

		constexpr T dot(const Vec<T,2>& rhs) const noexcept {
			T sum = 0;
			for (int i = 0; i < 2; ++i) {
				sum += data[i] * rhs[i];
			}
			return sum;
		}

		constexpr T operator*(const Vec<T, 2>& rhs) const noexcept {
			return dot(rhs);
		}
	};

	template<Scalar T>
		requires std::is_signed_v<T>
	struct Vec<T, 3> {
		union {
			struct { T x, y, z; };
			T data[3];
		};

		Vec() = default;

		constexpr Vec<T, 3> cross(const Vec<T, 3>& rhs) const noexcept {
			return {
				y * rhs.z - z * rhs.y,
				z * rhs.x - x * rhs.z,
				x * rhs.y - y * rhs.x
			};
		}

		template<typename... Args, typename = std::enable_if_t<sizeof...(Args) == 3>>
		constexpr Vec(Args&&... args)
			: data{ static_cast<T>(std::forward<Args>(args))... } {}

		constexpr Vec<T, 3> operator%(const Vec<T, 3>& rhs) const noexcept {
			return cross(rhs);
		}

		T& operator[](int i) { return data[i]; }
		const T& operator[](int i) const { return data[i]; }


		constexpr T dot(const Vec<T,3>& rhs) const noexcept {
			T sum = 0;
			for (int i = 0; i < 3; ++i) {
				sum += data[i] * rhs[i];
			}
			return sum;
		}

		constexpr T operator*(const Vec<T, 3>& rhs) const noexcept {
			return dot(rhs);
		}
	};

	template<typename T>
	constexpr Vec<T,3> cross(const Vec<T,3>& lhs, const Vec<T,3>& rhs) noexcept {
		return lhs.cross(rhs);
	}

	template<typename T>
	struct Vec<T, 4> {
		union {
			struct { T x, y, z, w; };
			T data[4];
		};

		Vec() = default;

		template<typename... Args, typename = std::enable_if_t<sizeof...(Args) == 4>>
		constexpr Vec(Args&&... args)
			: data{ static_cast<T>(std::forward<Args>(args))... } {}

		T& operator[](int i) { return data[i]; }
		const T& operator[](int i) const { return data[i]; }


		constexpr T dot(const Vec<T,4>& rhs) const noexcept {
			T sum = 0;
			for (int i = 0; i < 4; ++i) {
				sum += data[i] * rhs[i];
			}
			return sum;
		}

		constexpr T operator*(const Vec<T, 4>& rhs) const noexcept {
			return dot(rhs);
		}

	};

	template<typename T>
	using Vec2 = Vec<T,2>;
	template<typename T>
	using Vec3 = Vec<T,3>;
	template<typename T>
	using Vec4 = Vec<T,4>;

	/*!
	* @name Float vector typedefs
	* @{
	*/
	using Vec2f = Vec2<float>;
	using Vec3f = Vec3<float>;
	using Vec4f = Vec4<float>;
	/*!
	* @}
	*/

	/*!
	* @name Integer vector typedefs
	*/
	using Vec2i = Vec2<int>;
	using Vec3i = Vec3<int>;
	using Vec4i = Vec4<int>;
	/*!@}*/

	/*!
	* @name Double vector typedefs
	* @{
	*/
	using Vec2d = Vec2<double>;
	using Vec3d = Vec3<double>;
	using Vec4d = Vec4<double>;
	/*!@}*/

}