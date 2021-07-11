/**
 * @file global.cpp
 * @author Michal Kovar
 * @date 1 June 2020
 */

#include "../include/global.h"

int Global::parse(const string& str, vector<string>& res, const char delim) {
  res.clear();
  istringstream ss(str); // create stream from string
  string token;
  while (getline(ss, token, delim)) // get tokens due to delim
    if (!token.empty()) // skip empty tokens
      res.push_back(token);
  return res.size();
}

int Global::parse(const string& str, vector<string>& res, const string& delim) {
  res.clear();
  string token, strRemaining = str;
  size_t index;
  while ((index = strRemaining.find(delim)) != string::npos) { // find delim in string
    res.push_back(strRemaining.substr(0, index)); // push tokens to vector
    strRemaining = strRemaining.substr(index + delim.length(), strRemaining.length() - 1); // remove pushed token from string
  }
  return res.size();
}

bool Global::getTokens(queue<string>& content, vector<string>& tokens, int minSize) {
  if (content.empty()) 
    return false;
  string lineToParse = content.front();
  content.pop();
  Global::parse(lineToParse, tokens, DELIM); // get parsed tokens from string
  if ((int)tokens.size() < minSize) 
    return false;
  return true;
}

int Global::toInt(const string& str) {
  try {
    return stoi(str); // return int if string is convertable
  } catch (...) {
    return INVALID;
  }
}

string Global::toLower(const string& str) {
  string res = str;
  if (!CASE_SENSITIVE) // if case sensitivity is turned on, do not transform to lower
    transform(res.begin(), res.end(), res.begin(), ::tolower);
  return res;
}

Score::Score() { // reset score
  correct = 0;
  total = 0;
}