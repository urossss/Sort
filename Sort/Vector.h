#ifndef _VECTOR_H_
#define _VECTOR_H_

#include <exception>
#include <iostream>
using namespace std;


class ErrIndex: public exception {
public:
	const char* what() const override {
		return "Index out of range!";
	}
};


class Vector {
	int *a, n;
	int accesses = 0;
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
	void resetAccesses(){
		accesses = 0;
	}

	friend ostream& operator<<(ostream &os, const Vector &v);

	void swap(unsigned int, unsigned int);

private:
	void copyVector(const Vector &v);
	void moveVector(Vector &v);
	void deleteVector();

	void ascending();
	void descending();
	void shuffle();
};

#endif