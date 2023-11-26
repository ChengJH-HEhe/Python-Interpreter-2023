#pragma once
#ifndef ANY_OP
#define ANY_OP

#include<any>
#include<string>
#include "int2048.h"

using Bigint = sjtu::int2048;

//判断类型
template<typename T>
bool pd(std::any const &x);

template<typename T> 
T& Cast(std::any &x);

template<typename T> 
T const &Cast(std::any const &);

//加入inline ?
bool non(std::any);

//元组化简
template<typename T>
void simply(T&);

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
std::any idiv (std::any ,std::any);


// > < = <= >= !=
bool operator < (std::any, std::any);
bool operator > (std::any, std::any);
bool operator == (std::any, std::any);
bool operator != (std::any, std::any);
bool operator >= (std::any, std::any);
bool operator <= (std::any, std::any);

//augassign
std::any& operator +=(std::any &, const std::any &);
std::any& operator -=(std::any &, const std::any &);
std::any& operator *=(std::any &, std::any );
std::any& operator /=(std::any &, std::any );
std::any& iDiv(std::any &, std::any);
std::any& operator %=(std::any &, std::any );
std::ostream& operator<<(std::ostream&, std::any);
//-
std::any setNega(std::any);

#endif