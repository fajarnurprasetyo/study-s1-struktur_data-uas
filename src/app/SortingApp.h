#pragma once

#include "BaseApp.h"
#include "sorting/BitonicSort.h"
#include "sorting/BubbleSort.h"
#include "sorting/CocktailSort.h"

class SortingApp : public BaseApp
{
  string name()
  {
	return "Sorting Simulation";
  }

  void setup()
  {
	addApp(make_shared<BitonicSort>());
	addApp(make_shared<BubbleSort>());
	addApp(make_shared<CocktailSort>());
  }
};
