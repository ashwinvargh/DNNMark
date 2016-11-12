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

#include "dnnmark.h"
#include "utility.h"
#include "dnn_config_keywords.h"

namespace dnnmark {

//
// Internal data type. Code courtesy of Caffe
//

float DataType<float>::oneval = 1.0;
float DataType<float>::zeroval = 0.0;
const void* DataType<float>::one =
    static_cast<void *>(&DataType<float>::oneval);
const void* DataType<float>::zero =
    static_cast<void *>(&DataType<float>::zeroval);
double DataType<double>::oneval = 1.0;
double DataType<double>::zeroval = 0.0;
const void* DataType<double>::one =
    static_cast<void *>(&DataType<double>::oneval);
const void* DataType<double>::zero =
    static_cast<void *>(&DataType<double>::zeroval);

//
// DNNMark class definition
//
template <typename T>
DNNMark<T>::DNNMark()
: run_mode_(NONE) {
  mem_manager_ = MemoryManager<T>::GetInstance();
}

template <typename T>
int DNNMark<T>::ParseAllConfig(const std::string &config_file) {
  // TODO: use multithread in the future
  // Parse DNNMark specific config
  ParseDNNMarkConfig(config_file);

  // Parse Data specific config
  ParseDataConfig(config_file);

  // Parse Convolution specific config
  ParseConvolutionConfig(config_file);

}

template <typename T>
int DNNMark<T>::ParseDNNMarkConfig(const std::string &config_file) {
  std::ifstream is;
  is.open(config_file.c_str(), std::ifstream::in);

  // TODO: insert assert regarding run_mode_

  // Parse DNNMark config
  std::string s;
  while (!is.eof()) {
    // Obtain the string in one line
    std::getline(is, s);
    TrimStr(&s);

    // Check the specific configuration section markers
    if (isDNNMarkSection(s) || isCommentStr(s))
      continue;
    else if (isSection(s))
      break;

    // Obtain the acutal variable and value
    std::string var;
    std::string val;
    SplitStr(s, &var, &val);
    TrimStr(&var);
    TrimStr(&val);

    // Process all the keywords in config
    if(isDNNMarkKeywordExist(var)) {
      if (!var.compare("run_mode")) {
        if (!val.compare("None"))
          run_mode_ = NONE;
        else if(!val.compare("Standalone"))
          run_mode_ = STANDALONE;
        else if(!val.compare("Composed"))
          run_mode_ = COMPOSED;
        else
          std::cerr << "Unknown run mode" << std::endl;
      }
    } else {
      std::cerr << "Keywords not exists" << std::endl;
      //TODO return error
    }
  }

  is.close();
  return 0;
}

template <typename T>
int DNNMark<T>::ParseDataConfig(const std::string &config_file) {
  std::ifstream is;
  is.open(config_file.c_str(), std::ifstream::in);

  // Parse DNNMark config
  std::string s;
  while (!is.eof()) {
    // Obtain the string in one line
    std::getline(is, s);
    TrimStr(&s);

    // Check the specific configuration section markers
    if (isCommentStr(s)){
      continue;
    } else if (isDataSection(s)) {
      // Create a layer in the main class
      int layer_id = num_layers_;
      layers_map[layer_id].emplace(std::make_shared(DataLayer<T>()));

    } else if (isSection(s)) {
      break;
    }

    // Obtain the acutal variable and value
    std::string var;
    std::string val;
    SplitStr(s, &var, &val);
    TrimStr(&var);
    TrimStr(&val);


    // Process all the keywords in config
    if(isDataKeywordExist(var)) {
      if (!var.compare("n")) {
        data_param_.n_ = atoi(val.c_str());
      } else if (!var.compare("c")) {
        data_param_.c_ = atoi(val.c_str());
      } else if (!var.compare("h")) {
        data_param_.h_ = atoi(val.c_str());
      } else if (!var.compare("w")) {
        data_param_.w_ = atoi(val.c_str());
      }
    } else {
      std::cerr << "Keywords not exists" << std::endl;
      //TODO return error
    }
  }

  is.close();
  return 0;
}

template <typename T>
int DNNMark<T>::ParseConvolutionConfig(const std::string &config_file) {
  std::ifstream is;
  is.open(config_file.c_str(), std::ifstream::in);

  // Parse Convolution config
  std::string s;
  while (!is.eof()) {
    // Obtain the string in one line
    std::getline(is, s);
    TrimStr(&s);

    // Check the specific configuration section markers
    if (isConvolutionSection(s) || isCommentStr(s))
      continue;
    else if (isSection(s))
      break;

    // Create a layer in the main class
    int layer_id = num_layers_;
    

    // Obtain the acutal variable and value
    std::string var;
    std::string val;
    SplitStr(s, &var, &val);
    TrimStr(&var);
    TrimStr(&val);

    // Process all the keywords in config
    if(isConvolutionKeywordExist(var)) {
      if (!var.compare("name")) {
        name_.assign(val);
      } else if (!var.compare("")) {
      } else if (!var.compare("")) {
      } else if (!var.compare("")) {
      } else if (!var.compare("")) {
      } else if (!var.compare("")) {
      } else if (!var.compare("")) {
      } else if (!var.compare("")) {
      } else if (!var.compare("")) {
      }
    } else {
      std::cerr << "Keywords not exists" << std::endl;
      //TODO return error
    }
  }

  is.close();
  return 0;
}

// Explicit instantiation
template class DNNMark<TestType>;

} // namespace dnnmark

