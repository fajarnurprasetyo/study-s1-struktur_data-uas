#pragma once

#include "ofMain.h"

enum ofxTextAlign {
  TEXT_ALIGN_LEFT_BOTTOM = 0,
  TEXT_ALIGN_LEFT_MIDDLE = 1,
  TEXT_ALIGN_LEFT_TOP = 2,
  TEXT_ALIGN_CENTER_BOTTOM = 3,
  TEXT_ALIGN_CENTER_MIDDLE = 4,
  TEXT_ALIGN_CENTER_TOP = 5,
  TEXT_ALIGN_RIGHT_BOTTOM = 6,
  TEXT_ALIGN_RIGHT_MIDDLE = 7,
  TEXT_ALIGN_RIGHT_TOP = 8,
};

class ofxTrueTypeFont : public ofTrueTypeFont
{
public:
  void drawString(const std::string& s, float x, float y)
  {
	ofTrueTypeFont::drawString(s, x, y);
  }

  void drawString(const std::string& s, float x, float y, ofxTextAlign align)
  {
	ofRectangle r = getStringBoundingBox(s, 0, 0);
	switch (align)
	{
	case TEXT_ALIGN_LEFT_MIDDLE:
	  y += r.height * .5;
	  break;
	case TEXT_ALIGN_LEFT_TOP:
	  y += r.height;
	  break;
	case TEXT_ALIGN_CENTER_BOTTOM:
	  x -= r.width * .5;
	  break;
	case TEXT_ALIGN_CENTER_MIDDLE:
	  x -= r.width * .5;
	  y += r.height * .5;
	  break;
	case TEXT_ALIGN_CENTER_TOP:
	  x -= r.width * .5;
	  y += r.height;
	  break;
	case TEXT_ALIGN_RIGHT_BOTTOM:
	  x -= r.width;
	  break;
	case TEXT_ALIGN_RIGHT_MIDDLE:
	  x -= r.width;
	  y += r.height * .5;
	  break;
	case TEXT_ALIGN_RIGHT_TOP:
	  x -= r.width;
	  y += r.height;
	  break;
	}
	drawString(s, x, y);
  }

  // void drawStringCentered(string s, float x, float y, bool asVector = false) {
	 //ofVec2f offset = getOffset(s);
	 //if (!asVector)
	 //  drawString(s, x + offset.x, y + offset.y);
	 //else
	 //  drawStringAsShapes(s, x + offset.x, y + offset.y);
  // }

  // void drawStringCentered(string s, ofVec2f pos, bool asVector = false) {
	 //drawStringCentered(s, pos.x, pos.y, asVector);
  // }

  // void drawCenteredBoundingBox(string s, float x, float y, float padding = 0) {
	 //ofRectangle r = getStringBoundingBox(s, 0, 0);
	 //r.x -= padding;
	 //r.y -= padding;
	 //r.width += 2.0f * padding;
	 //r.height += 2.0f * padding;
	 //ofSetRectMode(OF_RECTMODE_CENTER);
	 //ofDrawRectangle(x, y, r.width, r.height);
	 //ofSetRectMode(OF_RECTMODE_CORNER);
  // }

  // void drawCenteredBoundingBox(string s, ofVec2f pos, float padding = 0) {
	 //drawCenteredBoundingBox(s, pos.x, pos.y, padding);
  // }

  // void drawStringCenteredVertically(string s, float x, float y) {
	 //ofVec2f offset = getOffset(s);
	 //drawString(s, x, y + offset.y);
  // }

  // void drawStringCenteredVertically(string s, ofVec2f pos) {
	 //drawStringCenteredVertically(s, pos.x, pos.y);
  // }

  // void drawStringCenteredHorizontally(string s, float x, float y) {
	 //ofVec2f offset = getOffset(s);
	 //drawString(s, x + offset.x, y);
  // }

  // void drawStringCenteredHorizontally(string s, ofVec2f pos) {
	 //drawStringCenteredHorizontally(s, pos.x, pos.y);
  // }
};

