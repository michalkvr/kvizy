/**
 * @file uictrl.cpp
 * @author Michal Kovar
 * @date 1 June 2020
 */

#include "../include/uictrl.h"

void UICtrl::init() {
  initscr();
  curs_set(0);
  clear();
}

void UICtrl::clean() { 
  clear();
}

void UICtrl::press() {
  draw("Press any key ...\n");
  read();
}

void UICtrl::draw(const string& text) { 
  printw("%s", text.c_str()); 
}

void UICtrl::draw(const vector<string>& items) {
  for (auto e : items) 
    draw(e + "\n");
}

void UICtrl::read() { 
  getch(); 
}

void UICtrl::read(char& c) { 
  c = getch(); 
}

void UICtrl::read(string& str) {
  while (1) {
    char buffer[BUFFER_LENGTH + 1];
    getnstr(buffer, BUFFER_LENGTH);
    string tmp(buffer);
    if (!tmp.empty()) {
      str = tmp;
      return;
    } 
    else
      invalid();
  }
}

void UICtrl::read(vector<string>& array) { // read string and push it to array
  string str;
  read(str);
  array.push_back(str);
}

void UICtrl::invalid() {
  draw("Invalid input. Try again: "); 
}

void UICtrl::close() { 
  endwin(); 
}
