#include <stdio.h>
#include <stdbool.h>
void swap(int *a, int *b)
{
  int tmp = *a;
  *a = *b;
  *b = tmp;
}
void min_shift_down(int nums[], int i, int len)
{
  while (true)
  {
    int l = 2 * i + 1, r = 2 * i + 2, mi = i;
    if (l < len && nums[l] < nums[mi])
    {
      mi = l;
    }
    if (r < len && nums[r] < nums[mi])
    {
      mi = r;
    }
    if (mi == i)
    {
      break;
    }
    swap(&nums[i], &nums[mi]);
    i = mi;
  }
}
void heap_sort(int nums[], int len)
{
  for (int i = len / 2 - 1; i >= 0; i--)
  {
    min_shift_down(nums, i, len);
  }
  for (int i = len - 1; i > 0; i--)
  {
    swap(&nums[i], &nums[0]);
    min_shift_down(nums, 0, i);
  }
}
int main()
{
  int nums[] = {3, 1, 5, 2, 4}, len = sizeof nums / sizeof nums[0];
  heap_sort(nums, len);
  for (int i = 0; i < len; i++)
  {
    printf("%d ", nums[i]);
  }
  printf("\n");
  return 0;
}