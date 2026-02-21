# FIXED SLIDING WINDOW
# Maximum sum of subarray of size k

def max_sum_subarray(arr, k):
    n = len(arr)
    if n < k:
        return -1

    window_sum = sum(arr[:k])
    max_sum = window_sum

    for i in range(k, n):
        window_sum += arr[i]      # add right element
        window_sum -= arr[i - k]  # remove left element
        max_sum = max(max_sum, window_sum)

    return max_sum


if __name__ == "__main__":
    arr = [2, 1, 5, 1, 3, 2]
    k = 3
    print("Max Sum of Subarray of size k:", max_sum_subarray(arr, k))
