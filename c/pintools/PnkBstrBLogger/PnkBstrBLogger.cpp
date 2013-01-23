#include "pnkbstrblogger.h"

KNOB<string> KnobOutputFile(KNOB_MODE_WRITEONCE, "pintool",
                "o", "donks.log", "specifity trace file name");
KNOB<BOOL>   KnobAsciiMode(KNOB_MODE_WRITEONCE, "pintool", "a", "0", "prints ascii only");

// Replacements
// UDP
static WINDOWS::INT replacementUDP(
	AFUNPTR functionUDP,
	WINDOWS::SOCKET s,
	WINDOWS::CHAR *buf,
	WINDOWS::INT len,
	WINDOWS::INT flags,
	WINDOWS::SOCKADDR *from,
	WINDOWS::INT *fromlen,
	WINDOWS::CHAR *functionName,
	CONTEXT *ctx)
{
	WINDOWS::INT retval;

	PIN_CallApplicationFunction(
		ctx, 
		PIN_ThreadId(),
		CALLINGSTD_STDCALL, functionUDP,
		PIN_PARG(WINDOWS::INT), &retval,
		PIN_PARG(WINDOWS::SOCKET), s,
		PIN_PARG(WINDOWS::CHAR *), buf,
		PIN_PARG(WINDOWS::INT), len,
		PIN_PARG(WINDOWS::INT), flags,
		PIN_PARG(WINDOWS::SOCKADDR *), from,
		PIN_PARG(WINDOWS::INT *), fromlen,
		PIN_PARG_END()
		);

	if ( retval != -1 ) 
	{
		fprintf( LogFile, "%s [%d]:\r\n", functionName, retval );
		fprintf( LogFile, "{\r\n" );
		PrintHexBuffer( buf, retval, KnobAsciiMode );
		fprintf( LogFile, "}\r\n" );
	}
	return retval;
}


// TCP
static WINDOWS::INT replacementTCP(
	AFUNPTR functionTCP, 
	WINDOWS::SOCKET s,
	WINDOWS::CHAR *buf,
	WINDOWS::INT len,
	WINDOWS::INT flags,
	WINDOWS::CHAR * functionName,
	CONTEXT * ctx)
{
	WINDOWS::INT retval;

	PIN_CallApplicationFunction(
		ctx, 
		PIN_ThreadId(),
		CALLINGSTD_STDCALL, functionTCP, // send or recv
		PIN_PARG(WINDOWS::INT), &retval, // return value first
		PIN_PARG(WINDOWS::SOCKET), s, 
		PIN_PARG(WINDOWS::CHAR *), buf,
		PIN_PARG(WINDOWS::INT), len,
		PIN_PARG(WINDOWS::INT), flags,
		PIN_PARG_END()
		);

	if ( retval != -1 ) 
	{
		fprintf( LogFile, "%s [%d]:\r\n", functionName, retval );
		fprintf( LogFile, "{\r\n" );
		PrintHexBuffer( buf, retval, KnobAsciiMode );
		fprintf( LogFile, "}\r\n" );
	}
	return retval;
}

// Helper Functions

VOID PrintHexBuffer( const char *buf, const int size, const bool onlyAscii )
{
	int row, column, i = 0;
	
	// You better be damn sure this ends with a \0.
	if ( onlyAscii )
	{
		fprintf( LogFile, "%s\r\n", buf );
		return;
	}

	for ( row = 0; ( i + 1 ) < size; row++ )
	{
		// hex
		for( column = 0; column < 16; column++ )
		{
			i = row * 16 + column;
			if ( column == 8 )
			{
				fprintf(LogFile, " " );
			}

			if ( i < size )
			{
				fprintf( LogFile, "%02X", (unsigned char)buf[i] );
			}
			else
			{
				fprintf( LogFile, "  " );
			}
			fprintf( LogFile, " " );
		}
		// ascii 
		for( column = 0; column < 16; column++ )
		{
			i = row * 16 + column;
			if ( column == 8 )
			{
				fprintf( LogFile, " " );
			}
			if( i < size )
			{
				if( buf[i] > 0x20 && buf[i] < 0x7F )
				{
					fprintf( LogFile, "%c", buf[i] );
				}
				else 
				{
					fprintf( LogFile, "." );
				}
			}
			else
			{
				break;
			}
		}
		fprintf( LogFile, "\r\n" );
	}
}

VOID Finish( int ignored, VOID *arg )
{
	fflush( LogFile );
	fclose( LogFile );
}

UINT32 Usage()
{
	std::cout << "records various pnkbstr junkz";
	std::cout << std::endl;
	std::cout << KNOB_BASE::StringKnobSummary();
	std::cout << std::endl;
	return 2;
}
// Hooks
VOID HookUDP( const IMG img, const AFUNPTR replacement, const char *functionName )
{
	std::cerr << "Found " << functionName << "..." << endl;
	RTN rtn = RTN_FindByName(img, functionName );

	PROTO proto = 
		PROTO_Allocate( PIN_PARG(WINDOWS::INT),   // retval
				CALLINGSTD_STDCALL,
				functionName,
				PIN_PARG(WINDOWS::SOCKET),			// s,
				PIN_PARG(WINDOWS::CHAR *),			// buf,
				PIN_PARG(WINDOWS::INT),				// len
				PIN_PARG(WINDOWS::INT),				// flags
				PIN_PARG(WINDOWS::SOCKADDR *),		// from|to,
				PIN_PARG(WINDOWS::INT *),			// fromlen|tolen,
				PIN_PARG_END()
				);

	RTN_ReplaceSignature(rtn, replacement,
			IARG_PROTOTYPE, proto,
			IARG_ORIG_FUNCPTR,
			IARG_FUNCARG_ENTRYPOINT_VALUE, 0,
			IARG_FUNCARG_ENTRYPOINT_VALUE, 1,
			IARG_FUNCARG_ENTRYPOINT_VALUE, 2,
			IARG_FUNCARG_ENTRYPOINT_VALUE, 3,
			IARG_FUNCARG_ENTRYPOINT_VALUE, 4,
			IARG_FUNCARG_ENTRYPOINT_VALUE, 5,
			IARG_CONTEXT,
			IARG_PTR, functionName,
			IARG_END
			);

	PROTO_Free(proto);
}

VOID HookRecvFrom( const IMG img )
{
	HookUDP( img, (AFUNPTR)replacementUDP, "recvfrom" );
}

VOID HookSendTo( const IMG img )
{
	HookUDP( img, (AFUNPTR)replacementUDP, "sendto" );
}

VOID HookTCP( const IMG img, const AFUNPTR replacement, const char *functionName )
{
	fprintf(LogFile, "Found %s...\r\n", functionName );
	std::cerr << "Found " << functionName << "..." << endl;

	// hook 
	RTN rtn = RTN_FindByName( img, functionName );

	PROTO proto = 
		PROTO_Allocate( PIN_PARG(WINDOWS::INT),
				CALLINGSTD_STDCALL,
				functionName,
				PIN_PARG(WINDOWS::SOCKET),			// s,
				PIN_PARG(WINDOWS::CHAR *),			// buf,
				PIN_PARG(WINDOWS::INT),				// len
				PIN_PARG(WINDOWS::INT),				// flags
				PIN_PARG_END()
				);
	
	RTN_ReplaceSignature(rtn, replacement,
			IARG_PROTOTYPE, proto,
			IARG_ORIG_FUNCPTR,
			IARG_FUNCARG_ENTRYPOINT_VALUE, 0,
			IARG_FUNCARG_ENTRYPOINT_VALUE, 1,
			IARG_FUNCARG_ENTRYPOINT_VALUE, 2,
			IARG_FUNCARG_ENTRYPOINT_VALUE, 3,
			IARG_PTR, functionName,
			IARG_CONTEXT,
			IARG_END
			);

	PROTO_Free(proto);
}

VOID HookSend( const IMG img )
{
	HookTCP( img, (AFUNPTR)replacementTCP, "send" );	
}
VOID HookRecv( const IMG img )
{
	HookTCP( img, (AFUNPTR)replacementTCP, "recv" );
}


VOID ImageLoad( IMG img, VOID *v )
{
	RTN rtn;
	// UDP
	if ( (rtn = RTN_FindByName( img, "recvfrom" )) != RTN_Invalid() )
	{
		HookRecvFrom( img );
	}
	if ( (rtn = RTN_FindByName( img, "sendto" )) != RTN_Invalid() )
	{
		HookSendTo( img );
	}

	// TCP
	if ( (rtn = RTN_FindByName( img, "recv" )) != RTN_Invalid() )
	{
		HookRecv( img );
	}
	if ( (rtn = RTN_FindByName( img, "send" )) != RTN_Invalid() )
	{
		HookSend( img );
	}
}

int main(int argc, char **argv)
{
	PIN_InitSymbols();

	if ( PIN_Init(argc, argv) )
		return Usage();

	LogFile = fopen( KnobOutputFile.Value().c_str(), "wb" );
	fprintf( LogFile, "Opened log file...\r\n" );
	IMG_AddInstrumentFunction( ImageLoad, NULL );
	PIN_AddFiniFunction( Finish, NULL );
	PIN_StartProgram();

	return 0;
}