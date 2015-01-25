#include <iostream>
#include <windows.h>
#include <stdio.h>
#include "zlib.h"

void print_chars(char *out_buf, int size)
{
	for (int i = 0; i < size; i++)
	{
		printf("%02x ", (BYTE)out_buf[i]);		
	}
	printf("\r\n");
	for (int i = 0; i < size; i++)
	{
		printf("%c", out_buf[i]);
	}
	printf("\r\n");
}

char * get_encoded_data(FILE *f, const int offset, const int size)
{
	int ret;
	char *data = (char *)calloc(size,sizeof(char));
	if (data == NULL)
	{
		printf("Error allocating space for data of get_encoded_data.\r\n");
		exit(-1);
	}
	ret = fseek(f, offset, SEEK_SET);
	printf("fseek ret: %d\r\n", ret);
	ret = fread(data, sizeof(char), size, f);
	printf("fread ret: %d\r\n", ret);
	return data;
}

char * pbcl_decode(char *outbuf, int buf_len, char *in_buf, int key_or_sessid)
{
	WORD randop;
	int i;
	int new_randop;
	char prev_char;
	char result_char; 
	int buf_len_minus_one;

	randop = key_or_sessid ^ 0x4a38;
	buf_len_minus_one = buf_len-1;
	for (i = 0; i < buf_len_minus_one; ++i)
	{
		if ( i || randop != key_or_sessid )
		{
			new_randop = 9421 * randop + 1;
		}
		else
		{
			new_randop = randop ^ 0x5B866694;
		}
		prev_char = key_or_sessid;
		randop = new_randop;
		if ( i )
		{
			prev_char = outbuf[i-1];
		}
		result_char = in_buf[i] - prev_char * ((unsigned int)new_randop >> 2);
		outbuf[i] = result_char;
		if (!result_char)
		{
			break;
		}
	}
	outbuf[i] = 0;
	return outbuf;
}



void decode(FILE *f, int offset, int size, int key)
{
	char *out_buf = (char *)calloc(size,sizeof(char));
	char *data = get_encoded_data(f, offset, size);
	if (out_buf == NULL)
	{
		printf("Error allocating space for out_buf of decode.\r\n");
		exit(-1);
	}
	pbcl_decode(out_buf, size, data, key);
	print_chars(out_buf, size);
	free(data);
	free(out_buf);
}

void read_and_decompress(FILE *f, int offset, int size, int output_size, char *key, char *output_path)
{
	FILE *out;
	int idx = 0;
	int err = 0;
	int key_len = strlen(key);
	char *data = (char *)calloc(size, sizeof(char));
	if (data == NULL)
	{
		printf("Error allocating data for read_and_decompress");
		exit(-1);
	}
	char *output = (char *)calloc(output_size, sizeof(char));
	if (data == NULL)
	{
		printf("Error allocating output for read_and_decompress");
		exit(-1);
	}
	data = get_encoded_data(f, offset, size);
	for (; idx < size; ++idx)
	{
		data[idx] ^= key[idx%key_len];
		if (idx < 5)
		{
			printf("%02x ", (BYTE)data[idx]);
		}
	}
	err = uncompress((Bytef *)output, (uLongf *)&output_size, (Bytef *)data, size);
	printf("uncompress return code: %d\r\n", err);
	for (idx = 0; idx < 5; idx++)
	{
		printf("%02x ", (BYTE)output[idx]);
	}
	out = fopen(output_path, "wb");
	fwrite(output, sizeof(char), output_size, out);
	fclose(out);
	free(data);
	free(output);

}
int main(int argc, char **argv)
{
	FILE *f;
	
	f = fopen("C:\\GitHub\\Sync\\idbs\\06072013\\pbcl.dll", "rb");
	
	/*
	decode(f, 0x630AC, 0x64, 0x3A13);
	decode(f, 0x63158, 0x12, 0x110F);
	decode(f, 0x6314C, 0x18, 0x388D);
	decode(f, 0x630D4, 0x64, 0x1BB1);
	
	decode(f, 0x6314C, 0x18, 0x388D);
	decode(f, 0x6324C, 0x12B, 0x9E1);
	decode(f, 0x63204, 0xA0, 0x13BA);	
	decode(f, 0x631C4, 0xff, 0x7867);
	decode(f, 0x631F0, 0x96, 0x3B2F);
	decode(f, 0x631DC, 0x96, 0x5F39);
	decode(f, 0x631A4, 0xc8, 0x2974);
	decode(f, 0x63224, 0xC8, 0x2BC1);
	*/
	decode(f, 0x6310C, 0x65, 0xda);
	// PnkBstrA
	//read_and_decompress(f, 0x63280, 0x9DCA, 0x12C58, "2304", "C:\\temp\\pnkbstra.exe");
	// PnkBstrB
	//read_and_decompress(f, 0x6D058, 0x24973, 0x44DF8, "2304", "C:\\temp\\pnkbstrb.exe");
	
	// PnkBstrK.sys
	//read_and_decompress(f, 0x919D8, 0x18C41, 0x220A0, "2304", "C:\\temp\\pnkbstrk.sys");
	fclose(f);
	
}
int stuff()
{
	FILE *f;
	f = fopen("C:\\GitHub\\Sync\\idbs\\06072013\\pbns.dat", "rb");
	char *data;
	char key[9] = {0};
	int size = 0;
	int key_len = 0;
	int idx = 0;
	int i = 0;
	if (f == NULL)
	{
		printf("null");
		return -1;
	}
	//_snprintf(key, 9, "%lu", 2304);
	_snprintf(key, 9, "%s", "bfp4f");
	fseek(f, 0, SEEK_END);
	size = ftell(f);
	fseek(f, 0, SEEK_SET);
	
	data = (char *)malloc(size*sizeof(char));
	key_len = strlen(key);
	fread(data, sizeof(char), size, f);
	printf("size: %d key_len: %d\r\n", size, key_len);
	for (; idx < size; ++idx)
	{
		printf("\\x%02x", (BYTE)data[idx]);
		data[idx] ^= key[idx%key_len];
	}
	for (; i < size; ++i)
	{
		//printf("%02x", (BYTE)data[i]);
	}

	return 0;
}