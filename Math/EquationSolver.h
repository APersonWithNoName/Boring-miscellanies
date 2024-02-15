#pragma once

#include<vector>
#include"COMPLEX.h"

// 方程中的特殊变量
	// for function"CubicEqSolver"
static CLD data_m(CLD c1, CLD c2, CLD u, CLD v) {
    CLD _m;
    if (abs(c1) >= abs(c2)) {
          CLD _m = pow((u + v), 1 / 3);          
    }
    else {
          CLD _m = pow((u - v), 1 / 3);
    }
    return _m;
}
  // for function"CubicEqSolver"
static CLD data_n(CLD m, CLD a, CLD b, CLD c) {
	  CLD _m;
    if (abs(m) != 0){
	  	CLD _n = (pow(b, 2) - CLD(3, 0) * a * c) / (CLD(9, 0) * pow(a, 2) * m);
	    return _n;
    }
	  else {
		  CLD _n = 0;
      return _n;
	  }
}

// 有求根公式的方程
// 变量名后的数字为第n次顶的系数
  //一次(线性)方程
std::vector<CLD> LinearEquationSolver(CLD data1, CLD data0) {
    std::vector<CLD>result;
    result.push_back(-(data0 / data1));
    return result;
}
  //二次方程
std::vector<CLD> QuadraticEquationSolver(CLD data2, CLD data1, CLD data0) {
    std::vector<CLD>result;
    CLD discriminant;
		discriminant = sqrt(pow(data1, 2) - CLD(4, 0) * data2 * data0);
		CLD casualdata1 = -(data1 / (CLD(2, 0) * data2));
		CLD casualdata2 = discriminant / (CLD(2, 0) * data2);
    result.push_back(casualdata1 + casualdata2);
    result.push_back(casualdata1 - casualdata2);
    return result;
}
std::vector<CLD> CubicEquationSolver(CLD data3, CLD data2, CLD data1, CLD data0) {
    std::vector<CLD>result;
    CLD u = (CLD(9, 0) * data3 * data2 * data1 -                      \
				 CLD(27, 0) * pow(data3, 2) * data0 -                     \
				 CLD(2, 0) * pow(data2, 3)) / (CLD(54, 0) * pow(data3, 2)
				);
		CLD v = (sqrt(                                                    \
				      CLD(3, 0) * (CLD(4, 0) * data3 * pow(data1, 3) -    \
				      pow((data2 * data1), 2) -                           \
				      CLD(18, 0) * data3 * data2 * data1 * data0 +        \
				      CLD(27, 0) * pow(data3 * data0, 2) +                \
				        CLD(4, 0) * pow(data2, 2) * data0)                \
		             )                                                    \
			    );
		CLD casualdata1 = u + v;
		CLD casualdata2 = u - v;
		CLD m = data_m(casualdata1, casualdata2, u, v);
		CLD n = data_n(m, data3, data2, data1);
    result.push_back(m + n - data2 / (CLD(3, 0) * data3));
    result.push_back(Omega * m + Omega2 * n - data2 / (CLD(3, 0) * data3));
    result.push_back(Omega2 * m + Omega * n - data2 / (CLD(3, 0) * data3));
    return result;
}
std::vector<CLD> QuarticEquationSolver(CLD data4, CLD data3, CLD data2, CLD data1, CLD data0) {
    std::vector<CLD>result;
    CLD _data3 = data3 / data4;
	  CLD _data2 = data2 / data4;
	  CLD _data1 = data1 / data4;
	  CLD _data0 = data0 / data4;
	  std::vector<CLD> casual1_vector ( CubicEquationSolver(
      CLD(8,0),                                                      \
      CLD(4,0) * _data2,                                             \
      CLD(8,0) * _data0 - CLD(2,0) * _data3 * _data1,                \
      _data0 * (_data3 * _data3 - CLD(4,0) * _data2) - _data1 * _data1       \
       ));
    CLD y = casual1_vector[0];
    CLD M = sqrt(CLD(8, 0) * y +                                     \
		  pow(_data3, 2) -                                               \
		  CLD(4, 0) * _data2
	  );
	  CLD N = _data3 * y - _data1;
    std::vector<CLD> casual2_vector = (QuadraticEquationSolver(
      CLD(2,0),                                                     \
      _data3 + M,                                                   \
      CLD(2,0) * (y + N/M)                                         \
       ));
    std::vector<CLD> casual3_vector = (QuadraticEquationSolver(
      CLD(2,0),                                                     \
      _data3 - M,                                                   \
      CLD(2,0) * (y + N/M)                                         \
      ));
    result.push_back(casual2_vector[0]);
    result.push_back(casual2_vector[1]);
    result.push_back(casual3_vector[0]);
    result.push_back(casual2_vector[1]);
    return result;
}
