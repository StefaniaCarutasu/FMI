/*
 * Windows-specific dynamic library manipulation routines
 */

#include <stdio.h>
#include "bisondynlib.h"

#include "windows.h"


void (*reset_flex_buffer)(void) = NULL;

void * bisondynlib_open(char *filename) {
    HINSTANCE hinstLib;

    hinstLib = LoadLibrary(filename);
    reset_flex_buffer = (void (*)(void)) GetProcAddress(hinstLib, "reset_flex_buffer");
    return (void *)hinstLib;
}

int  bisondynlib_close(void *handle) {
    return FreeLibrary((HINSTANCE)handle);
}

char * bisondynlib_err() {
    return NULL;
}

void bisondynlib_reset(void) {
    if (reset_flex_buffer)
        reset_flex_buffer();
}

char * bisondynlib_lookup_hash(void *handle) {
    char *hash;
    // rules_hash is a pointer, GetProcAddress returns the pointer's address
    // so it needs to be dereferenced
    hash = *((char **)GetProcAddress((HINSTANCE)handle, "rules_hash"));
    return hash;
}

PyObject * bisondynlib_run(void *handle, PyObject *parser, void *cb, void *in, int debug) {
  PyObject *(*pparser)(PyObject *, void *, void *, int);
    pparser = bisondynlib_lookup_parser(handle);
    (*pparser)(parser, cb, in, debug);
    if (PyErr_Occurred()){
        return NULL;
    }
    Py_INCREF(Py_None);
    return Py_None;

}

/*
 * function(void *) returns a pointer to a function(PyObject *, char *) returning PyObject*
 */
PyObject *(*bisondynlib_lookup_parser(void *handle))(PyObject *, void *, void *, int) {
    PyObject *(*pparser)(PyObject *, void *, void *, int);
    pparser = (PyObject *(*)(PyObject *, void *, void *, int))GetProcAddress((HINSTANCE)handle, "do_parse");
    return pparser;
}
