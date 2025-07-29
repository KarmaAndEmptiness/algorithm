#include <iostream>
#include <vector>
#include <algorithm>
void bucket_sort(std::vector<float> &nums)
{
  int k = nums.size() / 2;
  std::vector<std::vector<float>> buckets(k);
  for (float num : nums)
  {
    int i = num * k;
    buckets[i].push_back(num);
  }

  for (std::vector<float> &bucket : buckets)
  {
    std::sort(bucket.begin(), bucket.end());
  }

  int i = 0;
  for (std::vector<float> &bucket : buckets)
  {
    for (float num : bucket)
    {
      nums[i++] = num;
    }
  }
}
int main()
{
  std::vector<float> nums = {0.1, 0.2, 0.4, 0.3, 0.6, 0.5};
  bucket_sort(nums);
  for (const float &item : nums)
  {
    std::cout << item << " ";
  }
  std::cout << std::endl;
  return 0;
}