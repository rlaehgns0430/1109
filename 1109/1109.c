#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

long long count_first = 0;
long long count_random = 0;
long long count_median = 0;

void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int partition_first(int arr[], int low, int high) {
    int pivot = arr[low];
    int i = low;
    int j = high + 1;
    do {
        do {
            count_first++;
            i++;
        } while (i <= high && arr[i] < pivot);
        do {
            count_first++;
            j--;
        } while (arr[j] > pivot);
        if (i < j) swap(&arr[i], &arr[j]);
    } while (i < j);
    swap(&arr[low], &arr[j]);
    return j;
}

void quick_sort_first(int arr[], int low, int high) {
    if (low < high) {
        int p = partition_first(arr, low, high);
        quick_sort_first(arr, low, p - 1);
        quick_sort_first(arr, p + 1, high);
    }
}

int partition_random(int arr[], int low, int high) {
    int r = low + rand() % (high - low + 1);
    swap(&arr[low], &arr[r]);
    int pivot = arr[low];
    int i = low;
    int j = high + 1;
    do {
        do {
            count_random++;
            i++;
        } while (i <= high && arr[i] < pivot);
        do {
            count_random++;
            j--;
        } while (arr[j] > pivot);
        if (i < j) swap(&arr[i], &arr[j]);
    } while (i < j);
    swap(&arr[low], &arr[j]);
    return j;
}

void quick_sort_random(int arr[], int low, int high) {
    if (low < high) {
        int p = partition_random(arr, low, high);
        quick_sort_random(arr, low, p - 1);
        quick_sort_random(arr, p + 1, high);
    }
}

int partition_median(int arr[], int low, int high) {
    int mid = low + (high - low) / 2;
    int p_idx = low;
    count_median++;
    if (arr[low] < arr[mid]) {
        count_median++;
        if (arr[mid] < arr[high]) p_idx = mid;
        else {
            count_median++;
            if (arr[low] < arr[high]) p_idx = high;
            else p_idx = low;
        }
    }
    else {
        count_median++;
        if (arr[low] < arr[high]) p_idx = low;
        else {
            count_median++;
            if (arr[mid] < arr[high]) p_idx = high;
            else p_idx = mid;
        }
    }
    swap(&arr[low], &arr[p_idx]);
    int pivot = arr[low];
    int i = low;
    int j = high + 1;
    do {
        do {
            count_median++;
            i++;
        } while (i <= high && arr[i] < pivot);
        do {
            count_median++;
            j--;
        } while (arr[j] > pivot);
        if (i < j) swap(&arr[i], &arr[j]);
    } while (i < j);
    swap(&arr[low], &arr[j]);
    return j;
}

void quick_sort_median(int arr[], int low, int high) {
    if (low < high) {
        int p = partition_median(arr, low, high);
        quick_sort_median(arr, low, p - 1);
        quick_sort_median(arr, p + 1, high);
    }
}

int partition_iterative(int arr[], int low, int high) {
    int mid = low + (high - low) / 2;
    int p_idx = low;
    if (arr[low] < arr[mid]) {
        if (arr[mid] < arr[high]) p_idx = mid;
        else {
            if (arr[low] < arr[high]) p_idx = high;
            else p_idx = low;
        }
    }
    else {
        if (arr[low] < arr[high]) p_idx = low;
        else {
            if (arr[mid] < arr[high]) p_idx = high;
            else p_idx = mid;
        }
    }
    swap(&arr[low], &arr[p_idx]);
    int pivot = arr[low];
    int i = low;
    int j = high + 1;
    do {
        do { i++; } while (i <= high && arr[i] < pivot);
        do { j--; } while (arr[j] > pivot);
        if (i < j) swap(&arr[i], &arr[j]);
    } while (i < j);
    swap(&arr[low], &arr[j]);
    return j;
}

void quick_sort_iterative(int arr[], int low, int high) {
    int* stack = (int*)malloc(sizeof(int) * (high - low + 1));
    int top = -1;
    stack[++top] = low;
    stack[++top] = high;
    while (top >= 0) {
        high = stack[top--];
        low = stack[top--];
        int p = partition_iterative(arr, low, high);
        if (p - 1 > low) {
            stack[++top] = low;
            stack[++top] = p - 1;
        }
        if (p + 1 < high) {
            stack[++top] = p + 1;
            stack[++top] = high;
        }
    }
    free(stack);
}

int main() {
    srand((unsigned int)time(NULL));
    int sizes[] = { 1000, 2000, 4000, 8000, 16000, 20000 };
    int num_sizes = sizeof(sizes) / sizeof(sizes[0]);

    for (int i = 0; i < num_sizes; i++) {
        int n = sizes[i];
        int* orig = (int*)malloc(sizeof(int) * n);
        int* copy1 = (int*)malloc(sizeof(int) * n);
        int* copy2 = (int*)malloc(sizeof(int) * n);
        int* copy3 = (int*)malloc(sizeof(int) * n);

        for (int j = 0; j < n; j++) {
            orig[j] = rand() % 100000;
        }

        memcpy(copy1, orig, sizeof(int) * n);
        memcpy(copy2, orig, sizeof(int) * n);
        memcpy(copy3, orig, sizeof(int) * n);

        count_first = 0;
        quick_sort_first(copy1, 0, n - 1);

        count_random = 0;
        quick_sort_random(copy2, 0, n - 1);

        count_median = 0;
        quick_sort_median(copy3, 0, n - 1);

        printf("Data Size : %d\n\n", n);
        printf("Quick Sort (First)    : %lld comparisons\n", count_first);
        printf("Quick Sort (Random)   : %lld comparisons\n", count_random);
        printf("Quick Sort (Median-3) : %lld comparisons\n\n", count_median);

        free(orig);
        free(copy1);
        free(copy2);
        free(copy3);
    }

    int b_size = 10000;
    int* b_orig = (int*)malloc(sizeof(int) * b_size);
    int* b_copy1 = (int*)malloc(sizeof(int) * b_size);
    int* b_copy2 = (int*)malloc(sizeof(int) * b_size);

    for (int j = 0; j < b_size; j++) {
        b_orig[j] = rand() % 100000;
    }

    double rec_total = 0, iter_total = 0;
    int trials = 10;

    for (int t = 0; t < trials; t++) {
        memcpy(b_copy1, b_orig, sizeof(int) * b_size);
        memcpy(b_copy2, b_orig, sizeof(int) * b_size);

        clock_t start = clock();
        quick_sort_median(b_copy1, 0, b_size - 1);
        clock_t end = clock();
        rec_total += (double)(end - start) * 1000.0 / CLOCKS_PER_SEC;

        start = clock();
        quick_sort_iterative(b_copy2, 0, b_size - 1);
        end = clock();
        iter_total += (double)(end - start) * 1000.0 / CLOCKS_PER_SEC;
    }

    printf("Data Size : %d\n", b_size);
    printf("Pivot     : Median-of-Three\n\n");
    printf("Recursive Quick Sort : %.2f ms\n", rec_total / trials);
    printf("Iterative Quick Sort : %.2f ms\n", iter_total / trials);

    free(b_orig);
    free(b_copy1);
    free(b_copy2);

    return 0;
}