/**

    @file      cm_matrix.h
    @brief     
    @details   ~
    @author    Viola Case
    @date      12.12.2025
    @copyright © Viola Case, 2025.

**/
#pragma once

#include "cm_vector.h"

namespace CaseMath {
	template<Scalar T, size_t M, size_t N>
	struct Mat {
		union MyUnion {
			T data[M * N];
			// Vec<T, N> rows[M];
			// Vec<T, M> columns[N];
		};

		constexpr Mat() : data({}) {};

		constexpr T& operator()(size_t r, size_t c) noexcept {
			return data[r * N + c];
		}

		constexpr const T& operator()(size_t r, size_t c) const noexcept {
			return data[r * N + c];
		}
		
		template <size_t I>
		constexpr Mat<T, M, I> operator*(const Mat<T, N, I> &rhs) const noexcept {
			Mat<T, M, I> out{};

			for (size_t i = 0; i < M; ++i) {
				for (size_t j = 0; j < J; ++j) {
					T sum{};
					for (size_t k = 0; k < N; ++k) {
						sum += (*this)(i, k) * rhs(k, j);
					}
					out(i, j) = sum;
				}
			}
			return out;

		}

		constexpr Mat &operator +=(const Mat &rhs) noexcept {
			for (size_t i = 0; i < M * N; ++i) {
				data[i] += rhs.data[i];
			}
			return *this;
		}

		constexpr Mat &operator -=(const Mat &rhs) noexcept {
			for (size_t i = 0; i < M * N; ++i) {
				data[i] -= rhs.data[i];
			}
			return *this;
		}

		constexpr Mat operator +(const Mat &rhs) const noexcept {
			Mat result{ *this };
			return (result += rhs);
		}

		constexpr Mat operator -(const Mat &rhs) const noexcept {
			Mat result{ *this };
			return (result -= rhs);
		}

		constexpr T determinant() const noexcept {


		}

  /**
      @brief  returns the inverse if invertible, returns zero matrix if invertible 
  **/
		constexpr Mat inverse() const noexcept
			requires (M == N) {

		}


		

		static constexpr Mat zero() noexcept {
			return Mat{};
		}

		static constexpr Mat eye() noexcept
			requires (M == N) {

			Mat out{};
			for (size_t i = 0; i < M; ++i)
				out(i, i) = T{ 1 };
			return out;
		}

		static constexpr Mat identity() noexcept
			requires (M == N) {
			return eye();
		}

		constexpr Mat<T, N, M> transpose() const noexcept {
			Mat<T, N, M> out{};
			for (size_t i = 0; i < M; ++i) {
				for (size_t j = 0; j < N; ++j) {
					out(j, i) = (*this)(i, j);
				}
			}
			return out;
		}

		template<size_t K>
		static constexpr Mat diag(const Vec<T, K>& v) noexcept
			requires (M == K && N == K)
		{
			Mat out{};
			for (size_t i = 0; i < K; ++i)
				out(i, i) = v[i];
			return out;
		}

		constexpr T trace() const noexcept
			requires (M == N) {
			T out{};
			for (size_t i{}; i < N; ++i) {
				out += (*this)(i, i);
			}
			return out;
		}

	};

	
}