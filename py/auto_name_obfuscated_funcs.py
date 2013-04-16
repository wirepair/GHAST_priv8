from idautils import *
from idaapi import *

ea = ScreenEA()
func_start = GetFunctionAttr(ScreenEA(), FUNCATTR_START)
func_end = GetFunctionAttr(ScreenEA(), FUNCATTR_END)
done = False
addr = func_start
func_name = ""
run = 0
while addr < func_end:
    #if run > 10:
    #    break
    dis = GetDisasm(addr)
    dis_tuple = dis.split(' ')
    print dis_tuple
    if 'offset' in dis_tuple:
        func_name = dis_tuple[7]
        print "NAME %s"%func_name
    if func_name != "" and len(dis_tuple) == 7:
        print "dis_tuple[0] = %s and dis_tuple[6] = %s"%(dis_tuple[0],dis_tuple[6])
        if dis_tuple[0] == 'mov' and dis_tuple[6] == 'ecx':
            print "going to set: %s to fptr_%s"%(dis_tuple[5],func_name)
            if ('dword_' in dis_tuple[5]):
                write_addr = int(re.match('dword_(.*),', dis_tuple[5]).groups()[0], 16)
                print "%x"%write_addr
                MakeNameEx(write_addr, "fptr_"+func_name, 0)
    addr += ItemSize(addr)
    #run += 1
