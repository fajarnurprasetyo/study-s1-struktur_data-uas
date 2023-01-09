#pragma once

#include "base_sort.h"

class SelectionSort : public BaseSort
{
  char* name() {
	return "Selection Sort";
  }

  void sort()
  {
	int i, j, x;
	for (i = 0; i < data.arr.size() - 1; i++)
	{
	  selectItem(i);
	  if (!isThreadRunning())
		return;
	  x = i;
	  for (j = i + 1; j < data.arr.size(); j++) {
		if (!isThreadRunning())
		  return;
		selectItem(j);
		if (data.arr[j] < data.arr[x])
		  x = j;
	  }
	  if (x != i)
		swapItem(x, i);
	}
  }
};
