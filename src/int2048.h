#pragma once
#ifndef SJTU_BIGINTEGER
#define SJTU_BIGINTEGER

// Integer 1:
// 实现一个有符号的大整数类，只需支持简单的加减

// Integer 2:
// 实现一个有符号的大整数类，支持加减乘除，并重载相关运算符

// 请不要使用除了以下头文件之外的其它头文件
#include <complex>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <string>
#include <vector>

// 请不要使用 using namespace std;

namespace sjtu {
class int2048 {
  // todo
private:
  int f = 0;
  std::vector<int> v;

public:
  static constexpr int base = 10;
  // 构造函数
  int2048();
  int2048(long long);
  int2048(const std::string &);
  int2048(const int2048 &);
  bool toBool()  { return v.size() > 0; }
  double toDouble()  { return std::stod(this->toString()); }
  std::string toString()  {
    if (!v.size())
      return "0";
    std::string s;
    if (f == -1)
      s = "-";
    for (auto x = v.rbegin(); x != v.rend(); ++x)
      s += std::to_string(*x);
    return s;
  }
  __int128 to__int() {
    __int128 s = 0;
    if (!v.size())
      return s;
    for (auto x = v.rbegin(); x != v.rend(); ++x)
      s = s * 10 + *x;
    return s * f;
  }
  int toInt()  {
    if (!v.size())
      return 0;
    int s = 0;
    for (auto x = v.rbegin(); x != v.rend(); ++x)
      s = s * 10 + *x;
    return s * f;
  }
  friend int2048 getInv(int2048 &);
  void normalize();
  // 无符号
  int2048 &uadd(const int2048);
  int2048 &uminus(const int2048);
  // 以下给定函数的形式参数类型仅供参考，可自行选择使用常量引用或者不使用引用
  // 如果需要，可以自行增加其他所需的函数
  // ===================================
  // Integer1
  // ===================================

  // 读入一个大整数
  void read(const std::string &);
  // 输出储存的大整数，无需换行
  void print() const;

  // 加上一个大整数
  int2048 &add(const int2048 &);

  // 返回两个大整数之和
  friend int2048 add(int2048, const int2048 &);

  // 减去一个大整数
  int2048 &minus(const int2048 &);
  // 返回两个大整数之差
  friend int2048 minus(int2048, const int2048 &);

  // ===================================
  // Integer2
  // ===================================
  friend int cmp(std::vector<int>, std::vector<int>);

  int2048 operator+() const;
  int2048 operator-() const;

  int2048 &operator=(const int2048 &);

  int2048 &operator+=(const int2048 &);
  friend int2048 operator+(int2048, const int2048 &);

  int2048 &operator-=(const int2048 &);
  friend int2048 operator-(int2048, const int2048 &);

  int2048 &operator*=(const int2048 &);
  friend int2048 operator*(int2048, const int2048 &);

  int2048 &operator/=(const int2048 &);
  friend int2048 operator/(int2048, const int2048 &);

  int2048 &operator%=(const int2048 &);
  friend int2048 operator%(int2048, const int2048 &);

  int2048 &operator<<=(int);
  int2048 &operator>>=(int);

  friend std::istream &operator>>(std::istream &, int2048 &);
  friend std::ostream &operator<<(std::ostream &, const int2048 &);

  friend bool operator==(const int2048 &, const int2048 &);
  friend bool operator!=(const int2048 &, const int2048 &);
  friend bool operator<(const int2048 &, const int2048 &);
  friend bool operator>(const int2048 &, const int2048 &);
  friend bool operator<=(const int2048 &, const int2048 &);
  friend bool operator>=(const int2048 &, const int2048 &);
};
} // namespace sjtu


#endif