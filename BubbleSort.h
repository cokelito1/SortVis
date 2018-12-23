#pragma once

#include "Sorter.h"

template<typename T>
class BubbleSort : public Sorter<T> {
public:
	BubbleSort() : Sorter<T>() { }
	~BubbleSort() = default;

	virtual void Sort(std::function<bool(T&, T&)> comparer, std::vector<T>& Arr, std::function<void(size_t IndexOne, size_t IndexTwo, std::vector<T>& Arr)> Swap){
		for (int i = 0; i < Arr.size() - 1; i++) {
			bool isSorted = true;
			for (int j = 0; j < Arr.size() - i - 1; j++) {
				if (comparer(Arr[j], Arr[j + 1])) {
					Swap(j, j + 1, Arr);
					isSorted = false;
				}
			}
			if (isSorted) {
				break;
			}
			else {
				isSorted = true;
			}
		}
	}

	virtual bool Step(std::function<bool(T&, T&)> comparer, std::vector<T>& Arr, std::function<void(size_t IndexOne, size_t IndexTwo, std::vector<T>& Arr)> Swap) {
		if (Sorting) {
			if (comparer(Arr[IndexJ], Arr[IndexJ + 1])) {
				Swap(IndexJ, IndexJ + 1, Arr);
				Sorted = false;
			}

			if (IndexJ >= Arr.size() - IndexI - 2) {
				if (Sorted) {
					Sorting = false;
					return true;
				}
				else {
					Sorted = true;
				}

				IndexI++;
				IndexJ = 0;
			}
			else {
				IndexJ++;
			}

			return false;
		}

		return true;
	}

	virtual std::string GetName() { return "Bubble sort"; }
private:
	unsigned int IndexI = 0;
	unsigned int IndexJ = 0;

	bool Sorting = true;
	bool Sorted = true;
};