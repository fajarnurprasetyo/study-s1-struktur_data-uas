#pragma once

#include "ofMain.h"
#include "BaseApp.h"
#include "InputDataApp.h"
#include "CalculatorApp.h"
#include "GraphApp.h"
#include "BinaryTreeApp.h"
#include "SortingApp.h"

class MainApp : public BaseApp
{
  string name()
  {
	return "UAS1 Struktur Data";
  }

  void setup()
  {
	addApp(make_shared<InputDataApp>());
	addApp(make_shared<CalculatorApp>());
	addApp(make_shared<GraphApp>());
	addApp(make_shared<BinaryTreeApp>());
	addApp(make_shared<SortingApp>());
	BaseApp::setup(NULL);

	ofSetEscapeQuitsApp(false);
	ofBackground(20);
  }
};
