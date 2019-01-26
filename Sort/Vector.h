#ifndef _VECTOR_H_
#define _VECTOR_H_

#include <exception>
#include <iostream>
#include <vector>
using namespace std;


class ErrIndex: public exception {
public:
	const char* what() const override {
		return "Index out of range!";
	}
};


class Vector;


/*
 *	VectorItem
 */
class VectorItem {
	Vector *vector = nullptr;
	int value;
public:
	VectorItem(Vector *vec, int val) : vector(vec), value(val) {}

	void onComparison();

	bool operator==(const VectorItem &v) {
		onComparison();
		return value == v.value;
	}
	bool operator!=(const VectorItem &v) {
		onComparison();
		return value != v.value;
	}
	bool operator<(const VectorItem &v) {
		onComparison();
		return value < v.value;
	}
	bool operator<=(const VectorItem &v) {
		onComparison();
		return value <= v.value;
	}
	bool operator>(const VectorItem &v) {
		onComparison();
		return value > v.value;
	}
	bool operator>=(const VectorItem &v) {
		onComparison();
		return value >= v.value;
	}

	friend ostream& operator<<(ostream &os, const VectorItem &vi) {
		return os << vi.value;
	}
};


/*
 *	Vector
 */
class Vector {
	vector<VectorItem> elements;
	int n;
	mutable int accesses = 0, comparisons = 0, swaps = 0;
public:
	enum Order { ASCENDING, DESCENDING, SHUFFLED };

	Vector(int nn, Order order = SHUFFLED);
	Vector(const Vector &v) {
		copyVector(v);
	}
	Vector(Vector &&v) {
		moveVector(v);
	}
	~Vector() {
		deleteVector();
	}

	Vector& operator=(const Vector &v) {
		if (this != &v) {
			deleteVector();
			copyVector(v);
		}
		return *this;
	}
	Vector& operator=(Vector &&v) {
		if (this != &v) {
			deleteVector();
			moveVector(v);
		}
		return *this;
	}

	int getN() const {
		return n;
	}
	int getAccesses() const {
		return accesses;
	}
	int getComparisons() const {
		return comparisons;
	}
	int getSwaps() const {
		return swaps;
	}
	void resetAccesses(){
		accesses = 0;
	}
	void resetComparisons() {
		comparisons = 0;
	}
	void resetSwaps() {
		swaps = 0;
	}
	void incComparisons() {
		comparisons++;
	}

	friend ostream& operator<<(ostream &os, const Vector &v);

	void swap(int, int);

	VectorItem& operator[](int i) {
		if (i < 0 || i >= n)
			throw ErrIndex();
		accesses++;
		return elements[i];
	}
	const VectorItem& operator[](int i) const {
		if (i < 0 || i >= n)
			throw ErrIndex();
		accesses++;
		return elements[i];
	}

	void shuffle();

private:
	void copyVector(const Vector &v);
	void moveVector(Vector &v);
	void deleteVector();

	void ascending();
	void descending();
};


#endif