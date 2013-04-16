from idautils import *
ea = ScreenEA()
for ref in DataRefsTo(ea):
    print "ref'd from %s(0x%x)"%(GetFunctionName(ref), ref)
    
