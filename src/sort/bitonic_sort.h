#pragma once

#include "base_sort.h"

class BitonicSort : public BaseSort
{
  char* name() {
	return "Bitonic Sort";
  }

  void compare(int a, int b, bool asc) {
	if (
	  (asc && (data.arr[a] > data.arr[b])) ||
	  (!asc && (data.arr[a] < data.arr[b]))
	  )
	  swapItem(a, b);
  };

  void merge(int start, int count, bool asc) {
	if (count > 1)
	{
	  int k = count / 2;
	  for (int i = start; i < start + k; i++)
		compare(i, i + k, asc);
	  merge(start, k, asc);
	  merge(start + k, k, asc);
	}
  }

  void sort(int start, int count, bool asc)
  {
	if (count > 1)
	{
	  int half = count / 2;
	  sort(start, half, 1);
	  sort(start + half, half, 0);
	  merge(start, count, asc);
	}
  }

  void sort() {
	sort(0, data.arr.size(), true);
  }
};
