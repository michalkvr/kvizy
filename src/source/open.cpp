/**
 * @file open.cpp
 * @author Michal Kovar
 * @date 1 June 2020
 */

#include "../include/open.h"

void Open::build(UICtrl& ui) {
  regex.clear();
  query.clear();
  ui.draw("Your query: ");
  ui.read(query);
  ui.draw("\nCorrect answer: ");
  ui.read(correct);
  ui.clean();
  vector<string> menuItems({
    "1. Add regular expression",
    "2. Add similar answer", 
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
        readRegex(ui);
        break;
      case '2':
        ui.draw("Similar answer: ");
        ui.read(similar);
        break;
      case '3':
        return;
    }
  }
}

void Open::run(UICtrl& ui, Score& score) {
  ui.draw(query + "\n\n");
  ui.draw("Your answer: ");
  string answer;
  ui.read(answer);

  int points = evaluate(answer);
  ui.draw("\n");
  switch (points) {
    case POINTS_PER_QUESTION + BONUS: 
      ui.draw("Nice, answer is absolutely correct! - You got bonus points..\n");
      break;
    case POINTS_PER_QUESTION:
      ui.draw("Correct!\n");
      break;
    case NO_POINTS:
      ui.draw("Incorrect, maybe next time..\n");
      break;
  }
  ui.press();
  score.correct += points;
  score.total += POINTS_PER_QUESTION;
}

void Open::save(ostringstream& stream) {
  if (regex == "") 
    regex = EMPTY_FIELD;
  if (similar.empty()) 
    similar.push_back(EMPTY_FIELD);
  stream << OPEN << "\n"
         << similar.size() << DELIM 
         << query << DELIM 
         << correct << DELIM
         << regex << DELIM;
  for (size_t i = 0; i < similar.size(); i++) 
    stream << similar[i] << DELIM;
  stream << "\n";
}

bool Open::load(queue<string>& content) {
  vector<string> tokens;
  if (!Global::getTokens(content, tokens, MINH_OPEN)) 
    return false;

  size_t i = 0;
  int similarCnt = Global::toInt(tokens[i++]);
  if (similarCnt == INVALID) 
    return false;

  query = tokens[i++];
  correct = tokens[i++];
  regex = tokens[i++];
  if (regex == EMPTY_FIELD) 
    regex = "";

  while (i < tokens.size()) 
    similar.push_back(tokens[i++]);
  if (similar.front() == EMPTY_FIELD) 
    similar.clear();
  return true;
}

void Open::print(UICtrl& ui) {
  ui.draw("----------------------\n");
  ui.draw("--> OPEN QUESTION: <--\n");
  ui.draw("QUERY: " + query + "\n");
  ui.draw("CORRECT: " + correct + "\n");
  ui.draw("REGEX: " + regex + "\n");
  ui.draw("SIMILAR ANSWERS:\n");
  ui.draw(similar);
  ui.draw("----------------------\n");
}

int Open::evaluate(const string& answer) {
  string answerLower = Global::toLower(answer);
  bool foundSimilar = false;
  for (size_t i = 0; i < similar.size(); i++) {
    if (Global::toLower(similar[i]) == answerLower) {
      foundSimilar = true;
      break;
    }
  }

  if (Global::toLower(correct) == answerLower)
    return POINTS_PER_QUESTION + BONUS;
  else if (!regex.empty() && (answerLower.find(Global::toLower(regex)) != string::npos)) // if regex is not empty and found in answer, give points
    return POINTS_PER_QUESTION;
  else if (foundSimilar)
    return POINTS_PER_QUESTION;
  return NO_POINTS;
}

void Open::readRegex(UICtrl& ui) {
  if (!regex.empty())
    ui.draw(
        "Regular expression will be overridden (type 'DELETE' to delete)\n");
  string str;
  ui.draw("Type regular expression: ");
  ui.read(str);
  if (str == "DELETE")
    regex = "";
  else
    regex = str;
}