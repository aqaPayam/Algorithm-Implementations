def mergeSort(arr):
    inversion_count = 0
    if len(arr) <= 1:
        return 0

    mid = len(arr) // 2
    L = arr[:mid]
    R = arr[mid:]

    inversion_count += mergeSort(L)
    inversion_count += mergeSort(R)

    i = j = k = 0

    while i < len(L) and j < len(R):
        if L[i] < R[j]:
            arr[k] = L[i]
            i += 1
        else:
            arr[k] = R[j]
            j += 1
            inversion_count += len(L) - i
        k += 1

    while i < len(L):
        arr[k] = L[i]
        i += 1
        k += 1

    while j < len(R):
        arr[k] = R[j]
        j += 1
        k += 1

    return inversion_count


n = int(input())
arr = list(map(int, input().strip().split()))[:n]

result = mergeSort(arr)
print(result)
