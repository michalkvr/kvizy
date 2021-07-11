/**
 * @file basic.h
 * @author Michal Kovar
 * @date 1 June 2020
 */

#pragma once

#include "page.h"

using namespace std;

/**
 * @brief Represents specialized type of page. Contains vector with different
 * type of questions.
 */
class Basic : public Page {
 public:
  void run(UICtrl& ui, Score& score) override;
  void build(UICtrl& ui) override;
  void save(ostringstream& stream) override;
  bool load(queue<string>& content) override;
  void print(UICtrl& ui) override;

 private:
  vector<shared_ptr<Question>> questions;

  /**
   * @brief Deserializes line from loaded file, that contains quiz info.
   * @param content Queue with line of file content, which is processed inside
   * method.
   * @param questionCount I/O parameter of how many questions follows and should
   * be stored in object.
   * @return True if loading was successful, false otherwise.
   */
  bool loadInfo(queue<string>& content, int& questionCount);
};