#include <iostream>
#include <vector>
int median_three(std::vector<int> &nums, int left, int mid, int right)
{
  int l = left, r = right, m = mid;
  if ((m > l && r > m) || (m > r && l > m))
  {
    return m;
  }
  if ((l > m && r > l) || (l > r && m > l))
  {
    return l;
  }
  return r;
}
int partition(std::vector<int> &nums, int left, int right)
{
  int i = left, j = right, med = median_three(nums, left, (left + right) / 2, right);
  std::swap(nums[left], nums[med]);
  while (i < j)
  {
    while (i < j && nums[j] >= nums[left])
    {
      j--;
    }
    while (i < j && nums[i] <= nums[left])
    {
      i++;
    }
    std::swap(nums[i], nums[j]);
  }
  std::swap(nums[left], nums[i]);
  return i;
}
void quick_sort(std::vector<int> &nums, int left, int right)
{
  if (left >= right)
    return;
  int pivot = partition(nums, left, right);
  quick_sort(nums, left, pivot - 1);
  quick_sort(nums, pivot + 1, right);
}
int main()
{
  std::vector<int> nums = {3, 2, 1, 4, 5};
  quick_sort(nums, 0, nums.size() - 1);
  for (int item : nums)
  {
    std::cout << item << " ";
  }
  std::cout << std::endl;
  return 0;
}