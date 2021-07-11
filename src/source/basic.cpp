/**
 * @file basic.cpp
 * @author Michal Kovar
 * @date 1 June 2020
 */

#include "../include/basic.h"

void Basic::run(UICtrl& ui, Score& score) {
  ui.clean();
  ui.draw("This page is called \"" + name + "\"\n");
  ui.press();
  for (size_t i = 0; i < questions.size(); i++) {
    ui.clean();
    questions[i]->run(ui, score);
  }
}

void Basic::build(UICtrl& ui) {
  ui.draw("Name your page: ");
  ui.read(name);
  ui.draw("Choose a type of question:\n");
  vector<string> menuItems({
    "1. Open",
    "2. Singlechoice", 
    "3. Multichoice", 
    "4. Return"
  });

  char c;
  ui.clean();
  while (1) {
    ui.clean();
    ui.draw(menuItems);
    ui.read(c);
    ui.clean();
    switch (c) { // based on user input - build relevant question type and push to vector of questions
      case '1': {
        Open question;
        question.build(ui);
        questions.push_back(make_shared<Open>(question));
      } break;
      case '2': {
        Singlechoice question;
        question.build(ui);
        questions.push_back(make_shared<Singlechoice>(question));
      } break;
      case '3': {
        Multichoice question;
        question.build(ui);
        questions.push_back(make_shared<Multichoice>(question));
      } break;
      case '4':
        return;
    }
  }
}

void Basic::save(ostringstream& stream) {
  stream << BASIC << "\n" // add type of line
         << questions.size() << DELIM // number of questions  
         << name << DELIM << "\n"; // name of the page
  for (size_t i = 0; i < questions.size(); i++) 
    questions[i]->save(stream); // hand all questions to stream
}

bool Basic::load(queue<string>& content) {
  vector<string> tokens;
  int questionCount = 0;
  if (!loadInfo(content, questionCount)) // try to load quiz info
    return false;
 
  for (int i = 0; i < questionCount; i++) { 
    int type = Global::toInt(content.front());
    content.pop();
    if (type == OPEN) { // check which type should be next and load relevant type of question
      shared_ptr<Open> question(new Open);
      if (!question->load(content)) 
        return false;
      questions.push_back(question);
    } 
    else if (type == SINGLECHOICE) {
      shared_ptr<Singlechoice> question(new Singlechoice);
      if (!question->load(content)) return false;
      questions.push_back(question);
    } 
    else if (type == MULTICHOICE) {
      shared_ptr<Multichoice> question(new Multichoice);
      if (!question->load(content)) return false;
      questions.push_back(question);
    } 
    else
      return false;
  }
  return true;
}

void Basic::print(UICtrl& ui) {
  ui.draw("================================\n");
  ui.draw("=====> PAGE: " + name + " <=====\n");
  for (size_t i = 0; i < questions.size(); i++) questions[i]->print(ui);
  ui.draw("================================\n");
}

bool Basic::loadInfo(queue<string>& content, int& questionCount) {
  if (content.empty()) 
    return false;

  vector<string> tokens;
  if (!Global::getTokens(content, tokens, MINH_BASIC)) // parse current line and check if there is at least specific number of tokens
    return false;

  size_t i = 0;
  int tmp = Global::toInt(tokens[i++]);
  if (tmp == INVALID)
    return false;
  else
    questionCount = tmp;
  name = tokens[i];
  return true;
}