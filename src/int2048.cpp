#include "int2048.h"
#include "Any_op.h"

namespace fft {
bool on;
using comp = std::complex<double>;
const double pi = std::acos(-1);
const int base = 10;
void fft(std::vector<comp> &y, int len, int on) {
  std::vector<int> r;
  r.resize(len);
  for (int i = 0; i < len; ++i) {
    r[i] = r[i >> 1] >> 1;
    if (i & 1)
      r[i] |= len >> 1;
  }
  for (int i = 0; i < len; ++i)
    if (i < r[i])
      swap(y[i], y[r[i]]);
  for (int h = 2; h <= len; h <<= 1) {
    comp wn(cos(2 * pi / h), sin(on * 2 * pi / h));
    for (int j = 0; j < len; j += h) {
      comp w(1, 0);
      for (int k = j; k < j + h / 2; ++k) {
        comp u = y[k], v = w * y[k + h / 2];
        y[k] = u + v, y[k + h / 2] = u - v;
        w = w * wn;
      }
    }
  }
}
void mul(std::vector<int> &a, std::vector<int> b) {

  std::vector<comp> x1, x2;
  int n = a.size(), m = b.size();
  int len = 1, t = std::max(n, m);
  while (len < (t << 1))
    len <<= 1;
  for (int i = 0; i < n; ++i)
    x1.push_back(comp(a[i], 0));
  x1.resize(len);
  for (int i = 0; i < m; ++i)
    x2.push_back(comp(b[i], 0));
  x2.resize(len);
  fft(x1, len, 1), fft(x2, len, 1);
  for (int i = 0; i < len; ++i)
    x1[i] = x1[i] * x2[i];
  fft(x1, len, -1);
  a.resize(len);
  int tmp = 0;
  for (int i = 0; i < len; ++i) {
    a[i] = (int)(x1[i].real() / len + 0.49) + tmp;
    tmp = a[i] / base;
    a[i] %= base;
  }
  if (on)
    a.resize(n + m - 1);
  else {
    while (len && !a[len - 1])
      --len;
    a.resize(len);
  }
}
} // namespace fft

namespace sjtu {
void int2048::normalize() {
  while (v.size() && !*v.rbegin())
    v.pop_back();
  if (v.empty()) {
    f = 1;
    return;
  }
  while (*v.rbegin() >= base) {
    v.push_back(*v.rbegin() / base);
    *v.rbegin() %= base;
  }
  while (v.size() && !*v.rbegin())
    v.pop_back();
  if (v.empty())
    f = 1;
}
int2048::int2048() {
  f = 1;
  v.clear();
}
int2048::int2048(long long x) {
  f = 1;
  v.clear();
  if (x) {
    if (x < 0) {
      f = -1;
      x = -x;
    }
    while (x) {
      v.push_back(x % base);
      x /= base;
    }
  }
}
int2048::int2048(const std::string &c) {
  int va = 0, sz = c.size();
  f = 1;
  v.clear();
  for (int i = sz - 1; i >= 0; i--) {
    if (c[i] == '-')
      f = -1;
    else
      v.push_back(c[i] - '0');
  }
  while (v.size() && !*v.rbegin())
    v.pop_back();
  if (v.empty())
    f = 1;
}
int2048::int2048(const int2048 &b) { f = b.f, v = b.v; }

int2048 &int2048::uadd(const int2048 a) {
  if (a.v.empty()) {
    return *this;
  }
  int sz = v.size(), sza = a.v.size(), tmp = 0;
  if (sz < sza)
    v.resize(sza), sz = sza;

  for (int i = 0; i < sz - 1; ++i) {
    (i < sza) && (v[i] += a.v[i]);
    v[i] += tmp;
    tmp = v[i] / base;
    v[i] %= base;
  }
  int pos = sz - 1;
  (sz - 1 < sza) && (v[sz - 1] += a.v[sz - 1]);
  v[sz - 1] += tmp;
  while (v[pos] >= base) {
    v.push_back(v[pos] / base);
    v[pos] %= base;
    ++pos;
  }
  this->normalize();
  return *this;
}

int2048 &int2048::uminus(const int2048 a) {
  if (a.v.empty()) {
    return *this;
  }
  int sz = v.size(), sza = a.v.size();
  for (int i = 0; i < sz; ++i) {
    (i < sza) && (v[i] -= a.v[i]);
    if (v[i] < 0) {
      v[i] += base;
      v[i + 1]--;
    }
  }
  while (!*v.rbegin())
    v.pop_back();
  return *this;
}
// 以下给定函数的形式参数类型仅供参考，可自行选择使用常量引用或者不使用引用
// 如果需要，可以自行增加其他所需的函数
// ===================================
// Integer1
// ===================================
// 读入一个大整数
void int2048::read(const std::string &b) {
  int2048 tmp = int2048(b);
  f = tmp.f, v = tmp.v;
}
// 输出储存的大整数，无需换行
void int2048::print() const {

  if (v.empty()) {
    std::cout << '0';
    return;
  }

  if (f == -1)
    std::cout << '-';
  std::cout << *(--v.end());
  if (v.size() == 1)
    return;
  for (auto it = --(--v.end());; --it) {
    std::cout << *it;
    if (it == v.begin())
      return;
  }
}

int cmp(std::vector<int> a, std::vector<int> b) {
  int sza = a.size(), szb = b.size();
  if (sza != szb) {
    return (sza < szb) ? -1 : 1;
  }
  for (int i = sza - 1; ~i; --i)
    if (a[i] != b[i])
      return (a[i] < b[i]) ? -1 : 1;
  return 0;
}
// 加上一个大整数

int2048 &int2048::add(const int2048 &a) {
  // 符号不同，变减法，大的减小的符号是大的， *this换成大的，
  if (f != a.f) {
    int pd = cmp(v, a.v);
    if (!pd) {
      f = 1;
      v.resize(0);
      return *this;
    }
    if (pd == -1) {
      int2048 c(*this);
      v = a.v, f = a.f;
      (*this).uminus(c);
    } else {
      (*this).uminus(a);
    }
  } else {
    (*this).uadd(a);
  }
  return *this;
}
// 返回两个大整数之和
int2048 add(int2048 a, const int2048 &b) { return a.add(b); }

// 减去一个大整数
int2048 &int2048::minus(const int2048 &a) {
  if (a.v.empty()) {
    return *this;
  }
  if (f == a.f) {
    int pd = cmp(v, a.v);
    if (!pd) {
      f = 1;
      v.resize(0);
      // wei
      return *this;
    }
    if (pd == -1) {
      // wei
      int2048 c(*this);
      v = a.v, f = -f;
      (*this).uminus(c);
    } else {
      // you
      int2048 c(*this);
      (*this).uminus(a);
    }
  } else {
    (*this).uadd(a);
  }
  this->normalize();
  return *this;
}
// 返回两个大整数之差
int2048 minus(int2048 a, const int2048 &b) { return a.minus(b); }

// 重载运算符

int2048 int2048::operator+() const {
  int2048 c(*this);
  return c;
}
int2048 int2048::operator-() const {
  int2048 c(*this);
  c.f = -c.f;
  return c;
}

int2048 &int2048::operator=(const int2048 &b) {
  f = b.f;
  v = b.v;
  return *this;
}

int2048 &int2048::operator+=(const int2048 &b) { return this->add(b); }
int2048 operator+(int2048 a, const int2048 &b) {
  a += b;
  return a;
}

int2048 &int2048::operator-=(const int2048 &b) { return this->minus(b); }
int2048 operator-(int2048 a, const int2048 &b) {
  a -= b;
  return a;
}

int2048 &int2048::operator*=(const int2048 &b) {
  if (b.v.empty()) {
    v.resize(0), f = 1;
    return *this;
  }
  fft::mul(v, b.v);
  this->f *= b.f;
  this->normalize();
  return *this;
}
int2048 operator*(int2048 a, const int2048 &b) {
  a *= b;
  return a;
}

void reverse(std::vector<int> &a) {
  int sum = a.size() - 1;
  for (int i = 0; i <= sum - i; ++i) {
    std::swap(a[i], a[sum - i]);
  }
}

int2048 &int2048::operator<<=(int a) {
  reverse(v);
  int sz = int(v.size()) + a;
  v.resize(sz);
  reverse(v);
  return *this;
}
int2048 &int2048::operator>>=(int a) {
  reverse(v);
  int sz = int(v.size()) - a;
  v.resize(sz);
  reverse(v);
  return *this;
}

void division(int2048 &a, int2048 b) {
  std::vector<int2048> quot, indx;
  int2048 tmp(b), idx(1), ans(0);
  while (tmp <= a) {
    quot.push_back(tmp);
    indx.push_back(idx);
    tmp += tmp, idx += idx;
  }
  int pos = quot.size() - 1;
  tmp = 0;
  for (int i = pos; ~i; --i) {
    if (quot[i] <= a)
      tmp += indx[i], a -= quot[i];
    if (a == 0)
      break;
  }
  a = tmp;
}
int2048 getInv(int2048 &a) {
  int m = a.v.size();
  if (m < 80) {
    // brute
    int2048 c(int2048(1) <<= 2 * m);
    division(c, a);
    return c;
  }
  int k = (m + 5) >> 1;
  int2048 b(a);
  b >>= (m - k);
  int2048 z = getInv(b);
  int2048 c = ((2 * z) <<= (m - k)) - ((a * z * z) >>= 2 * k) - 1;
  int2048 rem = (int2048(1) <<= 2 * m) - c * a;
  if (rem >= a)
    c += 1;
  return c;
}
int2048 &int2048::operator/=(const int2048 &b1) {
  // a *1/b  1/(1/b)-b = 0 (b') = 2b' - b b'^2;
  int2048 b = b1;
  int f1 = f * b.f;
  f = b.f = 1;
  if (f1 == -1) {
    int2048 c;
    c.v = v;
    c += int2048((b - 1));
    this->v = c.v;
  }

  int sz1 = v.size(), sz2 = b.v.size();
  if (sz1 < sz2) {
    v.resize(0);
    f = 1;
    return *this;
  }
  if(sz1 < 38) {
    // int2048转__int128 
    __int128 lvalue = to__int(), rvalue = b.to__int();
    lvalue /=rvalue;
    v.clear();
    while(lvalue) v.push_back(lvalue%10), lvalue/=10;
    f = f1;
    return *this;
  }
  int2048 x(*this), y(b);
  if (sz1 > sz2 * 2) {
    int mb = sz1 - 2 * sz2;
    x <<= mb, y <<= mb;
    sz2 += mb, sz1 += mb;
  }
  int2048 z = getInv(y);
  // 微调
  z *= x;
  z >>= 2 * sz2;
  x = z * b;
  if ((*this - x >= b))
    z += 1;
  *this = z;
  f = f1;
  return *this;
}
int2048 operator/(int2048 a, const int2048 &b) { return a /= b; }

int2048 &int2048::operator%=(const int2048 &b) {
  int2048 c(*this - (*this / b) * b);
  *this = c;
  return *this;
}
int2048 operator%(int2048 a, const int2048 &b) { return a %= b; }

std::istream &operator>>(std::istream &in, int2048 &b) {
  std::string s;
  in >> s;
  b = int2048(s);
  return in;
}
std::ostream &operator<<(std::ostream &out, const int2048 &b) {
  if (b.v.empty()) {
    out << '0';
  } else {
    if (b.f == -1)
      out << '-';
    for (auto it = b.v.rbegin(); it != b.v.rend(); ++it)
      out << *it;
  }
  return out;
}

bool operator<(const int2048 &a, const int2048 &b) {
  if (a.f != b.f) {
    return a.f < b.f;
  } else {
    return (cmp(a.v, b.v) * a.f == -1) ? 1 : 0;
  }
}
bool operator==(const int2048 &a, const int2048 &b) {
  if (a.v.empty() && b.v.empty())
    return true;
  if (a.f != b.f || a.v.size() != b.v.size())
    return false;
  return (cmp(a.v, b.v) == 0) ? 1 : 0;
}
bool operator!=(const int2048 &a, const int2048 &b) { return !(a == b); }
bool operator>(const int2048 &a, const int2048 &b) {
  if (a.f != b.f) {
    return a.f > b.f;
  } else {
    return (cmp(a.v, b.v) * a.f == 1) ? 1 : 0;
  }
}
bool operator<=(const int2048 &a, const int2048 &b) {
  return (a < b || a == b);
}
bool operator>=(const int2048 &a, const int2048 &b) {
  return (a > b || a == b);
}

} // namespace sjtu