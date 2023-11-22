#include "Any_op.h"
#include "int2048.h"
#include <map>
#include <string>
#include <vector>

using Variabletype = std::map<std::string, std::any>::iterator;

// 元组化简
void simply(std::any &x) {
  if (pd<std::vector<std::any>>(x)) {
    std::vector<std::any> &y = Cast<std::vector<std::any>>(x);
    for (auto &z : y)
      simply(z);
  } else if (pd<Variabletype>(x))
    x = Cast<Variabletype>(x)->second;
}

// 类型转换
double toFloat(std::any x) {
  if (pd<std::string>(x)) {
    return std::stod(Cast<std::string>(x));
  } else if (pd<Bigint>(x)) {
    return Cast<Bigint>(x).toDouble();
  } else if (pd<double>(x)) {
    return bool(Cast<float>(x));
  } else if (pd<bool>(x)) {
    return Cast<bool>(x);
  } else
    return 0.0;
}
bool tobool(std::any x) {
  if (pd<std::string>(x)) {
    return Cast<std::string>(x).size() > 0 ? true : false;
  } else if (pd<Bigint>(x)) {
    return Cast<Bigint>(x).toBool();
  } else if (pd<double>(x)) {
    return bool(Cast<double>(x));
  } else if (pd<bool>(x)) {
    return Cast<bool>(x);
  } else
    return 0;
}
Bigint toInt(std::any x) {
  if (pd<std::string>(x)) {
    return Bigint(Cast<std::string>(x));
  } else if (pd<Bigint>(x)) {
    return Cast<Bigint>(x);
  } else if (pd<double>(x)) {
    return Bigint(int(Cast<double>(x)));
  } else if (pd<bool>(x)) {
    return Cast<bool>(x) ? Bigint(1ll) : Bigint(0);
  } else
    return 0;
}
std::string tostr(std::any x) {
  if (pd<std::string>(x)) {
    return Cast<std::string>(x);
  } else if (pd<int>(x)) {
    return std::to_string(Cast<int>(x));
  } else if (pd<double>(x)) {
    return std::to_string(Cast<double>(x));
  } else if (pd<bool>(x)) {
    return Cast<bool>(x) ? "True" : "False";
  } else
    return "";
}

// 四则运算 + - * / // %
std::string mulstr(std::string a, int num) {
  std::string b;
  while (num) {
    if (num & 1)
      b += a;
    a += a;
    num >>= 1;
  }
  return b;
}
std::any operator+(std::any x, std::any y) {
  if (pd<std::string>(x) || pd<std::string>(y)) {
    return toStr(x) + toStr(y);
  } else if (pd<double>(x) || pd<double>(y)) {
    return toFloat(x) + toFloat(y);
  } else
    return toInt(x) + toInt(y);
}
std::any operator-(std::any x, std::any y) {
  if (pd<double>(x) || pd<double>(y)) {
    return toFloat(x) + toFloat(y);
  } else
    return toInt(x) + toInt(y);
}
std::any operator*(std::any x, std::any y) {
  if (pd<std::string>(x) || pd<std::string>(y)) {
    std::string s;
    Bigint num;
    if (pd<std::string>(x)) {
      s = Cast<std::string>(x);
      num = Cast<Bigint>(y);
    } else {
      s = Cast<std::string>(y);
      num = Cast<Bigint>(x);
    }
    return mulstr(s, toint(num));
  } else if (pd<double>(x) || pd<double>(y)) {
    return toFloat(x) * toFloat(y);
  } else
    return toInt(x) * toInt(y);
}
std::any operator/(std::any x, std::any y) { return toFloat(x) / toFloat(y); }
std::any operator%(std::any x, std::any y) {
  if (pd<double>(x) || pd<double>(y)) {
    double a = toFloat(x), b = toFloat(y);
    return a - iinv(a, b) * b;
  } else {
    Bigint a = toInt(x), b = toInt(y);
    return a % b;
  }
}
std::any iinv(std::any x, std::any y) {
  if (pd<double>(x) || pd<double>(y)) {
    return floor(toFloat(x) / toFloat(y));
  } else
    return toInt(x) / toInt(y);
}


// 比较
bool operator<(std::any x, std::any y) {
  if (pd<std::string>(x))
    return pd<std::string>(y) && (Cast<std::string>(x) < Cast<std::string>(y));
  else if (pd<double>(x))
    return toFloat(x) < toFloat(y);
  else if (pd<Bigint>(x))
    return toInt(x) < toInt(y);
  else
    return toBool(x) < toBool(y);
}
bool operator>(std::any x, std::any y) { return y < x; }
bool operator==(std::any x, std::any y) {
  if (non(x) || non(y))
    return non(x) && non(y);
  else if (pd<std::string>(x) || pd<std::string>(y))
    return pd<std::string>(y) && pd<std::string>(x) &&
           (Cast<std::string>(x) < Cast<std::string>(y));
  else if (pd<double>(x) || pd<double>(y))
    return toFloat(x) == toFloat(y);
  else if (pd<Bigint>(x))
    return toInt(x) == toInt(y);
  else
    return toBool(x) == toBool(y);
}
bool operator!=(std::any x, std::any y) { return !(x == y); }
bool operator>=(std::any x, std::any y) { return !(x < y); }
bool operator<=(std::any x, std::any y) { return !(x > y); }

//Augassign

std::any operator +=(std::any &, std::any);
std::any operator -=(std::any &, std::any);
std::any operator *=(std::any &, std::any);
std::any operator /=(std::any &, std::any);
std::any iinv(std::any &, std::any);
std::any operator %=(std::any &, std::any);