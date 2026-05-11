#include <stdio.h>
#include <stdlib.h>

void printArray(int arr[], int size) {
    printf("[");

    for (int i = 0; i < size; i++) {
        printf("%d", arr[i]);

        if (i < size - 1) {
            printf(" ");
        }
    }

    printf("]\n");
}

int isSorted(int arr[], int size) {
    for (int i = 1; i < size; i++) {
        if (arr[i - 1] > arr[i]) {
            return 0;
        }
    }

    return 1;
}

void insertionSort(int arr[], int left, int right) {
    for (int i = left + 1; i <= right; i++) {
        int key = arr[i];
        int j = i - 1;

        while (j >= left && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }

        arr[j + 1] = key;
    }
}

void merge(int arr[], int left, int mid, int right) {
    int size1 = mid - left + 1;
    int size2 = right - mid;

    int* leftArr = malloc(size1 * sizeof(int));
    int* rightArr = malloc(size2 * sizeof(int));

    for (int i = 0; i < size1; i++) {
        leftArr[i] = arr[left + i];
    }

    for (int i = 0; i < size2; i++) {
        rightArr[i] = arr[mid + 1 + i];
    }

    int i = 0;
    int j = 0;
    int k = left;

    while (i < size1 && j < size2) {
        if (leftArr[i] <= rightArr[j]) {
            arr[k] = leftArr[i];
            i++;
        } else {
            arr[k] = rightArr[j];
            j++;
        }

        k++;
    }

    while (i < size1) {
        arr[k] = leftArr[i];
        i++;
        k++;
    }

    while (j < size2) {
        arr[k] = rightArr[j];
        j++;
        k++;
    }

    free(leftArr);
    free(rightArr);
}

void hybridMergeSort(int arr[], int left, int right, int k) {
    if (left >= right) {
        return;
    }

    int currentSize = right - left + 1;

    if (currentSize <= k) {
        insertionSort(arr, left, right);
        return;
    }

    int mid = left + (right - left) / 2;

    hybridMergeSort(arr, left, mid, k);
    hybridMergeSort(arr, mid + 1, right, k);

    merge(arr, left, mid, right);
}

int main() {
    int arr[] = {39, 9, 81, 45, 90, 27, 72, 18};
    int size = sizeof(arr) / sizeof(arr[0]);

    int k = 3;

    printf("Original array:\n");
    printArray(arr, size);

    hybridMergeSort(arr, 0, size - 1, k);

    printf("Sorted array:\n");
    printArray(arr, size);

    if (isSorted(arr, size)) {
        printf("Result: PASS\n");
    } else {
        printf("Result: FAIL\n");
    }

    return 0;
}