#include <stdio.h>
void swap(int *a, int *b)
{
  int tmp = *a;
  *a = *b;
  *b = tmp;
}
int median_three(int nums[], int left, int mid, int right)
{
  int l = left, r = right, m = mid;
  if ((l < m && m < r) || (r < m && m < l))
  {
    return mid;
  }
  if ((r < l && l < m) || (m < l && l < r))
  {
    return left;
  }
  return right;
}
int partition(int nums[], int left, int right)
{
  int i = left, j = right, med = median_three(nums, left, (left + right) / 2, right);
  swap(&nums[left], &nums[med]);
  while (i < j)
  {
    while (i < j && nums[j] <= nums[left])
    {
      j--;
    }
    while (i < j && nums[i] >= nums[left])
    {
      i++;
    }
    swap(&nums[i], &nums[j]);
  }
  swap(&nums[left], &nums[i]);
  return i;
}
void quick_sort(int nums[], int left, int right)
{
  if (left >= right)
  {
    return;
  }
  int pivot = partition(nums, left, right);
  quick_sort(nums, left, pivot - 1);
  quick_sort(nums, pivot + 1, right);
}
int main()
{
  int nums[] = {3, 1, 5, 4, 2}, len = sizeof nums / sizeof nums[0];
  quick_sort(nums, 0, len - 1);
  for (int i = 0; i < len; i++)
  {
    printf("%d ", nums[i]);
  }
  printf("\n");
  return 0;
}