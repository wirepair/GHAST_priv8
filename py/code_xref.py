from idautils import *
ea = ScreenEA()
for ref in DataRefsTo(ea):
    print "data ref'd from %s(0x%x)"%(GetFunctionName(ref), ref)

for ref in CodeRefsTo(ea, 0):
    print "code ref'd from %s(0x%x)"%(GetFunctionName(ref), ref)

    
