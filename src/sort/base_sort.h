#pragma once

#include "random"
#include "ofMain.h"
#include "ofxGui.h"

class SortData {
public:
  vector<int> arr;
  int selected = -1;
};

class BaseSort : public ofThread
{
private:
  bool _changed = false;

protected:
  virtual void sort() = 0;
  SortData data;
  int speed = 2;

  void threadedFunction() {
	sort();
  }

  void selectItem(int id) {
	data.selected = id;
	_changed = true;
	sleep(200 / speed);
	data.selected = -1;
	_changed = true;
  }

  void swapItem(int a, int b) {
	selectItem(a);
	int temp = data.arr[a];
	data.arr[a] = data.arr[b];
	data.arr[b] = temp;
	selectItem(b);
  }

public:
  virtual char* name() = 0;

  const bool changed() {
	if (_changed) {
	  _changed = false;
	  return true;
	}
	return false;
  }

  void shuffleData() {
	if (isThreadRunning()) {
	  stopThread();
	  waitForThread();
	}
	shuffle(data.arr.begin(), data.arr.end(), random_device());
	_changed = true;
  }

  void setDataCount(int& count) {
	if (isThreadRunning()) {
	  stopThread();
	  waitForThread();
	}
	data.arr.clear();
	for (int i = 0; i < count; i++)
	  data.arr.push_back(i + 1);
	shuffleData();
  }

  void setSortingSpeed(int speed) {
	lock();
	this->speed = speed;
	unlock();
  }

  SortData getData() {
	return data;
  }
};
