#include <windows.h>
#include <stdio.h>

// actually pbcl.dll doesn't take a char * arg, but w/e it works 
// by reading the returned ptr.
typedef char * (__cdecl *PB_ENCSTRING)(char *);

// Since they don't relocate .data we have to load the
// stupid file and make sure the base address is the same
// since the direct references won't get updated, we'll crash
// if it's not loaded at the address the ImageBase is set to.
unsigned int GetPEBaseAddress(const char *inputfile)
{
	PIMAGE_DOS_HEADER dosHeader; 
	PIMAGE_NT_HEADERS ntHeader;
	HANDLE hMapObject, hFile;
	LPVOID lpBase;
	unsigned int base;
	hFile = CreateFileA(inputfile, 
				       GENERIC_READ,
					   FILE_SHARE_READ,
					   NULL,
					   OPEN_EXISTING,
					   FILE_ATTRIBUTE_NORMAL,
					   NULL);
	
	hMapObject = CreateFileMapping( hFile, NULL, PAGE_READONLY, 0, 0, NULL );
    lpBase = MapViewOfFile( hMapObject, FILE_MAP_READ, 0, 0, 0 );
    dosHeader = (PIMAGE_DOS_HEADER)lpBase;
	if( dosHeader->e_magic != IMAGE_DOS_SIGNATURE )
	{
		base = 0;
	} 
	else
	{
		ntHeader = (PIMAGE_NT_HEADERS)( (DWORD)(dosHeader) + (dosHeader->e_lfanew) );
		base = ntHeader->OptionalHeader.ImageBase;
	}
	UnmapViewOfFile( lpBase );
    CloseHandle( hMapObject );
	CloseHandle( hFile );
	return base;
}

int main( int argc, char **argv )
{
	PB_ENCSTRING DecoderFunction;
	int functionAddress = 0;
	HMODULE hModule;
	char *pnkbstr = 0;
	char data[1024] = {0};
	unsigned int imageBase = 0;
	char *end = 0;
	char *ret = 0;

	if ( argc != 3 )
	{
		printf( "Usage: %s <path_to_binary> <address_of_xor_decoder_func_in_hex>" );
		return -1;
	}
	pnkbstr = argv[1];
	functionAddress = strtol( argv[2], &end, 16 );
	hModule = LoadLibraryA( pnkbstr );
	if ( hModule == NULL ) 
	{
		return -1;
	}
	imageBase = GetPEBaseAddress( pnkbstr );
	if ( (int)hModule != imageBase )
	{
		FreeLibrary( hModule );
		printf( "ERROR: module must be loaded at %08x got %08x instead, try again.", imageBase, (int)hModule );
		return -1;
	}
	DecoderFunction = (PB_ENCSTRING)functionAddress;
	ret = DecoderFunction( data );
	printf("%s", ret);
	FreeLibrary( hModule );
	return 0;
}