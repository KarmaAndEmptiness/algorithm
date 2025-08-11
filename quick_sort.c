#include <stdio.h>
void swap(int *a, int *b)
{
  int tmp = *a;
  *a = *b;
  *b = tmp;
}
size_t median_three(int nums[], int left, int mid, int right)
{
  size_t l = left, r = right, m = mid;
  if ((l < m && m < r) || (r < m && m < l))
  {
    return mid;
  }
  if ((m < l && l < r) || (r < l && l < m))
  {
    return left;
  }
  return right;
}
size_t partition(int nums[], size_t left, size_t right)
{
  size_t i = left, j = right, med = median_three(nums, left, (left + right) / 2, right);
  swap(&nums[left], &nums[med]);
  while (i < j)
  {
    while (i < j && nums[j] >= nums[left])
    {
      j--;
    }
    while (i < j && nums[i] <= nums[left])
    {
      i++;
    }
    swap(&nums[i], &nums[j]);
  }
  swap(&nums[left], &nums[i]);
  return i;
}
void quick_sort(int nums[], size_t left, size_t right)
{
  if (left >= right)
  {
    return;
  }
  size_t pivot = partition(nums, left, right);
  quick_sort(nums, left, pivot - 1);
  quick_sort(nums, pivot + 1, right);
}
int main()
{
  int nums[] = {3, 1, 2, 4, 5}, len = sizeof nums / sizeof nums[0];
  quick_sort(nums, 0, len - 1);
  for (size_t i = 0; i < len; i++)
  {
    printf("%d ", nums[i]);
  }
  printf("\n");
  return 0;
}