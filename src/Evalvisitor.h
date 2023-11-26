#pragma once
#ifndef PYTHON_INTERPRETER_EVALVISITOR_H
#define PYTHON_INTERPRETER_EVALVISITOR_H

// definition

#include "../generated/Python3ParserBaseVisitor.h"

class EvalVisitor : public Python3ParserBaseVisitor {

virtual std::any visitFile_input(Python3Parser::File_inputContext *) override;

virtual std::any visitFuncdef(Python3Parser::FuncdefContext *) override;

virtual std::any visitParameters(Python3Parser::ParametersContext *) override;

virtual std::any visitTypedargslist(Python3Parser::TypedargslistContext *) override;

virtual std::any visitTfpdef(Python3Parser::TfpdefContext *) override;

virtual std::any visitStmt(Python3Parser::StmtContext *) override;

virtual std::any visitSimple_stmt(Python3Parser::Simple_stmtContext *) override;

virtual std::any visitSmall_stmt(Python3Parser::Small_stmtContext *) override;

virtual std::any visitExpr_stmt(Python3Parser::Expr_stmtContext *) override;

virtual std::any visitAugassign(Python3Parser::AugassignContext *) override;

virtual std::any visitFlow_stmt(Python3Parser::Flow_stmtContext *) override;

// virtual std::any visitBreak_stmt(Python3Parser::Break_stmtContext *) override;

// virtual std::any visitContinue_stmt(Python3Parser::Continue_stmtContext *) override;

virtual std::any visitReturn_stmt(Python3Parser::Return_stmtContext *) override;

virtual std::any visitCompound_stmt(Python3Parser::Compound_stmtContext *) override;

virtual std::any visitIf_stmt(Python3Parser::If_stmtContext *) override;

virtual std::any visitWhile_stmt(Python3Parser::While_stmtContext *) override;

virtual std::any visitSuite(Python3Parser::SuiteContext *) override;

virtual std::any visitTest(Python3Parser::TestContext *) override;

virtual std::any visitOr_test(Python3Parser::Or_testContext *) override;

virtual std::any visitAnd_test(Python3Parser::And_testContext *) override;

virtual std::any visitNot_test(Python3Parser::Not_testContext *) override;

virtual std::any visitComparison(Python3Parser::ComparisonContext *) override;

virtual std::any visitComp_op(Python3Parser::Comp_opContext *) override;

virtual std::any visitArith_expr(Python3Parser::Arith_exprContext *) override;

//virtual std::any visitAddorsub_op(Python3Parser::Addorsub_opContext *) override;

virtual std::any visitTerm(Python3Parser::TermContext *) override;

//virtual std::any visitMuldivmod_op(Python3Parser::Muldivmod_opContext *) override;

virtual std::any visitFactor(Python3Parser::FactorContext *) override;

virtual std::any visitAtom_expr(Python3Parser::Atom_exprContext *) override;

virtual std::any visitTrailer(Python3Parser::TrailerContext *) override;

virtual std::any visitAtom(Python3Parser::AtomContext *) override;

virtual std::any visitTestlist(Python3Parser::TestlistContext *) override;

//virtual std::any visitArglist(Python3Parser::ArglistContext *) override;

virtual std::any visitArgument(Python3Parser::ArgumentContext *) override;

};
#endif//PYTHON_INTERPRETER_EVALVISITOR_H
