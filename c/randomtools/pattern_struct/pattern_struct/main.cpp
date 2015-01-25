#include <windows.h>


typedef struct _pattern_t {
	DWORD first_four_bytes;
	WORD _unused;
    BYTE type_code;
    BYTE pattern_byte_length;
    DWORD _unk2;
    DWORD additional_pattern_offset;
    DWORD additional_maybe_size;
    DWORD marker;
    WORD pattern_code;
    WORD _unk6;
    WORD pattern_offset;
    DWORD _unk7;
    DWORD _unk8;
    WORD pattern_data[124];
} pattern_s;
int main(int argc, char **argv)
{
	pattern_s p1;
	memset(&p1, 0x0, sizeof(p1));
	p1.first_four_bytes = "0x8B45FC0F";
	p1._unused = 0x0000;
	p1.type_code = 0x77;
	p1.pattern_byte_length = 0x16;
	p1._unk2 = 0x0000;
	p1.additional_pattern_offset = 0x00000000;
	p1.additional_maybe_size = 0x00000000;
	p1.marker = 0xffffffff;


//------------------------------------------------------------
//-----------       Created with 010 Editor        -----------
//------         www.sweetscape.com/010editor/          ------
//
// File    : C:\Tools\pattern.dump
// Address : 292 (0x124)
// Size    : 84 (0x54)
//------------------------------------------------------------
unsigned char hexData[84] = {
    0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x7A, 0xE6, 0x00, 0x00,
    0xA6, 0x16, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0xBE, 0x00, 0x08, 0x00,
    0x85, 0x00, 0xC9, 0x00, 0x74, 0x00, 0x3D, 0x00,
    0x8B, 0x00, 0x55, 0x00, 0x08, 0x00, 0x0F, 0x00,
    0xBE, 0x00, 0x02, 0x00, 0x8B, 0x00, 0x4D, 0x00,
    0xFC, 0x00, 0x0F, 0x00, 0xBE, 0x00, 0x11, 0x00,
    0x00, 0x00, 0x00, 0x00 
};

}