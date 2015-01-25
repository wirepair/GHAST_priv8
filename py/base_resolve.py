base = 0x220e0000
def rez(addr):
    print "%x"%(addr - base+0x10000000)