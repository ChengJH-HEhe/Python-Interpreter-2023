#include "Evalvisitor.h"
#include "Any_op.h"
#include "mytype.h"
#include <variant>

// implementation
// TODO: override all methods of Python3ParserBaseVisitor

// 留住 新变量、函数 空间
std::any EvalVisitor::visitFile_input(Python3Parser::File_inputContext *ctx) {
  auto y = ctx->stmt();
  if (y.empty())
    return {};
  for (auto z : y) {
    visitStmt(z);
  }
  return {};
}
std::any EvalVisitor::visitFuncdef(Python3Parser::FuncdefContext *ctx) {
  std::string name = ctx->NAME()->getText();
  return {};
}

std::any
EvalVisitor::visitCompound_stmt(Python3Parser::Compound_stmtContext *ctx) {
  if (ctx->if_stmt())
    visitIf_stmt(ctx->if_stmt());
  else if (ctx->while_stmt())
    visitWhile_stmt(ctx->while_stmt());
  else if (ctx->funcdef())
    visitFuncdef(ctx->funcdef());
}

std::any EvalVisitor::visitSmall_stmt(Python3Parser::Small_stmtContext *ctx) {
  if (ctx->expr_stmt()) {
    return visitExpr_stmt(ctx->expr_stmt());
  } else
    return visitFlow_stmt(ctx->flow_stmt());
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

std::any EvalVisitor::visitAugassign(Python3Parser::AugassignContext *ctx) {
  if (ctx->ADD_ASSIGN()) {
  }
}

std::any EvalVisitor::visitFlow_stmt(Python3Parser::Flow_stmtContext *ctx) {
  if (ctx->break_stmt())
    return FLOWSTMT::BREAK;
  else if (ctx->continue_stmt())
    return FLOWSTMT::CONTINUE;
  else if (ctx->return_stmt())
    return visitReturn_stmt(ctx->return_stmt());
  return {};
}

std::any EvalVisitor::visitReturn_stmt(Python3Parser::Return_stmtContext *ctx) {
  if (ctx->testlist())
    return visitTestlist(ctx->testlist());
  else
    return FLOWSTMT::RETURN;
}

std::any EvalVisitor::visitIf_stmt(Python3Parser::If_stmtContext *ctx) {
  //
  if (!ctx->IF())
    return {};
  auto y = ctx->test();
  int sz = y.size(), i = 0;
  --sz;
  for (; i < sz; ++i) {
    std::any &&z = visitTest(y[i]);
    simply(z);
    if (toBool(z))
      return visitSuite(ctx->suite(i));
  }
  if (ctx->suite(i))
    return visitSuite(ctx->suite(i));
  return {};
}

std::any EvalVisitor::visitWhile_stmt(Python3Parser::While_stmtContext *ctx) {
  //
  if (!ctx->WHILE())
    return {};
  while (true) {
    auto y = ctx->test();
    std::any &&z = visitTest(y);
    simply(z);
    if (toBool(z)) {
      auto &&tmp = visitSuite(ctx->suite());
      if (non(tmp))
        continue;
      if (pd<FLOWSTMT>(tmp)) {
        auto z = Cast<FLOWSTMT>(tmp);
        if (z == FLOWSTMT::BREAK)
          break;
        else if (z == FLOWSTMT::CONTINUE)
          continue;
        else if (z == FLOWSTMT::RETURN)
          return tmp;
      }
    } else
      break;
  }
  return {};
}

std::any EvalVisitor::visitSuite(Python3Parser::SuiteContext *ctx) {
  if (ctx->simple_stmt()) {
    auto &&tmp = visitSimple_stmt(ctx->simple_stmt());
    if (pd<FLOWSTMT>(tmp))
      return tmp;
  } else {
    auto tmp = ctx->stmt();
    if (tmp.empty())
      return {};
    for (int i = 0; i < tmp.size(); ++i) {
      auto &&temp = visitStmt(tmp[i]);
      if (pd<FLOWSTMT>(tmp))
        return tmp;
    }
  }
  return {};
}

std::any EvalVisitor::visitTest(Python3Parser::TestContext *ctx) {
  return visitOr_test(ctx->or_test());
}

std::any EvalVisitor::visitOr_test(Python3Parser::Or_testContext *ctx) {
  //
  if (!ctx->OR(0))
    return visitChildren(ctx);
  auto tmp = ctx->and_test();
  for (auto temp : tmp) {
    auto &&var = visitAnd_test(temp);
    if (toBool(var))
      return true;
  }
  return false;
}

std::any EvalVisitor::visitAnd_test(Python3Parser::And_testContext *ctx) {
  //
  if (!ctx->AND(0))
    return visitChildren(ctx); //` ``  ``  `   `
  auto tmp = ctx->not_test();
  if (tmp.empty())
    return true;
  for (auto y : tmp) {
    auto &&z = visitNot_test(y);
    simply(z);
    if (!toBool(z))
      return false;
  }
  return true;
}

std::any EvalVisitor::visitNot_test(Python3Parser::Not_testContext *ctx) {
  if (!ctx->NOT())
    return visitComparison(ctx->comparison());
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
      return x = y != xx;
    else if (cmp->GT_EQ())
      return x = y >= xx;
    else if (cmp->LT_EQ())
      return x = y <= xx;
    else if (cmp->LESS_THAN())
      return x = y < xx;
    else if (cmp->GREATER_THAN())
      return x = y > xx;
    else
      visitChildren(ctx);
  }
}


std::any EvalVisitor::visitArith_expr(Python3Parser::Arith_exprContext *ctx) {}

std::any EvalVisitor::visitAddorsub_op(Python3Parser::Addorsub_opContext *ctx) {

}

std::any EvalVisitor::visitTerm(Python3Parser::TermContext *ctx) {}

std::any
EvalVisitor::visitMuldivmod_op(Python3Parser::Muldivmod_opContext *ctx) {}

std::any EvalVisitor::visitFactor(Python3Parser::FactorContext *ctx) {}

std::any EvalVisitor::visitAtom_expr(Python3Parser::Atom_exprContext *ctx) {}

std::any EvalVisitor::visitTrailer(Python3Parser::TrailerContext *ctx) {}

std::any EvalVisitor::visitAtom(Python3Parser::AtomContext *ctx) {}

std::any EvalVisitor::visitTestlist(Python3Parser::TestlistContext *ctx) {}

std::any EvalVisitor::visitArglist(Python3Parser::ArglistContext *ctx) {}

std::any EvalVisitor::visitArgument(Python3Parser::ArgumentContext *ctx) {}