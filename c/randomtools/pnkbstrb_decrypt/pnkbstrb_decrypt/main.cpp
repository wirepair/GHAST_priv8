#include <windows.h>
#include <stdio.h>

int main(int argc, char **argv)
{
	unsigned idx = 0;
	unsigned char buf[] = "\x8C\xD8\x95\xA2\xFF\xAA\x94\x65\x23\x0D\x66\x06\x60\x99\xBC\x7E\xAA\xBB\xD2\xD6\xFC\x43\x86\x19\xCB\x3A\xDE\x7C\x95\x98\xF7\xBC\xC4\x58\xAB\xFB\x05\xAA\x14\x16\x79\x66\x5E\x1E\x01\x57\x16\xF7\xA8\xEE\xB3\x02\xD5\x07\xDE\xDB\x0D\x60\xE8\xAC\x73\x4C\x3A\x66\x09\xC7\x53";
	unsigned char *bufptr;
	unsigned buf_len = sizeof(buf);

	unsigned char output[1400] = {0};
	DWORD key = 0xcc82199c;
	DWORD randop = 0x24A7AC37 - 0x345A59E0 * key;
	DWORD shr_result = 0;
	DWORD decrypt_key = randop ^ sizeof(buf);
	DWORD ebp_save = 0;
	bufptr = buf;

	printf("randop: %08x sizeof encrypted buf: %x decrypt_key: %08x\n", randop, sizeof(buf), decrypt_key);
	for (int i = 0; i < sizeof(buf); i++)
	{
		printf("%c ", buf[i]);
	}
	__asm {
		mov ecx, decrypt_key // move our key into ecx
		mov edi, buf_len // sizeof(buf)
		lea esi, buf // move buf addr into esi
		lea eax, buf // move buf addr into eax
		xor edx, edx // clear edx
decrypt:
		imul ecx, 24CDh      //; ecx = new_randopkey
        lea eax, [edx+buf]
		mov bufptr, eax // ; mov addr of encrypted buff to stack
		inc ecx
		mov eax, ecx
		shr eax, 2
		mov bl, 0Dh
		imul bl
		mov bl, al
		mov al, dl
		add al, 43h
		mov dl, 0EFh
		imul dl
		mov dl, al
		mov eax, bufptr
		sub dl, bl
		add [eax], dl
		mov edx, idx
		inc edx             //; char *
		cmp edx, buf_len
		mov idx, edx
		jl short decrypt //; ecx = new_randopkey
	}
	/*
	do
	{
		decrypt_key = 9421 * decrypt_key + 1;
		shr_result = decrypt_key >> 2;
		buf[idx] = 239 * (buf[idx] + 67) - 13 * shr_result;
		idx++;
	} while(idx < sizeof(buf));
	*/
	for (int i = 0; i < sizeof(buf); i++)
	{
		printf("%c ", buf[i]);
	}
	printf("\n");
}