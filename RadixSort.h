#pragma once

#include "Sorter.h"
#include <array>

template<typename T>
class RadixSort : public Sorter<T>{
public:
	RadixSort() : Sorter<T>() { }
	~RadixSort() = default;

	virtual void Sort(std::function<bool(T&, T&)> Comparer, std::vector<T>& Arr, std::function<void(size_t IndexOne, size_t IndexTwo, std::vector<T>& Arr)> Swap) {
		while (Sorted) {
			for (auto& i : Arr) {
				Map[((int)i.getSize().y & Mask) >> shift].push_back(i.getSize().y);
				if (((int)i.getSize().y & Mask) >> shift != 0x00) {
					isSorted = false;
				}
			}

			int index = 0;
			for (auto& i : Map) {
				for (auto& j : i) {
					Arr[index].setSize(sf::Vector2f(Arr[index].getSize().x, j));
					index++;
				}
			}

			Mask <<= 4;
			shift += 4;
			if (isSorted) {
				Sorted = false;
			}
			else {
				isSorted = true;
				for (auto& i : Map) {
					i.clear();
				}
			}
		}
	}

	virtual bool Step(std::function<bool(T&, T&)> Comparer, std::vector<T>& Arr, std::function<void(size_t IndexOne, size_t IndexTwo, std::vector<T>& Arr)> Swap) { 
		if (Sorted) {
			Map[((int)Arr[IndexI].getSize().y & Mask) >> shift].push_back(Arr[IndexI].getSize().y);
			if (((int)Arr[IndexI].getSize().y & Mask) >> shift != 0x00) {
				isSorted = false;
			}
			IndexI++;

			int index = 0;
			for (auto& i : Map) {
				for (auto& j : i) {
					Arr[index].setSize(sf::Vector2f(Arr[index].getSize().x, j));
					index++;
				}
			}

			if (IndexI >= Arr.size() - 1) {
				Mask <<= 4;
				shift += 4;
				if (isSorted) {
					Sorted = false;
					return true;
				}
				else {
					isSorted = true;
					for (auto& i : Map) {
						i.clear();
					}
				}
				IndexI = 0;
			}
			return false;
		}
		return true;
	}

	virtual std::string GetName() { return "Radix Sort"; }

private:
	bool Sorted = true;
	bool isSorted = true;
	uint64_t Mask = 0x000000000000000F;
	uint64_t shift = 0x00;
	std::array<std::vector<int>, 0x10> Map;

	int IndexI = 0;
};