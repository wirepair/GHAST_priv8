from idautils import *
from idc import *
from idaapi import *
ea = ScreenEA()
print "Searching 0x%x..."%ea
for xref in XrefsTo(ea, 0):
    ref_type = ""
    if xref.type == dr_W:
        ref_type = "W"
    elif xref.type == dr_R:
        ref_type = "R"
    else:
        ref_type = "Unknown"
    print "%s(0x%x) | %s"%(GetFunctionName(xref.frm), xref.frm, ref_type)

