// The MIT License (MIT)
// 
// Copyright (c) 2016 Northeastern University
// 
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
// 
// The above copyright notice and this permission notice shall be included in 
// all copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#include <algorithm>
#include "dnn_config_keywords.h"

namespace dnnmark {

bool isSection(std::string &s) {
  return std::find(section_keywords.begin(),
                   section_keywords.end(), s)
         != section_keywords.end();
}

bool isDNNMarkSection(std::string &s) {
  return s.compare("[DNNMark]") == 0;
}

bool isDNNMarkKeywordExist(std::string &s) {
  return std::find(dnnmark_config_keywords.begin(),
                   dnnmark_config_keywords.end(), s)
         != data_config_keywords.end();
}

bool isDataSection(std::string &s) {
  return s.compare("[Data]") == 0;
}

bool isDataKeywordExist(std::string &s) {
  return std::find(data_config_keywords.begin(),
                   data_config_keywords.end(), s)
         != data_config_keywords.end();
}

bool isConvSection(std::string &s) {
  return s.compare("[Convolution]") == 0;
}

bool isConvKeywordExist(std::string &s) {
  return std::find(conv_config_keywords.begin(),
                   conv_config_keywords.end(), s)
         != conv_config_keywords.end();
}


}


