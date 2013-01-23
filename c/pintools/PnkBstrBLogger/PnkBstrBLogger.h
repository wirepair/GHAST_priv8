#ifndef PNKBSTRBLOGGER_H
#define PNKBSTRBLOGGER_H

#include "pin.H"
#include <iostream>
#include <fstream>


namespace WINDOWS {
#include "Winsock2.h"
#include "Windows.h"
}

// Helpers
VOID PrintHexBuffer( const char *buf, const int size, const bool onlyAscii );

// Hooks
VOID HookRecvFrom( IMG img );
VOID HookRecv( IMG img );

static FILE * LogFile;

// function offsets + prototypes.
const unsigned int pbSendRandnumbToSockOffset = 0x65B9;
typedef VOID * ( *FP_SEND_RAND )( );

const unsigned int pbCreateCustomStringWithRandnumbKey = 0x5871;
typedef VOID * ( *FP_CUSTOM_STRING )( );

const unsigned int pbEncAndSendBuf = 0x591D;
typedef VOID * ( *FP_ENC_SENDBUF )( char *buf, int len );
#endif // PNKBSTRBLOGGER_H