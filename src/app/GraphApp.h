#pragma once

#include "BaseApp.h"
#include "ofxGui.h"

class GraphNode
{
public:
  char value;
  ofPoint position;
  vector<GraphNode*> edges;
  bool visited = false;
  GraphNode* bfsParrent = NULL;

  GraphNode(char value, int x, int y)
  {
	this->value = value;
	position.x = x;
	position.y = y;
  }

  float dist(GraphNode& other)
  {
	return ofDist(position.x, position.y, other.position.x, other.position.y);
  }

  bool operator==(GraphNode& other)
  {
	return value == other.value;
  }

  bool operator!=(GraphNode& other)
  {
	return !operator==(other);
  }
};

class GraphApp : public BaseApp
{
  float nodeSize = 20;
  ofxTrueTypeFont font;

  ofxPanel settings;
  ofxIntSlider maxDistSlider;
  ofxButton
	clearButton,
	minSpanningTreeButton,
	bfsButton,
	shortestPathButton;

  vector<GraphNode> nodes;
  int maxDist;

  bool
	drawBFS = false,
	drawMST = false,
	drawShortestPath = false;

public:
  string name()
  {
	return "Graph Simulation";
  }

  void setup()
  {
	font.load("fonts/CaviarDreams_Bold.ttf", 12);
	settings.setup(name());

	maxDistSlider.addListener(this, &GraphApp::setMaxDist);
	settings.add(maxDistSlider.setup("Max Distance", 300, 100, 500));

	clearButton.addListener(this, &GraphApp::clearNodes);
	settings.add(clearButton.setup("Clear Nodes"));

	minSpanningTreeButton.addListener(this, &GraphApp::showMST);
	settings.add(minSpanningTreeButton.setup("Minimum Spanning Tree"));

	bfsButton.addListener(this, &GraphApp::showBFS);
	settings.add(bfsButton.setup("Breadth First Traversal"));
  }

  void showBFS()
  {
	drawBFS = true;
	drawMST = false;
	drawShortestPath = false;
  }

  void showMST()
  {
	drawBFS = false;
	drawMST = true;
	drawShortestPath = false;
  }

  void resetNodes()
  {
	for (auto& node : nodes)
	  node.visited = false;
  }

  int minDist(vector<GraphNode*>& dist)
  {
	int
	  min = INT_MAX,
	  minIdx = 0;
  }

  void updateNodes()
  {
	if (nodes.empty())
	  return;

	// ADDING EDGES
	for (auto& node : nodes)
	{
	  node.edges.clear();
	  node.bfsParrent = NULL;
	  for (auto& other : nodes)
		if (other != node && node.dist(other) < maxDist)
		  node.edges.push_back(&other);
	}

	// BFS
	resetNodes();
	list<GraphNode*> queue;
	auto& start = nodes.front();
	queue.push_back(&start);
	start.visited = true;
	while (!queue.empty())
	{
	  auto current = queue.front();
	  queue.pop_front();
	  if (current == &nodes.back())
		break;
	  for (auto other : current->edges)
		if (!other->visited)
		{
		  other->visited = true;
		  other->bfsParrent = current;
		  queue.push_back(other);
		}
	}
  }

  void setMaxDist(int& dist)
  {
	maxDist = dist;
	updateNodes();
  }

  void clearNodes()
  {
	nodes.clear();
  }

  void drawEdges(GraphNode& node)
  {
	if (!node.visited)
	{
	  node.visited = true;
	  for (auto other : node.edges)
	  {
		ofDrawLine(node.position, other->position);
		drawEdges(*other);
	  }
	}
  }

  void drawDistances(GraphNode& node)
  {
	if (!node.visited)
	{
	  node.visited = true;
	  for (auto other : node.edges)
	  {
		int dist = node.dist(*other);
		float
		  x = node.position.x + (other->position.x - node.position.x) * .5,
		  y = node.position.y + (other->position.y - node.position.y) * .5;
		ofRectangle r = font.getStringBoundingBox(ofToString(dist), 0, 0);
		r.x = x - (r.width * .5) - 1;
		r.y = y - (r.height * .5) - 1;
		r.width += 2;
		r.height += 2;
		ofSetColor(20);
		ofDrawRectangle(r);
		ofSetColor(220);
		font.drawString(ofToString(dist), x, y, TEXT_ALIGN_CENTER_MIDDLE);
		drawDistances(*other);
	  }
	}
  }

  void drawNodes(GraphNode& node)
  {
	if (!node.visited)
	{
	  node.visited = true;
	  ofPushMatrix();
	  ofTranslate(node.position);
	  ofSetColor(220);
	  ofDrawCircle(0, 0, nodeSize);
	  ofSetColor(20);
	  ofDrawCircle(0, 0, nodeSize - 2);
	  ofSetColor(220);
	  font.drawString(ofToString(node.value), 0, 0, TEXT_ALIGN_CENTER_MIDDLE);
	  ofPopMatrix();
	  for (auto other : node.edges)
		drawNodes(*other);
	}
  }

  void draw()
  {
	if (!nodes.empty())
	{
	  ofSetLineWidth(2);
	  ofSetColor(120);
	  resetNodes();
	  for (auto& node : nodes)
		drawEdges(node);

	  ofSetColor(0, 220, 0);

	  if (drawBFS)
	  {
		GraphNode* node = &nodes.back();
		while (1)
		{
		  auto parent = node->bfsParrent;
		  if (parent == NULL)
			break;
		  ofDrawLine(node->position, parent->position);
		  node = parent;
		}
	  }

	  if (drawMST)
	  {
		vector<GraphNode> reachedNodes, unreachedNodes = nodes;
		reachedNodes.push_back(unreachedNodes[0]);
		unreachedNodes.erase(unreachedNodes.begin());
		while (!unreachedNodes.empty())
		{
		  float record = 9999;
		  int rid = 0, uid = 0;
		  for (int r = 0; r < reachedNodes.size(); r++)
		  {
			for (int u = 0; u < unreachedNodes.size(); u++)
			{
			  auto& node = reachedNodes[r];
			  auto& other = unreachedNodes[u];
			  float dist = ofDist(node.position.x, node.position.y, other.position.x, other.position.y);
			  if (dist < record)
			  {
				record = dist;
				rid = r;
				uid = u;
			  }
			}
		  }
		  if (record < maxDist)
		  {
			ofDrawLine(reachedNodes[rid].position, unreachedNodes[uid].position);
			reachedNodes.push_back(unreachedNodes[uid]);
		  }
		  unreachedNodes.erase(unreachedNodes.begin() + uid);
		}
	  }

	  ofSetLineWidth(0);
	  resetNodes();
	  for (auto& node : nodes)
		drawDistances(node);

	  resetNodes();
	  for (auto& node : nodes)
		drawNodes(node);
	}
	settings.draw();
  }

  void mousePressed(int x, int y, int button)
  {
	if (button == 0 && nodes.size() < 26)
	{
	  char value = !nodes.empty() ? nodes[nodes.size() - 1].value + 1 : 'A';
	  nodes.push_back(GraphNode(value, x, y));
	  updateNodes();
	}
  }
};
