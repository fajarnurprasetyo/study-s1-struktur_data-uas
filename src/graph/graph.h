#pragma once

#include "node.h"

class Graph
{
private:
  ofxTrueTypeFont font;
  vector<Node> nodes;

public:
  void setup() {
	font.load("fonts/CaviarDreams_Bold.ttf", 18);
  };

  void reset() {
	nodes.clear();
  }

  void draw() {
	for (int i = 0; i < nodes.size(); i++)
	  nodes[i].drawLine(nodes, 200);
	for (int i = 0; i < nodes.size(); i++)
	  nodes[i].draw(font);
  }

  void mousePressed(int x, int y) {
	if (nodes.size() < 26) {
	  char value = nodes.size() > 0 ? nodes[nodes.size() - 1].value + 1 : 'A';
	  nodes.push_back(Node(value, x, y));
	}
  }
};
