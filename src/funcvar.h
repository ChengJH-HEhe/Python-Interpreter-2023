#pragma once
#ifndef funcvar_h
#define funcvar_h

#include "Evalvisitor.h"
using funcptr = Python3Parser::FuncdefContext*;
// vector<Data> (*forEachMethod) (const LinkedHashMap&);
// 函数指针的写法 和声明一样，只是*后面就是函数指针名，参数列表

// 记录他在哪一层空间，然后只保存在Mp中，不用修改两次
struct Scope {
  std::vector<std::unordered_map<std::string, std::any>> mp;
  int find(std::string);
  funcptr find_func(std::string);
  void init();
  void change(std::pair<std::string, int>, std::any, char);
  std::any getval(std::pair<std::string, int>);
};
extern Scope scope;

struct function {
  std::string NAME;
  std::unordered_map<funcptr, std::unordered_map<std::string, std::any>> Def;
  std::unordered_map<funcptr, std::vector<std::string>> varName;
  std::any func(std::string, Python3Parser::ArglistContext*);
  void create(std::string, funcptr);
};
void func_print(std::vector<std::any>);
#endif