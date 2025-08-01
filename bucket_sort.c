#include <stdio.h>
#include <stdbool.h>
void swap(float *a, float *b)
{
  float tmp = *a;
  *a = *b;
  *b = tmp;
}
void min_shift_down(float nums[], int i, int len)
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
void heap_sort(float nums[], int len)
{
  for (int i = len / 2 - 1; i >= 0; i--)
  {
    min_shift_down(nums, i, len);
  }
  for (int i = len - 1; i > 0; i--)
  {
    swap(&nums[0], &nums[i]);
    min_shift_down(nums, 0, i);
  }
}

void bucket_sort(float nums[], int len)
{
  if (len <= 1)
  {
    return;
  }
  int k = len / 2;
  float buckets[k][len];
  int sizes[k];
  for (int i = 0; i < k; i++)
  {
    sizes[i] = 0;
  }
  for (int i = 0; i < len; i++)
  {
    int j = nums[i] * k;
    buckets[j][sizes[j]++] = nums[i];
  }
  for (int i = 0; i < k; i++)
  {
    heap_sort(buckets[i], sizes[i]);
  }
  int idx = 0;
  for (int i = k - 1; i >= 0; i--)
  {
    for (int j = 0; j < sizes[i]; j++)
    {
      nums[idx++] = buckets[i][j];
    }
  }
}
int main()
{
  float nums[] = {0.3, 0.4, 0.6, 0.5};
  int len = sizeof nums / sizeof nums[0];
  bucket_sort(nums, len);
  for (int i = 0; i < len; i++)
  {
    printf("%f ", nums[i]);
  }
  printf("\n");
  return 0;
}