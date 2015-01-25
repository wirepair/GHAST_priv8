xor_idx = 0
def x(xor_with):
    return Name(LocByName("fptr_table")+(xor_with)*4)