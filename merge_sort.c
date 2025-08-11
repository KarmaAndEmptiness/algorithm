#include <stdio.h>
void merge(int nums[], size_t left, size_t mid, size_t right)
{
  size_t i = left, j = mid + 1, k = 0;
  int tmp[right - left + 1];
  while (i <= mid && j <= right)
  {
    if (nums[i] <= nums[j])
    {
      tmp[k++] = nums[i++];
    }
    else
    {
      tmp[k++] = nums[j++];
    }
  }
  while (i <= mid)
  {
    tmp[k++] = nums[i++];
  }
  while (j <= right)
  {
    tmp[k++] = nums[j++];
  }
  for (k = 0; k < right - left + 1; k++)
  {
    nums[left + k] = tmp[k];
  }
}
void merge_sort(int nums[], size_t left, size_t right)
{
  if (left >= right)
  {
    return;
  }
  size_t mid = (left + right) / 2;
  merge_sort(nums, left, mid);
  merge_sort(nums, mid + 1, right);
  merge(nums, left, mid, right);
}
int main()
{
  int nums[] = {3, 1, 2, 4, 5}, len = sizeof nums / sizeof nums[0];
  merge_sort(nums, 0, len - 1);
  for (size_t i = 0; i < len; i++)
  {
    printf("%d ", nums[i]);
  }
  printf("\n");
  return 0;
}