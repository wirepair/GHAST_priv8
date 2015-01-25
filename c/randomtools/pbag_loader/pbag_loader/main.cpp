#include <iostream>
#include <windows.h>
#include <winbase.h>
#include "zlib.h"

// unk_code (server) 357AFE48
// unk_code (client) 264B8BD3
typedef int (__cdecl *fptr_a)(int *server_cli_flag, int op_code, char *ptr_or_null, void *pointer);
using namespace std;

#define SET_PTR 81
#define CALL_RPM 76
#define GET_VERSION 77
#define GET_B050_ADDR 85
#define GET_0x2712 0x2712
#define GET_0x2711 0x2711
#define GET_0x2700 0x2700

int main(int argc, char **argv)
{
	/* pbag real calls */
	char *unk;
	char *encoded_zlib_data = 0;
	int source_len = 0;
	int uncompressed_size = 0;
	char *pbag_zlib_data = 0;
	char *key_and_uncompressed_data = 0;
	int len;


	int result;
	int server = 0x357AFE48;
	int client = 0x264B8BD3;
	int *pids[400] = {0}; 
	int pid = GetCurrentProcessId();
	char *unk_ = "w";
	char *ptr = "\0";//"2569EB6F7B4B";


	HMODULE pbagz = LoadLibrary(L"C:\\GitHub\\Sync\\idbs\\pbag.dll");
	fptr_a pbag_a;
	
	pbag_a = (fptr_a)GetProcAddress(pbagz, "a");
	
	unk = (char *)pbag_a(0, 84, 0, 0); // ret = 2
    source_len = pbag_a(0, 82, 0, 0); // ret = 80

    uncompressed_size = pbag_a(0, 83, 0, 0);       // ret = 94
    pbag_zlib_data = (char *)pbag_a(0, 85, 0, 0); // ret = base+0xb050 (zlib data)
	
	encoded_zlib_data = (char *)malloc(source_len+1);
	memset(encoded_zlib_data, 0, source_len);
	key_and_uncompressed_data = (char *)malloc(uncompressed_size+1);
	memset(key_and_uncompressed_data, 0, uncompressed_size);

	memcpy(encoded_zlib_data, pbag_zlib_data, source_len);
	
	strncpy(key_and_uncompressed_data, "bfp4f", 0x40);
	len = strlen(key_and_uncompressed_data);
	for (int idx = 0; idx < source_len; ++idx)
	{
		encoded_zlib_data[idx] ^= key_and_uncompressed_data[idx%len];
	}
	
	printf("Uncompressing...\r\n");
	int err = uncompress((Bytef *)key_and_uncompressed_data, (uLongf *)&uncompressed_size, (const Bytef *)encoded_zlib_data, source_len);
	printf("err: %d\r\n", err);
	
	printf("\r\n");
	for (int i = 0; i < uncompressed_size; i++)
	{
		printf("%c", (BYTE)key_and_uncompressed_data[i]);
	}
	return 0;
}


/*

	char *finished = "FINISHED";
	for (int i = 0; i < 400; i++)
	{
		pids[i] = &pid;
	}
	
	result = pbag_a(0, GET_VERSION, 0, 0);
	printf("pbag version: %d\r\n", result);

	result = pbag_a(0, 83, 0, 0); // 94
	printf("pbag: %d\r\n", result);

	result = pbag_a(0, 84, 0, 0); // 2
	printf("pbag: %d\r\n", result);
	
	result = pbag_a(0, 82, 0, 0); // 80
	printf("pbag: %d\r\n", result);

	result = pbag_a(0, 79, 0, 0); // 0
	printf("pbag: %d\r\n", result);

	result = pbag_a(0, GET_B050_ADDR, 0, 0); // 0
	printf("pbag: %08x\r\n", result);
		
	result = pbag_a(0, GET_B050_ADDR, 0, 0); // 0
	printf("pbag: %08x\r\n", result);
	//result = pbag_a(&client, GET_0x2711, 0, unk_);
	//printf("pbag: %s\r\n", result);

		//result = pbag_a(&client, GET_code1, 0, 0);
	//printf("pbag: %s\r\n", result);

		//result = pbag_a(0, SET_PTR, 0, pids);

	//result = pbag_a(&client, CALL_RPM, 0, (int *)unk_);
	//printf("pbag: %s\r\n", result);

*/