#include <windows.h>
#include <stdio.h>
#define _BYTE BYTE
#define _DWORD DWORD
#define _WORD WORD

int __cdecl sub_40C6A0(char *a1)
{
  char *v1; // edx@1
  int result; // eax@1
  char v3; // cl@2

  v1 = a1;
  result = 0;
  while ( 1 )
  {
    v3 = *(_BYTE *)v1;
    if ( *(_BYTE *)v1 == '-' )
      goto LABEL_6;
    if ( v3 < '0' || v3 > '9' )
      return result;
    result = v3 + 10 * result - 48;
LABEL_6:
    ++v1;
  }
}

char __cdecl pb_strcpy(char *a1, char *a2)
{
	char *i; // ecx@1
	char *j; // edx@4
	char result; // al@6

	for ( i = a1; *(_BYTE *)i; ++i );
	printf( "i; %08x\r\n", i);
	for ( j = a2; ; ++j )
	{
		result = *(_BYTE *)j;
		printf("result: %c\r\n", result);
		if ( !*(_BYTE *)j )
		{
		  break;
		}
		*(_BYTE *)i++ = result;
	}
	*(_BYTE *)i = 0;
	printf("%s\r\n", a1);
	return result;
}

int __cdecl pb_atoi(char *a1)
{
	char *v1; // edx@1
	int result; // eax@1
	char v3; // cl@2

	v1 = a1;
	result = 0;
	while ( 1 )
	{
		v3 = *(_BYTE *)v1;
		if ( *(_BYTE *)v1 == '-' )
		{
			++v1;
			continue;
		}
		if ( v3 < '0' || v3 > '9' ) 
		{
			return result;
		}
		result = v3 + 10 * result - 48;
		++v1;
	}
}

int __cdecl sub_406EA1(char *a1)
{
  char *v1; // edx@1
  int result; // eax@1
  char *v3; // esi@2
  int v4; // edi@3
  char v5; // cl@3
  bool v6; // zf@3
  int v7; // [sp+8h] [bp+8h]@2

  v1 = a1;
  result = *(_DWORD *)(a1 + 8);
  if ( *(_BYTE *)(a1 + 4) - 4 > 0 )
  {
    v3 = a1 + 44;
    v7 = *(_BYTE *)(a1 + 4) - 4;
    do
    {
      v4 = *(_WORD *)v3;
      v5 = *(_WORD *)v3 & 3;
      v3 += 2;
      v6 = v7-- == 1;
      result = v4 ^ ((unsigned int)result >> 24) ^ (result << v5);
    }
    while ( !v6 );
  }
  if ( !result )
    result = *(_DWORD *)(v1 + 28);
  return result;
}
int __cdecl pb_unk_xor_or_shift_by_eight(DWORD *a1)
{
  //return *(_BYTE *)a1 ^ *(_BYTE *)(a1 + 2) | ((*(_BYTE *)(a1 + 1) ^ *(_BYTE *)(a1 + 3)) << 8);
	int x = 0;
	__asm {
	mov     ecx, dword ptr [a1]
    movzx   edx, byte ptr [ecx+1]
	movzx   eax, byte ptr [ecx+3]
	xor     eax, edx
    movzx   edx, byte ptr [ecx+2]
    movzx   ecx, byte ptr [ecx]
    shl     eax, 8
    xor     edx, ecx
    or      eax, edx
	mov     x, eax
	}
	return x;
}

int __cdecl pb_unk_calculation(void *a1)
{
  void *v1; // edx@1
  int result; // eax@1
  char *v3; // esi@2
  int v4; // edi@3
  char v5; // cl@3
  bool v6; // zf@3
  int v7; // [sp+8h] [bp+8h]@2

  v1 = a1;
  result = *((_DWORD *)a1 + 2);
  if ( *((_BYTE *)a1 + 4) - 4 > 0 )
  {
    v3 = (char *)a1 + 44;
    v7 = *((_BYTE *)a1 + 4) - 4;
    do
    {
      v4 = *(_WORD *)v3;
      v5 = *(_WORD *)v3 & 3;
      v3 += 2;
      v6 = v7-- == 1;
      result = v4 ^ ((unsigned int)result >> 24) ^ (result << v5);
    }
    while ( !v6 );
  }
  if ( !result )
    result = *((_DWORD *)v1 + 7);
  return result;
}

int __cdecl sub_10001342(char *a1)
{
  char *buf; // edx@1
  int result; // eax@1
  char chr; // cl@2

  buf = a1;
  result = 0;
  while ( 1 )
  {
    chr = *buf;
    if ( *buf == '-' )
      goto out;
    if ( chr < '0' || chr > '9' )
      return result;
    result = chr + 10 * result - 48;
out:
    ++buf;
  }
}

int main(int argc, char ** argv) 
{
	
	//int ret = sub_40C6A0("134a");
	DWORD zonks = 0x0ffc458b;
	int idx = 0;
	printf("%d\n", sub_10001342("0xff"));
	BYTE *dwRandBuffPtr = (BYTE *)malloc(1500);
	if ( dwRandBuffPtr )
    {
		do
			*((_BYTE *)dwRandBuffPtr + idx++) = rand();
		while ( idx < 1500 );
    }
	printf("%x %x", dwRandBuffPtr[0], dwRandBuffPtr[1]);
	//printf("%x\r\n", pb_unk_xor_or_shift_by_eight(&zonks));

	/* pb_atoi
	int ret = pb_atoi("134a");
	printf( "ret: %d\r\n", ret, ret );
	*/

	/*
	pb_strcpy
	char *str1 = (char *)malloc(25 * sizeof(char));
	memset(str1, 0x0, 25);
	char str2[25] = "fdass";
	strcpy(str1, "bonk");
	char ret = pb_strcpy(str1, str2);
	printf( "ret: %c %s %s\r\n", ret, str1, str2 );
	*/
	return 0;
}