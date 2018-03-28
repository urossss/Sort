#include <stdio.h>


void printArray(int *a, int n) {
	for (int *pa = a; pa < a + n; printf("%d ", *pa++));
	printf("\n");
}

int main() {
	int *a, *pa, n;
	scanf("%d", &n);

	a = (int *)malloc(n * sizeof(int));
	if (a == NULL) return -1;

	for (pa = a; pa < a + n; *pa = pa++ - a + 1);

	printArray(a, n);
}