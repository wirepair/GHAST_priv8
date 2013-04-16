from idautils import *
from idaapi import *

ea = ScreenEA()
for ref in DataRefsTo(ea):
    dis = GetDisasm(ref)
    dis_tuple = dis.split(' ')
    #print dis_tuple
    if dis_tuple[0] == 'mov' and dis_tuple[5].startswith('dword_'):
        print "data ref'd from %s(0x%x)"%(GetFunctionName(ref), ref)
    
for ref in CodeRefsTo(ea, 0):
    dis = GetDisasm(ref)
    dis_tuple = dis.split(' ')
    if dis_tuple[0] == 'mov' and dis_tuple[5].startswith('dword_'):
        print "data ref'd from %s(0x%x)"%(GetFunctionName(ref), ref)


