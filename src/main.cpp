#include "ofMain.h"
#include "app/MainApp.h"

int main() {
  ofGLFWWindowSettings windowSettings;
  windowSettings.setSize(1024, 768);
  windowSettings.resizable = false;
  ofCreateWindow(windowSettings);
  return ofRunApp(new MainApp());
}
