#include "funcvar.h"
#include "Any_op.h"
#include "Evalvisitor.h"
#include <memory>
#include <unordered_map>
extern Scope scope;
std::vector<std::unordered_map<std::string,
                               std::shared_ptr<Python3Parser::FuncdefContext>>>
    fc;
EvalVisitor eva; // 存一个函数指针
void Scope::init() {
  std::unordered_map<std::string, std::any> nw;
  mp.push_back(nw);
}
int Scope::find(std::string x) {
  // 插入操作
  if (mp.back().find(x) != mp.back().end())
    return int(mp.size()) - 1; // std::cerr<<233,
  else if (mp[0].find(x) != mp[0].end())
    return 0;
  else
    return mp.back()[x] = {}, int(mp.size()) - 1;
  // iterator?
}
void Scope::change(std::pair<std::string, int> a, std::any &b, char c) {
  int pos = a.second;
  if (c == '=')
    mp[pos][a.first] = b;
  else if (c == '+')
    mp[pos][a.first] += b;
  else if (c == '-')
    mp[pos][a.first] -= b;
  else if (c == '*')
    mp[pos][a.first] *= b;
  else if (c == '/')
    mp[pos][a.first] /= b;
  else if (c == 'i')
    iDiv(mp[pos][a.first], b);
  else if (c == '%')
    mp[pos][a.first] %= b;
}
std::any Scope::getval(std::pair<std::string, int> a) {
  return mp[a.second][a.first];
}

// 放克！
void function::create(std::string str, Python3Parser::FuncdefContext *ctx) {
  // fc.back()[str] = std::make_shared<Python3Parser::FuncdefContext>(*ctx);
}

void func_print(std::vector<std::any> x) {
  if (x.empty())
    return;
  if (x.size() != 1)
    for (int i = 0; i < x.size() - 1; ++i) {
      // pair<std::string, std::any> \ 一个值
      std::cout << x[i] << " ";
    }
  std::cout << x.back() << std::endl;
}
// 在全局新建五个内置函数
