#pragma once

#include "Sorter.h"

template<typename T>
class SelectionSort : public Sorter<T> {
public:
	SelectionSort() = default;
	virtual ~SelectionSort() = default;

	virtual void Sort(std::function<bool(T&, T&)> Comparer, std::vector<T>& Arr, std::function<void(size_t IndexOne, size_t IndexTwo, std::vector<T>& Arr)> Swap) {
		for (int i = 0; i < Arr.size() - 1; i++) {
			SortedArray_Start = i;
			for (int j = i + 1; j < Arr.size(); j++) {
				if (Comparer(Arr[j], Arr[SortedArray_Start])) {
					SortedArray_Start = j;
				}
			}
			Swap(SortedArray_Start, i, Arr);
		}
	};
	virtual bool Step(std::function<bool(T&, T&)> Comparer, std::vector<T>& Arr, std::function<void(size_t IndexOne, size_t IndexTwo, std::vector<T>& Arr)> Swap) {
		if (sorted) {
			Arr[IndexJ - 1].setFillColor(sf::Color::White);
			Arr[IndexJ].setFillColor(sf::Color::Green);
			Arr[SortedArray_Start].setFillColor(sf::Color::Red);

			if (Comparer(Arr[IndexJ], Arr[SortedArray_Start])) {
				Arr[SortedArray_Start].setFillColor(sf::Color::White);
				SortedArray_Start = IndexJ;
				Arr[SortedArray_Start].setFillColor(sf::Color::Red);
				isSorted = false;
			}

			if (IndexJ >= Arr.size() - 1) {
				if (isSorted) {
					sorted = false;
					return true;
				}
				else {
					isSorted = true;
				}
				Arr[Arr.size() - 1].setFillColor(sf::Color::White);
				Swap(SortedArray_Start, IndexI, Arr);
				IndexI++;
				IndexJ = IndexI + 1;
			}
			else {
				IndexJ++;
			}

			if (IndexI >= Arr.size() - 1) {
				sorted = false;
			}
		}

		return false;
	};


	virtual std::string GetName() { return "Selection Sort"; }
private:
	size_t SortedArray_Start = 0;
	
	unsigned int IndexI = 0;
	unsigned int IndexJ = 1;

	bool sorted = true;
	bool isSorted = true;
};