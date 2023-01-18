#pragma once

#include "BaseApp.h"
#include "ofxGui.h"

class TreeNode {
public:
  int value, level;
  TreeNode
	* parent = NULL,
	* leftNode = NULL,
	* rightNode = NULL;

  TreeNode(int value, TreeNode* parent = NULL)
  {
	this->parent = parent;
	this->value = value;
	this->level = parent != NULL ? parent->level + 1 : 1;
  }

  int addNode(int value)
  {
	if (value == this->value)
	  return 0;

	if (value < this->value)
	{
	  if (leftNode == NULL)
	  {
		leftNode = new TreeNode(value, this);
		return level + 1;
	  }
	  return leftNode->addNode(value);
	}
	if (rightNode == NULL)
	{
	  rightNode = new TreeNode(value, this);
	  return level + 1;
	}
	return rightNode->addNode(value);
  }
};

class BinaryTreeApp : public BaseApp
{
  float nodeSize = 20;
  ofxTrueTypeFont font;

  ofxPanel settings;
  ofxIntField addNodeField;
  ofxButton
	randomButton,
	clearButton;

  ofRectangle
	scrollBar,
	scrollBarThumb;
  bool isScrolling = false;
  int scrollOffset = -1;

  TreeNode* root = NULL;
  int maxLevel = 0;
  int addRandomRetry = 1;

  vector<int>
	nodeInorder,
	nodePreorder,
	nodePostorder;

  string name()
  {
	return "Binary Tree";
  }

  void setup()
  {
	font.load("fonts/CaviarDreams_Bold.ttf", 12);
	settings.setup(name());

	addNodeField.addListener(this, &BinaryTreeApp::addNode);
	settings.add(addNodeField.setup("Add Node", ofRandom(1, 99)));

	randomButton.addListener(this, &BinaryTreeApp::addRandomNode);
	settings.add(randomButton.setup("Add Random Node"));

	clearButton.addListener(this, &BinaryTreeApp::clearNodes);
	settings.add(clearButton.setup("Clear Nodes"));

	scrollBar.width = ofGetWidth();
	scrollBar.height = 16;
	scrollBar.y = ofGetHeight() - scrollBar.height;

	scrollBarThumb.height = scrollBar.height;
	scrollBarThumb.y = scrollBar.y;
  }

  void traverseInorder(TreeNode* node)
  {
	if (node != NULL)
	{
	  traverseInorder(node->leftNode);
	  nodeInorder.push_back(node->value);
	  traverseInorder(node->rightNode);
	}
  }

  void traversePreorder(TreeNode* node)
  {
	if (node != NULL) {
	  nodePreorder.push_back(node->value);
	  traversePreorder(node->leftNode);
	  traversePreorder(node->rightNode);
	}
  }

  void traversePostorder(TreeNode* node)
  {
	if (node != NULL) {
	  traversePostorder(node->leftNode);
	  traversePostorder(node->rightNode);
	  nodePostorder.push_back(node->value);
	}
  }

  void traverse()
  {
	nodeInorder.clear();
	nodePreorder.clear();
	nodePostorder.clear();
	traverseInorder(root);
	traversePreorder(root);
	traversePostorder(root);
  }

  bool addNode(int& value)
  {
	bool added = false;
	if (root == NULL)
	{
	  root = new TreeNode(value);
	  maxLevel = 1;
	  added = true;
	}
	else
	{
	  int level = root->addNode(value);
	  if (level > maxLevel)
		maxLevel = level;
	  added = level != 0;
	}
	if (added)
	{
	  traverse();
	  scrollBarThumb.width = ofGetWidth() * (ofGetWidth() / (nodeSize * pow(2, maxLevel)));
	  scrollBarThumb.x = (ofGetWidth() * .5) - (scrollBarThumb.width * .5);
	  return true;
	}
	return false;
  }

  void addRandomNode()
  {
	int min = 1, max = 99;
	if (root != NULL)
	{
	  min = root->value - (10 * addRandomRetry);
	  max = root->value + (10 * addRandomRetry);
	}
	int rand = ofRandom(min, max);
	if (!addNode(rand))
	{
	  addRandomRetry++;
	  addRandomNode();
	}
	addRandomRetry = 1;
  }

  void clearNodes()
  {
	root = NULL;
	traverse();
	maxLevel = 0;
	scrollBarThumb.width = ofGetWidth() * (ofGetWidth() / (nodeSize * pow(2, maxLevel)));
	scrollBarThumb.x = (ofGetWidth() * .5) - (scrollBarThumb.width * .5);
  }

  void drawNode(TreeNode* node, float cx, float cy)
  {
	ofPushMatrix();
	ofTranslate(cx, cy);

	ofSetLineWidth(2);
	ofSetColor(220);
	if (node->leftNode != NULL)
	{
	  float x = nodeSize * -pow(2, (maxLevel - node->level - 1));
	  float y = nodeSize * 2.5;
	  ofDrawLine(0, 0, x, y);
	  drawNode(node->leftNode, x, y);
	}
	if (node->rightNode != NULL)
	{
	  float x = nodeSize * pow(2, (maxLevel - node->level - 1));
	  float y = nodeSize * 2.5;
	  ofDrawLine(0, 0, x, y);
	  drawNode(node->rightNode, x, y);
	}

	ofSetLineWidth(0);
	ofSetColor(220);
	ofDrawCircle(0, 0, nodeSize);
	ofSetColor(20);
	ofDrawCircle(0, 0, nodeSize - 2);
	ofSetColor(220);
	font.drawString(ofToString(node->value), 0, 0, TEXT_ALIGN_CENTER_MIDDLE);

	ofPopMatrix();
  }

  void draw()
  {
	if (root != NULL)
	{
	  float
		maxWidth = nodeSize * pow(2, maxLevel),
		offset = (ofGetWidth() * .5) - ((scrollBarThumb.width * .5) + scrollBarThumb.x);
	  ofPushMatrix();
	  ofTranslate(offset * (maxWidth / ofGetWidth()), 0);
	  drawNode(root, ofGetWidth() * .5, nodeSize);
	  ofPopMatrix();

	  string inorder, preorder, postorder;
	  for (int i = 0; i < nodeInorder.size(); i++)
	  {
		inorder += ofToString(nodeInorder[i]) + "; ";
		preorder += ofToString(nodePreorder[i]) + "; ";
		postorder += ofToString(nodePostorder[i]) + "; ";
	  }
	  ofPushMatrix();
	  ofTranslate(32, 560);
	  fontMenuItemSelected.drawString("Inorder", 0, 0);
	  fontMenuItemSelected.drawString(inorder, 0, 32);
	  fontMenuItemSelected.drawString("Preorder", 0, 64);
	  fontMenuItemSelected.drawString(preorder, 0, 96);
	  fontMenuItemSelected.drawString("Postorder", 0, 128);
	  fontMenuItemSelected.drawString(postorder, 0, 160);
	  ofPopMatrix();

	  if (scrollBarThumb.width < ofGetWidth())
	  {
		ofSetColor(10);
		ofDrawRectangle(scrollBar);
		ofSetColor(100);
		ofDrawRectangle(scrollBarThumb);
	  }
	}
	settings.draw();
  }

  void mousePressed(int x, int y, int button)
  {
	if (
	  button == 0 &&
	  scrollBarThumb.width < ofGetWidth() &&
	  y >(scrollBar.y - (scrollBar.height / 2))
	  )
	{
	  if (
		x > scrollBarThumb.x &&
		x < scrollBarThumb.x + scrollBarThumb.width
		)
	  {
		scrollOffset = x;
		isScrolling = true;
	  }
	}
  }

  void mouseDragged(int x, int y, int button)
  {
	if (button == 0 && isScrolling)
	{
	  scrollBarThumb.x += x - scrollOffset;
	  scrollOffset = x;
	  if (scrollBarThumb.x < 0)
		scrollBarThumb.x = 0;
	  else if (scrollBarThumb.x > ofGetWidth() - scrollBarThumb.width)
		scrollBarThumb.x = ofGetWidth() - scrollBarThumb.width;
	}
  }

  void mouseReleased(int x, int y, int button)
  {
	if (button == 0 && isScrolling)
	  isScrolling = false;
  }
};
