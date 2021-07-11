/**
 * @file open.h
 * @author Michal Kovar
 * @date 1 June 2020
 */

#pragma once

#include "question.h"

using namespace std;

/**
 * @brief Type of question where are not any possible answers offered.
 *        Only one answer is correct, but regular expression can be evaluated,
 *        aswell as similar answers.
 */
class Open : public Question {
 public:
  void run(UICtrl& ui, Score& score) override;
  void build(UICtrl& ui) override;
  void save(ostringstream& stream) override;
  bool load(queue<string>& content) override;
  void print(UICtrl& ui) override;
  int evaluate(const string& answer) override;

 private:
  string correct;
  vector<string> similar;
  string regex;

  /**
   * @brief Asks user for regular expression and save it into regex property.
   * @param ui UI object for user-app communication.
   */
  void readRegex(UICtrl& ui);
};