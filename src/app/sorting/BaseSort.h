#pragma once

#include "../BaseApp.h"
#include "random"

class SortData {
public:
  vector<int> arr;
  int selected = -1;
};

class BaseSort : public BaseApp, public ofThread
{
protected:
  ofxPanel settings;
  ofxIntField dataCountField;
  ofxButton
	shuffleButton,
	startSortButton;
  ofxIntSlider sortingSpeedSlider;

  int speed = 2;

  SortData _data, data;

  bool changed = false;

  void selectItem(int id) {
	data.selected = id;
	changed = true;
	ofSleepMillis(200 / speed);
	data.selected = -1;
	changed = true;
  }

  void swapItem(int a, int b) {
	selectItem(a);
	int temp = data.arr[a];
	data.arr[a] = data.arr[b];
	data.arr[b] = temp;
	selectItem(b);
  }

public:
  virtual string name() = 0;
  virtual void sort() = 0;

  void threadedFunction()
  {
	sort();
  }

  void setup()
  {
	settings.setup(name());

	dataCountField.addListener(this, &BaseSort::setDataCount);
	settings.add(dataCountField.setup("Data Count", 128, 16, 1024));

	shuffleButton.addListener(this, &BaseSort::shuffleData);
	settings.add(shuffleButton.setup("Shuffle Data"));

	startSortButton.addListener(this, &BaseSort::startSort);
	settings.add(startSortButton.setup("Start Sort"));

	sortingSpeedSlider.addListener(this, &BaseSort::setSortingSpeed);
	settings.add(sortingSpeedSlider.setup("Sorting Speed", 2, 1, 128));

  }

  void setDataCount(int& count)
  {
	if (count != _data.arr.size())
	{
	  if (isThreadRunning())
	  {
		stopThread();
		waitForThread();
	  }
	  data.arr.clear();
	  for (int i = 0; i < count; i++)
		data.arr.push_back(i + 1);
	  shuffleData();
	}
  }

  void shuffleData()
  {
	if (isThreadRunning())
	{
	  stopThread();
	  waitForThread();
	}
	shuffle(data.arr.begin(), data.arr.end(), random_device());
	changed = true;
  }

  void startSort()
  {
	startThread(true);
  }

  void setSortingSpeed(int& speed)
  {
	tryLock();
	this->speed = speed;
	unlock();
  }

  void update()
  {
	if (changed)
	{
	  lock();
	  _data = data;
	  changed = false;
	  unlock();
	}
  }

  void draw()
  {
	float W = ofGetWidth();
	float H = ofGetHeight();
	float c = _data.arr.size();
	float w = W / c;
	for (int i = 0; i < _data.arr.size(); i++)
	{
	  float n = _data.arr[i];
	  float h = H * (n / c);
	  float x = i * w;
	  float y = H - h;

	  if (i == _data.selected)
		ofSetColor(0, 220, 0);
	  else
		ofSetColor(220);
	  ofDrawRectangle(x, y, w, h);
	}
	settings.draw();
  }

  void keyPressed(int key)
  {
	if (key == OF_KEY_ESC)
	{
	  if (isThreadRunning())
	  {
		stopThread();
		waitForThread();
	  }
	  parent->program = 0;
	}
  }

  void exit()
  {
	if (isThreadRunning())
	{
	  stopThread();
	  waitForThread();
	}
  }
};
