def quickSort(arr):
    if len(arr) <= 1 :return arr

    else:
        p = arr[0]
        left = [x for x in arr[1:] if x < p]
        right = [x for x in arr[1:] if x >=p]

        return quickSort(left) + [p] + quickSort(right)
