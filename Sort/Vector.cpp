#include "Vector.h"


void VectorItem::onComparison() {
	vector->incComparisons();
}


Vector::Vector(int nn, Order order) {
	n = nn;

	switch (order) {
	case ASCENDING:
		ascending();
		break;
	case DESCENDING:
		descending();
		break;
	default:
		ascending();
		shuffle();
		break;
	}
}

void Vector::copyVector(const Vector &v) {
	n = v.n;
	elements = v.elements;
}

void Vector::moveVector(Vector &v) {
	n = v.n;
	v.elements = move(v.elements);
}

void Vector::deleteVector() {
	elements.clear();
	n = 0;
}

void Vector::swap(int i, int j) {
	if (i < 0 || i >= n || j < 0 || j >= n)
		throw ErrIndex();
	VectorItem tmp = elements[i];
	elements[i] = elements[j];
	elements[j] = tmp;
	swaps++;
}

void Vector::ascending() {
	for (int i = 0; i < n; i++)
		elements.push_back(VectorItem(this, i + 1));
}

void Vector::descending() {
	for (int i = 0; i < n; i++)
		elements.push_back(VectorItem(this, n - i));
}

void Vector::shuffle() {
	for (int i = n - 1; i > 0; i--) {
		int j = (int) (rand() / (RAND_MAX + 1.) * (i + 1));
		swap(i, j);
	}
	resetSwaps();
}

ostream& operator<<(ostream &os, const Vector &v) {
	os << '[';
	for (int i = 0; i < v.n; i++)
		os << ' ' << v.elements[i] << (i == v.n - 1 ? ' ' : ',');
	return os << ']';
}
