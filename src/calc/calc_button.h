#pragma once

class CalcButton
{
private:
  char* name;
  float x, y, w, h;
  bool isHover = false;
  bool isEnabled = true;

public:
  void setup(char* name, float x, float y, float w, float h) {
	this->name = name;
	this->x = x;
	this->y = y;
	this->w = w;
	this->h = h;
  }

  void enabled(bool enabled) {
	isEnabled = enabled;
  }

  void draw(ofxTrueTypeFont* font) {
	ofSetRectMode(OF_RECTMODE_CENTER);
	if (isHover)
	  ofSetColor(30);
	else
	  ofSetColor(10);
	ofDrawRectRounded(x, y, w, h, 2);
	if (isEnabled)
	  ofSetColor(200);
	else
	  ofSetColor(100);
	font->drawStringCentered(name, x, y);
  }

  bool contains(int x, int y) const {
	return
	  isEnabled &&
	  x > this->x - w / 2 &&
	  x < this->x + w / 2 &&
	  y > this->y - h / 2 &&
	  y < this->y + h / 2;
  }

  void mouseMoved(int x, int y) {
	isHover = contains(x, y);
  }
};
