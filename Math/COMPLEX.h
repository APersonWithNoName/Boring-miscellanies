/*
 *COMPLEX.h
 *一个看起来没什么用的头文件
 *定义了几个宏，常用的数学常量，以及几乎没用的几个函数，
 *不过在写数学方面可能有点用
 **/
#pragma once

#include<complex>
#include<math.h>
#include<iostream>

#define CLD std::complex<long double>
#define CD std::complex<double>
#define CI std::complex<int>
#define CF std::complex<float>

const std::complex<long double> PI (3.1415926, 0);
const std::complex<long double> E (2.71828, 0);
const std::complex<long double> Omega (-1 / 2, sqrt(3) / 2);
const std::complex<long double> Omega2 (-1 / 2, -sqrt(3) / 2);
/*
std::complex<long double> Re(Cstd::complex<long double> c) 
	return real(c);
}
std::complex<long double> Im(std::complex<long double> c) {
	return imag(c);
}
*/
void Printout(std::complex<long double> c)
{
	if (c.imag() > 0)
		  std::cout << c.real() << "+" << c.imag() << "i";
  else if (c.imag() < 0)
		  std::cout << c.real() << "-" << -(c.imag()) << "i";
  else if (c.imag() == 0)
		  std::cout << c.real() << "+0i";
  else
    ;
}
