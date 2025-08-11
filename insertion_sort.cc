#include <iostream>
#include <vector>
void insertion_sort(std::vector<int> &nums)
{
  if (nums.size() < 2)
  {
    return;
  }
  for (size_t i = 1; i < nums.size(); i++)
  {
    int base = nums[i], j = i - 1;
    while (j < i && nums[j] > base)
    {
      nums[j + 1] = nums[j];
      j--;
    }
    nums[j + 1] = base;
  }
}
int main()
{
  std::vector<int> nums = {3, 2, 4, 1, 5};
  insertion_sort(nums);
  for (const int &item : nums)
  {
    std::cout << item << " ";
  }
  std::cout << std::endl;
  return 0;
}