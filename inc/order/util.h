#ifndef ORDER_UTIL_H
#define ORDER_UTIL_H

/* (C) Copyright Vesa Karvonen 2004.
 *
 *    Distributed under the Boost Software License, Version 1.0.
 */

#define ORDER_DEF(t) ORDER_DEF_##t

#define ORDER_DEF_ARGS_LAST_AT_1(_0,_1) ORDER_DEF_##_1
#define ORDER_DEF_ARGS_LAST_AT_2(_0,_1,_2) ORDER_DEF_##_2
#define ORDER_DEF_ARGS_LAST_AT_3(_0,_1,_2,_3) ORDER_DEF_##_3
#define ORDER_DEF_ARGS_LAST_AT_4(_0,_1,_2,_3,_4) ORDER_DEF_##_4
#define ORDER_DEF_ARGS_LAST_AT_5(_0,_1,_2,_3,_4,_5) ORDER_DEF_##_5
#define ORDER_DEF_ARGS_LAST_AT_6(_0,_1,_2,_3,_4,_5,_6) ORDER_DEF_##_6
#define ORDER_DEF_ARGS_LAST_AT_7(_0,_1,_2,_3,_4,_5,_6,_7) ORDER_DEF_##_7

#define ORDER_PP_ARGS_FIRST_1(_0,...) _0
#define ORDER_PP_ARGS_FIRST_2(_0,_1,...) _0,_1
#define ORDER_PP_ARGS_FIRST_3(_0,_1,_2,...) _0,_1,_2
#define ORDER_PP_ARGS_FIRST_4(_0,_1,_2,_3,...) _0,_1,_2,_3
#define ORDER_PP_ARGS_FIRST_5(_0,_1,_2,_3,_4,...) _0,_1,_2,_3,_4
#define ORDER_PP_ARGS_FIRST_6(_0,_1,_2,_3,_4,_5,...) _0,_1,_2,_3,_4,_5
#define ORDER_PP_ARGS_FIRST_7(_0,_1,_2,_3,_4,_5,_6,...) _0,_1,_2,_3,_4,_5,_6

#define ORDER_PP_EAT(...)
#define ORDER_PP_EXPAND(l,r) l r
#define ORDER_PP_OPEN(P,...) P##__VA_ARGS__

#define ORDER_PP_NUM_ARGS_8(_,_8,_7,_6,_5,_4,_3,_2,_1,x,...) x

#endif