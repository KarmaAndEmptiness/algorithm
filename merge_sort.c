#include <stdio.h>
void merge(int nums[], int left, int mid, int right)
{
  int i = left, j = mid + 1, k = 0, len = right - left + 1;
  int tmp[len];
  while (i <= mid && j <= right)
  {
    if (nums[i] >= nums[j])
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
  for (k = 0; k < len; k++)
  {
    nums[left + k] = tmp[k];
  }
}
void merge_sort(int nums[], int left, int right)
{
  if (left >= right)
  {
    return;
  }
  int mid = (left + right) / 2;
  merge_sort(nums, left, mid);
  merge_sort(nums, mid + 1, right);
  merge(nums, left, mid, right);
}
int main()
{
  int nums[] = {3, 1, 5, 4, 2}, len = sizeof nums / sizeof nums[0];
  merge_sort(nums, 0, len - 1);
  for (int i = 0; i < len; i++)
  {
    printf("%d ", nums[i]);
  }
  printf("\n");
  return 0;
}