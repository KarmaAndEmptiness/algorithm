#include <stdio.h>
#include <stdbool.h>
void swap(int *a, int *b)
{
  int tmp = *a;
  *a = *b;
  *b = tmp;
}
void bubble_sort(int nums[], int len)
{
  for (size_t i = len - 1; i > 0; i--)
  {
    bool flag = false;
    for (size_t j = 0; j < i; j++)
    {
      if (nums[j] > nums[j + 1])
      {
        swap(&nums[j], &nums[j + 1]);
        flag = true;
      }
    }
    if (!flag)
    {
      break;
    }
  }
}
int main()
{
  int nums[] = {3, 1, 2, 4, 5}, len = sizeof nums / sizeof nums[0];
  bubble_sort(nums, len);
  for (size_t i = 0; i < len; i++)
  {
    printf("%d ", nums[i]);
  }
  printf("\n");
}