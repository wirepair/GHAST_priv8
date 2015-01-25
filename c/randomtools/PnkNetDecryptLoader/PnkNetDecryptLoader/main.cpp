#include <windows.h>
#include <stdio.h>

typedef int (__cdecl *DECRYPT)(int sender_flag, char *input_buffer, unsigned int size, int packet_index, unsigned char** output_buffer, unsigned int* output_size);
typedef int (__cdecl *INIT)(void);

void baleete(unsigned char *output)
{
	if (output != NULL)
		LocalFree(output);
}
int main(int argc, char **argv)
{
	HMODULE decryptor = LoadLibraryA("C:\\GitHub\\GHAST\\tests\\PnkNetDecryptor\\Release\\PnkNetDecryptor.dll");
	INIT init;
	DECRYPT decrypt;
	char buf1[] = {97,98,49,101,97,101,100,97,57,0};
	char buf2[] = {97,101,55,101,101,100,56,97,56,0};
	char buf3[] = {104,57,101,48,54,99,54,52,102,0};
	char buf4[] = {104,70,69,51,54,69,66,52,54,65,55,69,49,50,53,49,65,66,53,69,57,70,57,53,49,49,68,68,68,69,52,51,52,0};
	unsigned char buf5[] = {101,101,55,101,101,100,56,97,56,32,4,242,203,118,247,66,76,189,155,37,158,222,88,49,116,214,34,211,10,174,244,219,62,113,67,82,22,84,141,48,175,20,60,112,227,211,253,66,204,110,241,126,150,246,249,239,206,79,32,6,235,218,205,159,150,51,133,120,32,132,107,228,242,190,129,223,139};
	unsigned char buf6[] = {101,101,55,101,101,100,56,97,56,32,9,31,207,118,247,49,71,153,102,231,158,207,70,8,70,159,21,136,202,130,24,155,47,146,67,254,230,92,163,241,126,230,4,119,179,147,243,7,191,45,228,108,103,164,207,223,234,54,31,36,241,155,139,117,121,247,82,105,224,72,49,185,250,126,56,156,139};
	unsigned char buf7[] = {101,101,55,101,101,100,56,97,56,32,162,74,30,182,76,161,200,54,95,118};
	unsigned char *out = NULL;
	unsigned char *output = NULL;
	unsigned int output_size = 0;
	if (decryptor != NULL)
	{
		
		init = (INIT)GetProcAddress(decryptor, "init");
		decrypt = (DECRYPT)GetProcAddress(decryptor, "decrypt");
		init();
		printf("Decrypt: %p out: %p\n", output, out);
		decrypt(1, buf1, 10, 0, &output, &output_size);
		baleete(output);
		decrypt(0, buf2, 10, 0, &output, &output_size);
		baleete(output);
		decrypt(1, buf3, 10, 1, &output, &output_size);
		baleete(output);
		decrypt(0, buf4, 34, 1, &output, &output_size);
		baleete(output);
		//decrypt(1, (char *)buf5, 77, 3, &output, &output_size);
		//baleete(output);
		decrypt(1, (char *)buf7, 20, 6, &output, &output_size);
		
	}
}