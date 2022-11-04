#include <stdio.h>
#include <stdlib.h>

/*------------------------------------------------*/
/* Code to remove data from the processor caches. */
#define KB (1024)
#define MB (1024 * KB)
#define GB (1024 * MB)
#define LARGEST_CACHE_SZ (12 * MB)

static unsigned char dummy_buffer[LARGEST_CACHE_SZ];

void clean_cache() {
    unsigned long long i;
    for (i = 0; i < LARGEST_CACHE_SZ; i++)
        dummy_buffer[i] += 1;
}
/*------------------------------------------------*/

#define ARRAY_SIZE (512 * KB)
#define RAND_SEED 23

void quickSort(int *arr, int left, int right) {
    int i = left, j = right;
    int tmp;
    int pivot = arr[(left + right) / 2];

    /* partition */
    while (i <= j) {
        while (arr[i] < pivot)
            i++;
        while (arr[j] > pivot)
            j--;
        if (i <= j) {
            tmp = arr[i];
            arr[i] = arr[j];
            arr[j] = tmp;
            i++;
            j--;
        }
    };

    /* recursion */
    if (left < j)
        quickSort(arr, left, j);
    if (i < right)
        quickSort(arr, i, right);
}

void bubbleSort(int *arr, int n) {
    int tmp;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                tmp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = tmp;
            }
        }
    }
}

void merge(int *arr, int start, int mid, int end) {
    int *aux = malloc(sizeof(int) * (end - start + 1));

    int i = start;
    int j = mid + 1;
    int k = 0;

    while (i <= mid && j <= end) {
        if (arr[i] <= arr[j]) {
            aux[k] = arr[i];
            i++;
        } else {
            aux[k] = arr[j];
            j++;
        }
        k++;
    }

    while (i <= mid) {
        aux[k] = arr[i];
        i++;
        k++;
    }

    while (j <= end) {
        aux[k] = arr[j];
        j++;
        k++;
    }

    for (i = start, k = 0; i <= end; i++, k++) {
        arr[i] = aux[k];
    }
    free(aux);
}

void mergeSort(int *arr, int start, int end) {
    if (end <= start) return;
    int mid = (int) (start + end) / 2.0;

    mergeSort(arr, start, mid);
    mergeSort(arr, mid + 1, end);

    merge(arr, start, mid, end);
}

void insertionSort(int *arr, int n) {
    int i, j, tmp;
    for (i = 1; i < n; i++) {
        tmp = arr[i];
        for (j = i; j > 0 && arr[j - 1] > tmp; j--)
            arr[j] = arr[j - 1];
        arr[j] = tmp;
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: ./main <sort algorithm>\n");
        printf("0: quick sort\n");
        printf("1: bubble sort\n");
        printf("2: merge sort\n");
        printf("3: insertion sort\n");
        return EXIT_FAILURE;
    }
    int algorithm = atoi(argv[1]);
    
    clean_cache();
    int *array = malloc(sizeof(int) * ARRAY_SIZE);
    
    srand(RAND_SEED);       
    for (int i = 0; i < ARRAY_SIZE; i++)
        array[i] = rand();

    switch (algorithm) {
        case 0:
            quickSort(array, 0, ARRAY_SIZE - 1);
            break;
        case 1:
            bubbleSort(array, ARRAY_SIZE);
            break;
        case 2:
            mergeSort(array, 0, ARRAY_SIZE - 1);
            break;
        case 3:
            insertionSort(array, ARRAY_SIZE);
            break;
        default:
            break;
    }

    free(array);

    return EXIT_SUCCESS;
}