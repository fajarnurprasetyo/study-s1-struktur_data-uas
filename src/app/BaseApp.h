#pragma once

#include "ofMain.h"
#include "../addons/ofxTrueTypeFont.h"

class BaseApp : public ofBaseApp
{
protected:
  BaseApp* parent;

public:
  virtual string name() = 0;
  virtual void setup() = 0;

  ofxTrueTypeFont
	& fontMenuTitle = ofxTrueTypeFont(),
	& fontMenuItem = ofxTrueTypeFont(),
	& fontMenuItemSelected = ofxTrueTypeFont();

  int
	program = 0,
	selected = 0;
  vector<shared_ptr<BaseApp>> apps;

  void addApp(shared_ptr<BaseApp> app)
  {
	app.get()->setup();
	app.get()->setup(this);
	apps.push_back(app);
  }

  void setup(BaseApp* parent)
  {
	this->parent = parent;
	if (parent != NULL)
	{
	  fontMenuTitle = parent->fontMenuTitle;
	  fontMenuItem = parent->fontMenuItem;
	  fontMenuItemSelected = parent->fontMenuItemSelected;
	}
	else
	{
	  fontMenuTitle.loadFont("fonts/CaviarDreams_Bold.ttf", 32);
	  fontMenuItem.loadFont("fonts/CaviarDreams_Regular.ttf", 18);
	  fontMenuItemSelected.loadFont("fonts/CaviarDreams_Bold.ttf", 18);
	}
  }

  void update()
  {
	if (program != 0)
	  return apps[selected].get()->update();
  }

  void draw()
  {
	if (program == 0)
	{

	float x1 = 32;
	float y1 = 64;
	ofSetColor(220);
	fontMenuTitle.drawString(name(), x1, y1);

	ofPushMatrix();
	ofTranslate(x1, y1 * 1.5);
	float x2 = 24;
	float y2 = 32;
	for (int i = 0; i < apps.size(); i++)
	{
	  if (i != selected)
	  {
		ofSetColor(120);
		fontMenuItem.drawString(apps[i].get()->name(), x2, y2 * i);
	  }
	  else
	  {
		ofSetColor(220);
		fontMenuItemSelected.drawString(">", 0, y2 * i);
		fontMenuItemSelected.drawString(apps[i].get()->name(), x2, y2 * i);
	  }
	}
	ofPopMatrix();
	}
	else
	{
	  ofPushStyle();
	  apps[selected].get()->draw();
	  ofPopStyle();
	}
  }

  void keyPressed(int key)
  {
	if (program != 0)
	  return apps[selected].get()->keyPressed(key);

	switch (key) {
	case OF_KEY_UP:
	  if (selected == 0)
		selected = apps.size() - 1;
	  else
		selected--;
	  break;
	case OF_KEY_DOWN:
	  if (selected == apps.size() - 1)
		selected = 0;
	  else
		selected++;
	  break;
	case OF_KEY_RETURN:
	  if (!apps.empty())
		program = selected + 1;
	  break;
	case OF_KEY_ESC:
	  if (parent != NULL)
		parent->program = 0;
	  else
		ofExit();
	  break;
	}
  }

  void mouseMoved(int x, int y)
  {
	if (program != 0)
	  return apps[selected].get()->mouseMoved(x, y);
  }

  void mousePressed(int x, int y, int button)
  {
	if (program != 0)
	  return apps[selected].get()->mousePressed(x, y, button);
  }

  void mouseDragged(int x, int y, int button)
  {
	if (program != 0)
	  return apps[selected].get()->mouseDragged(x, y, button);
  }

  void mouseReleased(int x, int y, int button)
  {
	if (program != 0)
	  return apps[selected].get()->mouseReleased(x, y, button);
  }

  void exit()
  {
	if (program != 0)
	  return apps[selected].get()->exit();
  }
};
