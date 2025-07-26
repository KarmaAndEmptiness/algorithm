#include <iostream>
#include <vector>
void merge(std::vector<int> &nums, int left, int mid, int right)
{
  int i = left, j = mid + 1, k = 0;
  std::vector<int> tmp(right - left + 1);
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
  for (k = 0; k < tmp.size(); k++)
  {
    nums[left + k] = tmp[k];
  }
}
void merge_sort(std::vector<int> &nums, int left, int right)
{
  if (left >= right)
    return;
  int mid = (left + right) / 2;
  merge_sort(nums, left, mid);
  merge_sort(nums, mid + 1, right);
  merge(nums, left, mid, right);
}
int main()
{
  std::vector<int> nums = {3, 2, 1, 4, 5};
  merge_sort(nums, 0, nums.size() - 1);
  for (int item : nums)
  {
    std::cout << item << " ";
  }
  std::cout << std::endl;
  return 0;
}