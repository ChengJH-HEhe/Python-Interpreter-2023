#pragma once
#ifndef funcvar_h
#define funcvar_h

#include "Evalvisitor.h"
#include <any>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

// vector<Data> (*forEachMethod) (const LinkedHashMap&);
// 函数指针的写法 和声明一样，只是*后面就是函数指针名，参数列表

// 记录他在哪一层空间，然后只保存在Mp中，不用修改两次
struct Scope {
  std::vector<std::unordered_map<std::string, std::any>> mp;
  int find(std::string);
  void init();
  void change(std::pair<std::string, int>, std::any &, char);
  std::any getval(std::pair<std::string, int>);
};

struct function {
  std::string NAME;
  std::any func(std::string, std::vector<std::any>);
  void create(std::string, Python3Parser::FuncdefContext *);
};
void func_print(std::vector<std::any>);
#endif