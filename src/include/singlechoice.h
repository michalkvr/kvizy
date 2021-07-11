/**
 * @file singlechoice.h
 * @author Michal Kovar
 * @date 1 June 2020
 */

#pragma once

#include "question.h"

using namespace std;

/**
 * @brief Type of question with multiple possible answers stored in possible
 * property. Only one answer is correct.
 */
class Singlechoice : public Question {
 public:
  void run(UICtrl& ui, Score& score) override;
  void build(UICtrl& ui) override;
  void save(ostringstream& stream) override;
  bool load(queue<string>& content) override;
  void print(UICtrl& ui) override;
  int evaluate(const string& answer) override;

 private:
  vector<string> possible;
  string correct;
};