#include <iostream>
#include <vector>
using namespace std;
int partition(vector<int> &arr, int left, int right)
{
  int i = left, j = right;
  while (i < j)
  {
    while (i < j && arr[j] >= arr[left])
    {
      j--;
    }
    while (i < j && arr[i] <= arr[left])
    {
      i++;
    }
    swap(arr[i], arr[j]);
  }
  swap(arr[left], arr[i]);
  return i;
}
void quick_sort(vector<int> &arr, int left, int right)
{
  if (left >= right)
    return;
  int pivot = partition(arr, left, right);
  quick_sort(arr, left, pivot - 1);
  quick_sort(arr, pivot + 1, right);
}
int main()
{
  vector<int> arr = {3, 2, 1, 4, 5};
  quick_sort(arr, 0, arr.size() - 1);
  for (int item : arr)
  {
    cout << item << " ";
  }
  cout << endl;
  return 0;
}