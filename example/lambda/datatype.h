#ifndef ORDER_EXAMPLE_LAMBDA_DATATYPE_H_VAJK20040620
#define ORDER_EXAMPLE_LAMBDA_DATATYPE_H_VAJK20040620

// (C) Copyright Vesa Karvonen 2004.
//
//    Distributed under the Boost Software License, Version 1.0.

#include "order/interpreter.h"
#include "checked_malloc.h"

#define DATATYPE_define(datatypes)                              \
ORDER_PP(8seq_for_each                                          \
         (8fn(8DT,                                              \
              8let(8N,8tuple_at(0,8DT),                         \
                   8emit(8quote(typedef const struct),8N,       \
                         8quote(*),8N,8quote(;)))),             \
          8vseq_to_seq(8quote(datatypes))))                     \
                                                                \
ORDER_PP(8seq_for_each                                          \
         (8fn(8DT,                                              \
              8emit(8quote(DATATYPE_GEN_datatype),              \
                    8DT)),                                      \
          8vseq_to_seq(8quote(datatypes))))

#define DATATYPE_GEN_datatype(P, type_name, variants, ...)              \
ORDER_PP(8seq_for_each                                                  \
         (8fn(8V,                                                       \
              8seq_for_each_with_idx                                    \
              (8fn(8I, 8T,                                              \
                   8emit(8quote(DATATYPE_GEN_field_typedef),            \
                         8args(8tuple_at(0,8V),                         \
                               8I,                                      \
                               8T))),                                   \
               8tuple_at(1,8V))),                                       \
          8vseq_to_seq(8quote(variants))))                              \
                                                                        \
struct type_name {                                                      \
  enum {                                                                \
    ORDER_PP(8seq_for_each                                              \
             (8fn(8V,                                                   \
                  8emit(8quote(DATATYPE_GEN_tag),                       \
                        8args(8tuple_at(0,8V)))),                       \
              8vseq_to_seq(8quote(variants))))                          \
  } tag;                                                                \
                                                                        \
  union {                                                               \
    ORDER_PP(8seq_for_each                                              \
             (8fn(8V,                                                   \
                  8when(8seq_isnt_nil(8tuple_at(1,8V)),                 \
                        8emit(8quote(DATATYPE_GEN_variant_struct),      \
                              8V))),                                    \
              8vseq_to_seq(8quote(variants))))                          \
  } datum;                                                              \
};                                                                      \
                                                                        \
ORDER_PP(8seq_for_each                                                  \
         (8fn(8V,                                                       \
              8emit(8quote(DATATYPE_GEN_ctor),                          \
                    8args(8quote(type_name),                            \
                          8tuple_at(0,8V),                              \
                          8seq_size(8tuple_at(1,8V))))),                \
          8vseq_to_seq(8quote(variants))))

#define DATATYPE_GEN_tag(ctor_name) DATATYPE_TAG_##ctor_name,

#define DATATYPE_GEN_field_typedef(ctor_name, idx, type)        \
typedef type DATATYPE_FIELD_##idx##_TYPE_##ctor_name;

#define DATATYPE_GEN_variant_struct(P, ctor_name, field_types, ...)     \
struct {                                                                \
  ORDER_PP(8seq_for_each_with_idx                                       \
           (8fn(8I, 8T,                                                 \
                8emit(8T, 8cat(8quote(_), 8I), 8quote(;))),             \
            8quote(field_types)))                                       \
} ctor_name;

#define DATATYPE_GEN_ctor(type_name, ctor_name, field_cnt)      \
inline type_name                                                \
ctor_name(ORDER_PP(8for_each_in_range                           \
                   (8fn(8I,                                     \
                        8emit(8quote(DATATYPE_GEN_ctor_arg),    \
                              8args(8quote(ctor_name), 8I))),   \
                    0,                                          \
                    field_cnt))) {                              \
  struct type_name* ORDER_PP_FRESH_ID(result) =                 \
    checked_malloc(sizeof(struct type_name));                   \
                                                                \
  ORDER_PP_FRESH_ID(result)->tag = DATATYPE_TAG_##ctor_name;    \
                                                                \
  ORDER_PP(8for_each_in_range                                   \
           (8fn(8I,                                             \
                8emit(8quote(DATATYPE_GEN_ctor_assign),         \
                      8args(8quote(ctor_name), 8I))),           \
            0,                                                  \
            field_cnt))                                         \
                                                                \
  return ORDER_PP_FRESH_ID(result);                             \
}

#define DATATYPE_GEN_ctor_arg(ctor_name, field_idx)             \
ORDER_PP(8when(8isnt_0(field_idx),                              \
               8emit_comma))                                    \
     DATATYPE_FIELD_##field_idx##_TYPE_##ctor_name _##field_idx

#define DATATYPE_GEN_ctor_assign(ctor_name, idx)                \
ORDER_PP_FRESH_ID(result)->datum.ctor_name._##idx = _##idx;

#define DATATYPE_switch(expr, type_name, cases)         \
do {                                                    \
  const type_name ORDER_PP_FRESH_ID(value) = (expr);    \
                                                        \
  switch (ORDER_PP_FRESH_ID(value)->tag) {              \
    ORDER_PP(8seq_for_each                              \
             (8fn(8C,                                   \
                  8emit(8quote(DATATYPE_GEN_case),      \
                        8C)),                           \
              8vseq_to_seq(8quote(cases))))             \
  default:                                              \
    ERROR_exit("Invalid tag %d resulting from '%s'.",   \
               ORDER_PP_FRESH_ID(value)->tag, #expr);   \
  }                                                     \
} while (0)

#define DATATYPE_GEN_case(P, ctor_name, field_names, body, ...) \
case DATATYPE_TAG_##ctor_name: {                                \
  ORDER_PP(8seq_for_each_with_idx                               \
           (8fn(8I, 8FN,                                        \
                8emit(8quote(DATATYPE_GEN_var),                 \
                      8args(8quote(ctor_name),                  \
                            8I,                                 \
                            8FN))),                             \
            8quote(field_names)))                               \
  do { ORDER_PP_REM body } while (0);                           \
  break;                                                        \
}

#define DATATYPE_GEN_var(ctor_name, idx, name)          \
const DATATYPE_FIELD_##idx##_TYPE_##ctor_name name      \
= ORDER_PP_FRESH_ID(value)->datum.ctor_name._##idx;

#endif
