//Quick Sort
#include <stdio.h>

void swap(int arr[], int x, int y)
{
    int temp = arr[x];
    arr[x] = arr[y];
    arr[y] = temp;
}

int partition(int arr[], int l, int r)
{
    int pivot = arr[l];
    int start = l;
    int end = r;

    while (start < end)
    {
        while (arr[start] <= pivot)
            start++;
        while (arr[end] > pivot)
            end--;

        if (start < end)
            swap(arr, start, end);
    }

    swap(arr, l, end);
    return end;
}

void quickSort(int arr[], int l, int r)
{
    if (l >= r)
        return;

    int pivot = partition(arr, l, r);

    quickSort(arr, l, pivot - 1);
    quickSort(arr, pivot + 1, r);
}

void print(int arr[], int size)
{
    for (int i = 0; i < size; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

void main()
{
    int size;

    printf("\nEnter Size Of Array:");
    scanf("%d", &size);

    int arr[size];

    printf("\nEnter Array:");
    for (int i = 0; i < size; i++)
        scanf("%d", &arr[i]);

    printf("\nGiven array is \n");
    print(arr, size);

    quickSort(arr, 0, size - 1);

    printf("\nSorted array is \n");
    print(arr, size);
}