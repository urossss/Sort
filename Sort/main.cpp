#include "Vector.h"
#include <cstdlib>
#include <ctime>
#include <iostream>

using namespace std;


void printCurrentTime() {
	time_t pIntTime = time(NULL);
	struct tm* currentLocalTime = localtime(&pIntTime);
	char timeString[11];
	if (currentLocalTime) {
		strftime(timeString, 10, "%H:%M:%S", currentLocalTime);
		puts(timeString);
	}
}


int main() {
	srand(time(nullptr));
	rand(), rand(), rand();

	clock_t t1, t2;
	double d;

	Vector v(10);
	cout << v << endl;

	printCurrentTime();
}