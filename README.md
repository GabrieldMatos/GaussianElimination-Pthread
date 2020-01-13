This is an implementation of a parallel algorithm using the Pthread C library for the resolution of linear systems using the gauss method.

**to compile**:

- gcc gaussInit.c pthreadTest.c -o gauss_test -lpthread

**to execute**:

- ./gauss_test <#threads> < dimensao da matriz> < rand seed>
