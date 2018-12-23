#pragma once

#include <functional>
#include <vector>

template<typename T>
class Sorter {
public:
	Sorter() = default;
	virtual ~Sorter() = default;

	virtual void Sort(std::function<bool(T&, T&)> Comparer, std::vector<T>& Arr, std::function<void(size_t IndexOne, size_t IndexTwo, std::vector<T>& Arr)> Swap) = 0;
	virtual bool Step(std::function<bool(T&, T&)> Comparer, std::vector<T>& Arr, std::function<void(size_t IndexOne, size_t IndexTwo, std::vector<T>& Arr)> Swap) = 0;
	virtual std::string GetName() = 0;
};