#include "app.h"

//=============================================================================
void App::setup() {
  // FONTS
  filesystem::path
	caviarDreamsR = "fonts/CaviarDreams_Regular.ttf",
	caviarDreamsB = "fonts/CaviarDreams_Bold.ttf",
	caviarDreamsI = "fonts/CaviarDreams_Italic.ttf",
	caviarDreamsBI = "fonts/CaviarDreams_BoldItalic.ttf";

  caviarDreamsR18.load(caviarDreamsR, 18);

  caviarDreamsB14.load(caviarDreamsB, 14);
  caviarDreamsB18.load(caviarDreamsB, 18);
  caviarDreamsB32.load(caviarDreamsB, 32);

  // CALCULATOR
  calc.setup();

  // GRAPH
  graph.setup();

  // BINARY TREE
  treeSettings.setup("Binary Tree");

  treeAddNodeInput.addListener(this, &App::treeAddNode);
  treeSettings.add(treeAddNodeInput.setup("Add Node", 50, 0, 99));

  treeRandomCountInput.addListener(this, &App::treeSetRandomCount);
  treeSettings.add(treeRandomCountInput.setup("Random Node Count", 10, 10, 20));

  treeRandomButton.addListener(this, &App::treeGenerateRandom);
  treeSettings.add(treeRandomButton.setup("Generate Random Tree"));

  treeResetButton.addListener(this, &App::treeReset);
  treeSettings.add(treeResetButton.setup("Reset Tree"));

  treeScrollBar.addListener(this, &App::treeScrollBarCb);
  treeSettings.add(treeScrollBar.setup("Scroll Bar", 0, -100, 100));

  // SORTING SIMULATION
  sortingSettings.setup("Sorting Settings");

  sortingDataCountInput.addListener(this, &App::sortingSetDataCount);
  sortingSettings.add(sortingDataCountInput.setup("Data Count", 128, 8, 1024));

  sortingSpeedSlider.addListener(this, &App::sortingSetSortingSpeed);
  sortingSettings.add(sortingSpeedSlider.setup("Sorting Speed", 2, 1, 128));

  sortingShuffleButton.addListener(this, &App::sortingShuffle);
  sortingSettings.add(sortingShuffleButton.setup("Shuffle!"));

  sortingSortButton.addListener(this, &App::sortingSort);
  sortingSettings.add(sortingSortButton.setup("Sort!"));

  ofSetEscapeQuitsApp(false);
  ofBackground(20);
}

//=============================================================================
void App::treeAddNode(int& value) {
  int nodeLevel = 1;
  if (treeData == NULL)
	treeData = new Tree(NULL, value);
  else {
	nodeLevel = treeData->addNode(value);
  }
  if (nodeLevel > treeMaxNodeLevel) {
	treeMaxNodeLevel = nodeLevel;
	float maxWidth = treeNodeSize * pow(2, treeMaxNodeLevel);
	treeScrollBar.setMin(-maxWidth);
	treeScrollBar.setMax(maxWidth);
  }
  treeTraverse();
}

//=============================================================================
void App::treeSetRandomCount(int& count) {
  treeRandomCount = count;
}

//=============================================================================
void App::treeGenerateRandom() {
  treeScrollPosition = 0;
  treeMaxNodeLevel = 1;
  treeData = new Tree(NULL, 50);
  for (int i = 0; i < treeRandomCount; i++) {
	int rand = ofRandom(1, 49);
	if (i > treeRandomCount / 2)
	  rand = ofRandom(51, 99);
	treeAddNode(rand);
  }
  treeTraverse();
}

//=============================================================================
void App::treeReset() {
  treeScrollPosition = 0;
  treeMaxNodeLevel = 1;
  treeData = NULL;
  treeTraverse();
}

//=============================================================================
void App::treeTraverseInorder(Tree* node) {
  if (node != NULL) {
	treeTraverseInorder(node->leftNode);
	treeInorder.push_back(node->value);
	treeTraverseInorder(node->rightNode);
  }
}

//=============================================================================
void App::treeTraversePreorder(Tree* node) {
  if (node != NULL) {
	treePreorder.push_back(node->value);
	treeTraversePreorder(node->leftNode);
	treeTraversePreorder(node->rightNode);
  }
}

//=============================================================================
void App::treeTraversePostorder(Tree* node) {
  if (node != NULL) {
	treeTraversePostorder(node->leftNode);
	treeTraversePostorder(node->rightNode);
	treePostorder.push_back(node->value);
  }
}

//=============================================================================
void App::treeTraverse() {
  treeInorder.clear();
  treePreorder.clear();
  treePostorder.clear();
  treeTraverseInorder(treeData);
  treeTraversePreorder(treeData);
  treeTraversePostorder(treeData);
}

//=============================================================================
void App::treeScrollBarCb(float& possition) {
  treeScrollPosition = possition;
}

//=============================================================================
void App::sortingSetDataCount(int& count) {
  for (auto& prog : sortingMenu)
	prog.get()->setDataCount(count);
}

//=============================================================================
void App::sortingSetSortingSpeed(int& speed) {
  for (auto& prog : sortingMenu)
	prog.get()->setSortingSpeed(speed);
}

//=============================================================================
void App::sortingShuffle() {
  for (auto& prog : sortingMenu)
	prog.get()->shuffleData();
}

//=============================================================================
void App::sortingSort() {
  sortingMenu[sortingMenuSelected].get()->startThread();
}

//=============================================================================
void App::update() {
  if (sortingProgram != 0) {
	auto prog = sortingMenu[sortingMenuSelected].get();
	if (prog->changed()) {
	  prog->lock();
	  sortingData = prog->getData();
	  prog->unlock();
	}
  }
}

//=============================================================================
void App::drawMenu(char* title, vector<char*> menu, int selected) {
  float x1 = 32;
  float y1 = 64;
  ofSetColor(200);
  caviarDreamsB32.drawString("Sorting Program", x1, y1);

  ofPushMatrix();
  ofTranslate(x1, y1 * 1.5);
  float x2 = 24;
  float y2 = 32;
  for (int i = 0; i < menu.size(); i++)
  {
	if (i == selected) {
	  ofSetColor(200);
	  caviarDreamsB18.drawString(">", 0, y2 * i);
	  caviarDreamsB18.drawString(menu[i], x2, y2 * i);
	}
	else {
	  ofSetColor(100);
	  caviarDreamsR18.drawString(menu[i], x2, y2 * i);
	}
  }
  ofPopMatrix();
}

//=============================================================================
void App::drawTree(Tree* node, float cx, float cy) {
  ofPushMatrix();
  ofTranslate(cx, cy);

  ofSetLineWidth(2);
  if (node->leftNode != NULL) {
	float x = treeNodeSize * -pow(2, (treeMaxNodeLevel - node->leftNode->level));
	float y = treeNodeSize * 3;
	ofDrawLine(0, treeNodeSize, x, y + treeNodeSize);
	drawTree(node->leftNode, x, y);
  }
  if (node->rightNode != NULL) {
	float x = treeNodeSize * pow(2, (treeMaxNodeLevel - node->rightNode->level));
	float y = treeNodeSize * 3;
	ofDrawLine(0, treeNodeSize, x, y + treeNodeSize);
	drawTree(node->rightNode, x, y);
  }

  ofSetLineWidth(0);
  ofSetColor(200);
  ofDrawCircle(0, treeNodeSize, treeNodeSize);
  ofSetColor(20);
  ofDrawCircle(0, treeNodeSize, treeNodeSize - 2);
  ofSetColor(200);
  caviarDreamsB14.drawStringCentered(ofToString(node->value), 0, treeNodeSize);
  ofPopMatrix();
}

//=============================================================================
void App::drawTreeTraverse() {
  caviarDreamsB14.drawString("Inorder", 0, 0);
  caviarDreamsB14.drawString("Preorder", 0, 64);
  caviarDreamsB14.drawString("Postorder", 0, 128);
  float
	x1 = 0,
	x2 = 0,
	x3 = 0;
  for (int i = 0; i < treeInorder.size(); i++)
  {
	string
	  t1 = ofToString(treeInorder[i]) + "; ",
	  t2 = ofToString(treePreorder[i]) + "; ",
	  t3 = ofToString(treePostorder[i]) + "; ";
	caviarDreamsB14.drawString(t1, x1, 32);
	caviarDreamsB14.drawString(t2, x2, 96);
	caviarDreamsB14.drawString(t3, x3, 160);
	ofRectangle
	  bb1 = caviarDreamsB14.getStringBoundingBox(t1, 0, 0),
	  bb2 = caviarDreamsB14.getStringBoundingBox(t2, 0, 0),
	  bb3 = caviarDreamsB14.getStringBoundingBox(t3, 0, 0);
	x1 += bb1.width;
	x2 += bb2.width;
	x3 += bb3.width;
  }
}

//=============================================================================
void App::draw() {
  switch (mainProgram) {
	// MAIN MENU
  case 0:
	drawMenu("UAS1 Struktur Data", mainMenu, mainMenuSelected);
	break;
	// INPUT DATA
  case 1:
	caviarDreamsB18.drawString(inputData, 32, 64);
	break;
	// CALCULATOR
  case 2:
	calc.draw();
	break;
	// GRAPH
  case 3:
	graph.draw();
	break;
	// BINARY TREE
  case 4:
	if (treeData != NULL) {
	  ofPushMatrix();
	  ofTranslate(-treeScrollPosition, 0);
	  drawTree(treeData, ofGetWidth() / static_cast<float>(2), 0);
	  ofPopMatrix();
	  ofPushMatrix();
	  ofTranslate(32, 576);
	  drawTreeTraverse();
	  ofPopMatrix();
	}
	treeSettings.draw();
	break;
	// SORTING SIMULATION
  case 5:
	if (sortingProgram == 0) {
	  vector<char*> menu;
	  for (auto& item : sortingMenu)
		menu.push_back(item.get()->name());
	  drawMenu("Sorting Simulation", menu, sortingMenuSelected);
	}
	else {
	  float W = ofGetWidth();
	  float H = ofGetHeight();

	  float c = sortingData.arr.size();
	  float w = W / c;
	  for (int i = 0; i < sortingData.arr.size(); i++)
	  {
		float n = sortingData.arr[i];
		float h = H * (n / c);
		float x = i * w;
		float y = H - h;

		if (i == sortingData.selected)
		  ofSetColor(0, 200, 0);
		else
		  ofSetColor(200);
		ofDrawRectangle(x, y, w, h);
	  }
	  sortingSettings.draw();
	}
	break;
  }
}

//=============================================================================
void App::mainKeyPressed(int key) {
  if (mainProgram == 0) {
	int max = mainMenu.size() - 1;
	switch (key) {
	case OF_KEY_ESC:
	  ofExit();
	  break;
	case OF_KEY_UP:
	  if (mainMenuSelected == 0)
		mainMenuSelected = max;
	  else
		mainMenuSelected--;
	  break;
	case OF_KEY_DOWN:
	  if (mainMenuSelected == max)
		mainMenuSelected = 0;
	  else
		mainMenuSelected++;
	  break;
	case OF_KEY_RETURN:
	  mainProgram = mainMenuSelected + 1;
	  if (mainProgram == 3)
		graph.reset();
	  break;
	}
  }
}

//=============================================================================
void App::inputKeyPressed(int key) {
  switch (key) {
  case OF_KEY_ESC:
	mainProgram = 0;
	inputData.clear();
	break;
  case OF_KEY_BACKSPACE:
	if (inputData.size() > 0)
	  inputData.pop_back();
	break;
  }
}

//=============================================================================
void App::sortingKeyPressed(int key) {
  if (sortingProgram == 0) {
	int max = sortingMenu.size() - 1;
	switch (key) {
	case OF_KEY_ESC:
	  mainProgram = 0;
	  break;
	case OF_KEY_UP:
	  if (sortingMenuSelected == 0)
		sortingMenuSelected = max;
	  else
		sortingMenuSelected--;
	  break;
	case OF_KEY_DOWN:
	  if (sortingMenuSelected == max)
		sortingMenuSelected = 0;
	  else
		sortingMenuSelected++;
	  break;
	case OF_KEY_RETURN:
	  sortingProgram = sortingMenuSelected + 1;
	  break;
	}
  }
  else if (key == OF_KEY_ESC) {
	auto prog = sortingMenu[sortingMenuSelected].get();
	if (prog->isThreadRunning()) {
	  prog->stopThread();
	  prog->waitForThread();
	}
	sortingProgram = 0;
  }
}

//=============================================================================
void App::keyPressed(int key) {
  switch (mainProgram) {
  case 0:
	mainKeyPressed(key);
	break;
  case 1:
	inputKeyPressed(key);
  case 2:
  case 3:
  case 4:
	if (key == OF_KEY_ESC)
	  mainProgram = 0;
	break;
  case 5:
	sortingKeyPressed(key);
	break;
  }
}

//=============================================================================
void App::keyReleased(int key) {

}

//=============================================================================
void App::mouseMoved(int x, int y) {
  switch (mainProgram) {
  case 2:
	calc.mouseMoved(x, y);
	break;
  }
}

//=============================================================================
void App::mousePressed(int x, int y, int button) {
  if (button == OF_MOUSE_BUTTON_LEFT) {
	switch (mainProgram) {
	case 2:
	  calc.mousePressed(x, y);
	  break;
	case 3:
	  graph.mousePressed(x, y);
	  break;
	}
  }
}

//=============================================================================
void App::exit() {
  for (auto& prog : sortingMenu)
	if (prog.get()->isThreadRunning()) {
	  prog.get()->stopThread();
	  prog.get()->waitForThread();
	}
}
