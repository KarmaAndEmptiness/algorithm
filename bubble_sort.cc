#include <iostream>
#include <vector>
using namespace std;
void bubble_sort(vector<int> &arr)
{
  for (size_t i = arr.size() - 1; i > 0; i--)
  {
    for (size_t j = 0; j < i; j++)
    {
      if (arr[j] > arr[j + 1])
      {
        int tmp = 0;
        tmp = arr[j + 1];
        arr[j + 1] = arr[j];
        arr[j] = tmp;
      }
    }
  }
}
int main()
{
  vector<int> arr = {3, 2, 4, 1, 6};
  bubble_sort(arr);
  for (vector<int>::value_type item : arr)
  {
    cout << item << " ";
  }
  cout << endl;
  return 0;
}