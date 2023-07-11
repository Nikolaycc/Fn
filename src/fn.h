#ifndef FN_H
#define FN_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>

#define MAX_TEXT_BUFFER_LENGTH 1024
#define MAX_TEXTFORMAT_BUFFERS 4

#define Str char*

typedef enum {
    FN_INT8,
    FN_UINT8,
    FN_INT16,
    FN_UINT16,
    FN_INT32,
    FN_UINT32,
} FnType;

typedef struct {
    bool cl;
    void** param;
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

FnState FnInit(Str, Str);
void FnPInit(FnState*, Str, Str);
void FnDestroy(FnState*);

// utils
Str HL_Format(const Str, ...);

#endif
