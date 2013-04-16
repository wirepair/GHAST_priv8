#!/usr/bin/env python
import subprocess

import idaapi
from idautils import *
from idc import *

failed = True
loader = "C:\\GitHub\\GHAST_priv8\\py\\PnkDecoder.exe"
filepath = GetInputFilePath()
ea = ScreenEA()


print "Using: %s"%filepath
func = idaapi.get_func(ea).startEA

#screw you non-relocatable PE file.
for i in xrange(0, 100):
    proc = subprocess.Popen([loader, filepath, hex(func)],
                            stdout=subprocess.PIPE, 
                            stderr=subprocess.STDOUT)
    out = proc.communicate()
    if proc.returncode == 0:
        comment = "result = %s"%out[0]
        print "Successfully decoded %s"%comment
        SetFunctionCmt(func, comment, 1)
        failed = False
        break

if failed:
    print "Failed, please try again!"
