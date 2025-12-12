/**

    @file      cm_typetraits.h
    @brief     
    @details   ~
    @author    Viola Case
    @date      8.12.2025
    @copyright © Viola Case, 2025.

**/
#pragma once
#include <type_traits>

namespace CaseMath {
	template<typename T>
	concept StdScalar = std::is_arithmetic_v<T>;
	
	
	template<typename T>
	struct Comp;

	template<StdScalar T>
	struct Quat;



	template<typename T>
	concept Scalar = StdScalar<T> || 
		std::_Is_any_of_v<T, 
			Comp<typename T::value_type>, 
			Quat<typename T::value_type> 
		>;
	
	template<typename T>
	concept Signed = std::is_signed_v<T> || std::is_signed_v<typename T::value_type>;

	template<typename T>
	concept FloatingPoint = std::is_floating_point_v<T> || std::is_floating_point_v<typename T::value_type>;

	template<typename T>
	concept Integral = std::is_integral_v<T> || std::is_integral_v<typename T::value_type>;


	//
	//template<Scalar T, size_t N>
	//struct Vec;
	//
	//

	
}
