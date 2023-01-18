#pragma once

#include "BaseSort.h"

class BubbleSort : public BaseSort
{
  string name()
  {
	return "Bubble Sort";
  }

  void sort()
  {
	int i, j;
	for (i = 0; i < data.arr.size() - 1; i++) {
	  if (!isThreadRunning())
		return;
	  for (j = 0; j < data.arr.size() - i - 1; j++) {
		if (!isThreadRunning())
		  return;
		if (data.arr[j] > data.arr[j + 1])
		  swapItem(j, j + 1);
		else {
		  selectItem(j);
		  selectItem(j + 1);
		}
	  }
	}
  }
};
