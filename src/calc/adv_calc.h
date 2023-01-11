#pragma once

#include "calc/calc_button.h"

class AdvCalc
{
private:
  ofxTrueTypeFont
	bigFont,
	smallFont;

  float
	width, height,
	screenHeight;

  CalcButton
	calcButtonA,
	calcButtonB,
	calcButtonC,
	calcButtonD,
	calcButtonE,
	calcButtonF,
	calcButtonDot,
	calcButton0,
	calcButton1,
	calcButton2,
	calcButton3,
	calcButton4,
	calcButton5,
	calcButton6,
	calcButton7,
	calcButton8,
	calcButton9,
	calcButtonDel,
	calcButtonMin,
	calcButtonPlus,
	calcButtonDiv,
	calcButtonTimes,
	calcButtonExual,
	calcButtonBin,
	calcButtonOct,
	calcButtonDec,
	calcButtonHex,
	calcButtonDummy1,
	calcButtonDummy2,
	calcButtonDummy3;

  int program = 3;
  string
	n1 = "",
	n2 = "";
  int op = 0;

public:
  void setup() {
	bigFont.load("fonts/CaviarDreams_Bold.ttf", 56);
	smallFont.load("fonts/CaviarDreams_Bold.ttf", 18);
	width = ofGetWidth();
	height = ofGetHeight();
	screenHeight = height * 0.3;
	float btnw = width / 5;
	float btnh = (height - screenHeight) / 6.0;
	calcButtonA.setup("A", btnw * .5, screenHeight + (btnh * .5), btnw - 4, btnh - 4);
	calcButtonA.enabled(false);
	calcButtonB.setup("B", btnw * .5, screenHeight + (btnh * 1.5), btnw - 4, btnh - 4);
	calcButtonB.enabled(false);
	calcButtonC.setup("C", btnw * .5, screenHeight + (btnh * 2.5), btnw - 4, btnh - 4);
	calcButtonC.enabled(false);
	calcButtonD.setup("D", btnw * .5, screenHeight + (btnh * 3.5), btnw - 4, btnh - 4);
	calcButtonD.enabled(false);
	calcButtonE.setup("E", btnw * .5, screenHeight + (btnh * 4.5), btnw - 4, btnh - 4);
	calcButtonE.enabled(false);
	calcButtonF.setup("F", btnw * .5, screenHeight + (btnh * 5.5), btnw - 4, btnh - 4);
	calcButtonF.enabled(false);
	calcButtonDot.setup(".", btnw * 1.5, screenHeight + (btnh * 5.5), btnw - 4, btnh - 4);
	calcButton0.setup("0", btnw * 2.5, screenHeight + (btnh * 5.5), btnw - 4, btnh - 4);
	calcButton1.setup("1", btnw * 1.5, screenHeight + (btnh * 4.5), btnw - 4, btnh - 4);
	calcButton2.setup("2", btnw * 2.5, screenHeight + (btnh * 4.5), btnw - 4, btnh - 4);
	calcButton3.setup("3", btnw * 3.5, screenHeight + (btnh * 4.5), btnw - 4, btnh - 4);
	calcButton4.setup("4", btnw * 1.5, screenHeight + (btnh * 3.5), btnw - 4, btnh - 4);
	calcButton5.setup("5", btnw * 2.5, screenHeight + (btnh * 3.5), btnw - 4, btnh - 4);
	calcButton6.setup("6", btnw * 3.5, screenHeight + (btnh * 3.5), btnw - 4, btnh - 4);
	calcButton7.setup("7", btnw * 1.5, screenHeight + (btnh * 2.5), btnw - 4, btnh - 4);
	calcButton8.setup("8", btnw * 2.5, screenHeight + (btnh * 2.5), btnw - 4, btnh - 4);
	calcButton9.setup("9", btnw * 3.5, screenHeight + (btnh * 2.5), btnw - 4, btnh - 4);
	calcButtonDel.setup("<x", btnw * 3.5, screenHeight + (btnh * 1.5), btnw - 4, btnh - 4);
	calcButtonMin.setup("-", btnw * 4.5, screenHeight + (btnh * 4.5), btnw - 4, btnh - 4);
	calcButtonPlus.setup("+", btnw * 4.5, screenHeight + (btnh * 3.5), btnw - 4, btnh - 4);
	calcButtonDiv.setup("/", btnw * 4.5, screenHeight + (btnh * 2.5), btnw - 4, btnh - 4);
	calcButtonTimes.setup("x", btnw * 4.5, screenHeight + (btnh * 1.5), btnw - 4, btnh - 4);
	calcButtonExual.setup("=", btnw * 4.5, screenHeight + (btnh * 5.5), btnw - 4, btnh - 4);
	calcButtonBin.setup("Bin", btnw * 1.5, screenHeight + (btnh * .5), btnw - 4, btnh - 4);
	calcButtonBin.enabled(false);
	calcButtonOct.setup("Oct", btnw * 2.5, screenHeight + (btnh * .5), btnw - 4, btnh - 4);
	calcButtonOct.enabled(false);
	calcButtonDec.setup("Dec", btnw * 3.5, screenHeight + (btnh * .5), btnw - 4, btnh - 4);
	calcButtonDec.enabled(false);
	calcButtonHex.setup("Hex", btnw * 4.5, screenHeight + (btnh * .5), btnw - 4, btnh - 4);
	calcButtonHex.enabled(false);
	calcButtonDummy1.setup("", btnw * 1.5, screenHeight + (btnh * 1.5), btnw - 4, btnh - 4);
	calcButtonDummy2.setup("", btnw * 2.5, screenHeight + (btnh * 1.5), btnw - 4, btnh - 4);
	calcButtonDummy3.setup("", btnw * 3.5, screenHeight + (btnh * 5.5), btnw - 4, btnh - 4);
  }

  string opratorString() {
	if (op == 1)
	  return "-";
	if (op == 2)
	  return "+";
	if (op == 3)
	  return "/";
	if (op == 4)
	  return "x";
	return "";
  }

  void draw() {
	int xPad = 32;
	int yPad = 16;
	string t1 = n1.size() > 0 ? n1 : "0";
	ofVec2f off1 = bigFont.getOffset(t1);
	bigFont.drawString(t1, width - (off1.x * -2) - xPad, screenHeight - 16);
	if (op != 0) {
	  string t2 = n2 + opratorString();
	  ofVec2f off2 = smallFont.getOffset(t2);
	  smallFont.drawString(t2, width - (off2.x * -2) - xPad, screenHeight - 96);
	}

	calcButtonA.draw(&smallFont);
	calcButtonB.draw(&smallFont);
	calcButtonC.draw(&smallFont);
	calcButtonD.draw(&smallFont);
	calcButtonE.draw(&smallFont);
	calcButtonF.draw(&smallFont);
	calcButtonDot.draw(&smallFont);
	calcButton0.draw(&smallFont);
	calcButton1.draw(&smallFont);
	calcButton2.draw(&smallFont);
	calcButton3.draw(&smallFont);
	calcButton4.draw(&smallFont);
	calcButton5.draw(&smallFont);
	calcButton6.draw(&smallFont);
	calcButton7.draw(&smallFont);
	calcButton8.draw(&smallFont);
	calcButton9.draw(&smallFont);
	calcButtonDel.draw(&smallFont);
	calcButtonMin.draw(&smallFont);
	calcButtonPlus.draw(&smallFont);
	calcButtonDiv.draw(&smallFont);
	calcButtonTimes.draw(&smallFont);
	calcButtonExual.draw(&smallFont);
	calcButtonBin.draw(&smallFont);
	calcButtonOct.draw(&smallFont);
	calcButtonDec.draw(&smallFont);
	calcButtonHex.draw(&smallFont);
	calcButtonDummy1.draw(&smallFont);
	calcButtonDummy2.draw(&smallFont);
	calcButtonDummy3.draw(&smallFont);
  }

  void mouseMoved(int x, int y) {
	calcButtonA.mouseMoved(x, y);
	calcButtonB.mouseMoved(x, y);
	calcButtonC.mouseMoved(x, y);
	calcButtonD.mouseMoved(x, y);
	calcButtonE.mouseMoved(x, y);
	calcButtonF.mouseMoved(x, y);
	calcButtonDot.mouseMoved(x, y);
	calcButton0.mouseMoved(x, y);
	calcButton1.mouseMoved(x, y);
	calcButton2.mouseMoved(x, y);
	calcButton3.mouseMoved(x, y);
	calcButton4.mouseMoved(x, y);
	calcButton5.mouseMoved(x, y);
	calcButton6.mouseMoved(x, y);
	calcButton7.mouseMoved(x, y);
	calcButton8.mouseMoved(x, y);
	calcButton9.mouseMoved(x, y);
	calcButtonDel.mouseMoved(x, y);
	calcButtonMin.mouseMoved(x, y);
	calcButtonPlus.mouseMoved(x, y);
	calcButtonDiv.mouseMoved(x, y);
	calcButtonTimes.mouseMoved(x, y);
	calcButtonExual.mouseMoved(x, y);
	calcButtonBin.mouseMoved(x, y);
	calcButtonOct.mouseMoved(x, y);
	calcButtonDec.mouseMoved(x, y);
	calcButtonHex.mouseMoved(x, y);
  }

  string bin2dec(string num)
  {
	int n = stoi(num);
	int dec = 0;
	int base = 1;
	int temp = n;
	while (temp) {
	  int last = temp % 10;
	  temp = temp / 10;
	  dec += last * base;
	  base = base * 2;
	}
	return to_string(dec);
  }

  string dec2bin(string num)
  {
	int n = stoi(num);
	int bin[32]; 
	int i = 0;
	while (n > 0) {
	  bin[i] = n % 2;
	  n = n / 2;
	  i++;
	}
	string result;
	for (int j = i - 1; j >= 0; j--)
	  result.push_back(to_string(bin[j]).c_str()[0]);
	return result;
  }

  string calcDec(string n1, string n2) {
	string result;
	switch (op) {
	case 1:
	  result = to_string(stof(n2) - stof(n1));
	  break;
	case 2:
	  result = to_string(stof(n2) + stof(n1));
	  break;
	case 3:
	  result = to_string(stof(n2) / stof(n1));
	  break;
	case 4:
	  result = to_string(stof(n2) * stof(n1));
	  break;
	}
	if (result.find('.') != string::npos) {
	  char last = result[result.size() - 1];
	  while (last == '0' || last == '.') {
		result.pop_back();
		if (last == '.')
		  break;
		last = result[result.size() - 1];
	  }
	}
	return result;
  }

  string calcNumber() {
	if (op == 0)
	  return n1;
	switch (program) {
	case 1:
	  return dec2bin(calcDec(bin2dec(n2), bin2dec(n1)));
	  break;
	case 2:
	  break;
	case 3:
	  return calcDec(n2, n1);
	  break;
	case 4:
	  break;
	}
  }

  void putNumber(char n) {
	if (n == '.')
	{
	  if (n1.find('.') == std::string::npos)
		n1.push_back(n);
	  return;
	}
	if (n != '0' || n1.size() > 0)
	  n1.push_back(n);
  }

  void putOperator(int op) {
	if (n1.size() > 0)
	{
	  n2 = calcNumber();
	  n1.clear();
	  this->op = op;
	}
	else if (op == 1)
	  n1.push_back('-');
  }

  void deleteFn() {
	if (n1.size() > 0)
	  n1.pop_back();
	else if (op != 0) {
	  op = 0;
	  for (int i = 0; i < n2.size(); i++)
		n1.push_back(n2[i]);
	  n2.clear();
	}
  }

  void getResult() {
	if (op != 0 && n1.size() > 0) {
	  n1 = calcNumber();
	  n2.clear();
	  op = 0;
	}
  }

  void mousePressed(int x, int y, int button) {
	if (button == OF_MOUSE_BUTTON_LEFT) {
	  if (calcButtonA.contains(x, y))
		putNumber('A');
	  else if (calcButtonB.contains(x, y))
		putNumber('B');
	  else if (calcButtonC.contains(x, y))
		putNumber('C');
	  else if (calcButtonD.contains(x, y))
		putNumber('D');
	  else if (calcButtonE.contains(x, y))
		putNumber('E');
	  else if (calcButtonF.contains(x, y))
		putNumber('F');
	  else if (calcButton0.contains(x, y))
		putNumber('0');
	  else if (calcButtonDot.contains(x, y))
		putNumber('.');
	  else if (calcButton1.contains(x, y))
		putNumber('1');
	  else if (calcButton2.contains(x, y))
		putNumber('2');
	  else if (calcButton3.contains(x, y))
		putNumber('3');
	  else if (calcButton4.contains(x, y))
		putNumber('4');
	  else if (calcButton5.contains(x, y))
		putNumber('5');
	  else if (calcButton6.contains(x, y))
		putNumber('6');
	  else if (calcButton7.contains(x, y))
		putNumber('7');
	  else if (calcButton8.contains(x, y))
		putNumber('8');
	  else if (calcButton9.contains(x, y))
		putNumber('9');
	  else if (calcButtonDel.contains(x, y))
		deleteFn();
	  else if (calcButtonMin.contains(x, y))
		putOperator(1);
	  else if (calcButtonPlus.contains(x, y))
		putOperator(2);
	  else if (calcButtonDiv.contains(x, y))
		putOperator(3);
	  else if (calcButtonTimes.contains(x, y))
		putOperator(4);
	  else if (calcButtonExual.contains(x, y))
		getResult();
	  else if (calcButtonBin.contains(x, y))
	  {
		n1.clear();
		n2.clear();
		op = 0;
		program = 1;
		calcButtonA.enabled(false);
		calcButtonB.enabled(false);
		calcButtonC.enabled(false);
		calcButtonD.enabled(false);
		calcButtonE.enabled(false);
		calcButtonF.enabled(false);
		calcButtonDot.enabled(false);
		calcButton0.enabled(true);
		calcButton1.enabled(true);
		calcButton2.enabled(false);
		calcButton3.enabled(false);
		calcButton4.enabled(false);
		calcButton5.enabled(false);
		calcButton6.enabled(false);
		calcButton7.enabled(false);
		calcButton8.enabled(false);
		calcButton9.enabled(false);
	  }
	  else if (calcButtonOct.contains(x, y))
	  {
		n1.clear();
		n2.clear();
		op = 0;
		program = 2;
		calcButtonA.enabled(false);
		calcButtonB.enabled(false);
		calcButtonC.enabled(false);
		calcButtonD.enabled(false);
		calcButtonE.enabled(false);
		calcButtonF.enabled(false);
		calcButtonDot.enabled(false);
		calcButton0.enabled(true);
		calcButton1.enabled(true);
		calcButton2.enabled(true);
		calcButton3.enabled(true);
		calcButton4.enabled(true);
		calcButton5.enabled(true);
		calcButton6.enabled(true);
		calcButton7.enabled(true);
		calcButton8.enabled(false);
		calcButton9.enabled(false);
	  }
	  else if (calcButtonDec.contains(x, y))
	  {
		n1.clear();
		n2.clear();
		op = 0;
		program = 3;
		calcButtonA.enabled(false);
		calcButtonB.enabled(false);
		calcButtonC.enabled(false);
		calcButtonD.enabled(false);
		calcButtonE.enabled(false);
		calcButtonF.enabled(false);
		calcButtonDot.enabled(true);
		calcButton0.enabled(true);
		calcButton1.enabled(true);
		calcButton2.enabled(true);
		calcButton3.enabled(true);
		calcButton4.enabled(true);
		calcButton5.enabled(true);
		calcButton6.enabled(true);
		calcButton7.enabled(true);
		calcButton8.enabled(true);
		calcButton9.enabled(true);
	  }
	  else if (calcButtonHex.contains(x, y))
	  {
		n1.clear();
		n2.clear();
		op = 0;
		program = 4;
		calcButtonA.enabled(true);
		calcButtonB.enabled(true);
		calcButtonC.enabled(true);
		calcButtonD.enabled(true);
		calcButtonE.enabled(true);
		calcButtonF.enabled(true);
		calcButtonDot.enabled(false);
		calcButton0.enabled(true);
		calcButton1.enabled(true);
		calcButton2.enabled(true);
		calcButton3.enabled(true);
		calcButton4.enabled(true);
		calcButton5.enabled(true);
		calcButton6.enabled(true);
		calcButton7.enabled(true);
		calcButton8.enabled(true);
		calcButton9.enabled(true);
	  }
	}
  }
};
