#ifndef ORDER_INC_ORDER_LIB_STREAM_H_VAJK20040620
#define ORDER_INC_ORDER_LIB_STREAM_H_VAJK20040620

// (C) Copyright Vesa Karvonen 2004.
//
// Distributed under the Boost Software License, Version 1.0.

// NOTE: This is the "odd" stream data structure. Without
// memoization, "even" streams would be significantly less
// efficient.

// Constants

#define ORDER_PP_DEF_8stream_nil 8DEF_CONST,,

#define ORDER_PP_DEF_8stream_of_naturals 8DEF_CONST,((00),(,8STREAM_OF_NATURALS,(01))),
#define ORDER_PP_8STREAM_OF_NATURALS(P,_,i,...) (,(P##i,(,8STREAM_OF_NATURALS,ORDER_PP_NAT_SUCC P##i)),P##__VA_ARGS__)

// First-order

#define ORDER_PP_DEF_8seq_to_stream             \
ORDER_PP_FN(8fn(8S,                             \
                8stream_unfold(8seq_isnt_nil,   \
                               8seq_rest,       \
                               8seq_first,      \
                               8S)))

#define ORDER_PP_DEF_8stream_cons(f,r) ORDER_PP_MACRO(8pair(f,8delay(r)))

#define ORDER_PP_DEF_8stream_drop ORDER_PP_FN_CM(2,8STREAM_DROP)
#define ORDER_PP_8STREAM_DROP(P,s,n,...) (,ORDER_PP_OR(,ORDER_PP_NUM_IS_0(,P##n),ORDER_PP_ISNT_EDIBLE(,P##s))(,P##s,,ORDER_PP_STREAM_TAIL P##s,8STREAM_DROP,ORDER_PP_NUM_DEC(,P##n)),P##__VA_ARGS__)

#define ORDER_PP_DEF_8stream_head ORDER_PP_FN_CM(1,8STREAM_HEAD)
#define ORDER_PP_8STREAM_HEAD(P,s,...) (,ORDER_PP_STREAM_HEAD s##P,P##__VA_ARGS__)

#define ORDER_PP_DEF_8stream_is_cons ORDER_PP_MACRO(8seq_isnt_nil)

#define ORDER_PP_DEF_8stream_is_nil ORDER_PP_MACRO(8seq_is_nil)

#define ORDER_PP_DEF_8stream_tail ORDER_PP_FN_CM(1,8STREAM_TAIL)
#define ORDER_PP_8STREAM_TAIL(P,s,...) (,,ORDER_PP_STREAM_TAIL s##P,P##__VA_ARGS__)

#define ORDER_PP_DEF_8stream_take ORDER_PP_FN_CM(2,8STREAM_TAKE)
#define ORDER_PP_8STREAM_TAKE(P,s,n,...) (,ORDER_PP_OR(ORDER_PP_,NUM_IS_0(,P##n),ISNT_EDIBLE(,P##s))(,,(ORDER_PP_STREAM_TAKE s##P,8STREAM_TAKE,ORDER_PP_NUM_DEC(,P##n))ORDER_PP_RPAREN),P##__VA_ARGS__)
#define ORDER_PP_STREAM_TAKE(h,t) h,(,ORDER_PP_OPEN t

#define ORDER_PP_DEF_8stream_to_seq             \
ORDER_PP_FN(8fn(8S,                             \
                8seq_unfold(8stream_is_cons,    \
                            8stream_tail,       \
                            8stream_head,       \
                            8S)))

// Higher-order

#define ORDER_PP_DEF_8stream_filter ORDER_PP_FN_CM(2,8STREAM_FILTER)
#define ORDER_PP_8STREAM_FILTER(P,s,f,...) (,ORDER_PP_ISNT_EDIBLE(,P##s)(,,ORDER_PP_STREAM_HEAD s##P,ORDER_PP_OPEN f##P,8STREAM_FILTER_B,P##s,P##f),P##__VA_ARGS__)
#define ORDER_PP_8STREAM_FILTER_B(P,b,s,f,...) (,ORDER_PP_IF_##b(,(ORDER_PP_STREAM_HEAD s##P,(,ORDER_PP_STREAM_TAIL s##P,8STREAM_FILTER,P##f)),,ORDER_PP_STREAM_TAIL s##P,8STREAM_FILTER,P##f),P##__VA_ARGS__)


#define ORDER_PP_DEF_8stream_fold                               \
ORDER_PP_FN(8fn(8F,8R,8S,                                       \
                8if(8stream_is_nil(8S),                         \
                    8R,                                         \
                    8stream_fold(8F,                            \
                                 8ap(8F,8R,8stream_head(8S)),   \
                                 8stream_tail(8S)))))

#define ORDER_PP_DEF_8stream_for_each ORDER_PP_FN_CM(2,8STREAM_FOR_EACH)
#define ORDER_PP_8STREAM_FOR_EACH(P,s,f,...) (,ORDER_PP_ISNT_EDIBLE(,P##s)(,,ORDER_PP_STREAM_HEAD s##P,ORDER_PP_OPEN f##P,ORDER_PP_STREAM_TAIL s##P,8STREAM_FOR_EACH,P##f),P##__VA_ARGS__)

#define ORDER_PP_DEF_8stream_iterate ORDER_PP_FN_CM(2,8STREAM_ITERATE)
#define ORDER_PP_8STREAM_ITERATE(P,x,f,...) (,(P##x,(,8STREAM_ITERATE_B,P##f,P##x)),P##__VA_ARGS__)
#define ORDER_PP_8STREAM_ITERATE_B(P,_,f,x,...) (,P##x,ORDER_PP_OPEN f##P,8STREAM_ITERATE,P##f,P##__VA_ARGS__)

#define ORDER_PP_DEF_8stream_map                                                \
ORDER_PP_FN(8fn(8F,8S,                                                          \
                8unless(8stream_is_nil(8S),                                     \
                        8stream_cons(8ap(8F,8stream_head(8S)),                  \
                                     8stream_map(8F,8stream_tail(8S))))))

#define ORDER_PP_DEF_8stream_merge                                              \
ORDER_PP_FN(8fn(8F,8L,8R,                                                       \
                8cond((8stream_is_nil(8L),                                      \
                       8R)                                                      \
                      (8stream_is_nil(8R),                                      \
                       8L)                                                      \
                      (8ap(8F,8stream_head(8L),8stream_head(8R)),               \
                       8stream_cons(8stream_head(8L),                           \
                                    8stream_merge(8F,8stream_tail(8L),8R)))     \
                      (8else,                                                   \
                       8stream_cons(8stream_head(8S),                           \
                                    8stream_merge(8F,8L,8stream_tail(8R)))))))

#define ORDER_PP_DEF_8stream_unfold                                             \
ORDER_PP_FN(8fn(8C,8S,8F,8X,                                                    \
                8when(8ap(8C,8X),                                               \
                      8stream_cons(8ap(8F,8X),                                  \
                                   8stream_unfold(8C,8S,8F,8ap(8S,8X))))))

#define ORDER_PP_DEF_8stream_zip_with                                           \
ORDER_PP_FN(8fn(8F,8L,8R,                                                       \
                8unless(8or(8stream_is_nil(8L),                                 \
                            8stream_is_nil(8R)),                                \
                        8stream_cons(8ap(8F,                                    \
                                         8stream_head(8L),                      \
                                         8stream_head(8R)),                     \
                                     8stream_zip_with(8F,                       \
                                                      8stream_tail(8L),         \
                                                      8stream_tail(8R))))))

// Detail

#define ORDER_PP_STREAM_HEAD(h,t) h
#define ORDER_PP_STREAM_TAIL(h,t) ORDER_PP_OPEN t

#endif