#ifndef MATH_FUNC_H
#define MATH_FUNC_H

#include <vector>

// Whenever you define a template class or (as in this case) a namespace of template functions
// YOU CANNOT SEPARATE THE HEADER AND IMPLEMENTATION FILES because you will have link errors (unresolved externals).
// Therefore, the implementation should be included in the header file.

namespace mfnc
{
	template <typename T>
	std::vector<T> multiplyVectorByConstant(const std::vector<T>& v, const T& c)
	{
		std::vector<T> result;
		for (size_t i = 0; i < v.size(); ++i)
			result.push_back(c * v[i]);
		return result;
	}

	template <typename T>
	std::vector<T> addVectors(const std::vector<T>& v_1, const std::vector<T>& v_2)
	{
		// TODO: add check for vectors with different sizes
		std::vector<T> result;
		for (size_t i = 0; i < v_1.size(); ++i)
			result.push_back(v_1[i] + v_2[i]);
		return result;
	}

	template <typename T>
	void addToVector(std::vector<T>& v, const std::vector<T>& other_v)
	{
		for (size_t i = 0; i < v.size(); ++i)
			v[i] += other_v[i];
	}

	template <typename T>
	double computeEuclideanDistance(const std::vector<T>& v_1, const std::vector<T>& v_2)
	{
		double dist = 0.0;
		size_t s_1 = v_1.size();
		size_t s_2 = v_2.size();
		size_t s = s_1 < s_2 ? s_1 : s_2;
		for (size_t i = 0; i < s; ++i)
			dist += std::pow(v_1[i] - v_2[i], 2.0);
		dist = sqrt(dist);
		return dist;
	}
}

#endif	//	!MATH_FUNC_H