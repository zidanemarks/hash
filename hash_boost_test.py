#! /usr/bin/env python
import sys, os
from ctypes import *
cur_path=os.getcwd()
lib_path=cur_path+"/bin/"
sys.path.append(lib_path)
modules = lib_path+'/keyvaluehash.so'
assert(os.path.exists(modules)), "no hash module dynamic object generate"
import keyvaluehash

raw = "hello world , Across the Great Wall we can reach every corner of the world"
_len = len(raw)
seed = 0

print hex(keyvaluehash.RSHash(raw))
print hex(keyvaluehash.SDBMHash(raw))
print hex(keyvaluehash.JSHash(raw))
print hex(keyvaluehash.PJWHash(raw))
print hex(keyvaluehash.ELFHash(raw))
print hex(keyvaluehash.BKDRHash(raw))
print hex(keyvaluehash.DJBHash(raw))
print hex(keyvaluehash.APHash(raw))
print hex(keyvaluehash.PyMurmurHash64A(raw, _len, seed))
print hex(keyvaluehash.PyMurmurHash2(raw, _len, seed))




