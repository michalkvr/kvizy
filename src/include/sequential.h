/**
 * @file sequential.h
 * @author Michal Kovar
 * @date 1 June 2020
 */

#pragma once

#include "basic.h"
#include "page.h"

using namespace std;

/**
 * @brief Represents specialized type of page. Contains two answer each one
 *        corresponding with relevant Basic Page pointer.
 */
class Sequential : public Page {
 public:
  void run(UICtrl& ui, Score& score) override;
  void build(UICtrl& ui) override;
  void save(ostringstream& stream) override;
  bool load(queue<string>& content) override;
  void print(UICtrl& ui) override;

 private:
  string query;
  string firstAnswer;
  string secondAnswer;
  shared_ptr<Basic> firstPage;
  shared_ptr<Basic> secondPage;
};