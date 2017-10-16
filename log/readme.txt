gcc m_log.h m_log.c -shared -o liblog.so
gcc test.c -L. -llog -o test
export LD_LIBRARY_PATH=$(pwd)
