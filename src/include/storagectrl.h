/**
 * @file storagectrl.h
 * @author Michal Kovar
 * @date 1 June 2020
 */

#pragma once

#include <dirent.h>

#include <cstdio>
#include <fstream>
#include <queue>
#include <string>
#include <vector>

#include "global.h"

using namespace std;

/**
 * @brief Class is used for handling file operations in local storage.
 */
class StorageCtrl {
 public:
  /**
   * @brief Reads names of saved quizzes in local storage.
   * @param vec Names are pushed here.
   * @return True if reading was succesful. False otherwise.
   */
  bool static read(vector<string>& vec);

  /**
   * @brief Takes string serialized quiz and try to save it into file called
   * fileName.
   * @param fileName Name of new file, where quiz will be saved.
   * @param quizStr Serialized quiz which will be saved.
   * @return True if saving was succesful. False otherwise.
   */
  bool static save(const string& fileName, const string& quizStr);

  /**
   * @brief Takes target file and push it to the queue.
   * @param fileName Name of file with content to load.
   * @param content Queue where line of file will be pushed.
   * @return True if loading was succesful. False otherwise.
   */
  bool static load(const string& fileName, queue<string>& content);

  /**
   * @brief Deletes file.
   * @param fileName Name of file to delete.
   * @return True if deleting was succesful. False otherwise.
   */
  bool static deleteFile(const string& fileName);
};