#pragma once

#include "BaseSort.h"

class InsertionSort : public BaseSort
{
  string name()
  {
	return "Insertion Sort";
  }

  void sort()
  {
	int i, key, j;
	for (i = 1; i < data.arr.size(); i++)
	{
	  if (!isThreadRunning())
		return;
	  key = data.arr[i];
	  j = i - 1;
	  while (j >= 0 && data.arr[j] > key)
	  {
		if (!isThreadRunning())
		  return;
		data.arr[j + 1] = data.arr[j];
		j = j - 1;
	  }
	  data.arr[j + 1] = key;
	}
  }
};
