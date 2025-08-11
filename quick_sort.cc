#include <iostream>
#include <vector>
size_t median_three(const std::vector<int> &nums, size_t left, size_t mid, size_t right)
{
  size_t l = left, m = mid, r = right;
  if ((l < m && m < r) || (r < m && m < l))
  {
    return mid;
  }
  if ((m < l && l < r) || (r < l && l < m))
  {
    return left;
  }
  return right;
}
size_t partition(std::vector<int> &nums, size_t left, size_t right)
{
  size_t i = left, j = right, med = median_three(nums, left, (left + right) / 2, right);
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
void quick_sort(std::vector<int> &nums, size_t left, size_t right)
{
  if (left >= right)
  {
    return;
  }
  size_t pivot = partition(nums, left, right);
  quick_sort(nums, left, pivot - 1);
  quick_sort(nums, pivot + 1, right);
}
int main()
{
  std::vector<int> nums = {3, 2, 4, 1, 5};
  quick_sort(nums, 0, nums.size() - 1);
  for (const int &item : nums)
  {
    std::cout << item << " ";
  }
  std::cout << std::endl;
  return 0;
}