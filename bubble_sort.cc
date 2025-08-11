#include <iostream>
#include <vector>
void bubble_sort(std::vector<int> &nums)
{
  for (size_t i = nums.size() - 1; i > 0; i--)
  {
    bool flag = false;
    for (size_t j = 0; j < i; j++)
    {
      if (nums[j] > nums[j + 1])
      {
        std::swap(nums[j], nums[j + 1]);
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
  std::vector<int> nums = {3, 1, 2, 4, 5};
  bubble_sort(nums);
  for (const int &item : nums)
  {
    std::cout << item << " ";
  }
  std::cout << std::endl;
  return 0;
}