#include <iostream>
#include <vector>
using namespace std;
void insertion_sort(vector<int> &arr)
{
  for (size_t i = 1; i < arr.size(); i++)
  {
    int base = arr[i], j = i - 1;
    while (arr[j] >= 0 && arr[j] > base)
    {
      arr[j + 1] = arr[j];
      j--;
    }
    arr[j + 1] = base;
  }
}
int main()
{
  vector<int> arr = {3,2,1,4,5};
  insertion_sort(arr);
  for (vector<int>::value_type item : arr)
  {
    cout << item << " ";
  }
  cout << endl;
  return 0;
}