#pragma once

#include "BaseApp.h"

class InputDataApp : public BaseApp, public ofThread
{
  string input, greeting, language;

  string name()
  {
	return "Input Data";
  }

  void threadedFunction()
  {
	auto res = ofLoadURL("https://www.greetingsapi.com/random");
	if (res.status == 200)
	{
	  auto json = ofJson::parse(res.data);
	  greeting = json["greeting"].get<string>() + ", " + input;
	  language = json["language"].get<string>();
	}
	else
	{
	  greeting = "Halo, " + input;
	  language = "Indonesia";
	}
  }

  void setup()
  {

  }

  void draw()
  {
	float x = 32;
	float y = 64;
	if (input.empty())
	{
	  ofSetColor(120);
	  fontMenuTitle.drawString("Input your name", x, y);
	}
	ofSetColor(220);
	fontMenuTitle.drawString(input, x, y);
	if (ofGetElapsedTimeMillis() % 1000 > 500)
	  fontMenuTitle.drawString(input, x, y);
	else
	  fontMenuTitle.drawString(input + '|', x, y);

	if (!greeting.empty())
	{
	  fontMenuItemSelected.drawString(greeting, x, y + 32);
	  fontMenuItem.drawString("Language: " + language, x, y + 64);
	}
	else if (!input.empty())
	{
	  ofSetColor(120);
	  fontMenuItemSelected.drawString("Press enter!", x, y + 32);
	}
  }

  void keyPressed(int key)
  {
	switch (key)
	{
	case OF_KEY_BACKSPACE:
	  if (!input.empty())
		input.pop_back();
	  break;
	case OF_KEY_RETURN:
	  if (!input.empty())
		startThread();
	  break;
	case OF_KEY_ESC:
	  if (isThreadRunning())
		waitForThread();
	  parent->program = 0;
	  input.clear();
	  break;
	default:
	  if ((key >= 'A' && key <= 'Z') || (key >= 'a' && key <= 'z') || key == ' ')
		input.push_back(key);
	  break;
	}
  }
};
