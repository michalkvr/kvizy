/**
 * @file quiz.h
 * @author Michal Kovar
 * @date 1 June 2020
 */

#pragma once

#include "basic.h"
#include "item.h"
#include "page.h"
#include "sequential.h"

using namespace std;

/**
 * @brief Object of quiz is holding whole quiz - name, pages, date, author.
 */
class Quiz : public Item {
 public:
  void run(UICtrl& ui, Score& score) override;
  void build(UICtrl& ui) override;
  void save(ostringstream& stream) override;
  bool load(queue<string>& content) override;
  void print(UICtrl& ui) override;

 private:
  /**
   * @brief Struct holding date data.
   */
  struct Date {
    /**
     * @brief Construct object with current date.
     */
    Date();
    void set(const string& str);
    string toString();
    int day;
    int month;
    int year;
  };

  /**
   * @brief Print introductory dialog when process of quiz creation starts.
   * @param ui UI object for user-app communication.
   */
  void introDialog(UICtrl& ui);

  /**
   * @brief Process where type of page is acquired from user and then page
   * building process is called.
   * @param ui UI object for user-app communication.
   */
  void createNewPage(UICtrl& ui);

  /**
   * @brief Try to loads quiz info from relevant content line.
   * @param content Contains rows from saved file that was read.
   * @param pageCount Returns page count that follows in loading process.
   * @return True if loading of header was successful, return false otherwise.
   */
  bool loadInfo(queue<string>& content, int& pageCount);

  /**
   * @brief Save quiz to local storage.
   * @param ui UI object for user-app communication.
   */
  void saveQuiz(UICtrl& ui);

  /**
   * @brief Asks user for file name.
   * @param ui UI object for user-app communication.
   */
  string askForFileName(UICtrl& ui);

  Date date;
  string name;
  string author;
  vector<shared_ptr<Page>> pages;
};
