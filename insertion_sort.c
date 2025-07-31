#include <stdio.h>
void insertion_sort(int nums[], int len)
{
  if (len <= 0)
  {
    return;
  }
  for (int i = 1; i < len; i++)
  {
    int base = nums[i], j = i - 1;
    while (j >= 0 && nums[j] > base)
    {
      nums[j + 1] = nums[j];
      j--;
    }
    nums[j + 1] = base;
  }
}
int main()
{
  int nums[] = {3, 2, 1, 4, 5}, len = sizeof nums / sizeof nums[0];
  insertion_sort(nums, len);
  for (int i = 0; i < len; i++)
  {
    printf("%d ", nums[i]);
  }
  printf("\n");
  return 0;
}