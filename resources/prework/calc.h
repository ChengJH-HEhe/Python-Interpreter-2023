// 你需要提交这份代码
#pragma once
#include<iostream>
#include "visitor.h"
#include <any>

struct calculator : visitor {
    /// TODO: 完成所有需求
    std::any visit_num(num_node *ctx) override { 
        return ctx->number; 
    }
    std::any visit_add(add_node *ctx) override {
        visitor *calc = new calculator;
        auto lv = calc->visit(ctx->lnode);
        auto rv = calc->visit(ctx->rnode);
        if(auto lvalue = std::any_cast <double> (&lv)){
            if(auto rvalue = std::any_cast <double> (&rv))
                return *lvalue + *rvalue;
            else return nullptr;
        } else {
            if(auto lvalue = std::any_cast <long long> (&lv)) {
                if(auto rvalue = std::any_cast <long long> (&rv))
                    return *lvalue + *rvalue;
                else return nullptr;
            } else return nullptr;
        }
    }
    std::any visit_sub(sub_node *ctx) override {
        visitor *calc = new calculator;
        auto lv = calc->visit(ctx->lnode);
        auto rv = calc->visit(ctx->rnode);
        if(auto lvalue = std::any_cast <double> (&lv)){
            if(auto rvalue = std::any_cast <double> (&rv))
                return *lvalue - *rvalue;
            else return nullptr;
        } else {
            if(auto lvalue = std::any_cast <long long> (&lv)) {
                if(auto rvalue = std::any_cast <long long> (&rv))
                    return *lvalue - *rvalue;
                else return nullptr;
            } else return nullptr;
        }
    }
    std::any visit_mul(mul_node *ctx) override {
        visitor *calc = new calculator;
        auto lv = calc->visit(ctx->lnode);
        auto rv = calc->visit(ctx->rnode);
        if(auto lvalue = std::any_cast <double> (&lv)){
            if(auto rvalue = std::any_cast <double> (&rv))
                return *lvalue * *rvalue;
            else return nullptr;
        } else {
            if(auto lvalue = std::any_cast <long long> (&lv)) {
                if(auto rvalue = std::any_cast <long long> (&rv))
                    return *lvalue * *rvalue;
                else return nullptr;
            } else return nullptr;
        }
    }
    std::any visit_div(div_node *ctx) override {
        visitor *calc = new calculator;
        auto lv = calc->visit(ctx->lnode);
        auto rv = calc->visit(ctx->rnode);
        if(auto lvalue = std::any_cast <double> (&lv)){
            if(auto rvalue = std::any_cast <double> (&rv))
                return *lvalue / *rvalue;
            else return nullptr;
        } else {
            if(auto lvalue = std::any_cast <long long> (&lv)) {
                if(auto rvalue = std::any_cast <long long> (&rv))
                    return *lvalue / *rvalue;
                else return nullptr;
            } else return nullptr;
        }
    }
    ~calculator() override = default;
};

//if (auto value = std::any_cast <double> (&ctx->lnode))
//std::any visit_num(num_node *ctx) override { return ctx->number; }