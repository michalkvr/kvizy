/**
 * @file item.h
 * @author Michal Kovar
 * @date 1 June 2020
 */

#pragma once

#include <iostream>
#include <memory>
#include <queue>
#include <sstream>
#include <string>
#include <vector>

#include "global.h"
#include "uictrl.h"

using namespace std;

/**
 * @brief Base class for Quiz, Page and Question classes.
 */
class Item {
 public:
  /**
   * @brief Starts run process, when user runs specific quiz, derived classes
   * start their implementation of evaluation.
   * @param ui User interface objects, which is passed through derived run
   * methods. Needed for user-app communictation.
   * @param score Holds results of user.
   */
  virtual void run(UICtrl& ui, Score& score) = 0;
  /**
   * @brief Starts build proccess, each class implementation has own
   * building(creating) process.
   * @param ui User interface objects, which is passed through derived run
   * methods. Needed for user-app communictation.
   */
  virtual void build(UICtrl& ui) = 0;
  /**
   * @brief Starts saving proccess. Quiz is little by little serialized into
   * string and saved.
   * @param stream Stream where the data of inherited objects flow.
   */
  virtual void save(ostringstream& stream) = 0;
  /**
   * @brief Starts loading proccess. Save file is deserialized into quiz object
   * and prepared for run method.
   * @param content Contains all rows from saved file that was read.
   * @return True if loading of inherited object was successful, return false
   * otherwise.
   */
  virtual bool load(queue<string>& content) = 0;
  /**
   * @brief Starts printing proccess of quiz and its properties, method is never
   * called in current version - only for debugging.
   * @param ui User interface objects, which is passed through derived run
   * methods. Needed for user-app communictation.
   */
  virtual void print(UICtrl& ui) = 0;
  virtual ~Item() = default;
};