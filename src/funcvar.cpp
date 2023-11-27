#include "funcvar.h"
#include "Any_op.h"
#include "Evalvisitor.h"
#include "mytype.h"
#include <memory>
#include <unordered_map>
#include <vector>
extern Scope scope;

// 没有必要，新建函数空间与新建变量空间是同步的
//  std::vector<std::unordered_map<std::string,
//                                 std::shared_ptr<Python3Parser::FuncdefContext>>>
//      fc;

EvalVisitor eva; // 存一个函数指针
void Scope::init() {
  std::unordered_map<std::string, std::any> nw;
  mp.push_back(std::move(nw));
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

funcptr Scope::find_func(std::string x) {
  if (mp[0].find(x) != mp[0].end()){
    //std::cerr<<2333;
    auto tmp = Cast<funcptr>(mp[0][x]);
    //std::cerr<<2333;
    return tmp;
  }
  else return nullptr;
}
void Scope::change(std::pair<std::string, int> a, std::any b, char c) {
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
void function::create(std::string str, funcptr ctx) {
  // arglist
  scope.mp[0][str] = ctx;
  auto x = scope.find_func(str);
  auto list = ctx->parameters()->typedargslist();
  // 特判
  std::vector<std::string> v;
  std::unordered_map<std::string, std::any> mpFunc;
  static std::unordered_map<funcptr, std::unordered_map<std::string, std::any>>
      Def;
  static std::unordered_map<funcptr, std::vector<std::string>> varName;
  if (list) {
    auto All = list->tfpdef();   // 未设初值
    auto Default = list->test(); // 已设初值
    static int n = All.size(), m = Default.size();
    // 为变量申请空间
    for (int i = 0; i < n - m; ++i) {
      v.push_back(All[i]->getText());
      mpFunc[All[i]->getText()] = {};
    }
    for (int i = 0; i < m; ++i) {
      auto val = eva.visit(Default[i]);
      simply(val);
      mpFunc[All[i + n - m]->getText()] = val;
      v.push_back(All[i + n - m]->getText());
    }
    // ctx mpFUNC
  }
  Def[ctx] = mpFunc;
  varName[ctx] = v;
}

std::any function::func(std::string str, Python3Parser::ArglistContext* Arg) {
  // 新建变量空间，初始化函数定义
  static std::unordered_map<funcptr, std::unordered_map<std::string, std::any>>
      Def;
  static std::unordered_map<funcptr, std::vector<std::string>> varName;
  auto x = scope.find_func(str);
  //std::cerr<<Arg->depth()<<" ";
  scope.mp.push_back(Def[x]);
  std::vector<std::string> vec = varName[x]; // 每个参数名称
  if (Arg) {
    //std::cerr<<"Arg";
    auto arglist = Arg->argument();
    static int szArg = arglist.size(),
               szFunc = vec.size(); // sz 为 调用时 的 长度
    for (int i = 0; i < szArg; ++i) {
      // vec[i] = arglist[i]
      int pos = scope.find(vec[i]);
      auto node = arglist[i]->test();
      auto node0 = eva.visit(node[0]);
      if (node.size() == 1) {
        simply(node0);
        scope.change(make_pair(vec[i], pos), node0, '=');
      } else {
        // name  pair<string,int> 右getval
        auto newval = eva.visit(node[1]);
        simply(newval);
        std::pair<std::string, int> lvalue =
            Cast<std::pair<std::string, int>>(node0);
        lvalue.second = scope.find(lvalue.first);
        scope.change(lvalue, newval, '=');
      }
    }
    for(int i = szArg; i < szFunc; ++i) {
      int pos = scope.find(vec[i]);
      scope.change(make_pair(vec[i], scope.mp.size()-1),scope.mp[pos][vec[i]],'=');
    }
  }
  auto &&tmp = eva.visit(x->suite());

    // 先化简后清空
  std::any retVal;
  if (pd<flow>(tmp)) {
    std::any finalResult = Cast<flow>(tmp).an;
    if (non(finalResult)||(pd<std::vector<std::any>>(finalResult)&&(Cast<std::vector<std::any>>(finalResult).empty())))
      retVal = {};
    else if (pd<std::pair<std::string, int>>(finalResult)) {
      // 变量
      std::string s = Cast<std::pair<std::string, int>>(finalResult).first;
      return scope.mp[scope.find(s)][s];
    } else // if(pd<std::vector<std::any>>(finalResult.an))
      return finalResult;
  } else
    retVal = {};
  scope.mp.back().clear();
  scope.mp.pop_back();
  // 化简结果
  return retVal;
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
