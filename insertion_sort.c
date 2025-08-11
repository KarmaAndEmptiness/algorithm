#include <stdio.h>
void insertion_sort(int nums[], int len)
{
  if (len < 2)
  {
    return;
  }
  for (size_t i = 0; i < len; i++)
  {
    int base = nums[i + 1], j = i;
    while (j <= i && nums[j] > base)
    {
      nums[j + 1] = nums[j];
      j--;
    }
    nums[j + 1] = base;
  }
}
int main()
{
  int nums[] = {3, 1, 2, 4, 5}, len = sizeof nums / sizeof nums[0];
  insertion_sort(nums, len);
  for (size_t i = 0; i < len; i++)
  {
    printf("%d ", nums[i]);
  }
  printf("\n");
  return 0;
}