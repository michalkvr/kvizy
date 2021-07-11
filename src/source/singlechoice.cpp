/**
 * @file singlechoice.cpp
 * @author Michal Kovar
 * @date 1 June 2020
 */

#include "../include/singlechoice.h"

void Singlechoice::build(UICtrl& ui) {
  query.clear();
  ui.draw("Your query: ");
  ui.read(query);
  ui.draw("\nCorrect answer: ");
  ui.read(correct);
  ui.clean();
  vector<string> menuItems({
    "1. Add possible answer", 
    "2. Save and continue"
  });

  char c;
  while (1) {
    ui.clean();
    ui.draw(menuItems);
    ui.read(c);
    ui.clean();
    switch (c) {
      case '1':
        ui.draw("Possible answer: ");
        ui.read(possible);
        break;
      case '2':
        return;
    }
  }
}

void Singlechoice::run(UICtrl& ui, Score& score) {
  ui.draw(query + "\n\n");
  ui.draw("Possible answers:\n");
  ui.draw(possible);
  ui.draw("\n");
  ui.draw("Your answer: ");
  string answer;
  ui.read(answer);
  int points = evaluate(answer);

  ui.draw("\n");
  switch (points) {
    case POINTS_PER_QUESTION:
      ui.draw("Nice, your answer is correct!\n");
      break;
    case 0:
      ui.draw("Incorrect, maybe next time..\n");
      break;
  }
  ui.press();
  score.correct += points;
  score.total += POINTS_PER_QUESTION;
}

void Singlechoice::save(ostringstream& stream) {
  stream << HeaderType::SINGLECHOICE << "\n"
         << possible.size() << DELIM 
         << query << DELIM 
         << correct << DELIM;
  for (size_t i = 0; i < possible.size(); i++) 
    stream << possible[i] << DELIM;
  stream << "\n";
}

bool Singlechoice::load(queue<string>& content) {
  vector<string> tokens;
  if (!Global::getTokens(content, tokens, MINH_SINGLECHOICE)) 
    return false;

  size_t i = 0;
  int possibleCnt = Global::toInt(tokens[i++]);
  if (possibleCnt == INVALID) 
    return false;

  query = tokens[i++];
  correct = tokens[i++];

  while (i < tokens.size()) 
    possible.push_back(tokens[i++]);
  return true;
}

void Singlechoice::print(UICtrl& ui) {
  ui.draw("----------------------\n");
  ui.draw("--> SINGLECHOICE QUESTION: <--\n");
  ui.draw("QUERY: " + query + "\n");
  ui.draw("CORRECT: " + correct + "\n");
  ui.draw("POSSIBLE ANSWERS:\n");
  ui.draw(possible);
  ui.draw("----------------------\n");
}

int Singlechoice::evaluate(const string& answer) {
  if (Global::toLower(correct) == Global::toLower(answer))
    return POINTS_PER_QUESTION;
  return NO_POINTS;
}