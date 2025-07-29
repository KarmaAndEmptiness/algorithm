#include <iostream>
#include <vector>
void max_shift_down(std::vector<int> &nums, int i, int n)
{
  while (true)
  {
    int l = 2 * i + 1, r = 2 * i + 2, ma = i;
    if (l < n && nums[l] > nums[ma])
    {
      ma = l;
    }
    if (r < n && nums[r] > nums[ma])
    {
      ma = r;
    }
    if (ma == i)
    {
      break;
    }
    std::swap(nums[i], nums[ma]);
    i = ma;
  }
}
void heap_sort(std::vector<int> &nums)
{
  for (int i = nums.size() / 2 - 1; i >= 0; i--)
  {
    max_shift_down(nums, i, nums.size());
  }
  for (int i = nums.size() - 1; i > 0; i--)
  {
    std::swap(nums[0], nums[i]);
    max_shift_down(nums, 0, i);
  }
}
int main()
{
  std::vector<int> nums = {3, 2, 1, 4, 5};
  heap_sort(nums);
  for (int item : nums)
  {
    std::cout << item << " ";
  }
  std::cout << std::endl;
  return 0;
}