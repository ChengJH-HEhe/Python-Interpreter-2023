#pragma once
#ifndef ANY_OP
#define ANY_OP

#include "int2048.h"
#include <any>
#include <string>

using Bigint = sjtu::int2048;

enum FLOWSTMT { BREAK, CONTINUE, RETURN };

template <typename T> T &Cast(std::any &);

// 判断类型
template <typename T> bool pd(std::any const &);

template <typename T> T const &Cast(std::any const &);

bool non(std::any);

// 解析变量
void simply(std::any &);

class flow {
public:
  FLOWSTMT word;
  std::any an;
  flow(FLOWSTMT, std::any);
};

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
std::any &operator*=(std::any &, std::any);
std::any &operator/=(std::any &, std::any);
std::any &iDiv(std::any &, std::any);
std::any &operator%=(std::any &, std::any);
std::ostream &operator<<(std::ostream &, std::any);
//-
std::any setNega(std::any);

#endif