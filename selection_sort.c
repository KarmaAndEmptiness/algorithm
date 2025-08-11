#include <stdio.h>
void swap(int *a, int *b)
{
  int tmp = *a;
  *a = *b;
  *b = tmp;
}
void selection_sort(int nums[], int len)
{
  for (int i = 0; i < len; i++)
  {
    int ma = i;
    for (int j = i + 1; j < len; j++)
    {
      if (nums[j] > nums[ma])
      {
        ma = j;
      }
    }
    if (ma == i)
    {
      continue;
    }
    swap(&nums[i], &nums[ma]);
  }
}
int main()
{
  int nums[] = {3, 2, 1, 4, 5}, len = sizeof nums / sizeof nums[0];
  selection_sort(nums, len);
  for (int i = 0; i < len; i++)
  {
    printf("%d ", nums[i]);
  }
  printf("\n");
  return 0;
}