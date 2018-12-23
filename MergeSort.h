#pragma once

#include "Sorter.h"

template<typename T>
class MergeSort : public Sorter<T> {
public:
	MergeSort() = default;
	virtual ~MergeSort() = default;

	virtual void Sort(std::function<bool(T&, T&)> Comparer, std::vector<T>& Arr, std::function<void(size_t IndexOne, size_t IndexTwo, std::vector<T>& Arr)> Swap) {
		MergeSortt(Arr, 0, Arr.size() - 1);
	};
	virtual bool Step(std::function<bool(T&, T&)> Comparer, std::vector<T>& Arr, std::function<void(size_t IndexOne, size_t IndexTwo, std::vector<T>& Arr)> Swap) { return true; }

	virtual std::string GetName() { return "Merge Sort"; }
private:
	void Merge(std::vector<T>& Arr, int l, int m, int r) {
		int n1 = m - l + 1;
		int n2 = r - m;

		sf::RectangleShape* L, *R;
		L = new sf::RectangleShape[n1];
		R = new sf::RectangleShape[n2];
		for (int x = 0; x < n1; x++) {
			L[x] = Arr[l + x];
		}
		for (int x = 0; x < n2; x++) {
			R[x] = Arr[m + x + 1];
		}

		int i = 0;
		int j = 0;
		int k = l;
		while (i < n1 && j < n2) {
			if (L[i].getSize().y <= R[j].getSize().y) {
				Arr[k].setSize(sf::Vector2f(Arr[k].getSize().x, L[i].getSize().y));
				i++;
			}
			else {
				Arr[k].setSize(sf::Vector2f(Arr[k].getSize().x, R[j].getSize().y));
				j++;
			}
			k++;
		}

		while (i < n1) {
			Arr[k].setSize(sf::Vector2f(Arr[k].getSize().x, L[i].getSize().y));
			i++;
			k++;
		}

		while (j < n2) {
			Arr[k].setSize(sf::Vector2f(Arr[k].getSize().x, R[j].getSize().y));
			j++;
			k++;
		}

		delete[] R;
		delete[] L;
	}

	void MergeSortt(std::vector<T>& Arr, int l, int r) {
		if (l < r) {
			int m = l + (r - l) / 2;

			MergeSortt(Arr, l, m);
			MergeSortt(Arr, m + 1, r);
			Merge(Arr, l, m, r);
		}
	}
};