#ifndef ORDER_PRELUDE_BOOLEAN_H_VAJK20040620
#define ORDER_PRELUDE_BOOLEAN_H_VAJK20040620

/* (C) Copyright Vesa Karvonen 2004.
 *
 *    Distributed under the Boost Software License, Version 1.0.
 */

#define ORDER_DEF_true 8DEF_CONST,true
#define ORDER_SYM_true_true(P,v) ,P##v,

#define ORDER_DEF_false 8DEF_CONST,false
#define ORDER_SYM_false_false(P,v) ,P##v,

#define ORDER_DEF_not ORDER_CTOR(1,8NOT)
#define ORDER_CM_8NOT(P,b,...) (,ORDER_CM_8NOT_##b,P##__VA_ARGS__)
#define ORDER_CM_8NOT_true false
#define ORDER_CM_8NOT_false true

#endif