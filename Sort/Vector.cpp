#include "Vector.h"


Vector::Vector(int nn, Order order) {
	a = new int[n = nn];

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
	a = new int[n = v.n];
	for (int i = 0; i < n; i++)
		a[i] = v.a[i];
}

void Vector::moveVector(Vector &v) {
	a = v.a;
	n = v.n;
	v.a = nullptr;
}

void Vector::deleteVector() {
	delete[] a;
	a = nullptr;
	n = 0;
}

void Vector::swap(unsigned int i, unsigned int j) {
	if (i >= n || j >= n)
		throw ErrIndex();
	int tmp = a[i];
	a[i] = a[j];
	a[j] = tmp;
}

void Vector::ascending() {
	for (int i = 0; i < n; i++)
		a[i] = i + 1;
}

void Vector::descending() {
	for (int i = 0; i < n; i++)
		a[i] = n - i;
}

void Vector::shuffle() {
	for (int i = n - 1; i > 0; i--) {
		int j = rand() / (RAND_MAX + 1.) * (i + 1);
		swap(i, j);
	}
}

ostream& operator<<(ostream &os, const Vector &v) {
	os << '[';
	for (int i = 0; i < v.n; i++)
		os << ' ' << v.a[i] << (i == v.n - 1 ? ' ' : ',');
	return os << ']';
}
