/**
 * @file sequential.cpp
 * @author Michal Kovar
 * @date 1 June 2020
 */

#include "../include/sequential.h"

void Sequential::run(UICtrl& ui, Score& score) {
  string answer;
  ui.draw(query + "\n");
  while (1) {
    ui.read(answer);
    if (Global::toLower(answer) == Global::toLower(firstAnswer)) {
      firstPage->run(ui, score);
      return;
    } 
    else if (Global::toLower(answer) == Global::toLower(secondAnswer)) {
      secondPage->run(ui, score);
      return;
    }
    ui.invalid();
  }
}

void Sequential::build(UICtrl& ui) {
  ui.draw("Type sequential query: "); // get sequential query
  ui.read(query);
  ui.draw("Your first answer: "); // get first answer
  ui.read(firstAnswer);
  ui.draw("Your second answer: "); // get second answer
  ui.read(secondAnswer);
  ui.draw("\nLet's make page for your first answer ( " + firstAnswer + " ).\n");
  ui.press();
  ui.clean();
  Basic first;
  first.build(ui);
  firstPage = make_shared<Basic>(first); // build basic page for the first answer
  ui.clean();
  ui.draw("Now page for your second answer ( " + secondAnswer + " ).\n");
  ui.press();
  ui.clean();
  Basic second;
  second.build(ui);
  secondPage = make_shared<Basic>(second); // build basic page for the second answer
}

void Sequential::save(ostringstream& stream) {
  stream << SEQUENTIAL << "\n"
         << 2 << DELIM 
         << query << DELIM 
         << firstAnswer << DELIM 
         << secondAnswer << DELIM << "\n";
  firstPage->save(stream);
  secondPage->save(stream);
}

bool Sequential::load(queue<string>& content) { // load correct format of sequential query from content line
  vector<string> tokens;
  if (!Global::getTokens(content, tokens, MINH_SEQUENTIAL)) 
    return false;
  int i = 0;
  int answerCount = Global::toInt(tokens[i++]);
  if (answerCount < 0) 
    return false;
  query = tokens[i++];

  firstAnswer = tokens[i++];
  secondAnswer = tokens[i++];
  content.pop();
  Basic first;
  if (!first.load(content)) 
    return false;
  firstPage = make_shared<Basic>(first);
  content.pop();
  Basic second;
  if (!second.load(content)) 
    return false;
  secondPage = make_shared<Basic>(second);
  return true;
}

void Sequential::print(UICtrl& ui) {
  ui.draw("================================\n");
  ui.draw("=====> SEQUENTIAL PAGE <=====\n");
  ui.draw("Query: " + query + "\n");
  ui.draw("First answer: " + firstAnswer + "\n");
  ui.draw("Second answer: " + secondAnswer + "\n");
  firstPage->print(ui);
  secondPage->print(ui);
  ui.draw("================================\n");
}