#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

void insertion(int *a, int n) {
	int i, j;
	for (i = 1; i < n; i++) {
		int tmp = *(a + i);
		for (j = i - 1; j >= 0; j--) {
			if (tmp < *(a + j)) {
				*(a + j + 1) = *(a + j);
			}
			else break;
		}
		*(a + j + 1) = tmp;
	}
}

void counting(int *a, int n) {
	int *count = (int*)calloc(n + 1, sizeof(int)), i;
	if (count == NULL) exit(1);

	int *b = (int*)malloc(n * sizeof(int));
	if (b == NULL) exit(2);
	memcpy(b, a, n * sizeof(int));

	for (i = 0; i < n; i++) count[a[i]]++;
	for (i = 1; i <= n; i++) count[i] += count[i - 1];
	
	for (i = 0; i < n; i++) {
		a[count[b[i]] - 1] = b[i];
		count[b[i]]--;
	}

	free(b);
	free(count);
}

void quick(int *a, int beg, int end) {
	if (beg == end) return;
	int wall = beg;
	for (int i = beg; i < end; i++)
		if (a[i] < a[end]) {
			swap(&a[i], &a[wall]);
			wall++;
		}
	swap(&a[wall], &a[end]);
	if (wall > beg) quick(a, beg, wall - 1);
	if (wall < end) quick(a, wall + 1, end);
}

void printArray(int *a, int n) {
	for (int *pa = a; pa < a + n; printf("%d ", *pa++));
	printf("\n");
}

void printCurrentTime() {
	time_t pIntTime = time(NULL);
	struct tm* currentLocalTime = localtime(&pIntTime);
	char timeString[11];
	if (currentLocalTime) {
		strftime(timeString, 10, "%H:%M:%S", currentLocalTime);
		puts(timeString);
	}
}

/*int main() {
	int *a, *pa, n;
	clock_t t1, t2;
	double d;

	scanf("%d", &n);

	a = (int *)malloc(n * sizeof(int));
	if (a == NULL) return -1;

	srand(time(NULL));

	for (pa = a; pa < a + n; *pa++ = rand() / (RAND_MAX + 1.) * n + 1);

	//printArray(a, n);

	printCurrentTime();
	t1 = clock();
	//selection(a, n);
	//insertion(a, n);
	counting(a, n);
	//quick(a, 0, n - 1);

	t2 = clock();
	d = (double)(t2 - t1) / CLOCKS_PER_SEC;
	printCurrentTime();
	printf("%lgs\n", d);

	//printArray(a, n);

	free(a);
}*/