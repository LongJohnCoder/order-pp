#ifndef ORDER_PRELUDE_CONTROL_H_VAJK20040620
#define ORDER_PRELUDE_CONTROL_H_VAJK20040620

/* (C) Copyright Vesa Karvonen 2004.
 *
 *    Distributed under the Boost Software License, Version 1.0.
 */

#define ORDER_PP_DEF_when(t,...) 8EVAL_IF,t,do(__VA_ARGS__),nil
#define ORDER_PP_DEF_unless(t,...) 8EVAL_IF,t,nil,do(__VA_ARGS__)

#define ORDER_PP_DEF_for_each_in_range ORDER_PP_FN_CM(3,8PASS_NIL_4,8FOR_EACH_IN_RANGE_4)
#define ORDER_PP_CM_8FOR_EACH_IN_RANGE_4(P,_,f,lo,hi,...) (,ORDER_PP_EQUAL(,P##lo,P##hi)(,(,),P##lo,ORDER_PP_OPEN f##P,8FOR_EACH_IN_RANGE_4,P##f,ORDER_PP_INC_##lo,P##hi),P##__VA_ARGS__)

#endif