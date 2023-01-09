#pragma once
class Tree {
public:
  int
	value,
	level;
  Tree
	* parent = NULL,
	* leftNode = NULL,
	* rightNode = NULL;

  Tree(Tree* parent, int value) {
	this->parent = parent;
	this->level = parent == NULL ? 0 : parent->level + 1;
	this->value = value;
  }

  int addNode(int value) {
	if (value == this->value)
	  return this->level;
	if (value < this->value)
	{
	  if (leftNode != NULL)
		return leftNode->addNode(value);
	  leftNode = new Tree(this, value);
	  return this->level + 1;
	}
	if (rightNode != NULL)
	  return rightNode->addNode(value);
	rightNode = new Tree(this, value);
	return this->level + 1;
  }
};

