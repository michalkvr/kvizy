/**
 * @file storagectrl.cpp
 * @author Michal Kovar
 * @date 1 June 2020
 */

#include "../include/storagectrl.h"

bool StorageCtrl::read(vector<string> &vec) { // read
  DIR *dir;
  dir = opendir(EXAMPLE_DIR);
  if (!dir) // if null, folder could not be opened
    return false;

  struct dirent *ent;
  while ((ent = readdir(dir))) {
    string tmp(ent->d_name);
    if (tmp != "." && tmp != "..") 
      vec.push_back(tmp);
  }
  closedir(dir);
  return true;
}

bool StorageCtrl::load(const string &fileName, queue<string> &content) { // load file names from example folder
  ifstream file;
  string buffer = "";
  file.open(buffer + EXAMPLE_DIR + "/" + fileName);
  if (file.bad()) 
    return false;
  buffer.clear();
  while (getline(file, buffer)) {
    content.push(buffer);
    buffer.clear();
  }
  file.close();
  return true;
}

bool StorageCtrl::save(const string &fileName, const string &quizStr) { // create file and save serialized quiz
  ofstream file;
  string buffer = "";
  file.open(buffer + EXAMPLE_DIR + "/" + fileName);
  if (file.bad()) 
    return false;
  file << quizStr;
  file.close();
  return true;
}

bool StorageCtrl::deleteFile(const string &fileName) { // remove file
  string buffer = "";
  if (remove((buffer + EXAMPLE_DIR + "/" + fileName).c_str()) != 0)
    return false;
  return true;
}