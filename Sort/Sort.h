#ifndef _SORT_H_
#define _SORT_H_

#include "Vector.h"
#include <ctime>


class Sort {
protected:
	clock_t t1, t2;
public:
	virtual ~Sort() {}

	virtual void sort(Vector &v) = 0;
	
	double timeElapsed() const {
		return 1000.0 * (t2 - t1) / CLOCKS_PER_SEC;
	}
};


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

#endif