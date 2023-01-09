#pragma once

#include "ofMain.h"

#include "addons/ofxCenteredTrueTypeFont.h"

#include "tree/tree.h"

#include "sort/base_sort.h"
#include "sort/bingo_sort.h"
#include "sort/bitonic_sort.h"
#include "sort/brick_sort.h"
#include "sort/bubble_sort.h"
#include "sort/bucket_sort.h"
#include "sort/cocktail_sort.h"
#include "sort/comb_sort.h"
#include "sort/counting_sort.h"
#include "sort/cycle_sort.h"
#include "sort/gnome_sort.h"
#include "sort/heap_sort.h"
#include "sort/insertion_sort.h"
#include "sort/merge_sort.h"
#include "sort/merge3_sort.h"
#include "sort/pancake_sort.h"
#include "sort/pigeonhole_sort.h"
#include "sort/quick_sort.h"
#include "sort/radix_sort.h"
#include "sort/selection_sort.h"
#include "sort/shell_sort.h"
#include "sort/sleep_sort.h"
#include "sort/stooge_sort.h"
#include "sort/strand_sort.h"
#include "sort/structure_sort.h"
#include "sort/tag_sort.h"
#include "sort/tim_sort.h"
#include "sort/tree_sort.h"

class App : public ofBaseApp {
private:
  // FONTS
  ofxCenteredTrueTypeFont
	caviarDreamsCR14;

  ofTrueTypeFont
	caviarDreamsR18,

	caviarDreamsB18,
	caviarDreamsB32;

  int mainProgram = 0;
  vector<char*> mainMenu = {
	"Input Data",
	"Advanced Calc",
	"Graph Simulation",
	"Binary Tree",
	"Sorting Simulation",
  };
  int mainMenuSelected = 0;

  // BINARY TREE
  float
	treeNodeSize = 25,
	treeScrollPosition = 0,
	treeRandomCount = 10;
  int
	treeMaxNodeLevel = 1,
	treeNodeValue;
  Tree* treeData = NULL;
  ofxPanel treeSettings;
  ofxIntField
	treeAddNodeInput,
	treeRandomCountInput;
  ofxButton
	treeRandomButton,
	treeResetButton;
  ofxFloatSlider treeScrollBar;
  void treeAddNode(int& value);
  void treeSetRandomCount(int& count);
  void treeGenerateRandom();
  void treeReset();
  void treeScrollBarCb(float& possition);

  // SORTING SIMULATION
  int sortingProgram = 0;
  vector<shared_ptr<BaseSort>> sortingMenu = {
	//make_shared<BingoSort>(),
	make_shared<BitonicSort>(),
	//make_shared<BrickSort>(),
	make_shared<BubbleSort>(),
	//make_shared<BucketSort>(),
	make_shared<CocktailSort>(),
	//make_shared<CombSort>(),
	//make_shared<CountingSort>(),
	//make_shared<CycleSort>(),
	//make_shared<GnomeSort>(),
	//make_shared<HeapSort>(),
	//make_shared<InsertionSort>(),
	//make_shared<MergeSort>(),
	//make_shared<Merge3Sort>(),
	//make_shared<PancakeSort>(),
	//make_shared<PigeonholeSort>(),
	//make_shared<QuickSort>(),
	//make_shared<RadixSort>(),
	make_shared<SelectionSort>(),
	//make_shared<ShellSort>(),
	//make_shared<SleepSort>(),
	//make_shared<StoogeSort>(),
	//make_shared<StrandSort>(),
	//make_shared<StructureSort>(),
	//make_shared<TagSort>(),
	//make_shared<TimSort>(),
	//make_shared<TreeSort>(),
  };
  int sortingMenuSelected = 0;
  SortData sortingData;
  ofxPanel sortingSettings;
  ofxIntField sortingDataCountInput;
  ofxIntSlider sortingSpeedSlider;
  ofxButton
	sortingShuffleButton,
	sortingSortButton;
  void sortingSetDataCount(int& count);
  void sortingSetSortingSpeed(int& count);
  void sortingShuffle();
  void sortingSort();

public:
  void setup();
  void update();
  void drawMenu(char* title, vector<char*> menu, int selected);
  void drawTree(Tree* tree, float x, float y);
  void draw();

  void mainKeyPressed(int key);
  void sortingKeyPressed(int key);
  void keyPressed(int key);
  void keyReleased(int key);
  void mouseMoved(int x, int y);
  void mouseDragged(int x, int y, int button);
  void mousePressed(int x, int y, int button);
  void mouseReleased(int x, int y, int button);
  void mouseEntered(int x, int y);
  void mouseExited(int x, int y);
  void windowResized(int w, int h);
  void dragEvent(ofDragInfo dragInfo);
  void gotMessage(ofMessage msg);
  void exit();
};
