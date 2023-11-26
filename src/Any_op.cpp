#include "Any_op.h"
#include "funcvar.h"
#include "int2048.h"
#include <iomanip>
#include <map>
#include <string>
#include <vector>

// 未连接上 头文件，
extern Scope scope;
// scope 类似一个栈，0指向全局空间，back指向当前空间

// TODO 元组化简
// 由于在新建变量时，如果是声明变量，返回值是Pair
// 加入inline ?
bool non(std::any x) { return !x.has_value(); }

void simply(std::any &x) {
  if (pd<std::vector<std::any>>(x)) {
    std::vector<std::any> &y = Cast<std::vector<std::any>>(x);
    for (auto &z : y)
      simply(z);
  } else if (pd<std::pair<std::string, int>>(x)) {
    auto tmp = Cast<std::pair<std::string, int>>(x);
    x = scope.mp[tmp.second][tmp.first];
  }
}
// 类型转换
double toFloat(std::any x) {
  if (pd<std::string>(x)) {
    return std::stod(Cast<std::string>(x));
  } else if (pd<Bigint>(x)) {
    return Cast<Bigint>(x).toDouble();
  } else if (pd<double>(x)) {
    return (Cast<float>(x));
  } else if (pd<bool>(x)) {
    return Cast<bool>(x) ? 1.0 : 0.0;
  } else
    return 0.0;
}
bool toBool(std::any x) {
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
int toint(std::any x) { return Cast<Bigint>(x).toInt(); }
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
std::string toStr(std::any x) {
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
    return a - idiv(a, b) * b;
  } else {
    Bigint a = toInt(x), b = toInt(y);
    return a % b;
  }
}
std::any idiv(std::any x, std::any y) {
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
bool operator<=(std::any x, std::any y) { return !(y < x); }

// Augassign

std::any &operator+=(std::any &a, std::any const &b) {
  if (pd<Bigint>(a) && pd<Bigint>(b)) {
    Cast<Bigint>(a) += Cast<Bigint>(b);
    return a;
  }
  return a = a + b;
}
std::any &operator-=(std::any &a, std::any const &b) {
  if (pd<Bigint>(a) && pd<Bigint>(b)) {
    Cast<Bigint>(a) -= Cast<Bigint>(b);
    return a;
  }
  return a = a - b;
}
std::any &operator*=(std::any &a, std::any const &b) {
  if (pd<Bigint>(a) && pd<Bigint>(b)) {
    Cast<Bigint>(a) *= Cast<Bigint>(b);
    return a;
  }
  return a = a * b;
}
std::any &operator/=(std::any &a, std::any const &b) { return a = a / b; }
std::any &iDiv(std::any &a, std::any const &b) { return a = idiv(a, b); }
std::any &operator%=(std::any &a, std::any const &b) {
  if (pd<Bigint>(a) && pd<Bigint>(b)) {
    Cast<Bigint>(a) %= Cast<Bigint>(b);
    return a;
  }
  return a = a % b;
}

std::ostream &operator<<(std::ostream &os, std::any now) {
  std::any tmp;
  if (pd<std::pair<std::string, std::any>>(now))
    tmp = Cast<std::pair<std::string, std::any>>(now).second;
  else
    tmp = now;
  if (pd<std::vector<std::any>>(now)) {
    std::vector<std::any> &list = Cast<std::vector<std::any>>(now);
    os << list[0];
    for (int i = 1; list[i] != list.end(); ++i)
      os << " " << list[i];
  } else if (pd<std::string>(now)) {
    std::string s = Cast<std::string>(now);
    os << s;
  } else if (pd<double>(now)) {
    os << std::fixed << std::setprecision(6) << Cast<double>(now);
  } else if (pd<Bigint>(now)) {
    os << Cast<Bigint>(now);
  } else if (pd<bool>(now)) {
    os << (Cast<bool>(now) ? "True" : "False");
  } else if (non(now))
    os << "None";
  return os;
}
std::any setNega(std::any a) {
  if(pd<std::vector<std::any>>(a)) {
     std::vector<std::any> tmp, tmp1 = Cast<std::vector<std::any>>(a);
     for(auto y : tmp1) 
      tmp.emplace_back(setNega(y));
    return tmp;
  } else {
    if(pd<Bigint>(a)) return -Cast<Bigint>(a);
    else if(pd<double>(a)) return -Cast<double>(a);
    else return -toInt(a);
  }
}