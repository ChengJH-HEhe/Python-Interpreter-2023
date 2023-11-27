#include "Evalvisitor.h"

#include "Any_op.h"
#include "funcvar.h"
#include "mytype.h"
#include <any>
#include <cstdio>
#include <map>
#include <utility>
#include <variant>

// implementation
// TODO: override all methods of Python3ParserBaseVisitor

Scope scope;
function f;
// 留住 新变量、函数 空间
std::any EvalVisitor::visitFile_input(Python3Parser::File_inputContext *ctx) {
  scope.init();
  auto y = ctx->stmt();
  if (y.empty())
    return {};
  for (auto z : y) {
    visitStmt(z);
  }
  return {};
}
//- Stands for: **t**yped **f**unction **p**arameter **def**inition
std::any EvalVisitor::visitTfpdef(Python3Parser::TfpdefContext *ctx) {
  return ctx->getText();
}
// TODO
std::any EvalVisitor::visitFuncdef(Python3Parser::FuncdefContext *ctx) {
  std::string name = ctx->NAME()->getText();
  f.create(name, ctx);
  // evalvisitor 遍历树的函数指针
  // ctx 存树上节点的子信息
  return {};
}

std::any
EvalVisitor::visitCompound_stmt(Python3Parser::Compound_stmtContext *ctx) {
  if (ctx->if_stmt()) {
    auto &&v = visitIf_stmt(ctx->if_stmt());
    if (pd<flow>(v))
      return v;
  } else if (ctx->while_stmt()) {
    auto &&v = visitWhile_stmt(ctx->while_stmt());
    if (pd<flow>(v))
      return v;
    else {return {};}
  } else if (ctx->funcdef()) {
    visitFuncdef(ctx->funcdef());
    return {};
  }
    
  return {};
}

std::any EvalVisitor::visitSmall_stmt(Python3Parser::Small_stmtContext *ctx) {
  
  if (ctx->expr_stmt()) {
    return visitExpr_stmt(ctx->expr_stmt());
  } else if(ctx->flow_stmt()) {
    return visitFlow_stmt(ctx->flow_stmt());
  }
  else return {};
}
std::any EvalVisitor::visitSimple_stmt(Python3Parser::Simple_stmtContext *ctx) {
  
  return visitSmall_stmt(ctx->small_stmt());
}
std::any EvalVisitor::visitStmt(Python3Parser::StmtContext *ctx) {
  if (ctx->simple_stmt()) {
    return visitSimple_stmt(ctx->simple_stmt());
  } else if (ctx->compound_stmt()) {
    return visitCompound_stmt(ctx->compound_stmt());
  } else
    return {};
}

std::any EvalVisitor::visitFlow_stmt(Python3Parser::Flow_stmtContext *ctx) {

  if (ctx->break_stmt())
    return flow(FLOWSTMT::BREAK, {});
  else if (ctx->continue_stmt())
    return flow(FLOWSTMT::CONTINUE, {});
  else if (ctx->return_stmt()){
    return visitReturn_stmt(ctx->return_stmt());
  }
  return {};
}

std::any EvalVisitor::visitReturn_stmt(Python3Parser::Return_stmtContext *ctx) {
  if (ctx->testlist()) {
    
    return flow(FLOWSTMT::RETURN, std::move(visitTestlist(ctx->testlist())));
  }
  else {
    //std::cerr<<ctx->depth()<<std::endl;
    return flow(FLOWSTMT::RETURN, std::vector<std::any>());
  }
}

std::any EvalVisitor::visitIf_stmt(Python3Parser::If_stmtContext *ctx) {
  //
  if (!ctx->IF())
    return {};
  auto y = ctx->test();
  auto zz = ctx->suite();
  int sz = y.size(), i = 0;
  for (; i < sz; ++i) {
    std::any &&z = visitTest(y[i]);
    if (toBool(z))
      return visitSuite(zz[i]);
  }
  if (ctx->suite(i))
    return visitSuite(zz[i]);
  return {};
}

std::any EvalVisitor::visitWhile_stmt(Python3Parser::While_stmtContext *ctx) {
  //
  if (!ctx->WHILE())
    return {};
  int cnt = 0;
  while (true) {
    auto y = ctx->test();
    std::any &&z = visitTest(y);
    
    if (toBool(z)) {
      auto &&tmp = visitSuite(ctx->suite());
      if (non(tmp)|| (pd<std::vector<std::any>>(tmp) && Cast<std::vector<std::any>>(tmp).empty()))
        continue;
      if (pd<flow>(tmp)) {
        auto z = Cast<flow>(tmp);
        if (z.word == FLOWSTMT::BREAK)
          break;
        else if (z.word == FLOWSTMT::CONTINUE)
          continue;
        else if (z.word == FLOWSTMT::RETURN)
          return tmp;
      }
    } else
      break;
  }
  return {};
}

std::any EvalVisitor::visitSuite(Python3Parser::SuiteContext *ctx) {
  
  if (auto test = ctx->simple_stmt()) {
    auto &&tmp = visitSimple_stmt(test);
    if (pd<flow>(tmp))
      return tmp;
  } else {
    auto tmp = ctx->stmt();
    if (tmp.empty())
      return {};
    for (int i = 0; i < tmp.size(); ++i) {
      auto &&temp = visitStmt(tmp[i]);
      if (pd<flow>(temp))
        return Cast<flow>(temp);
    }
  }
  return {};
}

std::any EvalVisitor::visitTest(Python3Parser::TestContext *ctx) {
  
  if(!ctx->or_test()){
    return visitChildren(ctx);
  }
  else{
    return visitOr_test(ctx->or_test());
  }  
  // ctx->or_test()->and_test()->assign();
}

std::any EvalVisitor::visitOr_test(Python3Parser::Or_testContext *ctx) {
  //
  if (!ctx->OR(0)){
    return visitChildren(ctx);
  }
  //std::cerr<<ctx->depth()<<std::endl;
  auto tmp = ctx->and_test();
  for (auto temp : tmp) {
    auto &&var = visitAnd_test(temp);
    if (toBool(var))
      return true;
  }
  return false;
}

std::any EvalVisitor::visitAnd_test(Python3Parser::And_testContext *ctx) {
  
  if (!ctx->AND(0)) {
    return visitChildren(ctx); //
  }
  auto tmp = ctx->not_test();
  if (tmp.empty())
    return true;
  for (auto y : tmp) {
    auto &&z = visitNot_test(y);
    if (!toBool(z))
      return false;
  }
  return true;
}

std::any EvalVisitor::visitNot_test(Python3Parser::Not_testContext *ctx) {
  if (!ctx->NOT()) {
    
    return visitComparison(ctx->comparison());
  }
  else {
    auto &&tmp = visitNot_test(ctx->not_test());
    simply(tmp);
    return !toBool(tmp);
  }
}

std::any EvalVisitor::visitComparison(Python3Parser::ComparisonContext *ctx) {
  if (ctx->comp_op().empty())
    return visitChildren(ctx);
  auto x = ctx->arith_expr();
  auto z = ctx->comp_op();
  auto &&y = visitArith_expr(x[0]);
  simply(y);
  // 使得返回的值能够直接使用
  if ((int)x.size() == 1)
    return y;
  for (int i = 1; i < (int)x.size(); ++i) {
    auto xx = visitArith_expr(x[i]);
    simply(xx);
    auto &cmp = z[i - 1];
    bool x = true;
    if (cmp->EQUALS())
      x = y == xx;
    else if (cmp->NOT_EQ_2())
      x = y != xx;
    else if (cmp->GT_EQ())
      x = y >= xx;
    else if (cmp->LT_EQ())
      x = y <= xx;
    else if (cmp->LESS_THAN())
      x = y < xx;
    else if (cmp->GREATER_THAN())
      x = y > xx;
    if (!x)
      return false;
    y = std::move(xx);
  }
  return true;
}

std::any EvalVisitor::visitArith_expr(Python3Parser::Arith_exprContext *ctx) {
  // term (addorsubop term)
  auto y = ctx->term();
  auto &&tmp = visitTerm(ctx->term(0));
  if (y.size() <= 1)
    return tmp;
  simply(tmp);
  auto z = ctx->addorsub_op();
  for (int i = 1; i < y.size(); ++i) {
    auto &&temp = visitTerm(y[i]);
    simply(temp);
    if (z[i - 1]->ADD())
      tmp += temp;
    else if (z[i - 1]->MINUS())
      tmp -= temp;
  }
  return tmp;
}

std::any EvalVisitor::visitTerm(Python3Parser::TermContext *ctx) {
  // factor (muldivmod_op factor)
  auto y = ctx->factor();
  if (y.empty())
    return {};
  auto &&res = visitFactor(y[0]);
  auto z = ctx->muldivmod_op();
  if (y.size() <= 1)
    return res;
  simply(res);
  for (int i = 1; i < y.size(); ++i) {
    auto &&temp = visitFactor(y[i]);
    simply(temp);
    auto op = z[i - 1];
    if (op->DIV())
      res /= temp;
    else if (op->IDIV())
      iDiv(res, temp);
    else if (op->MOD())
      res %= temp;
    else if (op->STAR())
      res *= temp;
  }
  return res;
}

std::any EvalVisitor::visitFactor(Python3Parser::FactorContext *ctx) {
  //'+' '-'
  if (ctx->factor()) {
    auto &&rvalue = visitFactor(ctx->factor());
    simply(rvalue);
    if (ctx->MINUS())
      return setNega(rvalue);
    else
      return rvalue;
  } else if (ctx->atom_expr())
    return visitAtom_expr(ctx->atom_expr());
  return {};
}

// TODO/done

std::any EvalVisitor::visitExpr_stmt(Python3Parser::Expr_stmtContext *ctx) {
  if (!ctx->ASSIGN(0) && !ctx->augassign())
    return visitChildren(ctx);
  //std::cerr<<"Expr_stmt"<<std::endl;
  auto var = ctx->testlist();
  char tp = '=';
  if (ctx->augassign()) {
    auto op = ctx->augassign();
    if (op->ADD_ASSIGN())
      tp = '+';
    else if (op->DIV_ASSIGN())
      tp = '/';
    else if (op->IDIV_ASSIGN())
      tp = 'i';
    else if (op->MOD_ASSIGN())
      tp = '%';
    else if (op->MULT_ASSIGN())
      tp = '*';
    else if (op->SUB_ASSIGN())
      tp = '-';
    
        std::vector<std::any> x =
        Cast<std::vector<std::any>>(visitTestlist(var[0]));
    std::vector<std::any> y =
        Cast<std::vector<std::any>>(visitTestlist(var[1]));
    for (auto &z : y)
      simply(z);
    int sz = std::min(x.size(), y.size());
    for (int i = 0; i < sz; ++i) {
      if (!pd<std::pair<std::string, int>>(x[i]))
        continue;
      scope.change(Cast<std::pair<std::string, int>>(x[i]), y[i], tp);
    }
  } else {
    auto rhs = Cast<std::vector<std::any>>(visitTestlist(var.back()));
    for (auto &_rhs : rhs)
      simply(_rhs);//std::cerr<<"rhs"<<_rhs;
    static int cd = var.size() - 1;
    // std::cerr<<"Expr_stmt"<<" "<<cd<<std::endl;
    for (int i = 0; i < cd; ++i) {
      //std::cerr<<233;
      auto lhs = Cast<std::vector<std::any>>(visitTestlist(var[i]));
      static int range = std::min(lhs.size(), rhs.size());
      for (int j = 0; j < range; ++j) {
        if (!pd<std::pair<std::string, int>>(lhs[j])){
          continue;
        }
        scope.change(Cast<std::pair<std::string, int>>(lhs[j]), rhs[j], '=');
      }
    }
  }

  return {};
}

// TODO/ done
std::any EvalVisitor::visitAtom_expr(Python3Parser::Atom_exprContext *ctx) {
  auto &&v = visitAtom(ctx->atom());
  if (ctx->trailer()) {
    auto arglist = ctx->trailer()->arglist();
    std::string tmp;
    //std::cerr<<233;
    if(pd<std::pair<std::string, int>>(v))
      tmp = Cast<std::pair<std::string, int>>(v).first;
    else
      tmp = Cast<std::string>(v);
    if(!arglist && (tmp == "print" || tmp == "int" || tmp == "bool" || tmp == "float" || tmp == "str")){
      return {};
    }
    std::vector<Python3Parser::ArgumentContext *> argument;
    if(arglist) argument = arglist->argument();
    // 变量返回pair<std::string,int>
    
      std::vector<std::any> realArgument;
      for (auto i : argument)
        realArgument.emplace_back(visitArgument(i));
      // std::cerr << "Atom_expr" << realArgument.back() << " ";
      //  Specifically builtin_func tpdir
      int tp = 0;
      if (tmp == "int")
        return toInt(realArgument[0]);
      else if (tmp == "bool")
        return toBool(realArgument[0]);
      else if (tmp == "float")
        return toFloat(realArgument[0]);
      else if (tmp == "str")
        return toStr(realArgument[0]);
      else if(tmp == "print") {
        func_print(realArgument);
        return {};
      }else {
        auto tmp1 = f.func(tmp, arglist);
        //f.func(std::string, Python3Parser::ArglistContext *)
        return tmp1;
      }
      //std::cerr<<ctx->getText();
  } else
    return v;
}

// TODO NAME /done
std::any EvalVisitor::visitAtom(Python3Parser::AtomContext *ctx) {
  if (ctx->FALSE())
    return false;
  else if (ctx->TRUE())
    return true;
  else if (ctx->test())
    return visitTest(ctx->test());
  else if (ctx->NONE())
    return {};
  else if (ctx->NAME()) {
    // 是变量
    auto x = ctx->NAME()->getText();
    if (x == "int" || x == "bool" || x == "float" || x == "str" ||
        x == "print") {
      return x;
    } else {
      return make_pair(x, scope.find(x));
    }
  } else if (ctx->NUMBER()) {
    // double \ int2048
    auto y = ctx->getText();
    if (y.find('.') == std::string::npos)
      return toInt(y);
    else
      return std::stod(y);
  } else {
    // string+
    auto x = ctx->STRING();
    std::string s;
    int length = 0;
    for (auto y : x) {
      std::string tmp = y->getText();
      int sz = tmp.size();
      //std::cerr<<sz<<std::endl;
      s += tmp.substr(1, sz - 2);
    }
    return std::move(s);
  }
}

std::any EvalVisitor::visitTestlist(Python3Parser::TestlistContext *ctx) {
  // visitTest -> visitAtom 给出 新变量name ， 允许name = val
  auto x = ctx->test();
  if (x.empty())
    return std::vector<std::any>();
  else {
    std::vector<std::any> a;
    for (int i = 0; i < x.size(); ++i) {
      auto &&var2 = visitTest(x[i]);
      a.emplace_back(var2);
    }
    return a;
  }
}

std::any EvalVisitor::visitArgument(Python3Parser::ArgumentContext *ctx) {
  if (ctx->test(1)) {
    auto &&var2 = visitTest(ctx->test(1));
    // move 否则无法写入make_pair的参数
    // pair 返回<函数名 , 现在的赋值>
    return std::make_pair<std::string, std::any>(ctx->test(0)->getText(),
                                                 std::move(var2));
  } else {
    // 返回一个值 已知变量需要解析为值
    auto &&var = visitTest(ctx->test(0));
     //std::cerr << "Argument" << var << std::endl;
    if (pd<std::pair<std::string, int>>(var))
      return scope.getval(Cast<std::pair<std::string, int>>(var));
    else
      return var;
  }
}