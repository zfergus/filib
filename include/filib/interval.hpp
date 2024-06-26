/*********************************************************************/
/*                                                                   */
/*   fi_lib  --- A fast interval library (Version 1.2)               */
/*                                                                   */
/*  Authors:                                                         */
/*  --------                                                         */
/*  Werner Hofschuster, Walter Kraemer                               */
/*  Wissenschaftliches Rechnen/Softwaretechnologie                   */
/*  Universitaet Wuppertal, Germany                                  */
/*                                                                   */
/*  Copyright:                                                       */
/*  ----------                                                       */
/*  Copyright (C) 1997-2000 Institut fuer Wissenschaftliches Rechnen */
/*                          und Mathematische Modellbildung (IWRMM)  */
/*                                           and                     */
/*                          Institut fuer Angewandte Mathematik      */
/*                          Universitaet Karlsruhe, Germany          */
/*            (C) 2000-2005 Wiss. Rechnen/Softwaretechnologie        */
/*                          Universitaet Wuppertal, Germany          */
/*                                                                   */
/*  This library is free software; you can redistribute it and/or    */
/*  modify it under the terms of the GNU Library General Public      */
/*  License as published by the Free Software Foundation; either     */
/*  version 2 of the License, or (at your option) any later version. */
/*                                                                   */
/*  This library is distributed in the hope that it will be useful,  */
/*  but WITHOUT ANY WARRANTY; without even the implied warranty of   */
/*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.             */
/*  See the GNU Library General Public License for more details.     */
/*                                                                   */
/*  You should have received a copy of the GNU Library General Public*/
/*  License along with this library; if not, write to the Free       */
/*  Foundation, Inc., 59 Temple Place, Suite 330, Boston,            */
/*  MA  02111-1307  USA                                              */
/*                                                                   */
/*********************************************************************/

#pragma once

#include <filib/fi_lib.h>
#include <iostream>
#include <iomanip>
#include <algorithm>

/* ------------------------------------------------------------------- */
/* --- assignment                                                  --- */
/* ------------------------------------------------------------------- */

inline interval _interval(double x)
{
  interval w;

  w.INF = x;
  w.SUP = x;

  return w;
}

inline interval _interval(double x, double y)
{
  interval w;

  if (x > y)
  {
    std::cout << "Error: Invalid arguments in function _interval" << std::endl;
  }
  w.INF = x;
  w.SUP = y;

  return w;
}

/* ------------------------------------------------------------------- */
/* --- IO (input/output)                                           --- */
/* ------------------------------------------------------------------- */

inline std::istream &operator>>(std::istream &is, interval &a)
{
  double help, ioconst;

  ioconst = (1e17 - 1) * 1e27;

  is >> help;
  if ((help < -ioconst) || (help > ioconst))
    a.INF = q_pred(q_pred(help));
  else
    a.INF = q_pred(help);

  is >> help;
  if ((help < -ioconst) || (help > ioconst))
    a.SUP = q_succ(q_succ(help));
  else
    a.SUP = q_succ(help);

  return is;
}

inline std::ostream &operator<<(std::ostream &os, interval a)
{
  interval help;

  help.INF = q_pred(q_pred(a.INF));
  help.SUP = q_succ(q_succ(a.SUP));

  std::ios_base::fmtflags aktform = std::cout.flags();
  os << "[" << std::setprecision(15) << std::setw(23) << std::setiosflags(std::ios::scientific);
  os << help.INF;
  std::cout.flags(aktform);
  os << "," << std::setprecision(15) << std::setw(23) << std::setiosflags(std::ios::scientific);
  os << help.SUP;
  std::cout.flags(aktform);
  os << " ]";

  return os;
}

/* ------------------------------------------------------------------- */
/* --- interval arithmetic (basic operations)                      --- */
/* ------------------------------------------------------------------- */

inline interval operator+(interval a, interval b)
{
  return add_ii(a, b);
}

inline interval operator+(interval a, double b)
{
  return add_id(a, b);
}

inline interval operator+(double a, interval b)
{
  return add_di(a, b);
}

inline interval operator+(interval a)
{
  return a;
}

inline interval &operator+=(interval &lhs, const interval &rhs)
{
  lhs = add_ii(lhs, rhs);
  return lhs;
}

inline interval &operator+=(interval &lhs, const double &rhs)
{
  lhs = add_id(lhs, rhs);
  return lhs;
}

inline interval operator-(interval a, interval b)
{
  return sub_ii(a, b);
}

inline interval operator-(interval a, double b)
{
  return sub_id(a, b);
}

inline interval operator-(double a, interval b)
{
  return sub_di(a, b);
}

inline interval operator-(interval a)
{
  return _interval(-a.SUP, -a.INF);
}

inline interval &operator-=(interval &lhs, const interval &rhs)
{
  lhs = sub_ii(lhs, rhs);
  return lhs;
}

inline interval &operator-=(interval &lhs, const double &rhs)
{
  lhs = sub_id(lhs, rhs);
  return lhs;
}

inline interval operator*(interval a, interval b)
{
  return mul_ii(a, b);
}

inline interval operator*(interval a, double b)
{
  return mul_id(a, b);
}

inline interval operator*(double a, interval b)
{
  return mul_di(a, b);
}

inline interval &operator*=(interval &lhs, const interval &rhs)
{
  lhs = mul_ii(lhs, rhs);
  return lhs;
}

inline interval &operator*=(interval &lhs, const double &rhs)
{
  lhs = mul_id(lhs, rhs);
  return lhs;
}

inline interval operator/(interval a, interval b)
{
  return div_ii(a, b);
}

inline interval operator/(interval a, double b)
{
  return div_id(a, b);
}

inline interval operator/(double a, interval b)
{
  return div_di(a, b);
}

inline interval &operator/=(interval &lhs, const interval &rhs)
{
  lhs = div_ii(lhs, rhs);
  return lhs;
}

inline interval &operator/=(interval &lhs, const double &rhs)
{
  lhs = div_id(lhs, rhs);
  return lhs;
}

/* ------------------------------------------------------------------- */
/* --- interval arithmetic (logical operations)                    --- */
/* ------------------------------------------------------------------- */

inline bool operator==(interval a, interval b)
{
  return ieq_ii(a, b);
}

inline bool operator==(interval a, double b)
{
  return ieq_ii(a, _interval(b));
}

inline bool operator==(double a, interval b)
{
  return ieq_ii(_interval(a), b);
}

inline bool operator!=(interval a, interval b)
{
  return a.INF != b.INF || a.SUP != b.SUP;
}

inline bool operator!=(interval a, double b)
{
  return a.INF != b || a.SUP != b;
}

inline bool operator!=(double a, interval b)
{
  return a != b.INF || a != b.SUP;
}

inline bool operator<(interval a, interval b)
{
  // return in_ii(a, b);
  return a.SUP < b.INF;
}

inline bool operator<(interval a, double b)
{
  // return a.INF < b && b < a.SUP;
  return a.SUP < b;
}

inline bool operator<(double a, interval b)
{
  // return b.INF < a && a < b.SUP;
  return a < b.INF;
}

inline bool operator<=(interval a, interval b)
{
  // return b.INF <= a.INF && a.SUP <= b.SUP;
  return a.SUP <= b.INF;
}

inline bool operator<=(interval a, double b)
{
  return a.SUP <= b;
}

inline bool operator<=(double a, interval b)
{
  return a <= b.INF;
}

inline bool operator>(interval a, interval b)
{
  // return b.INF > a.INF && a.SUP > b.SUP;
  return a.INF > b.SUP;
}

inline bool operator>(interval a, double b)
{
  // return a.INF < b && b < a.SUP;
  return a.INF > b;
}

inline bool operator>(double a, interval b)
{
  return a > b.SUP;
}

inline bool operator>=(interval a, interval b)
{
  // return b.INF >= a.INF && a.SUP >= b.SUP;
  return a.INF >= b.SUP;
}

inline bool operator>=(interval a, double b)
{
  // return a.INF <= b && b <= a.SUP;
  return a.INF >= b;
}

inline bool operator>=(double a, interval b)
{
  return a >= b.SUP;
}

inline bool in(double a, interval b)
{
  return in_di(a, b);
}

inline bool in(interval a, interval b)
{
  return in_ii(a, b);
}

inline bool empty(interval a)
{
  return a.INF > a.SUP;
}

inline interval operator|(interval a, interval b)
{
  return hull(a, b);
}

inline interval operator&(interval a, interval b)
{
  return intsec(a, b);
}

inline interval &operator|=(interval &lhs, const interval &rhs)
{
  lhs = lhs | rhs;
  return lhs;
}

inline interval &operator&=(interval &lhs, const interval &rhs)
{
  lhs = lhs & rhs;
  return lhs;
}

/* ------------------------------------------------------------------- */
/* --- utilities, mid, diam, ...                                   --- */
/* ------------------------------------------------------------------- */

inline double inf(interval a)
{
  return a.INF;
}

inline double sup(interval a)
{
  return a.SUP;
}

inline double mid(interval a)
{
  return q_mid(a);
}

inline bool disjoint(interval a, interval b)
{
  return dis_ii(a, b);
}

inline double diam(interval a)
{
  return q_diam(a);
}

inline double drel(interval a)
{
  if ((a.SUP <= -q_minr) || (q_minr <= a.INF))
  {
    if (a.INF > 0)
      return diam(a) / a.INF;
    else
      return diam(a) / (-a.SUP);
  }
  else
  {
    return diam(a);
  }
}

inline interval blow(interval x, double eps)
{
  interval y;
  y = (1.0 + eps) * x - eps * x;
  return (_interval(q_pred(y.INF), q_succ(y.SUP)));
}

/* min max function, same as what BOOST does */
inline interval max(interval x, interval y)
{
  return _interval(std::max(x.INF, y.INF), std::max(x.SUP, y.SUP));
}

inline interval max(interval x, double y)
{
  return _interval(std::max(x.INF, y), std::max(x.SUP, y));
}

inline interval max(double x, interval y)
{
  return _interval(std::max(x, y.INF), std::max(x, y.SUP));
}

inline interval min(interval x, interval y)
{
  return _interval(std::min(x.INF, y.INF), std::min(x.SUP, y.SUP));
}

inline interval min(interval x, double y)
{
  return _interval(std::min(x.INF, y), std::min(x.SUP, y));
}

inline interval min(double x, interval y)
{
  return _interval(std::min(x, y.INF), std::min(x, y.SUP));
}

/* ------------------------------------------------------------------- */
/* --- interval arithmetic (elementary functions)                  --- */
/* ------------------------------------------------------------------- */

inline interval sqr(interval a)
{
  return j_sqr(a);
}

inline interval sqrt(interval a)
{
  return j_sqrt(a);
}

/* exponentiation */

inline interval exp(interval a)
{
  return j_exp(a);
}

inline interval exp2(interval a)
{
  return j_exp2(a);
}

inline interval exp10(interval a)
{
  return j_ex10(a);
}

inline interval expm1(interval a)
{
  return j_expm(a);
}

/* logarithm */

inline interval log(interval a)
{
  return j_log(a);
}

inline interval log2(interval a)
{
  return j_log2(a);
}

inline interval log10(interval a)
{
  return j_lg10(a);
}

inline interval log1p(interval a)
{
  return j_lg1p(a);
}

/* trigonometric functions */

inline interval sin(interval a)
{
  return j_sin(a);
}

inline interval cos(interval a)
{
  return j_cos(a);
}

inline interval cot(interval a)
{
  return j_cot(a);
}

inline interval tan(interval a)
{
  return j_tan(a);
}

/* inverse trigonometric functions */

inline interval asin(interval a)
{
  return j_asin(a);
}

inline interval acos(interval a)
{
  return j_acos(a);
}

inline interval acot(interval a)
{
  return j_acot(a);
}

inline interval atan(interval a)
{
  return j_atan(a);
}

/* hyperbolic functions */

inline interval sinh(interval a)
{
  return j_sinh(a);
}

inline interval cosh(interval a)
{
  return j_cosh(a);
}

inline interval coth(interval a)
{
  return j_coth(a);
}

inline interval tanh(interval a)
{
  return j_tanh(a);
}

/* inverse hyperbolic functions */

inline interval asinh(interval a)
{
  return j_asnh(a);
}

inline interval acosh(interval a)
{
  return j_acsh(a);
}

inline interval acoth(interval a)
{
  return j_acth(a);
}

inline interval atanh(interval a)
{
  return j_atnh(a);
}

/* error function */

inline interval erf(interval a)
{
  return j_erf(a);
}

inline interval erfc(interval a)
{
  return j_erfc(a);
}
