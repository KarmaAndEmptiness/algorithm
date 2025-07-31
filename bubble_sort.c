#include <stdio.h>
void swap(int *a, int *b)
{
  int tmp = *a;
  *a = *b;
  *b = tmp;
}
void bubble_sort(int nums[], int len)
{
  for (int i = len - 1; i > 0; i--)
  {
    for (int j = 0; j < i; j++)
    {
      if (nums[j] > nums[j + 1])
      {
        swap(&nums[j], &nums[j + 1]);
      }
    }
  }
}
int main()
{
  int nums[] = {3, 2, 1, 4, 5}, len = sizeof nums / sizeof nums[0];
  bubble_sort(nums, len);
  for (int i = 0; i < len; i++)
  {
    printf("%d ", nums[i]);
  }
  printf("\n");
  return 0;
}