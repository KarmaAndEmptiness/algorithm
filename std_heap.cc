#include <iostream>
#include <queue>
int main()
{
  std::vector<int> nums{1, 2, 3, 4, 5};
  std::priority_queue<int, std::vector<int>, std::less<int>> max_heap(nums.begin(), nums.end());
  while (!max_heap.empty())
  {
    std::cout << max_heap.top() << " ";
    max_heap.pop();
  }
  std::cout << std::endl;
  return 0;
}