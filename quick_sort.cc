#include <iostream>
#include <vector>
using namespace std;
void swap(vector<int>::value_type &a, vector<int>::value_type &b)
{
  vector<int>::value_type tmp;
  tmp = a;
  a = b;
  b = tmp;
}
int partition(vector<int> &arr, size_t left, size_t right)
{
  int i = left, j = -1; 
  while (i < right)
  {
    if (arr[i] < arr[right])
    {
      swap(arr[i],arr[++j]);
    }
    i++;
  }
  swap(arr[right], arr[++j]);
  return j;
}
void quick_sort(vector<int> &arr, size_t left, size_t right)
{
  if(left >= right)
    return ;
  size_t pivot = partition(arr, left, right);

  if (pivot <= 0 || pivot >= arr.size() - 1)
    return;
  quick_sort(arr, left, pivot - 1);
  quick_sort(arr, pivot + 1, right);
}
int main()
{
  vector<int> arr = {3, 2, 1, 5, 4};
  quick_sort(arr, 0, arr.size() - 1);
  for (vector<int>::value_type item : arr)
  {
    cout << item << " ";
  }
  cout << endl;
  return 0;
}