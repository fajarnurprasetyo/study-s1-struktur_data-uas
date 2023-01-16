#pragma once

class Node
{
public:
  char value;
  ofVec2f position;

  Node(char value, float x, float y) {
	this->value = value;
	position.x = x;
	position.y = y;
  }

  void drawLine(vector<Node>& nodes, float maxDist) {
	ofSetLineWidth(2);
	ofSetColor(200);
	for (auto& other : nodes) {
	  if (other.value != value && ofDist(position.x, position.y, other.position.x, other.position.y) < maxDist)
		ofDrawLine(position, other.position);
	}
  }

  void draw(ofxTrueTypeFont& font) {
	ofSetLineWidth(0);
	ofSetColor(200);
	ofDrawCircle(position, 20);
	ofSetColor(20);
	font.drawStringCentered(ofToString(value), position);
  }
};
