/**
 * @file app.cpp
 * @author Michal Kovar
 * @date 1 June 2020
 */

#include "../include/app.h"

void App::run() {
  ui.init();
  mainMenu();
  ui.close();
}

void App::mainMenu() {
  char c;
  vector<string> menuItems = {
    "1. Run a Quiz", 
    "2. Editor", 
    "3. Credits",
    "4. Quit"
  };

  ui.clean();
  while (1) {
    ui.draw(menuItems);
    ui.read(c);
    ui.clean();
    switch (c) {
      case '1':
        runQuiz();
        break;
      case '2':
        editor();
        break;
      case '3':
        credits();
        break;
      case '4':
        return;
    }
    ui.clean();
  }
}

void App::runQuiz() {
  vector<string> quizNames;
  shared_ptr<Quiz> quiz(new Quiz);
  StorageCtrl::read(quizNames); // read saved quizzes
  ui.draw(quizNames);
  string userInput;
  ui.draw("Type name of the quiz you wish to try: ");
  ui.read(userInput); // ask user for quiz name to 
  for (auto name : quizNames) { // compare user input with quiz names
    if (userInput == name) {
      if (!loadQuiz(name, quiz)) { // load quiz if found
        ui.clean();
        ui.invalid();
        ui.draw("\n");
        ui.press();
        return;
      }
      Score score;
      quiz->run(ui, score); // run loaded quiz
      evaluateQuiz(score); // evaluate acquired score 
      return;
    }
  }
  ui.clean();
  ui.draw("Quiz does not exist!\n");
  ui.press();
}

void App::credits() {
  ui.draw("Quiz was created by Michal Kovar, student of CTU\n");
  ui.press();
}

void App::editor() {
  char c;
  vector<string> menuItems = {
    "1. Show Quizzes", 
    "2. Create a New Quiz",
    "3. Delete Quiz", 
    "4. Return"
  };

  ui.clean();
  while (1) {
    ui.draw(menuItems);
    ui.read(c);
    ui.clean();
    switch (c) {
      case '1':
        showQuizzes();
        break;
      case '2':
        createNewQuiz();
        break;
      case '3':
        deleteQuiz();
        break;
      case '4':
        return;
    }
    ui.clean();
  }
}

void App::showQuizzes() {
  vector<string> quizNames;
  StorageCtrl::read(quizNames);
  ui.draw(quizNames);
  ui.press();
}

void App::createNewQuiz() {
  shared_ptr<Quiz> quiz(new Quiz);
  quiz->build(ui);
}

void App::deleteQuiz() {
  vector<string> quizNames;
  shared_ptr<Quiz> quiz(new Quiz);
  StorageCtrl::read(quizNames);
  ui.draw(quizNames);
  string userInput;
  ui.draw("Type name of the quiz you wish to delete: ");
  ui.read(userInput);
  ui.draw("\n");
  for (auto name : quizNames) {
    if (userInput == name) {
      if (StorageCtrl::deleteFile(name)) {
        ui.draw("Quiz successfully deleted!\n");
        ui.press();
        return;
      }
      ui.draw("Quiz cannot be deleted.\n");
      ui.press();
    }
  }
  ui.clean();
  ui.draw("Quiz does not exist!\n");
  ui.press();
}

bool App::loadQuiz(string target, shared_ptr<Quiz> quiz) {
  queue<string> content;
  if (!StorageCtrl::load(target, content)) 
    return false;
  int type = Global::toInt(content.front());  // try to convert line from content 
  if (type == INVALID) // line is not convertable 
    return false;
  content.pop();
  if (type != QUIZ) // if converted type is not QUIZ, then saved format is invalid
    return false; 
  if (!quiz->load(content)) // load quiz
    return false;
  return true;
}

void App::evaluateQuiz(Score& score) {
  stringstream ss;
  ui.clean();
  ss << "You have finished the quiz.\n"
     << "Your score is: " << score.correct << " / " << score.total << " !\n";
  ui.draw(ss.str());
  ui.press();
}
