#ifndef _DIALOGMANAGER_H_
#define _DIALOGMANAGER_H_

#include <string>
#include <vector>

#include "eventManager.h"
#include "vec2d.h"

class DialogManager {
 public:
  ;
  DialogManager() {
    this->singleText = " ";
    this->singleName = " ";
    this->output.push_back(" ");
    this->output.push_back(" ");
  };

  void handleDialog(std::vector<std::string> speakers,
                    std::vector<std::string> texts) {
    // std::cout << "handle Dialog";
    this->speakers.assign(speakers.begin(), speakers.end());
    this->texts.assign(texts.begin(), texts.end());

    max = speakers.size();
    // std::cout << max << std::endl;
    pointer = 0;
  };

  void handleDialog(std::string name, std::string text) {
    this->singleName.assign(name.begin(), name.end());
    this->singleText.assign(text.begin(), text.end());
    max = 1;
    pointer = 0;
  };

  std::vector<std::string> getDialog(void) {
    if (this->singleText == " ") {
      output[0] = speakers[pointer];
      output[1] = texts[pointer];
      return output;

    } else {
      output[0] = singleName;
      output[1] = singleText;
      return output;
    }
  };

  void clearDialog() {
    if (this->singleText == " ") {
      if (pointer < max - 1) {
        pointer++;
      } else {
        speakers.clear();
        texts.clear();
        pointer = 0;
        max = 0;
      }
    } else {
      singleText = " ";
      singleName = " ";
      pointer = 0;
      max = 0;
    }
  };
  bool check(void) {
    if (max) {
      return true;
    } else {
      return false;
    }
  }

 private:
  int pointer, max;

  std::string singleText;
  std::string singleName;

  std::vector<std::string> speakers, texts;
  std::vector<std::string> output;
};

#endif
