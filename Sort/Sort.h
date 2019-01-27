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
	void sort(Vector &v) override;
};

 
/*
 * Shell Sort
 *
 * Increments by Knuth: Hi-1 = 3Hi + 1
 */
class Shell: public Sort {
public:
	void sort(Vector &v) override;
};


/*
 * Selection Sort
 */
class Selection: public Sort {
public:
	void sort(Vector &v) override;
};


/*
 * Heap Sort
 */
class Heap: public Sort {
public:
	void sort(Vector &v) override;
};


/*
 * Bubble Sort
 */
class Bubble: public Sort{
public:
	void sort(Vector &v) override;
};


/*
 * Quick Sort
 */
class Quick: public Sort {
public:
	enum PivotType { FIRST, LAST, MIDDLE, RANDOM, MEDIAN3};

	void sort(Vector &v) override {
		t1 = clock();
		quick(v, 0, v.getN() - 1);
		t2 = clock();
	}
	
	void setPivotType(PivotType pp) {
		p = pp;
	}

private:
	PivotType p = MEDIAN3;

	struct PivotIndex {
		VectorItem vi;
		int ind;
	};

	PivotIndex selectPivot(Vector &v, int low, int high);
	int partition(Vector &v, int low, int high);
	void quick(Vector &v, int low, int high);
};


/*
 * Radix Exchange
 */
class RadixExchange: public Sort {
public:
	void sort(Vector &v) override {
		t1 = clock();
		int width = sizeof(v[0].getValue()) * 8;
		radixExchange(v, 0, v.getN() - 1, width - 1);
		t2 = clock();
	}
private:
	int partition(Vector &v, int low, int high, int bit);
	void radixExchange(Vector &v, int low, int high, int bit);
};


/*
 * Counting Sort
 */
class Counting: public Sort{
public:
	void sort(Vector &v) override;
};


/*
 * Radix Sort
 */
class Radix: public Sort {
public:
	void sort(Vector &v) override;
};

#endif