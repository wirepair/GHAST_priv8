from ctypes import *

offset = 0x2c9d

punk_path = "C:\\GitHub\\GHAST_priv8\\py\\PnkBstrB.exe"
pnk = CDLL(punk_path)
punk_base = windll.kernel32.GetModuleHandleA(punk_path)
print hex(punk_base)

BufArray = create_string_buffer(1024)
addr = punk_base+offset
print "Calling func @ %08x"%addr
#prototype = CFUNCTYPE(c_char_p, POINTER(c_char))(addr)
#print prototype(POINTER(BufArray))
prototype = CFUNCTYPE(c_char_p, c_char_p)(addr)
print prototype(BufArray)
print BufArray
