/**
 * @file page.h
 * @author Michal Kovar
 * @date 1 June 2020
 */

#pragma once

#include "item.h"
#include "multichoice.h"
#include "open.h"
#include "question.h"
#include "singlechoice.h"

using namespace std;

/**
 * @brief Base class for different type of pages.
 */
class Page : public Item {
 protected:
  string name;
};