
#include "hash_boost_wrapper.h"

using namespace boost::python;
using namespace std;


uint64_t PyMurmurHash64A(char *str,  int len, unsigned int seed){
  return MurmurHash64A(str, len, seed);
};

uint32_t PyMurmurHash2(char *str,  int len, unsigned int seed){
  return MurmurHash2(str, len, seed);
};


BOOST_PYTHON_MODULE(keyvaluehash) 
{
    //python boost package declaration
    def("PyMurmurHash64A", PyMurmurHash64A, args("str", "len", "seed"), "murmur 64 hash func");
    def("PyMurmurHash2", PyMurmurHash2, args("str"), "murmur 32 hash func");
    def("RSHash", RSHash, args("str"), "RS hash func");
    def("SDBMHash", SDBMHash, args("str"), "SDBM hash func");
    def("JSHash", JSHash, args("str"), "JS hash func");
    def("PJWHash", PJWHash, args("str"), "PJW hash func");
    def("ELFHash", ELFHash, args("str"), "ELF hash func");
    def("BKDRHash", BKDRHash, args("str"), "BKDR hash func");
    def("DJBHash", DJBHash, args("str"), "DJB hash func");
    def("APHash",  APHash, args("str"), "AP hash func");
}
