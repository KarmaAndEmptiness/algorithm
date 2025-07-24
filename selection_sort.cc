#include <iostream>
#include <vector>
using namespace std;
void selection_sort(vector<int> &arr)
{
  for (size_t i = 0; i < arr.size() - 1; i++)
  {
    int k = i, tmp = 0;
    for (size_t j = i + 1; j < arr.size(); j++)
    {
      if (arr[j] < arr[k])
      {
        k = j;
      }
    }
    tmp = arr[i];
    arr[i] = arr[k];
    arr[k] = tmp;
  }
}
int main()
{
  vector<int> arr = {3, 2, 1, 4, 5};
  selection_sort(arr);
  for (vector<int>::value_type item : arr)
  {
    cout << item << " ";
  }
  cout << endl;
  return 0;
}