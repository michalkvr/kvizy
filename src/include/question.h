/**
 * @file question.h
 * @author Michal Kovar
 * @date 1 June 2020
 */

#pragma once

#include "item.h"

using namespace std;

/**
 * @brief Base class for different type of questions.
 */
class Question : public Item {
 public:
  /**
   * @brief Evaluates answer from user.
   * @param answer Answer to evaluate.
   * @return Global constant POINTS_PER_QUESTION if correct, NO_POINTS otherwise
   */
  virtual int evaluate(const string& answer) = 0;
  virtual ~Question() = default;

 protected:
  string query;
};