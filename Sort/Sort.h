#ifndef _SORT_H_
#define _SORT_H_

#include "Vector.h"
#include <ctime>


class Sort {
protected:
	clock_t t1 = 0, t2 = 0;
public:
	virtual ~Sort() {}

	virtual void sort(Vector &v) = 0;

	double timeElapsed() const {
		return 1000.0 * (t2 - t1) / CLOCKS_PER_SEC;
	}
};


/*
 * Insertion Sort
 */
class Insertion: public Sort {
public:
	void sort(Vector &v) override {
		t1 = clock();
		int n = v.getN();
		for (int i = 1; i < n; i++) {
			VectorItem key = v[i];
			int j = i - 1;
			while (j >= 0 && v[j] > key) {
				v[j + 1] = v[j];
				j--;
			}
			v[j + 1] = key;
		}
		t2 = clock();
	}
};

 
/*
 * Shell Sort
 *
 * Increments by Knuth: Hi-1 = 3Hi + 1
 */
class Shell: public Sort {
public:
	void sort(Vector &v) override {
		t1 = clock();
		int incs[] = { 193710244, 64570081, 21523360, 7174453, 2391484,
			797161, 265720, 88573, 29524, 9841,
			3280, 1093, 364, 121, 40, 13, 4, 1 };
		int t = sizeof(incs) / sizeof(incs[0]), n = v.getN(), k = 0, inc;
		while (incs[k] >= n)
			k++;
		for (; k < t; k++) {
			inc = incs[k];
			for (int i = inc; i < n; i++) {
				VectorItem key = v[i];
				int j = i - inc;
				while (j >= 0 && v[j] > key) {
					v[j + inc] = v[j];
					j -= inc;
				}
				v[j + inc] = key;
			}
		}
		t2 = clock();
	}
};


/*
 * Selection Sort
 */
class Selection: public Sort {
public:
	void sort(Vector &v) override {
		t1 = clock();
		int n = v.getN(), pos;
		for (int i = 0; i < n - 1; i++) {
			VectorItem min = v[i];
			pos = i;
			for (int j = i + 1; j < n; j++)
				if (v[j] < min) {
					min = v[j];
					pos = j;
				}
			v[pos] = v[i];
			v[i] = min;
		}
		t2 = clock();
	}
};


/*
 * Heap Sort
 */
class Heap: public Sort {
public:
	void sort(Vector &v) override {
		t1 = clock();
		int n = v.getN(), i, f, s;
		for (i = 1; i < n; i++) {
			VectorItem nhe = v[i];
			s = i;
			f = s / 2;
			while (s > 0 && v[f] < nhe) {
				v[s] = v[f];
				s = f;
				f = s / 2;
			}
			v[s] = nhe;
		}
		for (i = n - 1; i > 0; i--) {
			VectorItem last = v[i];
			v[i] = v[0];
			f = 0;
			if (i > 2 && v[2] > v[1])
				s = 2;
			else
				s = 1;
			while (s < i && v[s] > last) {
				v[f] = v[s];
				f = s;
				s = 2 * f;
				if (s < i - 1 && v[s] < v[s + 1])
					s++;
			}
			v[f] = last;
		}
		t2 = clock();
	}
};


/*
 * Bubble Sort
 */
class Bubble: public Sort{
public:
	void sort(Vector &v) override {
		t1 = clock();
		int n = v.getN(), pos = n, bound, i;
		do {
			bound = pos;
			pos = 0;
			for (i = 0; i < bound - 1; i++)
				if (v[i] > v[i + 1]) {
					v.swap(i, i + 1);
					pos = i;
				}
		} while (pos != 0);
		t2 = clock();
	}
};

#endif