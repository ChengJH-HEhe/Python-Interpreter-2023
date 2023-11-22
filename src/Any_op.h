#pragma once
#ifndef ANY_OP
#define ANY_OP

#include<any>
#include<string>
#include "int2048.h"

using Bigint = sjtu::int2048;

//判断类型
template<typename T>
bool pd(std::any const &x) {
    return std::any_cast<T>(&x);
}

template<typename T> 
T& Cast(std::any &x) {
    return std::any_cast<T &>(x);
}
template<typename T> 
T const &Cast(std::any const &x) {
    return std::any_cast<T const &>(x);
}

//加入inline ?
inline bool non(std::any x) {
    return !x.has_value();
}
//元组化简
void simply(std::any&);

//基本类型
// int float str

//类型转换
bool toBool(std::any);
int toint(std::any);
Bigint toInt(std::any);
std::string toStr(std::any);
double toFloat(std::any);

//+ - * / // = 
std::any operator + (std::any,std::any);
std::any operator - (std::any,std::any);
std::any operator * (std::any,std::any);
std::string mulstr (std::string, Bigint);
std::any operator / (std::any,std::any);
std::any operator % (std::any,std::any);
std::any iinv (std::any ,std::any);


// > < = <= >= !=
bool operator < (std::any, std::any);
bool operator > (std::any, std::any);
bool operator == (std::any, std::any);
bool operator != (std::any, std::any);
bool operator >= (std::any, std::any);
bool operator <= (std::any, std::any);

//augassign
std::any operator +=(std::any &, std::any);
std::any operator -=(std::any &, std::any);
std::any operator *=(std::any &, std::any);
std::any operator /=(std::any &, std::any);
std::any iinv(std::any &, std::any);
std::any operator %=(std::any &, std::any);
#endif