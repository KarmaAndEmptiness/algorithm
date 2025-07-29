#include <iostream>
#include <vector>
int peek(std::vector<int> &nums)
{
  return nums[0];
}
int parent(int i)
{
  return (i - 1) / 2;
}
int left(int i)
{
  return 2 * i + 1;
}
int right(int i)
{
  return 2 * i + 2;
}
void max_shift_up(std::vector<int> &nums)
{
  if (nums.size() <= 1)
  {
    return;
  }
  for (int i = 1; i < nums.size(); i++)
  {
    int j = i;
    while (true)
    {
      int p = parent(j);
      if (p < 0 || nums[j] <= nums[p])
      {
        break;
      }
      std::swap(nums[j], nums[p]);
      j = p;
    }
  }
}
void min_shift_up(std::vector<int> &nums)
{
  if (nums.size() <= 1)
  {
    return;
  }
  for (int i = 1; i < nums.size(); i++)
  {
    int j = i;
    while (true)
    {
      int p = parent(j);
      if (p < 0 || nums[j] >= nums[p])
      {
        break;
      }
      std::swap(nums[j], nums[p]);
      j = p;
    }
  }
}
void max_shift_down(std::vector<int> &nums, int i)
{
  while (true)
  {
    int l = left(i), r = right(i), ma = i;
    if (l < nums.size() && nums[l] > nums[ma])
    {
      ma = l;
    }
    if (r < nums.size() && nums[r] > nums[ma])
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

void max_shift_down(std::vector<int> &nums)
{
  max_shift_down(nums, 0);
}

void min_shift_down(std::vector<int> &nums, int i)
{
  while (true)
  {
    int mi = i, l = left(i), r = right(i);
    if (l < nums.size() && nums[l] < nums[mi])
    {
      mi = l;
    }
    if (r < nums.size() && nums[r] < nums[mi])
    {
      mi = r;
    }
    if (mi == i)
    {
      break;
    }
    std::swap(nums[mi], nums[i]);
    i = mi;
  }
}

void min_shift_down(std::vector<int> &nums)
{
  min_shift_down(nums, 0);
}

void max_pop(std::vector<int> &nums)
{
  std::swap(nums[0], nums[nums.size() - 1]);
  nums.pop_back();
  max_shift_down(nums);
}
void min_pop(std::vector<int> &nums)
{
  std::swap(nums[0], nums[nums.size() - 1]);
  nums.pop_back();
  min_shift_down(nums);
}

void make_max_heap(std::vector<int> &nums)
{
  for (int i = nums.size() / 2 - 1; i >= 0; i--)
  {
    max_shift_down(nums, i);
  }
}
void make_min_heap(std::vector<int> &nums)
{
  for (int i = nums.size() / 2 - 1; i >= 0; i--)
  {
    min_shift_down(nums, i);
  }
}
int main()
{
  std::vector<int> max_nums = {3, 2, 4, 5, 1};
  max_shift_up(max_nums);
  for (int item : max_nums)
  {
    std::cout << item << " ";
  }
  std::cout << std::endl;
  while (max_nums.size())
  {
    std::cout << peek(max_nums) << " ";
    max_pop(max_nums);
  }
  std::cout << std::endl;

  max_nums = {3, 2, 4, 5, 1};
  make_max_heap(max_nums);
  for (int item : max_nums)
  {
    std::cout << item << " ";
  }
  std::cout << std::endl;

  while (max_nums.size())
  {
    std::cout << peek(max_nums) << " ";
    max_pop(max_nums);
  }
  std::cout << std::endl;

  std::vector<int> min_nums = {3, 2, 4, 1, 5};
  min_shift_up(min_nums);
  for (int item : min_nums)
  {
    std::cout << item << " ";
  }
  std::cout << std::endl;
  while (min_nums.size())
  {
    std::cout << peek(min_nums) << " ";
    min_pop(min_nums);
  }
  std::cout << std::endl;

  min_nums = {3, 2, 4, 1, 5};
  make_min_heap(min_nums);
  for (int item : min_nums)
  {
    std::cout << item << " ";
  }
  std::cout << std::endl;
  while (min_nums.size())
  {
    std::cout << peek(min_nums) << " ";
    min_pop(min_nums);
  }
  std::cout << std::endl;
  return 0;
}