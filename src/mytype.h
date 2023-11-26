#pragma once
#ifndef mytype
#define mytype 
#include <vector>
#include <any>

enum class FLOWSTMT { BREAK, CONTINUE, RETURN };
struct flow {
  FLOWSTMT word;
  std::any an;
  flow(FLOWSTMT, std::any);
};

//类型名！

#endif