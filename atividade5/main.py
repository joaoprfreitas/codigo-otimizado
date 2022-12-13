import timeit
import numpy as np
import functools

def numpyMatrixMultiplication(A, B):
    return np.dot(A, B)

def defaultMatrixMultiplication(A, B):
    C = [[0 for i in range(len(B[0]))] for j in range(len(A))]
    for i in range(len(A)):
        for j in range(len(B[0])):
            for k in range(len(B)):
                C[i][j] += A[i][k] * B[k][j]
    return C

def testMatrixMultiplication():
    size = 200

    # default matrix
    A = [[np.random.randint(0, 10) for i in range(size)] for j in range(size)]
    B = [[np.random.randint(0, 10) for i in range(size)] for j in range(size)]

    # numpy matrix
    C = np.matrix([[np.random.randint(0, 10) for i in range(size)] for j in range(size)])
    D = np.matrix([[np.random.randint(0, 10) for i in range(size)] for j in range(size)])

    print("Default matrix multiplication: " + str(timeit.timeit(lambda: defaultMatrixMultiplication(A, B), number=10)) + "s")
    print("Numpy matrix multiplication: " + str(timeit.timeit(lambda: numpyMatrixMultiplication(C, D), number=10)) + "s")

def listToTuple(function):
    'Decorator to convert list to tuple'
    def wrapper(*args):
        args = [tuple(x) if type(x) == list else x for x in args]
        result = function(*args)
        result = tuple(result) if type(result) == list else result
        return result
    return wrapper

@listToTuple
def mergeSort(arr):
    if len(arr) <= 1:
        return arr
    mid = len(arr) // 2
    left = mergeSort(arr[:mid])
    right = mergeSort(arr[mid:])
    return merge(left, right)

@listToTuple
@functools.lru_cache(maxsize=None)
def cachedMergeSort(arr):
    if len(arr) <= 1:
        return arr
    mid = len(arr) // 2
    left = cachedMergeSort(arr[:mid])
    right = cachedMergeSort(arr[mid:])
    return merge(left, right)

def merge(left, right):
    result = []
    i = j = 0
    while i < len(left) and j < len(right):
        if left[i] < right[j]:
            result.append(left[i])
            i += 1
        else:
            result.append(right[j])
            j += 1
    result.extend(left[i:])
    result.extend(right[j:])
    return result

def testMergeSort():
    size = 500000
    arr1 = [np.random.randint(0, 100) for i in range(size)]
    arr2 = [np.random.randint(0, 100) for i in range(size)]
    print("Merge sort: " + str(timeit.timeit(lambda: mergeSort(arr1), number=10)) + "s")
    print("Cached merge sort: " + str(timeit.timeit(lambda: cachedMergeSort(arr2), number=10)) + "s")

def main():
    testMatrixMultiplication()
    testMergeSort()

if __name__ == '__main__':
    main()