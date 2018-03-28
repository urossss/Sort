#include <stdio.h>
#include <stdlib.h>
#include <time.h>


void swap(int *a, int *b) {
	int t = *a;
	*a = *b;
	*b = t;
}

void selection(int *a, int n) {
	for (int i = 0; i < n - 1; i++)
		for (int j = i + 1; j < n; j++)
			if (*(a + j) < *(a + i)) swap(a + i, a + j);
}

void printArray(int *a, int n) {
	for (int *pa = a; pa < a + n; printf("%d ", *pa++));
	printf("\n");
}

int main() {
	int *a, *pa, n;
	scanf("%d", &n);

	a = (int *)malloc(n * sizeof(int));
	if (a == NULL) return -1;

	srand(time(NULL));

	for (pa = a; pa < a + n; *pa++ = rand() / (RAND_MAX + 1.) * n + 1);

	printArray(a, n);

	// sort
	selection(a, n);

	printArray(a, n);
}