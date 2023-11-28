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
  //    3
  //a b c
  scope.mp[0][str] = ctx;
}
int cnt;

// func 调用出现问题
// 单参数赋值 done
// 函数套函数 值与test?
/*
miller rabin 传参出错
定义： miller_rabin(x,n)
list = 2
ALL x, n
default 空
调用： miller_rabin(i,x)
Arg i = 2 
default x = 2
*/
std::any function::func(std::string str,  std::vector<Python3Parser::ArgumentContext *> argument) {
  // 新建变量空间，初始化函数定义
  auto ctx = scope.find_func(str);
  auto list = ctx->parameters()->typedargslist();

  std::vector<std::string> vec;// all the variable names
  std::vector<std::any> realArgument;

  //把初值先算出来。
  if(argument.size()) {
    // a = 5 或 std::any
    // 1,1,4,5,1,4, arg , 5
    //                    b
    int szArg = argument.size(); 
    for(int i = 0; i < szArg; ++i)
      realArgument.push_back(eva.visit(argument[i]));
  }
  std::unordered_map<std::string, std::any> mpFunc;// corresponding values r
  scope.mp.push_back(std::move(mpFunc));
  if (list) {
    auto All = list->tfpdef();   // 未设初值
    auto Default = list->test(); // 已设初值 arith_expr
    int n = All.size(), m = Default.size();
    //为变量申请空间
    for (int i = 0; i < n - m; ++i) {
      vec.push_back(All[i]->getText());
      scope.mp.back()[vec.back()] = {};
    }
    for (int i = 0; i < m; ++i) {
      vec.push_back(All[i + n - m]->NAME()->getText());
      scope.mp.back()[vec.back()] = eva.visit(Default[i]);
    }
    // ctx mpFUNC
  }
  
  if (argument.size()) {
     // 已经给的值
    int szFunc = vec.size(), szArg = realArgument.size();     // sz 为调用时的总长度
    int nowpos = scope.mp.size() - 1;//目前层
    for (int i = 0; i < szArg; ++i) {
      auto &&res = realArgument[i];
      if(pd<std::pair<std::string, std::any>>(res)) {
        auto pr = Cast<std::pair<std::string, std::any>>(res);
        scope.change(make_pair(pr.first, nowpos), pr.second, '=');// c = 5
      } else {
        scope.change(make_pair(vec[i], nowpos), res, '='); // 1
      }
    }
  }

  auto &&tmp = eva.visit(ctx->suite());
  //std::cout<<Cast<flow>(tmp).an;
    // 先化简后清空
  std::any retVal;
  if (pd<flow>(tmp)) {
    std::any finalResult = Cast<flow>(tmp).an;
    if (non(finalResult)||(pd<std::vector<std::any>>(finalResult)
      &&(Cast<std::vector<std::any>>(finalResult).empty())))
      retVal = {};
    else if (pd<std::pair<std::string, int>>(finalResult)) {
      // 变量
      std::string s = Cast<std::pair<std::string, int>>(finalResult).first;
      retVal = scope.mp[scope.find(s)][s];
    } else // if(pd<std::vector<std::any>>(finalResult.an))
      retVal = finalResult;
  } else
    retVal = {};
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
  if(!x.empty())std::cout << x.back();
  std::cout << std::endl;
}
// 在全局新建五个内置函数
