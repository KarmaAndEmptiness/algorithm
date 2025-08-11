#include <iostream>
#include <vector>
void selection_sort(std::vector<int> &nums)
{
  for (size_t i = 0; i < nums.size() - 1; i++)
  {
    size_t ma = i;
    for (int j = i + 1; j < nums.size(); j++)
    {
      if (nums[j] > nums[ma])
      {
        ma = j;
      }
    }
    std::swap(nums[i], nums[ma]);
  }
}
int main()
{
  std::vector<int> nums = {3, 2, 4, 1, 5};
  selection_sort(nums);
  for (const int &item : nums)
  {
    std::cout << item << " ";
  }
  std::cout << std::endl;
  return 0;
}