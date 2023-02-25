extern "C" {
int _write( int handle, char *buf, int count) {
    //Serial2.write(buf, count);
    return count;
}
};
#include <new>
namespace std {
    const std::nothrow_t nothrow;
}
void* operator new(unsigned int size, std::nothrow_t const&){ return malloc(size);}
void* operator new[](unsigned int size, std::nothrow_t const&){ return malloc(size);}
