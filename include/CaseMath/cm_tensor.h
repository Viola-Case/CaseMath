/**

    @file      cm_tensor.h
    @brief     
    @details   ~
    @author    Viola Case
    @date      17.12.2025
    @copyright © Viola Case, 2025.

**/
#pragma once

#include "cm_typetraits.h"

namespace CaseMath {
	template<Scalar T, size_t L, size_t M, size_t N>
	struct Tensor {
		T data[L*M*N];
	};
}