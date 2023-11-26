#pragma once
#ifndef ANY_OP
#define ANY_OP

#include "int2048.h"
#include <any>
#include <string>

using Bigint = sjtu::int2048;


template <typename T> bool pd(std::any const &x) {
  return std::any_cast<T>(&x);
}

template <typename T> T &Cast(std::any &x) { return std::any_cast<T &>(x); }
template <typename T> T const &Cast(std::any const &x) {
  return std::any_cast<T const &>(x);
}
bool non(std::any);

// 解析变量
void simply(std::any &);



// 基本类型
//  int float str

// 类型转换
bool toBool(std::any);
int toint(std::any);
Bigint toInt(std::any);
std::string toStr(std::any);
double toFloat(std::any);

//+ - * / // =
std::any operator+(std::any, std::any);
std::any operator-(std::any, std::any);
std::any operator*(std::any, std::any);
std::string mulstr(std::string, int);
std::any operator/(std::any, std::any);
std::any operator%(std::any, std::any);
std::any idiv(std::any, std::any);

// > < = <= >= !=
bool operator<(std::any, std::any);
bool operator>(std::any, std::any);
bool operator==(std::any, std::any);
bool operator!=(std::any, std::any);
bool operator>=(std::any, std::any);
bool operator<=(std::any, std::any);

// augassign
std::any &operator+=(std::any &, const std::any &);
std::any &operator-=(std::any &, const std::any &);
std::any &operator*=(std::any &, const std::any &);
std::any &operator/=(std::any &, const std::any &);
std::any &iDiv(std::any &, const std::any &);
std::any &operator%=(std::any &, const std::any&);
std::ostream &operator<<(std::ostream &, std::any);
//-
std::any setNega(std::any);

#endif