/**
 * @file uictrl.h
 * @author Michal Kovar
 * @date 1 June 2020
 */

#pragma once

#include <ncurses.h>

#include <string>
#include <vector>

#include "global.h"
#include "storagectrl.h"

using namespace std;

/**
 * @brief Interface for user-app communcation.
 */
class UICtrl {
 public:
  /**
   * @brief Initializes screen.
   */
  void init();
  /**
   * @brief Clears screen.
   */
  void clean();
  /**
   * @brief Print text and wait for press key.
   */
  void press();
  /**
   * @brief Draw string on screen.
   */
  void draw(const string& text);
  /**
   * @brief Draw vector of strings on screen.
   */
  void draw(const vector<string>& menuItems);
  /**
   * @brief Waits for pressing any key.
   */
  void read();
  /**
   * @brief Reads key from user.
   * @param c Pressed key.
   */
  void read(char& c);
  /**
   * @brief Reads string from user.
   * @param str String which was read from user.
   */
  void read(string& str);
  /**
   * @brief Reads string from user and push it to vector.
   * @param array Array where read string is pushed.
   */
  void read(vector<string>& array);
  /**
   * @brief Print error text;
   */
  void invalid();
  /**
   * @brief End screen.
   */
  void close();
};