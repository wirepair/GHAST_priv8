from idaapi import *
from idc import *


start = SelStart()
end = SelEnd()
xor_list = []
xor_lines = {}
def unxor(xor_with):
    return Name(LocByName("fptr_table")+(xor_with)*4)

for i in Heads(start, end):
    try:
        if GetMnem(i) == "lea" and "fptr_table" not in GetOpnd(i, 1) and "ebp" not in GetOpnd(i, 1) and "+" in GetDisasm(i) and GetOperandValue(i, 1) > 0xFFFFF:
            print GetOperandValue(i, 1)
            xor_list.append(GetOperandValue(i, 1))
            xor_lines[GetOperandValue(i, 1)] = i
    except:
        pass
xor_list.sort()
print "----"
if ( len(xor_list) % 2 != 0):
    print "List isn't divisible by two"
else:
    for i in xrange(0, len(xor_list), 2):
        function_name = unxor(xor_list[i]^xor_list[i+1])
        if (xor_lines[xor_list[i+1]] > xor_lines[xor_list[i]]):
            MakeRptCmt(xor_lines[xor_list[i+1]], function_name)
        else:
            MakeRptCmt(xor_lines[xor_list[i]], function_name)
