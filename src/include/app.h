/**
 * @file app.h
 * @author Michal Kovar
 * @date 1 June 2020
 */ 

#pragma once

#include "uictrl.h"
#include "storagectrl.h"
#include "quiz.h"

#include <memory>
#include <string>
#include <queue>
#include <vector>

using namespace std;

/**
 * @brief Core of application - holds user interface, menus and runs actions.
 */
class App {
  public:
    /**
     * @brief Runs main menu of application.
     */
    void run();

  private:
    /**
     * @brief Holds UI object for dialog client-user.
     */
    UICtrl ui;

    /**
     * @brief Runs main menu of application.
     */
    void mainMenu();

    /**
     * @brief Runs editor menu of application.
     */
    void editor();

    /**
     * @brief Asks user for quiz to run and starts the quiz.
     */
    void runQuiz();

    /**
     * @brief Display some information about application and author.
     */
    void credits(); 

    /**
     * @brief Starts process of building a quiz.
     */
    void createNewQuiz(); 

    /**
     * @brief Asks user for quiz to delete and try to delete it.
     */
    void deleteQuiz();

    /**
     * @brief Shows created quizzes.
     */
    void showQuizzes();

    /**
     * @brief Tries to load quiz from file.
     * @param target File name of quiz to load.
     * @param quiz Prepared empty quiz for loading process.
     * @return True if loading was successful, return false otherwise.
     */
    bool loadQuiz(string target, shared_ptr<Quiz> quiz);

    /**
      * @brief Display user's score.
      * @param score Score object holding results of user.
      */
    void evaluateQuiz(Score & score);
};  
