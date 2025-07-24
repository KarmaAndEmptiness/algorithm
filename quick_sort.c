#include <stdio.h>
int median_three(int arr[], int left, int mid, int right)
{
  int l = arr[left], m = arr[mid], r = arr[right];
  if ((m > l && r > m) || (m > r && l > m))
  {
    return mid;
  }
  if ((l > m && r > l) || (l > r && m > l))
  {
    return left;
  }
  return right;
}
void swap(int *a, int *b)
{
  int tmp = 0;
  tmp = *a;
  *a = *b;
  *b = tmp;
}
int partition(int arr[], int left, int right)
{
  int mid = median_three(arr, left, (left + right) / 2, right), pivot = arr[mid], i = left, j = right;
  swap(&arr[left], &arr[mid]);
  while (i < j)
  {
    while (i < j && arr[j] >= pivot)
    {
      j--;
    }
    while (i < j && arr[i] <= pivot)
    {
      i++;
    }
    swap(&arr[i], &arr[j]);
  }
  swap(&arr[left], &arr[i]);
  return i;
}
void quick_sort(int arr[], int left, int right)
{
  if (left >= right)
    return;
  int pivot = partition(arr, left, right);
  quick_sort(arr, left, pivot - 1);
  quick_sort(arr, pivot + 1, right);
}
int main()
{
  int arr[] = {3, 2, 1, 4, 5};
  int len = sizeof arr / sizeof arr[0];
  quick_sort(arr, 0, len - 1);
  for (int i = 0; i < len; i++)
  {
    printf("%d ", arr[i]);
  }
  printf("\n");
  return 0;
}