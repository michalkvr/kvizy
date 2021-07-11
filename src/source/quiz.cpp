/**
 * @file quiz.cpp
 * @author Michal Kovar
 * @date 1 June 2020
 */

#include "../include/quiz.h"

void Quiz::run(UICtrl &ui, Score &score) {
  ui.clean();
  ui.draw("This is quiz called " + name + ", created " + date.toString() + " by " + author + ".\n");
  ui.press();
  for (size_t i = 0; i < pages.size(); i++) {
    ui.clean();
    pages[i]->run(ui, score);
  }
}

void Quiz::build(UICtrl &ui) {
  introDialog(ui);
  vector<string> menuItems({
    "1. Create a new page",
    "2. Save quiz and return back",
    "3. Return back wihtout saving"
  });

  char c;
  ui.clean();
  while (1) {
    ui.clean();
    ui.draw(menuItems);
    ui.read(c);
    ui.clean();
    switch (c) {
      case '1':
        createNewPage(ui);
        break;
      case '2':
        saveQuiz(ui);
        return;
      case '3':
        return;
    }
  }
}

void Quiz::save(ostringstream &stream) {
  stream << HeaderType::QUIZ << "\n"
         << pages.size() << DELIM 
         << name << DELIM 
         << author << DELIM
         << date.toString() << DELIM << "\n";
  for (size_t i = 0; i < pages.size(); i++) 
    pages[i]->save(stream);
}

bool Quiz::load(queue<string> &content) {
  vector<string> tokens;
  int pageCount = 0;

  if (content.empty()) 
    return false;
  if (!loadInfo(content, pageCount)) // check quiz info
    return false;
  if (content.empty()) 
    return false;

  for (int i = 0; i < pageCount; i++) { // load relevant type of page due to user input
    int type = Global::toInt(content.front());
    content.pop();
    if (type == BASIC) {
      shared_ptr<Basic> page(new Basic);
      if (!page->load(content)) 
        return false;
      pages.push_back(page);
    } 
    else if (type == SEQUENTIAL) {
      shared_ptr<Sequential> page(new Sequential);
      if (!page->load(content)) 
        return false;
      pages.push_back(page);
    } 
    else {
      return false;
    }
  }
  return true;
}

void Quiz::print(UICtrl &ui) {
  ui.draw("QUIZ:" + name + author + date.toString());
  ui.draw("___________________________________________________________\n");
  for (size_t i = 0; i < pages.size(); i++) {
    pages[i]->print(ui);
  }
  ui.draw("___________________________________________________________\n");
}

void Quiz::introDialog(UICtrl &ui) {
  ui.draw("Type your name: ");
  ui.read(author);
  ui.clean();
  ui.draw("Name your brand new quiz: ");
  ui.read(name);
  ui.clean();
  ui.draw("Let's get started "
          + (author.find(' ') != string::npos ? author.substr(0, author.find(' ')) : author)
          + ", shall we?\n"); // print first name of author
  ui.read();
  ui.clean();
}

void Quiz::createNewPage(UICtrl &ui) {
  vector<string> menuItems(
      {"1. Create a basic page", "2. Create a sequential page", "3. Return"});

  char c;
  ui.clean();
  while (1) {
    ui.clean();
    ui.draw(menuItems);
    ui.read(c);
    ui.clean();
    switch (c) {
      case '1': {
        Basic page;
        page.build(ui);
        pages.push_back(make_shared<Basic>(page));
      } break;
      case '2':  
      {
        Sequential page;
        page.build(ui);
        pages.push_back(make_shared<Sequential>(page));
      } break;
      case '3':
        return;
    }
  }
}

bool Quiz::loadInfo(queue<string> &content, int &pageCount) {
  vector<string> tokens;
  if (!Global::getTokens(content, tokens, MINH_QUIZ)) return false;

  size_t i = 0;
  int tmp = Global::toInt(tokens[i++]);
  if (tmp == INVALID)
    return false;
  else
    pageCount = tmp;

  name = tokens[i++];
  author = tokens[i++];
  date.set(tokens[i]);
  return true;
}

void Quiz::saveQuiz(UICtrl &ui) {
  ostringstream stream; // prepare stream and start saving process
  save(stream);
  if(pages.empty()) {
    ui.clean();
    ui.draw("Empty quiz cannot be saved.\n");
    ui.press();
    ui.clean();
    return;
  }
  string newName = askForFileName(ui);
  string quizStr = stream.str();
  if (quizStr.back() == '\n') // if last char is \n, remove it 
    quizStr.pop_back();
  if (!StorageCtrl::save(newName, quizStr)) {
    ui.draw("Something went wrong...\n");
    ui.press();
  } 
  else {
    ui.draw("Saving successful.\n");
    ui.press();
  }
}

string Quiz::askForFileName(UICtrl &ui) {
  vector<string> quizNames;
  StorageCtrl::read(quizNames);
  string newName = "default";
  while (1) {
    ui.clean();
    ui.draw(quizNames);
    ui.draw("\nSave your quiz as: ");
    ui.read(newName);
    ui.draw("\n");
    bool taken = false;
    for (size_t i = 0; i < quizNames.size(); i++) {
      if (newName == quizNames[i]) 
        taken = true;
    }
    if (taken) {
      ui.draw("File name is already taken, let's try another one!\n");
      ui.press();
      continue;
    } 
    else
      return newName;
  }
}

Quiz::Date::Date() { // get current date
  time_t theTime = time(NULL);
  struct tm *aTime = localtime(&theTime);
  day = aTime->tm_mday;
  month = aTime->tm_mon + 1;
  year = aTime->tm_year + 1900;
}

void Quiz::Date::set(const string &str) { // check if parsed strings are convertable and set date
  vector<string> tokens;
  Global::parse(str, tokens, DATE_DELIM);

  int tmp, i = 0;
  if ((tmp = Global::toInt(tokens[i++])) != INVALID) day = tmp;
  if ((tmp = Global::toInt(tokens[i++])) != INVALID) month = tmp;
  if ((tmp = Global::toInt(tokens[i])) != INVALID) year = tmp;
}

string Quiz::Date::toString() { // stringify date
  stringstream ss;
  ss << day << DATE_DELIM << month << DATE_DELIM << year;
  return ss.str();
}
