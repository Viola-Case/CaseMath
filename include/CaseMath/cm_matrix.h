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
			Vec<T, N> rows[M];
			Vec<T, M> columns[N];
		};
		
	};
}