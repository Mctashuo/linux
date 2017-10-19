gcc m_log.h m_log.c -shared -o liblog.so -fPIC
gcc test.c -L. -llog -o test
export LD_LIBRARY_PATH=$(pwd)
