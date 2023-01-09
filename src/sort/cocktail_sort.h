#pragma once

#include "base_sort.h"

class CocktailSort : public BaseSort
{
  char* name() {
	return "Cocktail Sort";
  }

  void sort()
  {
	bool swapped = true;
	int start = 0;
	int end = data.arr.size() - 1;

	while (swapped) {
	  if (!isThreadRunning())
		return;
	  swapped = false;
	  for (int i = start; i < end; i++) {
		if (!isThreadRunning())
		  return;
		if (data.arr[i] > data.arr[i + 1]) {
		  swapItem(i, i + 1);
		  swapped = true;
		}
		else {
		  selectItem(i);
		  selectItem(i + 1);
		}
	  }
	  if (!swapped)
		break;
	  end--;
	  swapped = false;
	  for (int i = end - 1; i >= start; --i) {
		if (!isThreadRunning())
		  return;
		if (data.arr[i] > data.arr[i + 1]) {
		  swapItem(i + 1, i);
		  swapped = true;
		}
		else {
		  selectItem(i + 1);
		  selectItem(i);
		}
	  }
	  start++;
	}
  }
};
