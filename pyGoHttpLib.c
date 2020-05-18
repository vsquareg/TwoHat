#define _CFFI_

/* We try to define Py_LIMITED_API before including Python.h.

   Mess: we can only define it if Py_DEBUG, Py_TRACE_REFS and
   Py_REF_DEBUG are not defined.  This is a best-effort approximation:
   we can learn about Py_DEBUG from pyconfig.h, but it is unclear if
   the same works for the other two macros.  Py_DEBUG implies them,
   but not the other way around.

   Issue #350 is still open: on Windows, the code here causes it to link
   with PYTHON36.DLL (for example) instead of PYTHON3.DLL.  A fix was
   attempted in 164e526a5515 and 14ce6985e1c3, but reverted: virtualenv
   does not make PYTHON3.DLL available, and so the "correctly" compiled
   version would not run inside a virtualenv.  We will re-apply the fix
   after virtualenv has been fixed for some time.  For explanation, see
   issue #355.  For a workaround if you want PYTHON3.DLL and don't worry
   about virtualenv, see issue #350.  See also 'py_limited_api' in
   setuptools_ext.py.
*/
#if !defined(_CFFI_USE_EMBEDDING) && !defined(Py_LIMITED_API)
#  include <pyconfig.h>
#  if !defined(Py_DEBUG) && !defined(Py_TRACE_REFS) && !defined(Py_REF_DEBUG)
#    define Py_LIMITED_API
#  endif
#endif

#include <Python.h>
#ifdef __cplusplus
extern "C" {
#endif
#include <stddef.h>

/* This part is from file 'cffi/parse_c_type.h'.  It is copied at the
   beginning of C sources generated by CFFI's ffi.set_source(). */

typedef void *_cffi_opcode_t;

#define _CFFI_OP(opcode, arg)   (_cffi_opcode_t)(opcode | (((uintptr_t)(arg)) << 8))
#define _CFFI_GETOP(cffi_opcode)    ((unsigned char)(uintptr_t)cffi_opcode)
#define _CFFI_GETARG(cffi_opcode)   (((intptr_t)cffi_opcode) >> 8)

#define _CFFI_OP_PRIMITIVE       1
#define _CFFI_OP_POINTER         3
#define _CFFI_OP_ARRAY           5
#define _CFFI_OP_OPEN_ARRAY      7
#define _CFFI_OP_STRUCT_UNION    9
#define _CFFI_OP_ENUM           11
#define _CFFI_OP_FUNCTION       13
#define _CFFI_OP_FUNCTION_END   15
#define _CFFI_OP_NOOP           17
#define _CFFI_OP_BITFIELD       19
#define _CFFI_OP_TYPENAME       21
#define _CFFI_OP_CPYTHON_BLTN_V 23   // varargs
#define _CFFI_OP_CPYTHON_BLTN_N 25   // noargs
#define _CFFI_OP_CPYTHON_BLTN_O 27   // O  (i.e. a single arg)
#define _CFFI_OP_CONSTANT       29
#define _CFFI_OP_CONSTANT_INT   31
#define _CFFI_OP_GLOBAL_VAR     33
#define _CFFI_OP_DLOPEN_FUNC    35
#define _CFFI_OP_DLOPEN_CONST   37
#define _CFFI_OP_GLOBAL_VAR_F   39
#define _CFFI_OP_EXTERN_PYTHON  41

#define _CFFI_PRIM_VOID          0
#define _CFFI_PRIM_BOOL          1
#define _CFFI_PRIM_CHAR          2
#define _CFFI_PRIM_SCHAR         3
#define _CFFI_PRIM_UCHAR         4
#define _CFFI_PRIM_SHORT         5
#define _CFFI_PRIM_USHORT        6
#define _CFFI_PRIM_INT           7
#define _CFFI_PRIM_UINT          8
#define _CFFI_PRIM_LONG          9
#define _CFFI_PRIM_ULONG        10
#define _CFFI_PRIM_LONGLONG     11
#define _CFFI_PRIM_ULONGLONG    12
#define _CFFI_PRIM_FLOAT        13
#define _CFFI_PRIM_DOUBLE       14
#define _CFFI_PRIM_LONGDOUBLE   15

#define _CFFI_PRIM_WCHAR        16
#define _CFFI_PRIM_INT8         17
#define _CFFI_PRIM_UINT8        18
#define _CFFI_PRIM_INT16        19
#define _CFFI_PRIM_UINT16       20
#define _CFFI_PRIM_INT32        21
#define _CFFI_PRIM_UINT32       22
#define _CFFI_PRIM_INT64        23
#define _CFFI_PRIM_UINT64       24
#define _CFFI_PRIM_INTPTR       25
#define _CFFI_PRIM_UINTPTR      26
#define _CFFI_PRIM_PTRDIFF      27
#define _CFFI_PRIM_SIZE         28
#define _CFFI_PRIM_SSIZE        29
#define _CFFI_PRIM_INT_LEAST8   30
#define _CFFI_PRIM_UINT_LEAST8  31
#define _CFFI_PRIM_INT_LEAST16  32
#define _CFFI_PRIM_UINT_LEAST16 33
#define _CFFI_PRIM_INT_LEAST32  34
#define _CFFI_PRIM_UINT_LEAST32 35
#define _CFFI_PRIM_INT_LEAST64  36
#define _CFFI_PRIM_UINT_LEAST64 37
#define _CFFI_PRIM_INT_FAST8    38
#define _CFFI_PRIM_UINT_FAST8   39
#define _CFFI_PRIM_INT_FAST16   40
#define _CFFI_PRIM_UINT_FAST16  41
#define _CFFI_PRIM_INT_FAST32   42
#define _CFFI_PRIM_UINT_FAST32  43
#define _CFFI_PRIM_INT_FAST64   44
#define _CFFI_PRIM_UINT_FAST64  45
#define _CFFI_PRIM_INTMAX       46
#define _CFFI_PRIM_UINTMAX      47
#define _CFFI_PRIM_FLOATCOMPLEX 48
#define _CFFI_PRIM_DOUBLECOMPLEX 49
#define _CFFI_PRIM_CHAR16       50
#define _CFFI_PRIM_CHAR32       51

#define _CFFI__NUM_PRIM         52
#define _CFFI__UNKNOWN_PRIM           (-1)
#define _CFFI__UNKNOWN_FLOAT_PRIM     (-2)
#define _CFFI__UNKNOWN_LONG_DOUBLE    (-3)

#define _CFFI__IO_FILE_STRUCT         (-1)


struct _cffi_global_s {
    const char *name;
    void *address;
    _cffi_opcode_t type_op;
    void *size_or_direct_fn;  // OP_GLOBAL_VAR: size, or 0 if unknown
                              // OP_CPYTHON_BLTN_*: addr of direct function
};

struct _cffi_getconst_s {
    unsigned long long value;
    const struct _cffi_type_context_s *ctx;
    int gindex;
};

struct _cffi_struct_union_s {
    const char *name;
    int type_index;          // -> _cffi_types, on a OP_STRUCT_UNION
    int flags;               // _CFFI_F_* flags below
    size_t size;
    int alignment;
    int first_field_index;   // -> _cffi_fields array
    int num_fields;
};
#define _CFFI_F_UNION         0x01   // is a union, not a struct
#define _CFFI_F_CHECK_FIELDS  0x02   // complain if fields are not in the
                                     // "standard layout" or if some are missing
#define _CFFI_F_PACKED        0x04   // for CHECK_FIELDS, assume a packed struct
#define _CFFI_F_EXTERNAL      0x08   // in some other ffi.include()
#define _CFFI_F_OPAQUE        0x10   // opaque

struct _cffi_field_s {
    const char *name;
    size_t field_offset;
    size_t field_size;
    _cffi_opcode_t field_type_op;
};

struct _cffi_enum_s {
    const char *name;
    int type_index;          // -> _cffi_types, on a OP_ENUM
    int type_prim;           // _CFFI_PRIM_xxx
    const char *enumerators; // comma-delimited string
};

struct _cffi_typename_s {
    const char *name;
    int type_index;   /* if opaque, points to a possibly artificial
                         OP_STRUCT which is itself opaque */
};

struct _cffi_type_context_s {
    _cffi_opcode_t *types;
    const struct _cffi_global_s *globals;
    const struct _cffi_field_s *fields;
    const struct _cffi_struct_union_s *struct_unions;
    const struct _cffi_enum_s *enums;
    const struct _cffi_typename_s *typenames;
    int num_globals;
    int num_struct_unions;
    int num_enums;
    int num_typenames;
    const char *const *includes;
    int num_types;
    int flags;      /* future extension */
};

struct _cffi_parse_info_s {
    const struct _cffi_type_context_s *ctx;
    _cffi_opcode_t *output;
    unsigned int output_size;
    size_t error_location;
    const char *error_message;
};

struct _cffi_externpy_s {
    const char *name;
    size_t size_of_result;
    void *reserved1, *reserved2;
};

#ifdef _CFFI_INTERNAL
static int parse_c_type(struct _cffi_parse_info_s *info, const char *input);
static int search_in_globals(const struct _cffi_type_context_s *ctx,
                             const char *search, size_t search_len);
static int search_in_struct_unions(const struct _cffi_type_context_s *ctx,
                                   const char *search, size_t search_len);
#endif

/* this block of #ifs should be kept exactly identical between
   c/_cffi_backend.c, cffi/vengine_cpy.py, cffi/vengine_gen.py
   and cffi/_cffi_include.h */
#if defined(_MSC_VER)
# include <malloc.h>   /* for alloca() */
# if _MSC_VER < 1600   /* MSVC < 2010 */
   typedef __int8 int8_t;
   typedef __int16 int16_t;
   typedef __int32 int32_t;
   typedef __int64 int64_t;
   typedef unsigned __int8 uint8_t;
   typedef unsigned __int16 uint16_t;
   typedef unsigned __int32 uint32_t;
   typedef unsigned __int64 uint64_t;
   typedef __int8 int_least8_t;
   typedef __int16 int_least16_t;
   typedef __int32 int_least32_t;
   typedef __int64 int_least64_t;
   typedef unsigned __int8 uint_least8_t;
   typedef unsigned __int16 uint_least16_t;
   typedef unsigned __int32 uint_least32_t;
   typedef unsigned __int64 uint_least64_t;
   typedef __int8 int_fast8_t;
   typedef __int16 int_fast16_t;
   typedef __int32 int_fast32_t;
   typedef __int64 int_fast64_t;
   typedef unsigned __int8 uint_fast8_t;
   typedef unsigned __int16 uint_fast16_t;
   typedef unsigned __int32 uint_fast32_t;
   typedef unsigned __int64 uint_fast64_t;
   typedef __int64 intmax_t;
   typedef unsigned __int64 uintmax_t;
# else
#  include <stdint.h>
# endif
# if _MSC_VER < 1800   /* MSVC < 2013 */
#  ifndef __cplusplus
    typedef unsigned char _Bool;
#  endif
# endif
#else
# include <stdint.h>
# if (defined (__SVR4) && defined (__sun)) || defined(_AIX) || defined(__hpux)
#  include <alloca.h>
# endif
#endif

#ifdef __GNUC__
# define _CFFI_UNUSED_FN  __attribute__((unused))
#else
# define _CFFI_UNUSED_FN  /* nothing */
#endif

#ifdef __cplusplus
# ifndef _Bool
   typedef bool _Bool;   /* semi-hackish: C++ has no _Bool; bool is builtin */
# endif
#endif

/**********  CPython-specific section  **********/
#ifndef PYPY_VERSION


#if PY_MAJOR_VERSION >= 3
# define PyInt_FromLong PyLong_FromLong
#endif

#define _cffi_from_c_double PyFloat_FromDouble
#define _cffi_from_c_float PyFloat_FromDouble
#define _cffi_from_c_long PyInt_FromLong
#define _cffi_from_c_ulong PyLong_FromUnsignedLong
#define _cffi_from_c_longlong PyLong_FromLongLong
#define _cffi_from_c_ulonglong PyLong_FromUnsignedLongLong
#define _cffi_from_c__Bool PyBool_FromLong

#define _cffi_to_c_double PyFloat_AsDouble
#define _cffi_to_c_float PyFloat_AsDouble

#define _cffi_from_c_int(x, type)                                        \
    (((type)-1) > 0 ? /* unsigned */                                     \
        (sizeof(type) < sizeof(long) ?                                   \
            PyInt_FromLong((long)x) :                                    \
         sizeof(type) == sizeof(long) ?                                  \
            PyLong_FromUnsignedLong((unsigned long)x) :                  \
            PyLong_FromUnsignedLongLong((unsigned long long)x)) :        \
        (sizeof(type) <= sizeof(long) ?                                  \
            PyInt_FromLong((long)x) :                                    \
            PyLong_FromLongLong((long long)x)))

#define _cffi_to_c_int(o, type)                                          \
    ((type)(                                                             \
     sizeof(type) == 1 ? (((type)-1) > 0 ? (type)_cffi_to_c_u8(o)        \
                                         : (type)_cffi_to_c_i8(o)) :     \
     sizeof(type) == 2 ? (((type)-1) > 0 ? (type)_cffi_to_c_u16(o)       \
                                         : (type)_cffi_to_c_i16(o)) :    \
     sizeof(type) == 4 ? (((type)-1) > 0 ? (type)_cffi_to_c_u32(o)       \
                                         : (type)_cffi_to_c_i32(o)) :    \
     sizeof(type) == 8 ? (((type)-1) > 0 ? (type)_cffi_to_c_u64(o)       \
                                         : (type)_cffi_to_c_i64(o)) :    \
     (Py_FatalError("unsupported size for type " #type), (type)0)))

#define _cffi_to_c_i8                                                    \
                 ((int(*)(PyObject *))_cffi_exports[1])
#define _cffi_to_c_u8                                                    \
                 ((int(*)(PyObject *))_cffi_exports[2])
#define _cffi_to_c_i16                                                   \
                 ((int(*)(PyObject *))_cffi_exports[3])
#define _cffi_to_c_u16                                                   \
                 ((int(*)(PyObject *))_cffi_exports[4])
#define _cffi_to_c_i32                                                   \
                 ((int(*)(PyObject *))_cffi_exports[5])
#define _cffi_to_c_u32                                                   \
                 ((unsigned int(*)(PyObject *))_cffi_exports[6])
#define _cffi_to_c_i64                                                   \
                 ((long long(*)(PyObject *))_cffi_exports[7])
#define _cffi_to_c_u64                                                   \
                 ((unsigned long long(*)(PyObject *))_cffi_exports[8])
#define _cffi_to_c_char                                                  \
                 ((int(*)(PyObject *))_cffi_exports[9])
#define _cffi_from_c_pointer                                             \
    ((PyObject *(*)(char *, struct _cffi_ctypedescr *))_cffi_exports[10])
#define _cffi_to_c_pointer                                               \
    ((char *(*)(PyObject *, struct _cffi_ctypedescr *))_cffi_exports[11])
#define _cffi_get_struct_layout                                          \
    not used any more
#define _cffi_restore_errno                                              \
    ((void(*)(void))_cffi_exports[13])
#define _cffi_save_errno                                                 \
    ((void(*)(void))_cffi_exports[14])
#define _cffi_from_c_char                                                \
    ((PyObject *(*)(char))_cffi_exports[15])
#define _cffi_from_c_deref                                               \
    ((PyObject *(*)(char *, struct _cffi_ctypedescr *))_cffi_exports[16])
#define _cffi_to_c                                                       \
    ((int(*)(char *, struct _cffi_ctypedescr *, PyObject *))_cffi_exports[17])
#define _cffi_from_c_struct                                              \
    ((PyObject *(*)(char *, struct _cffi_ctypedescr *))_cffi_exports[18])
#define _cffi_to_c_wchar_t                                               \
    ((_cffi_wchar_t(*)(PyObject *))_cffi_exports[19])
#define _cffi_from_c_wchar_t                                             \
    ((PyObject *(*)(_cffi_wchar_t))_cffi_exports[20])
#define _cffi_to_c_long_double                                           \
    ((long double(*)(PyObject *))_cffi_exports[21])
#define _cffi_to_c__Bool                                                 \
    ((_Bool(*)(PyObject *))_cffi_exports[22])
#define _cffi_prepare_pointer_call_argument                              \
    ((Py_ssize_t(*)(struct _cffi_ctypedescr *,                           \
                    PyObject *, char **))_cffi_exports[23])
#define _cffi_convert_array_from_object                                  \
    ((int(*)(char *, struct _cffi_ctypedescr *, PyObject *))_cffi_exports[24])
#define _CFFI_CPIDX  25
#define _cffi_call_python                                                \
    ((void(*)(struct _cffi_externpy_s *, char *))_cffi_exports[_CFFI_CPIDX])
#define _cffi_to_c_wchar3216_t                                           \
    ((int(*)(PyObject *))_cffi_exports[26])
#define _cffi_from_c_wchar3216_t                                         \
    ((PyObject *(*)(int))_cffi_exports[27])
#define _CFFI_NUM_EXPORTS 28

struct _cffi_ctypedescr;

static void *_cffi_exports[_CFFI_NUM_EXPORTS];

#define _cffi_type(index)   (                           \
    assert((((uintptr_t)_cffi_types[index]) & 1) == 0), \
    (struct _cffi_ctypedescr *)_cffi_types[index])

static PyObject *_cffi_init(const char *module_name, Py_ssize_t version,
                            const struct _cffi_type_context_s *ctx)
{
    PyObject *module, *o_arg, *new_module;
    void *raw[] = {
        (void *)module_name,
        (void *)version,
        (void *)_cffi_exports,
        (void *)ctx,
    };

    module = PyImport_ImportModule("_cffi_backend");
    if (module == NULL)
        goto failure;

    o_arg = PyLong_FromVoidPtr((void *)raw);
    if (o_arg == NULL)
        goto failure;

    new_module = PyObject_CallMethod(
        module, (char *)"_init_cffi_1_0_external_module", (char *)"O", o_arg);

    Py_DECREF(o_arg);
    Py_DECREF(module);
    return new_module;

  failure:
    Py_XDECREF(module);
    return NULL;
}


#ifdef HAVE_WCHAR_H
typedef wchar_t _cffi_wchar_t;
#else
typedef uint16_t _cffi_wchar_t;   /* same random pick as _cffi_backend.c */
#endif

_CFFI_UNUSED_FN static uint16_t _cffi_to_c_char16_t(PyObject *o)
{
    if (sizeof(_cffi_wchar_t) == 2)
        return (uint16_t)_cffi_to_c_wchar_t(o);
    else
        return (uint16_t)_cffi_to_c_wchar3216_t(o);
}

_CFFI_UNUSED_FN static PyObject *_cffi_from_c_char16_t(uint16_t x)
{
    if (sizeof(_cffi_wchar_t) == 2)
        return _cffi_from_c_wchar_t((_cffi_wchar_t)x);
    else
        return _cffi_from_c_wchar3216_t((int)x);
}

_CFFI_UNUSED_FN static int _cffi_to_c_char32_t(PyObject *o)
{
    if (sizeof(_cffi_wchar_t) == 4)
        return (int)_cffi_to_c_wchar_t(o);
    else
        return (int)_cffi_to_c_wchar3216_t(o);
}

_CFFI_UNUSED_FN static PyObject *_cffi_from_c_char32_t(unsigned int x)
{
    if (sizeof(_cffi_wchar_t) == 4)
        return _cffi_from_c_wchar_t((_cffi_wchar_t)x);
    else
        return _cffi_from_c_wchar3216_t((int)x);
}

union _cffi_union_alignment_u {
    unsigned char m_char;
    unsigned short m_short;
    unsigned int m_int;
    unsigned long m_long;
    unsigned long long m_longlong;
    float m_float;
    double m_double;
    long double m_longdouble;
};

struct _cffi_freeme_s {
    struct _cffi_freeme_s *next;
    union _cffi_union_alignment_u alignment;
};

_CFFI_UNUSED_FN static int
_cffi_convert_array_argument(struct _cffi_ctypedescr *ctptr, PyObject *arg,
                             char **output_data, Py_ssize_t datasize,
                             struct _cffi_freeme_s **freeme)
{
    char *p;
    if (datasize < 0)
        return -1;

    p = *output_data;
    if (p == NULL) {
        struct _cffi_freeme_s *fp = (struct _cffi_freeme_s *)PyObject_Malloc(
            offsetof(struct _cffi_freeme_s, alignment) + (size_t)datasize);
        if (fp == NULL)
            return -1;
        fp->next = *freeme;
        *freeme = fp;
        p = *output_data = (char *)&fp->alignment;
    }
    memset((void *)p, 0, (size_t)datasize);
    return _cffi_convert_array_from_object(p, ctptr, arg);
}

_CFFI_UNUSED_FN static void
_cffi_free_array_arguments(struct _cffi_freeme_s *freeme)
{
    do {
        void *p = (void *)freeme;
        freeme = freeme->next;
        PyObject_Free(p);
    } while (freeme != NULL);
}

/**********  end CPython-specific section  **********/
#else
_CFFI_UNUSED_FN
static void (*_cffi_call_python_org)(struct _cffi_externpy_s *, char *);
# define _cffi_call_python  _cffi_call_python_org
#endif


#define _cffi_array_len(array)   (sizeof(array) / sizeof((array)[0]))

#define _cffi_prim_int(size, sign)                                      \
    ((size) == 1 ? ((sign) ? _CFFI_PRIM_INT8  : _CFFI_PRIM_UINT8)  :    \
     (size) == 2 ? ((sign) ? _CFFI_PRIM_INT16 : _CFFI_PRIM_UINT16) :    \
     (size) == 4 ? ((sign) ? _CFFI_PRIM_INT32 : _CFFI_PRIM_UINT32) :    \
     (size) == 8 ? ((sign) ? _CFFI_PRIM_INT64 : _CFFI_PRIM_UINT64) :    \
     _CFFI__UNKNOWN_PRIM)

#define _cffi_prim_float(size)                                          \
    ((size) == sizeof(float) ? _CFFI_PRIM_FLOAT :                       \
     (size) == sizeof(double) ? _CFFI_PRIM_DOUBLE :                     \
     (size) == sizeof(long double) ? _CFFI__UNKNOWN_LONG_DOUBLE :       \
     _CFFI__UNKNOWN_FLOAT_PRIM)

#define _cffi_check_int(got, got_nonpos, expected)      \
    ((got_nonpos) == (expected <= 0) &&                 \
     (got) == (unsigned long long)expected)

#ifdef MS_WIN32
# define _cffi_stdcall  __stdcall
#else
# define _cffi_stdcall  /* nothing */
#endif

#ifdef __cplusplus
}
#endif

/************************************************************/

 //passed to the real C compiler
        #include "gohttplib.h"
        #include <Python.h>
    

/************************************************************/

static void *_cffi_types[] = {
/*  0 */ _CFFI_OP(_CFFI_OP_FUNCTION, 2), // char *()(long, char *)
/*  1 */ _CFFI_OP(_CFFI_OP_PRIMITIVE, 9), // long
/*  2 */ _CFFI_OP(_CFFI_OP_POINTER, 33), // char *
/*  3 */ _CFFI_OP(_CFFI_OP_FUNCTION_END, 0),
/*  4 */ _CFFI_OP(_CFFI_OP_FUNCTION, 7), // int()(unsigned int, char *, int)
/*  5 */ _CFFI_OP(_CFFI_OP_PRIMITIVE, 8), // unsigned int
/*  6 */ _CFFI_OP(_CFFI_OP_NOOP, 2),
/*  7 */ _CFFI_OP(_CFFI_OP_PRIMITIVE, 7), // int
/*  8 */ _CFFI_OP(_CFFI_OP_FUNCTION_END, 0),
/*  9 */ _CFFI_OP(_CFFI_OP_FUNCTION, 1), // long()(void)
/* 10 */ _CFFI_OP(_CFFI_OP_FUNCTION_END, 0),
/* 11 */ _CFFI_OP(_CFFI_OP_FUNCTION, 34), // void()(char *)
/* 12 */ _CFFI_OP(_CFFI_OP_NOOP, 2),
/* 13 */ _CFFI_OP(_CFFI_OP_FUNCTION_END, 0),
/* 14 */ _CFFI_OP(_CFFI_OP_FUNCTION, 34), // void()(char *, void(*)(unsigned int, Request *))
/* 15 */ _CFFI_OP(_CFFI_OP_NOOP, 2),
/* 16 */ _CFFI_OP(_CFFI_OP_POINTER, 18), // void(*)(unsigned int, Request *)
/* 17 */ _CFFI_OP(_CFFI_OP_FUNCTION_END, 0),
/* 18 */ _CFFI_OP(_CFFI_OP_FUNCTION, 34), // void()(unsigned int, Request *)
/* 19 */ _CFFI_OP(_CFFI_OP_PRIMITIVE, 8),
/* 20 */ _CFFI_OP(_CFFI_OP_POINTER, 31), // Request *
/* 21 */ _CFFI_OP(_CFFI_OP_FUNCTION_END, 0),
/* 22 */ _CFFI_OP(_CFFI_OP_FUNCTION, 34), // void()(unsigned int, Request *, void(*)(unsigned int, Request *))
/* 23 */ _CFFI_OP(_CFFI_OP_PRIMITIVE, 8),
/* 24 */ _CFFI_OP(_CFFI_OP_NOOP, 20),
/* 25 */ _CFFI_OP(_CFFI_OP_NOOP, 16),
/* 26 */ _CFFI_OP(_CFFI_OP_FUNCTION_END, 0),
/* 27 */ _CFFI_OP(_CFFI_OP_FUNCTION, 34), // void()(unsigned int, int)
/* 28 */ _CFFI_OP(_CFFI_OP_PRIMITIVE, 8),
/* 29 */ _CFFI_OP(_CFFI_OP_PRIMITIVE, 7),
/* 30 */ _CFFI_OP(_CFFI_OP_FUNCTION_END, 0),
/* 31 */ _CFFI_OP(_CFFI_OP_STRUCT_UNION, 0), // Request
/* 32 */ _CFFI_OP(_CFFI_OP_POINTER, 33), // char const *
/* 33 */ _CFFI_OP(_CFFI_OP_PRIMITIVE, 2), // char
/* 34 */ _CFFI_OP(_CFFI_OP_PRIMITIVE, 0), // void
};

static void _cffi_d_Call_HandleFunc(unsigned int x0, Request * x1, void(* x2)(unsigned int, Request *))
{
  Call_HandleFunc(x0, x1, x2);
}
#ifndef PYPY_VERSION
static PyObject *
_cffi_f_Call_HandleFunc(PyObject *self, PyObject *args)
{
  unsigned int x0;
  Request * x1;
  void(* x2)(unsigned int, Request *);
  Py_ssize_t datasize;
  struct _cffi_freeme_s *large_args_free = NULL;
  PyObject *arg0;
  PyObject *arg1;
  PyObject *arg2;

  if (!PyArg_UnpackTuple(args, "Call_HandleFunc", 3, 3, &arg0, &arg1, &arg2))
    return NULL;

  x0 = _cffi_to_c_int(arg0, unsigned int);
  if (x0 == (unsigned int)-1 && PyErr_Occurred())
    return NULL;

  datasize = _cffi_prepare_pointer_call_argument(
      _cffi_type(20), arg1, (char **)&x1);
  if (datasize != 0) {
    x1 = ((size_t)datasize) <= 640 ? (Request *)alloca((size_t)datasize) : NULL;
    if (_cffi_convert_array_argument(_cffi_type(20), arg1, (char **)&x1,
            datasize, &large_args_free) < 0)
      return NULL;
  }

  x2 = (void(*)(unsigned int, Request *))_cffi_to_c_pointer(arg2, _cffi_type(16));
  if (x2 == (void(*)(unsigned int, Request *))NULL && PyErr_Occurred())
    return NULL;

  Py_BEGIN_ALLOW_THREADS
  _cffi_restore_errno();
  { Call_HandleFunc(x0, x1, x2); }
  _cffi_save_errno();
  Py_END_ALLOW_THREADS

  (void)self; /* unused */
  if (large_args_free != NULL) _cffi_free_array_arguments(large_args_free);
  Py_INCREF(Py_None);
  return Py_None;
}
#else
#  define _cffi_f_Call_HandleFunc _cffi_d_Call_HandleFunc
#endif

static void _cffi_d_HandleFunc(char * x0, void(* x1)(unsigned int, Request *))
{
  HandleFunc(x0, x1);
}
#ifndef PYPY_VERSION
static PyObject *
_cffi_f_HandleFunc(PyObject *self, PyObject *args)
{
  char * x0;
  void(* x1)(unsigned int, Request *);
  Py_ssize_t datasize;
  struct _cffi_freeme_s *large_args_free = NULL;
  PyObject *arg0;
  PyObject *arg1;

  if (!PyArg_UnpackTuple(args, "HandleFunc", 2, 2, &arg0, &arg1))
    return NULL;

  datasize = _cffi_prepare_pointer_call_argument(
      _cffi_type(2), arg0, (char **)&x0);
  if (datasize != 0) {
    x0 = ((size_t)datasize) <= 640 ? (char *)alloca((size_t)datasize) : NULL;
    if (_cffi_convert_array_argument(_cffi_type(2), arg0, (char **)&x0,
            datasize, &large_args_free) < 0)
      return NULL;
  }

  x1 = (void(*)(unsigned int, Request *))_cffi_to_c_pointer(arg1, _cffi_type(16));
  if (x1 == (void(*)(unsigned int, Request *))NULL && PyErr_Occurred())
    return NULL;

  Py_BEGIN_ALLOW_THREADS
  _cffi_restore_errno();
  { HandleFunc(x0, x1); }
  _cffi_save_errno();
  Py_END_ALLOW_THREADS

  (void)self; /* unused */
  if (large_args_free != NULL) _cffi_free_array_arguments(large_args_free);
  Py_INCREF(Py_None);
  return Py_None;
}
#else
#  define _cffi_f_HandleFunc _cffi_d_HandleFunc
#endif

static void _cffi_d_ListenAndServe(char * x0)
{
  ListenAndServe(x0);
}
#ifndef PYPY_VERSION
static PyObject *
_cffi_f_ListenAndServe(PyObject *self, PyObject *arg0)
{
  char * x0;
  Py_ssize_t datasize;
  struct _cffi_freeme_s *large_args_free = NULL;

  datasize = _cffi_prepare_pointer_call_argument(
      _cffi_type(2), arg0, (char **)&x0);
  if (datasize != 0) {
    x0 = ((size_t)datasize) <= 640 ? (char *)alloca((size_t)datasize) : NULL;
    if (_cffi_convert_array_argument(_cffi_type(2), arg0, (char **)&x0,
            datasize, &large_args_free) < 0)
      return NULL;
  }

  Py_BEGIN_ALLOW_THREADS
  _cffi_restore_errno();
  { ListenAndServe(x0); }
  _cffi_save_errno();
  Py_END_ALLOW_THREADS

  (void)self; /* unused */
  if (large_args_free != NULL) _cffi_free_array_arguments(large_args_free);
  Py_INCREF(Py_None);
  return Py_None;
}
#else
#  define _cffi_f_ListenAndServe _cffi_d_ListenAndServe
#endif

static int _cffi_d_ResponseWriter_Write(unsigned int x0, char * x1, int x2)
{
  return ResponseWriter_Write(x0, x1, x2);
}
#ifndef PYPY_VERSION
static PyObject *
_cffi_f_ResponseWriter_Write(PyObject *self, PyObject *args)
{
  unsigned int x0;
  char * x1;
  int x2;
  Py_ssize_t datasize;
  struct _cffi_freeme_s *large_args_free = NULL;
  int result;
  PyObject *pyresult;
  PyObject *arg0;
  PyObject *arg1;
  PyObject *arg2;

  if (!PyArg_UnpackTuple(args, "ResponseWriter_Write", 3, 3, &arg0, &arg1, &arg2))
    return NULL;

  x0 = _cffi_to_c_int(arg0, unsigned int);
  if (x0 == (unsigned int)-1 && PyErr_Occurred())
    return NULL;

  datasize = _cffi_prepare_pointer_call_argument(
      _cffi_type(2), arg1, (char **)&x1);
  if (datasize != 0) {
    x1 = ((size_t)datasize) <= 640 ? (char *)alloca((size_t)datasize) : NULL;
    if (_cffi_convert_array_argument(_cffi_type(2), arg1, (char **)&x1,
            datasize, &large_args_free) < 0)
      return NULL;
  }

  x2 = _cffi_to_c_int(arg2, int);
  if (x2 == (int)-1 && PyErr_Occurred())
    return NULL;

  Py_BEGIN_ALLOW_THREADS
  _cffi_restore_errno();
  { result = ResponseWriter_Write(x0, x1, x2); }
  _cffi_save_errno();
  Py_END_ALLOW_THREADS

  (void)self; /* unused */
  pyresult = _cffi_from_c_int(result, int);
  if (large_args_free != NULL) _cffi_free_array_arguments(large_args_free);
  return pyresult;
}
#else
#  define _cffi_f_ResponseWriter_Write _cffi_d_ResponseWriter_Write
#endif

static void _cffi_d_ResponseWriter_WriteHeader(unsigned int x0, int x1)
{
  ResponseWriter_WriteHeader(x0, x1);
}
#ifndef PYPY_VERSION
static PyObject *
_cffi_f_ResponseWriter_WriteHeader(PyObject *self, PyObject *args)
{
  unsigned int x0;
  int x1;
  PyObject *arg0;
  PyObject *arg1;

  if (!PyArg_UnpackTuple(args, "ResponseWriter_WriteHeader", 2, 2, &arg0, &arg1))
    return NULL;

  x0 = _cffi_to_c_int(arg0, unsigned int);
  if (x0 == (unsigned int)-1 && PyErr_Occurred())
    return NULL;

  x1 = _cffi_to_c_int(arg1, int);
  if (x1 == (int)-1 && PyErr_Occurred())
    return NULL;

  Py_BEGIN_ALLOW_THREADS
  _cffi_restore_errno();
  { ResponseWriter_WriteHeader(x0, x1); }
  _cffi_save_errno();
  Py_END_ALLOW_THREADS

  (void)self; /* unused */
  Py_INCREF(Py_None);
  return Py_None;
}
#else
#  define _cffi_f_ResponseWriter_WriteHeader _cffi_d_ResponseWriter_WriteHeader
#endif

static long _cffi_d_loadJson(void)
{
  return loadJson();
}
#ifndef PYPY_VERSION
static PyObject *
_cffi_f_loadJson(PyObject *self, PyObject *noarg)
{
  long result;
  PyObject *pyresult;

  Py_BEGIN_ALLOW_THREADS
  _cffi_restore_errno();
  { result = loadJson(); }
  _cffi_save_errno();
  Py_END_ALLOW_THREADS

  (void)self; /* unused */
  (void)noarg; /* unused */
  pyresult = _cffi_from_c_int(result, long);
  return pyresult;
}
#else
#  define _cffi_f_loadJson _cffi_d_loadJson
#endif

static char * _cffi_d_returnFromJson(long x0, char * x1)
{
  return returnFromJson(x0, x1);
}
#ifndef PYPY_VERSION
static PyObject *
_cffi_f_returnFromJson(PyObject *self, PyObject *args)
{
  long x0;
  char * x1;
  Py_ssize_t datasize;
  struct _cffi_freeme_s *large_args_free = NULL;
  char * result;
  PyObject *pyresult;
  PyObject *arg0;
  PyObject *arg1;

  if (!PyArg_UnpackTuple(args, "returnFromJson", 2, 2, &arg0, &arg1))
    return NULL;

  x0 = _cffi_to_c_int(arg0, long);
  if (x0 == (long)-1 && PyErr_Occurred())
    return NULL;

  datasize = _cffi_prepare_pointer_call_argument(
      _cffi_type(2), arg1, (char **)&x1);
  if (datasize != 0) {
    x1 = ((size_t)datasize) <= 640 ? (char *)alloca((size_t)datasize) : NULL;
    if (_cffi_convert_array_argument(_cffi_type(2), arg1, (char **)&x1,
            datasize, &large_args_free) < 0)
      return NULL;
  }

  Py_BEGIN_ALLOW_THREADS
  _cffi_restore_errno();
  { result = returnFromJson(x0, x1); }
  _cffi_save_errno();
  Py_END_ALLOW_THREADS

  (void)self; /* unused */
  pyresult = _cffi_from_c_pointer((char *)result, _cffi_type(2));
  if (large_args_free != NULL) _cffi_free_array_arguments(large_args_free);
  return pyresult;
}
#else
#  define _cffi_f_returnFromJson _cffi_d_returnFromJson
#endif

_CFFI_UNUSED_FN
static void _cffi_checkfld__Request(Request *p)
{
  /* only to generate compile-time warnings or errors */
  (void)p;
  { char const * *tmp = &p->Method; (void)tmp; }
  { char const * *tmp = &p->Host; (void)tmp; }
  { char const * *tmp = &p->URL; (void)tmp; }
  { char const * *tmp = &p->Body; (void)tmp; }
  { char const * *tmp = &p->Headers; (void)tmp; }
}
struct _cffi_align__Request { char x; Request y; };

static const struct _cffi_global_s _cffi_globals[] = {
  { "Call_HandleFunc", (void *)_cffi_f_Call_HandleFunc, _CFFI_OP(_CFFI_OP_CPYTHON_BLTN_V, 22), (void *)_cffi_d_Call_HandleFunc },
  { "HandleFunc", (void *)_cffi_f_HandleFunc, _CFFI_OP(_CFFI_OP_CPYTHON_BLTN_V, 14), (void *)_cffi_d_HandleFunc },
  { "ListenAndServe", (void *)_cffi_f_ListenAndServe, _CFFI_OP(_CFFI_OP_CPYTHON_BLTN_O, 11), (void *)_cffi_d_ListenAndServe },
  { "ResponseWriter_Write", (void *)_cffi_f_ResponseWriter_Write, _CFFI_OP(_CFFI_OP_CPYTHON_BLTN_V, 4), (void *)_cffi_d_ResponseWriter_Write },
  { "ResponseWriter_WriteHeader", (void *)_cffi_f_ResponseWriter_WriteHeader, _CFFI_OP(_CFFI_OP_CPYTHON_BLTN_V, 27), (void *)_cffi_d_ResponseWriter_WriteHeader },
  { "loadJson", (void *)_cffi_f_loadJson, _CFFI_OP(_CFFI_OP_CPYTHON_BLTN_N, 9), (void *)_cffi_d_loadJson },
  { "returnFromJson", (void *)_cffi_f_returnFromJson, _CFFI_OP(_CFFI_OP_CPYTHON_BLTN_V, 0), (void *)_cffi_d_returnFromJson },
};

static const struct _cffi_field_s _cffi_fields[] = {
  { "Method", offsetof(Request, Method),
              sizeof(((Request *)0)->Method),
              _CFFI_OP(_CFFI_OP_NOOP, 32) },
  { "Host", offsetof(Request, Host),
            sizeof(((Request *)0)->Host),
            _CFFI_OP(_CFFI_OP_NOOP, 32) },
  { "URL", offsetof(Request, URL),
           sizeof(((Request *)0)->URL),
           _CFFI_OP(_CFFI_OP_NOOP, 32) },
  { "Body", offsetof(Request, Body),
            sizeof(((Request *)0)->Body),
            _CFFI_OP(_CFFI_OP_NOOP, 32) },
  { "Headers", offsetof(Request, Headers),
               sizeof(((Request *)0)->Headers),
               _CFFI_OP(_CFFI_OP_NOOP, 32) },
};

static const struct _cffi_struct_union_s _cffi_struct_unions[] = {
  { "Request_", 31, _CFFI_F_CHECK_FIELDS,
    sizeof(Request), offsetof(struct _cffi_align__Request, y), 0, 5 },
};

static const struct _cffi_typename_s _cffi_typenames[] = {
  { "FuncPtr", 18 },
  { "Request", 31 },
  { "ResponseWriterPtr", 5 },
};

static const struct _cffi_type_context_s _cffi_type_context = {
  _cffi_types,
  _cffi_globals,
  _cffi_fields,
  _cffi_struct_unions,
  NULL,  /* no enums */
  _cffi_typenames,
  7,  /* num_globals */
  1,  /* num_struct_unions */
  0,  /* num_enums */
  3,  /* num_typenames */
  NULL,  /* no includes */
  35,  /* num_types */
  0,  /* flags */
};

#ifdef __GNUC__
#  pragma GCC visibility push(default)  /* for -fvisibility= */
#endif

#ifdef PYPY_VERSION
PyMODINIT_FUNC
_cffi_pypyinit_pyGoHttpLib(const void *p[])
{
    p[0] = (const void *)0x2601;
    p[1] = &_cffi_type_context;
#if PY_MAJOR_VERSION >= 3
    return NULL;
#endif
}
#  ifdef _MSC_VER
     PyMODINIT_FUNC
#  if PY_MAJOR_VERSION >= 3
     PyInit_pyGoHttpLib(void) { return NULL; }
#  else
     initpyGoHttpLib(void) { }
#  endif
#  endif
#elif PY_MAJOR_VERSION >= 3
PyMODINIT_FUNC
PyInit_pyGoHttpLib(void)
{
  return _cffi_init("pyGoHttpLib", 0x2601, &_cffi_type_context);
}
#else
PyMODINIT_FUNC
initpyGoHttpLib(void)
{
  _cffi_init("pyGoHttpLib", 0x2601, &_cffi_type_context);
}
#endif

#ifdef __GNUC__
#  pragma GCC visibility pop
#endif
