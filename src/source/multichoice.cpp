/**
 * @file multichoice.cpp
 * @author Michal Kovar
 * @date 1 June 2020
 */

#include "../include/multichoice.h"

void Multichoice::build(UICtrl& ui) {
  query.clear();
  ui.draw("Your query: ");
  ui.read(query);
  ui.clean();
  vector<string> menuItems({
    "1. Add correct answer", 
    "2. Add possible answer",
    "3. Save and continue"
  });

  char c;
  while (1) {
    ui.clean();
    ui.draw(menuItems);
    ui.read(c);
    ui.clean();
    switch (c) {
      case '1':
        ui.draw("Correct answer: ");
        ui.read(correct);
        break;
      case '2':
        ui.draw("Possible answer: ");
        ui.read(possible);
        break;
      case '3':
        return;
    }
  }
}

void Multichoice::run(UICtrl& ui, Score& score) {
  ui.draw(query + "\n\n");
  ui.draw("Possible answers:\n");
  ui.draw(possible);
  ui.draw("Separate your answers with \"");
  ui.draw(ANSWER_DELIM);
  ui.draw("\"");
  ui.draw("\nYour answers: ");
  string answer;
  ui.read(answer);
  answer += ";";

  int points = evaluate(answer);
  ui.draw("\n");
  if (points == POINTS_PER_QUESTION * (int)correct.size()) 
    ui.draw("Nice, your answer is correct!\n");
  else if (points > NO_POINTS) // if at least some of correct answers matched, some poinst are given
    ui.draw("Some answers are correct, you get some points\n");
  else
    ui.draw("Incorrect, maybe next time..\n");
  ui.press();
  score.correct += points;
  score.total += POINTS_PER_QUESTION;
}

void Multichoice::save(ostringstream& stream) {
  stream << MULTICHOICE << "\n" 
         << possible.size() << DELIM 
         << query << DELIM;
  for (size_t i = 0; i < correct.size(); i++) 
    stream << correct[i] << DELIM; 
  for (size_t i = 0; i < possible.size(); i++) 
    stream << possible[i] << DELIM;
  stream << "\n";
}

bool Multichoice::load(queue<string>& content) {
  vector<string> tokens;
  if (!Global::getTokens(content, tokens, MINH_MULTICHOICE))  // parse current line and check if there is at least specific number of tokens
    return false;

  int i = 0;
  int correctCnt = Global::toInt(tokens[i++]);
  if (correctCnt == INVALID) 
    return false;
  query = tokens[i++];

  while (i < correctCnt) 
    correct.push_back(tokens[i++]);
  while (i < (int)tokens.size()) 
    possible.push_back(tokens[i++]);
  return true;
}

void Multichoice::print(UICtrl& ui) {
  ui.draw("----------------------\n");
  ui.draw("--> MULTICHOICE QUESTION: <--\n");
  ui.draw("QUERY: " + query + "\n");
  ui.draw("CORRECT ANSWERS:\n");
  ui.draw(correct);
  ui.draw("POSSIBLE ANSWERS:\n");
  ui.draw(possible);
  ui.draw("----------------------\n");
}

int Multichoice::evaluate(const string& answer) {
  vector<string> tokens;
  string tmp = answer;
  remove_if(tmp.begin(), tmp.end(), ::isspace); // get rid of spaces from answer
  Global::parse(tmp, tokens, ANSWER_DELIM); // seperate with relevant delimiter
  int points = 0;
  for (size_t i = 0; i < correct.size(); i++) { // compare each user answer with each correct answer
    for (size_t j = 0; j < tokens.size(); j++) {
      if (Global::toLower(correct[i]) == Global::toLower(tokens[j])) { // give corresponding number of points
        points += POINTS_PER_QUESTION;
        break;
      }
    }
  }
  if (tokens.size() > correct.size()) // of some of answers were correct, but there are to many answers from user
    return POINTS_PER_QUESTION;
  return points;
}