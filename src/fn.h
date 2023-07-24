#ifndef FN_H
#define FN_H

#include <cstdint>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdarg.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>

#define MAX_TEXT_BUFFER_LENGTH 1024
#define MAX_TEXTFORMAT_BUFFERS 4
#define MAX_BLOCKS_LENGHT 26
#define MAX_TYPE_PARAMS_LENGHT 32
#define MAX_BLOCKS_NAME_LENGHT 32

#define Str char*
#define FnBlockS char[MAX_BLOCKS_NAME_LENGHT][MAX_BLOCKS_LENGHT]
#define FNULL FN_NULL

typedef enum {
    FN_INT8,
    FN_UINT8,
    FN_INT16,
    FN_UINT16,
    FN_INT32,
    FN_UINT32,
    FN_NULL,
} FnType;

typedef struct {
    FnType ret;
    FnType* params;
    uint16_t len;
} FnFuncType;

typedef struct {
    Str* blocks;
} FnBlock;

typedef struct {
    Str cgn;
    uint32_t len;
} FnFunc;

typedef struct {
    Str cgn;
    uint32_t len;
} FnDec;

typedef struct {
    bool cl;
    void* param;
} FnCallable;

typedef struct {
    FnType type;
    FnCallable callable;
    Str name;
    void* val;
} FnVal;

typedef struct {
    FILE* fl;
    Str fln;
} FnLLVMOut;

typedef struct {
    Str module;
    Str target;
    FnVal* val;
} FnLLVM;

typedef struct {
    FnLLVMOut ll;
    FnLLVM module;
} FnState;

// Init & Destroy
FnState FnInit(Str, Str);
void FnPInit(FnState*, Str, Str);
void FnDestroy(FnState*);

// Types
Str FnTypeS(FnType);

// Module Manipulation                             //
void FnModuleAddFunc(FnState*, FnFunc);            //  Functions
void FnModuleAddFuncI(FnState*, FnFunc, uint32_t); //

void FnModuleAddVal(FnState*, FnVal);              //  Val

// Declares
FnDec FnDecNew(Str, FnFuncType);

// Funcitons
FnFuncType FnFuncTypeN(FnType, FnType*);
FnBlock FnBlockAppend(Str*);
FnFunc FnFuncNew(Str, FnFuncType);

void FnFuncAddBuilder(FnFunc*, FnType, Str, int32_t, int32_t); // add i32 %arg1, %arg2
void FnFuncAddLLBuilder(FnFunc*, FnType, Str, int64_t, int64_t); //
void FnFuncMulBuilder(FnFunc*, FnType, Str, int32_t, int32_t);
void FnFuncMulLLBuilder(FnFunc*, FnType, Str, int64_t, int64_t);
void FnFuncDivBuilder(FnFunc*, FnType, Str, int32_t, int32_t);
void FnFuncDivLLBuilder(FnFunc*, FnType, Str, int64_t, int64_t);
void FnFuncSubBuilder(FnFunc*, FnType, Str, int32_t, int32_t);
void FnFuncSubLLBuilder(FnFunc*, FnType, Str, int64_t, int64_t);

void FnSysCall(FnFunc*, Str);
void FnCalls(FnFunc*, Str);

// Utils
Str HL_Format(const Str, ...);

#endif
