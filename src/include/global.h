/**
 * @file global.h
 * @author Michal Kovar
 * @date 1 June 2020
 */

#pragma once

#include <algorithm>
#include <queue>
#include <sstream>
#include <string>
#include <vector>

#define EXAMPLE_DIR "examples"

/**
 * @brief Max buffer length while getting input from user in terminal.
 */
#define BUFFER_LENGTH 200

/**
 * @brief Used for indication of fail int conversion
 */
#define INVALID -1

/**
 * @brief Bunch of used delimiters.
 */
#define DELIM "|~|"
#define DATE_DELIM '.'
#define ANSWER_DELIM ";"

/**
 * @brief This value is used instead of empty field when saving quiz into file.
 */
#define EMPTY_FIELD ":null:"

/**
 * @brief 0 = case insensitive comparison of answers, 1 = case sensitive
 * comparison.
 */
#define CASE_SENSITIVE 0

using namespace std;

/**
 * @brief Used for evaluating correct answers.
 */
enum Points { NO_POINTS = 0, POINTS_PER_QUESTION = 1, BONUS = 1 };

/**
 * @brief Used for format checking of fetched saved quizzes. If loaded quiz line
 * is less than MINH_* value, than quiz is invalid.
 */
enum MinHeaderSize {
  MINH_QUIZ = 4,
  MINH_BASIC = 2,
  MINH_SEQUENTIAL = 4,
  MINH_OPEN = 5,
  MINH_SINGLECHOICE = 4,
  MINH_MULTICHOICE = 6
};

/**
 * @brief Used for identification of object type.
 */
enum HeaderType { QUIZ, BASIC, SEQUENTIAL, OPEN, SINGLECHOICE, MULTICHOICE };

/**
 * @brief Struct holding score of user while running quiz.
 */
struct Score {
  Score();
  int correct;
  int total;
};

/**
 * @brief Bunch of useful functions
 */
class Global {
 public:
  /**
   * @brief Parse a string based on given char delimiter. Mainly helping method
   * for getTokens(...) method.
   * @param str Holds string to parse.
   * @param res Holds vector where parsed tokens are pushed.
   * @param delim Gives desired delimiter.
   * @return How many tokens were parsed.
   */
  static int parse(const string& str, vector<string>& res, const char delim);
  
  /**
   * @brief Parse a string based on given string delimiter. Mainly helping
   * method for getTokens(...) method.
   * @param str Holds string to parse.
   * @param res Holds vector where parsed tokens are pushed.
   * @param delim Gives desired delimiter.
   * @return How many tokens were parsed.
   */
  static int parse(const string& str, vector<string>& res, const string& delim);

  /**
   * @brief Function used for parsing line from loaded file.
   * @param content Holds line from loaded file.
   * @param tokens Holds vector where parsed tokens are pushed.
   * @param minSize Holds expected minimal count of line that should be acquired
   * from parsing.
   * @return True if successful, false otherwise.
   */
  static bool getTokens(queue<string>& content, vector<string>& tokens,
                        int minSize);

  /**
   * @brief Function for convertion from string to int.
   * @param str String that should be convert into string.
   * @return -1 of Global INVALID if exception is thrown. Return value of
   * converted int otherwise.
   */
  static int toInt(const string& str);

  /**
   * @brief Function for transformation string to lower case if case sensitivity
   * is turned off in global.h
   * @param str String that should be transformed into lower case string.
   * @return Transformed string if case sensitivity is turned off, returns same
   * string which was passed otherwise.
   */
  static string toLower(const string& str);
};
