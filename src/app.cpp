#include "app.h"

//=============================================================================
void App::setup() {
  // FONTS
  filesystem::path
	caviarDreamsR = "fonts/CaviarDreams_Regular.ttf",
	caviarDreamsB = "fonts/CaviarDreams_Bold.ttf",
	caviarDreamsI = "fonts/CaviarDreams_Italic.ttf",
	caviarDreamsBI = "fonts/CaviarDreams_BoldItalic.ttf";

  caviarDreamsCR14.load(caviarDreamsR, 14);

  caviarDreamsR18.load(caviarDreamsR, 18);

  caviarDreamsB18.load(caviarDreamsB, 18);
  caviarDreamsB32.load(caviarDreamsB, 32);

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
}

//=============================================================================
void App::treeReset() {
  treeScrollPosition = 0;
  treeMaxNodeLevel = 1;
  treeData = NULL;
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
  float r = treeNodeSize / 2;
  ofPushMatrix();
  ofTranslate(cx, cy);

  ofSetLineWidth(2);
  if (node->leftNode != NULL) {
	float x = treeNodeSize * -pow(2, (treeMaxNodeLevel - node->leftNode->level));
	float y = treeNodeSize * 3;
	ofDrawLine(0, r, x, y + r);
	drawTree(node->leftNode, x, y);
  }
  if (node->rightNode != NULL) {
	float x = treeNodeSize * pow(2, (treeMaxNodeLevel - node->rightNode->level));
	float y = treeNodeSize * 3;
	ofDrawLine(0, r, x, y + r);
	drawTree(node->rightNode, x, y);
  }

  ofSetLineWidth(0);
  ofSetColor(200);
  ofDrawCircle(0, treeNodeSize, treeNodeSize);
  ofSetColor(20);
  ofDrawCircle(0, treeNodeSize, treeNodeSize - 2);
  ofSetColor(200);
  caviarDreamsCR14.drawStringCentered(ofToString(node->value), 0, treeNodeSize);
  ofPopMatrix();
}

//=============================================================================
void App::draw() {
  switch (mainProgram) {
	// MAIN MENU
  case 0:
	drawMenu("UAS1 Struktur Data", mainMenu, mainMenuSelected);
	break;
	// BINARY TREE
  case 4:
	if (treeData != NULL) {
	  ofPushMatrix();
	  ofTranslate(treeScrollPosition, 0);
	  drawTree(treeData, ofGetWidth() / static_cast<float>(2), 0);
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
	  break;
	}
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

}

//=============================================================================
void App::mouseDragged(int x, int y, int button) {

}

//=============================================================================
void App::mousePressed(int x, int y, int button) {

}

//=============================================================================
void App::mouseReleased(int x, int y, int button) {

}

//=============================================================================
void App::mouseEntered(int x, int y) {

}

//=============================================================================
void App::mouseExited(int x, int y) {

}

//=============================================================================
void App::windowResized(int w, int h) {

}

//=============================================================================
void App::gotMessage(ofMessage msg) {

}

//=============================================================================
void App::dragEvent(ofDragInfo dragInfo) {

}

//=============================================================================
void App::exit() {
  for (auto& prog : sortingMenu)
	if (prog.get()->isThreadRunning()) {
	  prog.get()->stopThread();
	  prog.get()->waitForThread();
	}
}
