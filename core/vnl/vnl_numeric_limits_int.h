// <begin copyright notice>
// ---------------------------------------------------------------------------
//
//                   Copyright (c) 1997 TargetJr Consortium
//               GE Corporate Research and Development (GE CRD)
//                             1 Research Circle
//                            Niskayuna, NY 12309
//                            All Rights Reserved
//              Reproduction rights limited as described below.
//                               
//      Permission to use, copy, modify, distribute, and sell this software
//      and its documentation for any purpose is hereby granted without fee,
//      provided that (i) the above copyright notice and this permission
//      notice appear in all copies of the software and related documentation,
//      (ii) the name TargetJr Consortium (represented by GE CRD), may not be
//      used in any advertising or publicity relating to the software without
//      the specific, prior written permission of GE CRD, and (iii) any
//      modifications are clearly marked and summarized in a change history
//      log.
//       
//      THE SOFTWARE IS PROVIDED "AS IS" AND WITHOUT WARRANTY OF ANY KIND,
//      EXPRESS, IMPLIED OR OTHERWISE, INCLUDING WITHOUT LIMITATION, ANY
//      WARRANTY OF MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE.
//      IN NO EVENT SHALL THE TARGETJR CONSORTIUM BE LIABLE FOR ANY SPECIAL,
//      INCIDENTAL, INDIRECT OR CONSEQUENTIAL DAMAGES OF ANY KIND OR ANY
//      DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS,
//      WHETHER OR NOT ADVISED OF THE POSSIBILITY OF SUCH DAMAGES, OR ON
//      ANY THEORY OF LIABILITY ARISING OUT OF OR IN CONNECTION WITH THE
//      USE OR PERFORMANCE OF THIS SOFTWARE.
//
// ---------------------------------------------------------------------------
// <end copyright notice>
//-*- c++ -*-------------------------------------------------------------------
#ifndef vnl_numeric_limits_int_h_
#define vnl_numeric_limits_int_h_
#ifdef __GNUC__
#pragma interface
#endif
//
// Class : numeric_limits_int
//
// .SECTION Description
//    numeric_limits specialized for int.
//
// .NAME        numeric_limits_int - Integer numeric limits.
// .FILE        vnl/numeric_limits_int.cxx
// .SECTION Author
//     Andrew W. Fitzgibbon, Oxford RRG, 28 Aug 96
//
// .SECTION Modifications:
//     <none yet>
//
//-----------------------------------------------------------------------------

#include <vcl/vcl_compiler.h>
#include <vnl/vnl_numeric_limits.h>

#ifdef IUE_64_BIT
# define vnl_tmp_signed32 ????
#else
# define vnl_tmp_signed32 int
#endif

VCL_DECLARE_SPECIALIZATION(class vnl_numeric_limits<vnl_tmp_signed32>)

class vnl_numeric_limits<vnl_tmp_signed32> {
public:
  static const bool is_specialized VCL_STATIC_CONST_INIT_INT(true);
  inline static int min() { return -0x7fffffff; }
  inline static int max() { return 0x7fffffff; }
  static const int digits   VCL_STATIC_CONST_INIT_INT(31);
  static const int digits10 VCL_STATIC_CONST_INIT_INT(9);
  static const bool is_signed  VCL_STATIC_CONST_INIT_INT(true);
  static const bool is_integer VCL_STATIC_CONST_INIT_INT(true);
  static const bool is_exact   VCL_STATIC_CONST_INIT_INT(true);
  static const int radix VCL_STATIC_CONST_INIT_INT(2);
  inline static int epsilon()     { return 0; }
  inline static int round_error() { return 0; }
  static const int min_exponent   VCL_STATIC_CONST_INIT_INT(-31);
  static const int min_exponent10 VCL_STATIC_CONST_INIT_INT(-9);
  static const int max_exponent   VCL_STATIC_CONST_INIT_INT(31);
  static const int max_exponent10 VCL_STATIC_CONST_INIT_INT(9);
  static const bool has_infinity      VCL_STATIC_CONST_INIT_INT(false);
  static const bool has_quiet_NaN     VCL_STATIC_CONST_INIT_INT(false);
  static const bool has_signaling_NaN VCL_STATIC_CONST_INIT_INT(false);
  static const bool has_denorm        VCL_STATIC_CONST_INIT_INT(false);
  static int infinity() { return max(); }
  static int quiet_NaN();
  static int signaling_NaN();
  inline static int denorm_min()    { return min(); }
  static const bool is_iec559  VCL_STATIC_CONST_INIT_INT(false);
  static const bool is_bounded VCL_STATIC_CONST_INIT_INT(true);
  static const bool is_modulo  VCL_STATIC_CONST_INIT_INT(true);
  static const bool traps      VCL_STATIC_CONST_INIT_INT(false);
  static const bool tinyness_before VCL_STATIC_CONST_INIT_INT(false);
  static const vnl_float_round_style round_style VCL_STATIC_CONST_INIT_INT(vnl_round_toward_zero);
};

#undef vnl_tmp_signed32

#endif   // DO NOT ADD CODE AFTER THIS LINE! END OF DEFINITION FOR CLASS numeric_limits_float.

