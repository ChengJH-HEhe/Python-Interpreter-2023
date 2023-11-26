#include"mytype.h"
#include"Any_op.h"

flow::flow(FLOWSTMT a, std::any b ) {
  word = a;
  auto &c = Cast<std::vector<std::any>>(b);
  for (auto &d : c)
    simply(d);
  // 万一是个vector 析构了（也不会寄）；加快速度
  if (c.size() == 1)
    an = std::move(c[0]);
  else
    an = std::move(c);
}