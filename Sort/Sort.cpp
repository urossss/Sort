#include "Sort.h"


/*
 * Insertion Sort
 */
void Insertion::sort(Vector &v) {
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


/*
 * Shell Sort
 *
 * Increments by Knuth: Hi-1 = 3Hi + 1
 */
void Shell::sort(Vector &v) {
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


/*
 * Selection Sort
 */
void Selection::sort(Vector &v) {
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


/*
 * Heap Sort
 */
void Heap::sort(Vector &v) {
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


/*
 * Bubble Sort
 */
void Bubble::sort(Vector &v) {
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


/*
 * Quick Sort
 */

// returns pivot and its index in a Vector
Quick::PivotIndex Quick::selectPivot(Vector &v, int low, int high) {
	int ind;
	switch (p) {
	case FIRST:
		return { v[low], low };
	case LAST:
		return { v[high], high };
	case MIDDLE:
		ind = low + (high - low) / 2;
		return { v[ind], ind };
	case RANDOM:
		ind = (int) (rand() / (RAND_MAX + 1.0) * (high - low + 1) + low);
		return { v[ind], ind };
	default:
		ind = low + (high - low) / 2;
		VectorItem a = v[low], b = v[high], c = v[ind];
		if (a <= b)
			if (b <= c)
				return { b, high };
			else if (a <= c)
				return { c, ind };
			else
				return { a, low };
		else
			if (a <= c)
				return { a, low };
			else if (b <= c)
				return { c, ind };
			else
				return { b, high };
	}
}

int Quick::partition(Vector &v, int low, int high) {
	PivotIndex pi = selectPivot(v, low, high);
	VectorItem pivot = pi.vi;
	int i = low, j = high;
	while (i < j) {
		while (i < j && v[i] <= pivot)
			i++;
		while (v[j] > pivot)
			j--;
		if (i < j) {
			v.swap(i, j);
			if (j == pi.ind)
				pi.ind = i;
		}
	}
	v[pi.ind] = v[j];
	v[j] = pivot;
	return j;
}

void Quick::quick(Vector &v, int low, int high) {
	if (low < high) {
		int j = partition(v, low, high);
		quick(v, low, j - 1);
		quick(v, j + 1, high);
	}
}


/*
 * Radix Exchange
 */
int RadixExchange::partition(Vector &v, int low, int high, int bit) {
	int mask = 1 << bit, i = low, j = high;
	while (i < j) {
		while (i < j && (v[i].getValue() & mask) == 0)
			i++;
		while (i < j && (v[j].getValue() & mask) != 0)
			j--;
		if (i < j)
			v.swap(i, j);
	}
	return j * ((v[j].getValue() & mask) ? 1 : -1);	// negative if pivot should be part of the left partition in next iteration
}

void RadixExchange::radixExchange(Vector &v, int low, int high, int bit) {
	if (low < high && bit >= 0) {
		int j = partition(v, low, high, bit);
		int h1 = (j < 0 ? -j : j - 1);
		int l2 = (j < 0 ? -j + 1 : j);
		radixExchange(v, low, h1, bit - 1);
		radixExchange(v, l2, high, bit - 1);
	}
}


/*
 * Counting Sort
 */
void Counting::sort(Vector &v) {
	t1 = clock();
	Vector tmp = v;
	int n = v.getN(), i, *c = new int[n + 1];
	for (i = 0; i <= n; i++)
		c[i] = 0;
	for (i = 0; i < n; i++)
		c[v[i].getValue()]++;
	for (i = 2; i <= n; i++)
		c[i] += c[i - 1];
	for (i = n - 1; i >= 0; i--)
		tmp[c[v[i].getValue()]-- - 1] = v[i];
	v = tmp;
	delete[] c;
	t2 = clock();
}
