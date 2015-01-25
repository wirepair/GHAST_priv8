#include <iostream>
#include <windows.h>
#include <winbase.h>

// unk_code (server) 357AFE48
// unk_code (client) 264B8BD3
typedef int (__cdecl *fptr_a)(int unk_server_cli_code, signed int op_code, char *ptr_or_null, int unk_pointer);
using namespace std;

int main(int argc, char **argv)
{
	
	char *Y = "\x89\x44\x24\x74\x89\x44\x24\x6c\x89\x74\x24\x5c\x8b\x0b\x8b\x41\x40\x56\x53\xff\xd0\x8b\x0d\x00\x00\x00\x00\x8b\x11\x8b\x82\xa8\x00\x00\x00\x8b\x4d\x08\x57\x89\x41\x08\xff\x15";
	char *data = "<p> w 59002 16a6 16 8b 45 fc f be 8 85 c9 74 3d 8b 55 8 f be 2 8"\
"b 4d fc f be 11<p> W 89214 1a5c 28 7e 0 2 32 98 18 a9 bb e4 e0 9"\
"0 98 ee c0 16 13 8 8e 54 d5 9c 1c e1 d1 4b 55 48 a7 a7 5c 25 25"\
"97 c5 83 eb a1 79 da e<p> Y 80555 1000 30 89 44 24 74 89 44 24 6"\
"c 89 74 24 5c 8b b 8b 41 40 56 53 ff d0 8b d * * * * 8b 11 8b 82"\
" a8 0 0 0 8b 4d 8 57 89 41 8 ff 15 +1c52,1000 * * *<p> Y 70864 1"\
"000 3e d9 44 24 38 d9 c0 dd 5 +12b5f,100 * * * dc c9 d9 c9 d9 5c"\
" 24 2c d9 44 24 3c d9 c0 d8 ca d9 5c 24 30 d9 44 24 40 d9 c0 de"\
"cb d9 ca d9 5c 24 34 dd 5 * * * * dc cb d9 cb d9 5c 24 20 d8 ca<"\
"p> Y 70865 1000 45 cc cc cc cc cc cc cc cc cc cc cc cc cc cc a1"\
"+10ca64,100 * * * 56 57 8b 3d * * * * 85 c0 75 26 8b 35 * * * *"\
"68 * * * * ff d6 a3 * * * * 85 c0 75 10 68 c8 0 0 0 ff d7 a1 * *"\
" * * 85 c0 74 e0<p> Y 70877 1000 3b 85 c0 f 84 4d 3 0 0 6a 4 50"\
"ff 15 * * * * 85 c0 f 85 3c 3 0 0 8b 86 54 1 0 0 8b 40 4 85 c0 f"\
" 84 2b 3 0 0 6a 4 50 ff 15 +62f3,100 * * * 85 c0 f 85 1a 3 0 0<p"\
"> Y 132908 1000 55 55 8b ec 83 ec 8 89 4d f8 83 7d 8 0 75 9 8b 4"\
"5 f8 83 c0 18 89 45 8 83 7d c 0 75 c 6a d ff 15 +58f8,0 * * * 33"\
" c0 eb 25 8b 4d c f b6 11 8d 4 d5 * * * * 89 45 fc 8b 4d c 51 8b"\
" 55 8 52 8b 45 fc 50 8b 55 fc 8b 4d f8 ff 52 4 8b e5 5d c2 8 0<p"\
"> Y 60344 1000 44 50 e8 23 ab 2 0 3b c3 59 89 45 ec 74 13 8b c7"\
"c1 e0 2 50 e8 10 ab 2 0 3b c3 59 89 45 e8 75 c c7 45 e4 e 0 7 80"\
" e9 38 1 0 0 8d 45 fc 50 53 53 ff 75 f8 33 ff 89 7d 8 ff 15 +47b"\
"d0,100 * * * 8d 45 f4<p> Y 80905 1000 6e 8b 44 24 10 2b c6 50 56"\
" 8d 4c 24 60 8b c7 e8 * * * * ff 70 4 ff 30 8d 44 24 28 50 e8 *"\
"* * * 8d 54 24 58 e8 * * * * 8b 44 24 10 40 68 +1000,100 * * * 8"\
"d 74 24 64 89 44 24 18 e8 * * * * ff 74 24 24 8b f0 ff 74 24 24"\
"56 e8 * * * * ff 76 4 8d 44 24 34 ff 36 89 5c 24 38 50 89 5c 24"\
"40 e8 * * * * 8d 54 24 60 e8<p> Y 132111 1000 54 56 57 8b 7c 24"\
"c 57 ff 15 +4309,100 * * * 68 * * * * 57 8b f0 ff 15 * * * * 83"\
"c4 8 85 c0 74 2b 68 * * * * 68 * * * * ff 15 * * * * 50 ff 15 *"\
"* * * 85 c0 74 b 50 8b c6 e8 cb fe ff ff 83 c4 4 a3 * * * * 5f 8"\
"b c6 5e c2 4 0<p> Y 80951 1678 16 4c 50 59 41 52 45 20 53 52 41"\
"20 45 49 41 49 4d 47 4e +1005,100 * * *<p> Y 50937 1000 66 55 8b"\
" ec 83 e4 c0 81 ec f4 2 0 0 a1 +e89d7,100 * * * 33 c4 89 84 24 f"\
"0 2 0 0 53 56 33 c0 57 8b f1 89 44 24 44 8b d * * * * 8b 11 50 8"\
"b 42 20 ff d0 8b f8 57 b9 * * * * e8 80 ec ff ff 84 c0 f 84 f6 8"\
" 0 0 57 b9 * * * * e8 fd ef ff ff d9 5c 24 40 57 b9 * * * * e8 5"\
"e ed ff ff d9 ee 8b d<p> Y 71090 1000 42 56 ff 75 c 50 50 ff 15"\
"* * * * 6a 1 8d 8b 20 5 0 0 50 89 45 20 e8 97 3d fe ff 8b f8 85"\
"ff f 8c cd 15 0 0 ff 75 20 8d bb 20 5 0 0 ff 37 56 ff 75 c 6a 0"\
"6a 0 ff 15 +123674,100 * * * 8b 7<p> Y 71087 1000 47 33 c0 e9 b6"\
" 0 0 0 8b 4d f8 8b 51 1 89 55 e0 8b 45 e0 8b 4d f8 8d 54 1 5 89"\
"55 d8 8b 45 d8 3b 45 c 74 f 6a c ff 15 +1338a6,100 * * * 33 c0 e"\
"9 89 0 0 0 8b 4d f4 51 8b 55 f8 52 8d 4d e4 e8 b3 37 ff ff 8b 45"\
" 8<p> Y 50441 1000 41 6a 8 e8 5f 5 0 0 59 83 65 fc 0 ff 35 +4206"\
",100 * * * ff d6 89 45 e4 ff 35 * * * * ff d6 59 59 89 45 e0 8d"\
"45 e0 50 8d 45 e4 50 ff 75 8 8b 35 * * * * ff d6 59 50 e8 22 5 0"\
" 0 89 45 dc<p> Y 71088 1000 34 50 e8 db ba 1 0 83 c4 c 83 7f 14"\
"10 72 c 8b f 51 ff 15 +1cde3,100 * * * 83 c4 4 8b 45 c c6 7 0 89"\
" 7 89 77 14 89 5f 10 83 fe 10 72 2 8b f8 c6 4 1f 0<p> Y 50436 10"\
"00 41 6a 8 e8 23 6 0 0 59 83 65 fc 0 ff 35 * * * * ff d6 89 45 e"\
"4 ff 35 +52a9,100 * * * ff d6 59 59 89 45 e0 8d 45 e0 50 8d 45 e"\
"4 50 ff 75 8 8b 35 * * * * ff d6 59 50 e8 e6 5 0 0 89 45 dc<p> Y"\
" 71092 1000 37 56 50 51 ff 15 +5ef6,100 * * * 8b f0 85 f6 75 22"\
"a1 * * * * 85 c0 74 8 8b 10 50 8b 42 44 ff d0 a1 * * * * 85 c0 7"\
"4 8 8b 8 8b 51 4c 50 ff d2 8b c6 5e c2 8 0<p> Y 81906 bc14 11 5c"\
" 43 61 74 61 6c 79 73 74 50 69 70 65 +7155,aa0 * * *<p> Y 80661"\
"1000 34 83 f8 2 74 d 6a 1f e8 6b 5 0 0 59 e9 b5 0 0 0 ff 35 * *"\
"* * 8b 35 * * * * ff d6 59 89 45 c 85 c0 f 84 87 0 0 0 ff 35 +35"\
"f5,100 * * * ff d6<p> Y 50468 1000 34 53 56 57 8b 7c 24 10 80 7f"\
" 2d 0 8b d9 8b f7 75 27 8b 46 8 50 8b cb e8 e4 ff ff ff 8b 36 8d"\
" 4f c ff 15 +306f7,100 * * * 57 e8 11 f5 2 0 83 c4 4 80 7e 2d 0<"\
"p> Y 71101 1000 40 57 e8 2e 4 0 0 85 c0 75 b4 57 ff 15 * * * * 5"\
"f 5e 33 c0 5b 8b 8c 24 24 3 0 0 33 cc e8 12 38 1 0 81 c4 28 3 0"\
"0 c3 8b 74 24 24 57 ff 15 +14b9a,100 * * * 8b 8c 24 30 3 0 0 5f"\
"8b c6<p> Y 80673 1000 41 50 57 e8 2c 35 0 0 85 c0 f 85 5e ff ff"\
"ff 57 ff 15 * * * * 33 c0 5f 5e 8b 8c 24 2c 6 0 0 33 cc e8 fd 24"\
" 3 0 8b e5 5d c3 8b 74 24 20 57 ff 15 +343a2,100 * * * 8b 8c 24"\
"34 6 0 0 5f 8b c6<p> Y 50499 1000 33 53 55 56 57 ff 35 * * * * e"\
"8 e3 6e 0 0 ff 35 +376cc,1000 * * * 8b f0 89 74 24 18 e8 d2 6e 0"\
" 0 8b f8 3b fe 59 59 f 82 84 0 0 0 8b df 2b de 8d 6b 4<p> Y 7112"\
"9 1000 32 8b ec ff 35 +1aa9d,1000 * * * e8 68 53 0 0 85 c0 59 74"\
" 3 5d ff e0 6a 2 e8 eb 58 0 0 59 5d e9 e0 fe ff ff 33 c0 50 50 5"\
"0 50 50 e8 d0 ff ff ff 83 c4 14<p> Y 71134 1000 3c 8b ec 6a 1 e8"\
" 24 8 1 0 5d ff 25 * * * * 8b ff 55 8b ec 6a 1 e8 11 8 1 0 d9 45"\
" 1c 51 d9 1c 24 ff 75 18 ff 75 14 ff 75 10 ff 75 c ff 75 8 ff 15"\
" +5c92e,1000 * * * 5d c2 18 0<p> Y 71133 1000 30 53 53 53 ff 76"\
"10 ff 15 * * * * 6a 1 ff 76 10 ff 15 +44181,1000 * * * ff 75 ec"\
"e8 66 ae 2 0 ff 75 e8 e8 5e ae 2 0 8b 45 e4 59 59 5f 5e 5b c9<p>"\
" Y 60954 1000 34 ff d0 8b 4c 24 4 51 e8 a9 ff ff ff 8b c 24 8b 5"\
"4 24 1c 8b 44 24 18 52 8b 54 24 18 50 8b 44 24 18 52 8b 54 24 18"\
" 50 52 ff 15 +1000,100 * * * 83 c4 8 c2 14 0<p> Y 51004 1000 41"\
"6a 8 e8 66 3 0 0 59 83 65 fc 0 ff 35 * * * * ff d6 89 45 e4 ff 3"\
"5 +29092,100 * * * ff d6 59 59 89 45 e0 8d 45 e0 50 8d 45 e4 50"\
"ff 75 8 8b 35 * * * * ff d6 59 50 e8 29 3 0 0 89 45 dc<p> Y 7113"\
"6 1000 32 51 51 ff 15 +4a5f1,1000 * * * 83 65 10 0 8d 85 6c ff f"\
"f ff c6 45 a3 0 89 45 c 33 f6 39 75 10 74 5d 6a 17 59 33 c0 8d 7"\
"d a4 f3 ab 8b 45 c 8b 8 89 4d a4<p> Y 71138 1000 34 f7 d8 89 46"\
"8 33 c0 50 50 ff 75 c 89 46 10 50 8b 45 fc 56 66 c7 46 c 1 0 66"\
"c7 46 e 20 0 ff 70 10 ff 15 +4c541,1000 * * * 56 8b f8 e8 ea f7"\
"2 0 59 8b c7<p> Y 50946 1000 6f 53 53 ff 75 14 ff 75 10 33 c0 39"\
" 5d 24 f 95 c0 8d 4 c5 1 0 0 0 50 ff 75 20 ff 15 +1000,100 * * *"\
" 8b f0 89 75 d0 3b f3 f 84 b8 1 0 0 c7 45 fc 1 0 0 0 8d 4 36 83"\
"c0 3 83 e0 fc e8 4a 88 ff ff 89 65 e8 8b c4 89 45 e4 83 4d fc ff"\
" eb 1b 33 c0 40 c3 8b 65 e8 e8 a5 29 0 0 33 db 89 5d e4 83 4d fc"\
" ff 8b 7d d4 8b 75 d0 39 5d e4<p> Y 130805 1000 2b 52 56 e8 f3 0"\
" 0 0 85 c0 75 eb 56 ff 15 +1f4e,1000 * * * 5e 33 c0 5f 8b 8c 24"\
"24 2 0 0 33 cc e8 39 f 0 0 81 c4 28 2 0 0 c3<p> Y 50561 1000 3a"\
"55 8b ec 6a 1 e8 2e 56 0 0 5d ff 25 * * * * 8b ff 55 8b ec 6a 1"\
"e8 1b 56 0 0 d9 45 1c 51 d9 1c 24 ff 75 18 ff 75 14 ff 75 10 ff"\
"75 c ff 75 8 ff 15 +38dfb,1000 * * * 5d<p> Y 71158 1000 41 50 8d"\
" 8d 74 fc ff ff ff 15 +2ff51,1000 * * * 8b f8 c7 45 fc 1 0 0 0 d"\
"9 85 d0 fc ff ff dd 9d ac fc ff ff d9 85 d4 fc ff ff dc 25 * * *"\
" * e8 a1 fa 2 0 8d 8d e0 fc ff ff 8b d8 e8 e4 f7 ff ff 99<p> Y 5"\
"0600 1000 40 55 8b ec 6a 1 e8 df a6 0 0 d9 45 1c 51 51 d9 5c 24"\
"4 d9 45 18 d9 1c 24 ff 75 14 ff 75 10 ff 75 c ff 75 8 ff 15 +402"\
"48,1000 * * * 5d c2 18 0 8b ff 55 8b ec 83 ec 20 d9 45 18 56 d8"\
"45 1c 51 51<p> W 89711 33a0 41 b8 1 0 0 0 e8 6 94 0 0 e8 31 b3 0"\
" 0 50 85 c0 f 85 6d 3 0 0 c6 45 f8 1 8d 4d c4 8d 55 ac b8 1 0 0"\
"0 e8 e4 93 0 0 e8 f b3 0 0 50 85 c0 f 85 a2 1 0 0 e8 e1 ec 0 0 8"\
"9 c3<p> W 89241 3370 62 55 89 e5 81 ec 94 0 0 0 89 9d 6c ff ff f"\
"f 89 b5 70 ff ff ff c7 45 9c 0 0 0 0 c7 45 a0 0 0 0 0 c7 45 a4 0"\
" 0 0 0 8d 4d ec 8d 55 d4 b8 1 0 0 0 e8 6 94 0 0 e8 31 b3 0 0 50"\
"85 c0 f 85 6d 3 0 0 c6 45 f8 1 8d 4d c4 8d 55 ac b8 1 0 0 0 e8 e"\
"4 93 0 0 e8 f b3 0 0 50<p> Y 80918 1000 64 e8 9f 25 0 0 68 +1000"\
",100 * * * ff 15 * * * * e8 bf f9 ff ff 8b f0 85 f6 74 3b 83 3d"\
"5c * * * * 74 32 83 3d 60 * * * * 74 29 8b 46 40 68 * * * * 50 e"\
"8 c9 33 0 0 8b 8e a8 0 0 0 68 * * * * 51 a3 c4 e2 1 10 e8 b3 33"\
"0 0 a3 * * * * 5f 33 c0 5e c2 4 0 cc cc cc cc cc cc cc<p> Y 8071"\
"3 1000 45 8d 55 4 89 95 e4 fd ff ff 8d 45 4 8b 48 fc 89 8d d4 fd"\
" ff ff 8b 55 c 89 95 c8 fc ff ff 8b 45 10 89 85 cc fc ff ff 8b 4"\
"d 4 89 8d d4 fc ff ff ff 15 * * * * 89 45 f4 6a 0 ff 15 +1e98e,1"\
"000 * * * 8d 55 f8 52<p> Y 80723 1000 42 51 ff 75 8 ff 76 10 ff"\
"15 +4817d,1000 * * * 3b c3 89 45 e4 f 8c 98 2 0 0 ff 75 f8 ff 15"\
" * * * * 8b 0 3b 46 24 8b 7e 28 89 45 d0 89 7d d4 7e 3a 8d 45 8"\
"50 8d 45 d0 50 8b ce e8 5b e6 ff ff 3b c3<p> Y 80711 1000 36 5e"\
"e8 83 df ff ff 81 c5 a8 2 0 0 c9 c3 55 8b ec ff 35 +15db2,1000 *"\
" * * e8 f5 23 0 0 85 c0 59 74 3 5d ff e0 6a 2 e8 f4 48 0 0 59 5d"\
" e9 e0 fe ff ff 8b 44 24 4<p> W 89918 2423 51 56 ff 50 10 8b 74"\
"24 14 8b 10 6a 1 56 8b c8 ff 12 85 c0 75 5 e8 c3 ff ff ff 3b ee"\
"7d 2 8b f5 8d 4e 1 8b d1 57 c1 e9 2 8d 78 10 89 7c 24 18 8d 73 1"\
"0 f3 a5 8b ca 83 e1 3 f3 a4 89 68 4 8d 43 c 83 c9 ff f0 f c1 8 4"\
"9 85 c9 5f 7f 8 8b b<p> W 89925 14b8 41 5f 5e 5b 8b 8c 24 90 2b"\
"0 0 33 cc e8 83 14 0 0 8b e5 5d c3 8d b4 24 30 12 0 0 bf 19 0 0"\
"0 8d a4 24 0 0 0 0 8b c6 8d 50 1 8a 8 83 c0 1 84 c9 75 f7 2b c2"\
"74 7 56 53 e8 7 c 0 0<p> W 80739 1e14 60 52 d9 5c 24 20 d9 84 24"\
" 80 0 0 0 d9 5c 24 24 d9 84 24 84 0 0 0 d9 5c 24 28 e8 8c fd ff"\
"ff 84 c0 f 84 a8 0 0 0 d9 44 24 1c d9 54 24 40 d9 44 24 20 d9 54"\
" 24 44 d8 6c 24 2c d9 5c 24 14 d9 44 24 14 d9 e1 d9 5c 24 14 d9"\
"44 24 14 d9 c0 d9 44 24 28 de e3 d9 ca d9 5c 24 14 d9 44 24 14<p"\
"> W 70985 80 50 c 20 52 8d 48 41 3c de 48 41 3c de 48 41 3c de 4"\
"1 39 af de 4b 41 3c de 48 41 3d de fb 41 3c de 27 37 96 de a2 40"\
" 3c de 27 37 a2 de 1d 41 3c de 27 37 93 de 7c 41 3c de 27 37 97"\
"de f0 41 3c de 27 37 a7 de 49 41 3c de 27 37 a6 de 49 41 3c de<p"\
"> Y 71185 1000 3b f 84 a8 2d 0 0 6a 1 ff 15 +4c80,1000 * * * 66"\
"85 c0 f 84 df 0 0 0 80 3d * * * * f 85 d2 0 0 0 8b 6c 24 14 d9 4"\
"4 2b 1c e8 1f 47 0 0 d9 44 2b 18 8b f8 e8 14 47 0 0<p> Y 71958 1"\
"000 34 d9 9c 24 5c 1 0 0 8b 8c 24 5c 1 0 0 51 52 68 * * * * e8 1"\
"b 93 ff ff 6a 1 ff 15 +4199,1000 * * * 66 85 c0 74 74 83 3d 3c 1"\
"4 52 67 a 7e 6b c6 47 8 1<p> Y 50647 1000 47 8b c2 80 7c 18 2c 0"\
" f 84 a8 2d 0 0 6a 1 ff 15 +4b60,1000 * * * 66 85 c0 f 84 df 0 0"\
" 0 80 3d ca 6 f7 66 0 f 85 d2 0 0 0 8b 6c 24 14 d9 44 2b 1c e8 a"\
"f 47 0 0 d9 44 2b 18 8b f8 e8 a4 47 0 0 d9 44 2b 14<p> Y 60906 1"\
"000 33 0 c3 55 8b ec 51 8d 55 fc 89 75 fc a7 f8 59 62 39 f8 34 5"\
"9 62 d +1000,100 * * * a7 f8 59 62 c f8 34 14 a7 f8 34 a7 f8 36"\
"a6 f8 17 14 a7 f8 59 62 8 f8 37<p> W 71191 80 50 72 75 c9 ab 36"\
"14 a7 f8 36 14 a7 f8 36 14 a7 f8 59 62 3b f8 34 14 a7 f8 59 62 3"\
"9 f8 34 14 a7 f8 59 62 d f8 3d 14 a7 f8 59 62 c f8 34 14 a7 f8 3"\
"f 6c 34 f8 33 14 a7 f8 36 14 a6 f8 17 14 a7 f8 59 62 8 f8 37 14"\
"a7 f8 59 62 3a f8 37 14 a7 f8<p> Y 50651 1000 51 33 ed ff 15 +23"\
"1a4,1000 * * * f af c6 33 c5 50 e8 85 5f 1 0 83 c4 4 e8 8a 5f 1"\
"0 99 b9 * * * * f7 f9 8a 44 24 13 8a da 3a d8 75 6d e8 73 5f 1 0"\
" 99 b9 6 0 0 0 f7 f9 83 fa 3 7d 14 e8 61 5f 1 0 f b6 c0 99 b9 *"\
"* * * f7 f9 2 da<p> Y 50649 1000 41 83 c7 8 89 45 80 8b 47 fc 89"\
" 45 84 8d 45 9c 50 ff 75 88 f be c2 ff 75 e0 89 7d d4 50 ff 75 9"\
"8 8d 45 80 53 50 ff 35 +3af45,1000 * * * e8 5a 2b 0 0 59 ff d0 8"\
"b 7d e8 83 c4 1c 81 e7 80 0 0 0 74 1a<p> Y 80753 1000 42 57 8d 8"\
"5 e8 fd ff ff 50 ff 15 +556ee,1000 * * * 8d 85 ec fe ff ff 33 db"\
" 89 45 fc 43 8b 86 * * * * 85 c0 74 e 83 78 58 0 74 8 8b 40 64 8"\
"9 45 f4 eb 4 83 65 f4 0 * * e8 23 a2 3 0 85 c0 59 74 b<p> Y 7196"\
"1 134f 42 79 6e 4b dc f9 24 bf 64 ab 58 f2 fd df 3b 4d 79 8f 76"\
"17 17 f 20 48 87 9e 9e 3a 9 +1000,100 * * * 92 36 6a 9c 5d 7d f1"\
" 62 b c9 b1 e8 97 e1 cd 8 f4 72 e1 f eb e3 67 17 96 8d eb 6e 1e"\
"48 50 58 aa 50<p> Y 50658 1000 41 83 c7 8 89 45 80 8b 47 fc 89 4"\
"5 84 8d 45 9c 50 ff 75 88 f be c2 ff 75 e0 89 7d d4 50 ff 75 98"\
"8d 45 80 53 50 ff 35 +3af45,1000 * * * e8 5a 2b 0 0 59 ff d0 8b"\
"7d e8 83 c4 1c 81 e7 80 0 0 0 74 1a<p> Y 82930 1000 22 14 0 16 0"\
" f0 13 fe 7e 26 0 28 0 10 14 fe 7e 3f 0 0 0 0 0 0 0 0 0 0 0 +966"\
"66632,10 * * * a0 6<p> Y 80784 1000 44 50 c6 44 24 c 0 e8 68 35"\
"3 0 8b 94 24 18 4 0 0 83 c4 c 8d 8c 24 10 4 0 0 51 52 8d 44 24 8"\
" 50 ff 15 +35006,1000 * * * 8b d * * * * 83 c4 c 51 51 8d 54 24"\
"8 52 56 e8 72 3e 0 0 83 c4 c 8b c8<p> Y 71998 1000 55 e8 cc ca f"\
"f ff 85 c0 74 13 8b 45 8 3b c1 74 4a 8b 11 89 10 8b 49 4 89 48 4"\
" eb 3e d9 45 c d8 * +1000,100 * * * df e0 f6 c4 41 8b 45 8 75 22"\
" d9 45 c d9 fa d8 3d * * * * d9 c0 d8 9 d9 5d f8 d8 49 4 8b 4d f"\
"8 89 8 d9 5d fc 8b 4d fc eb c6 d9 ee d9 18<p> Y 50910 4210 c 41"\
"69 6d 53 74 79 6c 65 +68ff3,500 * * *<p> Y 72905 1000 55 e8 14 c"\
"a ff ff 85 c0 74 13 8b 45 8 3b c1 74 4a 8b 11 89 10 8b 49 4 89 4"\
"8 4 eb 3e d9 45 c d8 * +1000,100 * * * df e0 f6 c4 41 8b 45 8 75"\
" 22 d9 45 c d9 fa d8 3d * * * * d9 c0 d8 9 d9 5d f8 d8 49 4 8b 4"\
"d f8 89 8 d9 5d fc 8b 4d fc eb c6 d9 ee d9 18<p> Y 60951 1000 26"\
" 72 65 6e 64 65 72 65 72 2e 74 77 65 61 6b 6e 65 61 72 70 6c 61"\
"6e * * * +100100,10 * * * 0 0 0 0 0 0 0 0 0<p> Y 50752 1000 4f 5"\
"0 8d 45 f4 64 a3 0 0 0 0 8b f1 89 75 f0 83 7e 18 10 72 c 8b 46 4"\
" 50 e8 6a 39 0 0 83 c4 4 c7 46 18 f 0 0 0 c7 46 14 0 0 0 0 c6 46"\
" 4 0 8b ce c7 45 fc 0 0 0 0 ff 15 +5ea2,1000 * * * 8b 6 50 e8 3e"\
" 39 0 0 83 c4 4 8b ce<p> Y 80814 1000 32 52 8b 45 8 50 8b 4d 10"\
"51 8b 55 c 52 6a 0 8d 4d e0 e8 cc 22 fe ff 8b 0 8b 48 4 51 ff 15"\
" +a4da,1000 * * * 89 45 fc 83 7d fc 0 74 33 83 7d f0 0 75 2d<p>"\
"Y 60955 3aa1 3c 3f 24 62 61 ce 6 3c 35 13 +1000,100 * * * 32 86"\
"fd 4e 35 ce d8 b1 d 45 2d 6 3c 35 1e ac 23 af f7 c6 d2 39 37 7f"\
"31 ce a6 6e 4d af 82 9c a3 22 8 a7 b0 8f b1 79 f7 * * * * b7 bf<"\
"p> Y 90907 202 48 95 89 ac 24 a6 34 2c e 5d d7 15 f2 83 ce 95 d"\
"fd 3c 3b 7a 14 62 88 8a 6e da 5 4d 25 4c d6 ea 3e 9c ad f 97 7d"\
"8c af d8 d5 9e c1 3f c2 +1000,100 * * * 7d de bc 32 8c 4d ed 39"\
"8a 7 d8 8e 20 df 4d f3 aa dd 1b 9d e1 dc<p> Y 50791 1000 33 57 5"\
"3 ff 75 24 ff 15 +131d4,1000 * * * 89 45 f8 57 e8 b2 dd ff ff 59"\
" ff 75 f4 e8 a9 dd ff ff 8b 45 f8 59 8d 65 e4 5f 5e 5b 8b 4d fc"\
"33 cd e8 66 d6 ff ff c9 c3<p> Y 50795 1000 40 53 53 eb 6 ff 75 2"\
"0 ff 75 1c ff 75 f8 57 53 ff 75 24 ff 15 +12784,1000 * * * 89 45"\
" f8 57 e8 b2 dd ff ff 59 ff 75 f4 e8 a9 dd ff ff 8b 45 f8 59 8d"\
"65 e4 5f 5e 5b 8b 4d fc 33 cd e8 66 d6 ff ff c9 c3<p> Y 80836 10"\
"00 42 50 ff d2 8b 45 10 8b 4d c 3 4d 14 99 2b c2 d1 f8 3 45 8 89"\
" 45 10 db 45 10 a1 +65cd,1000 * * * 50 d9 5d 10 d9 45 10 89 4d 1"\
"0 d9 55 ec db 45 c d9 5d f0 d9 5d f4 db 45 10 d9 5d f8 8b 10 8b"\
"42 10 ff d0";

	char *ponk = "\x8b\x45\xfc\x0f\xbe\x08\x85\xc9\x74\x3d\x8b\x55\x08\x0f\xbe\x02\x8b\x4d\xfc\x0f\xbe\x11";
	int wait;
	char *one_cmd = "AAAA";
	char **one_cmd_ptr = &one_cmd;
	//HMODULE pbcl = LoadLibrary(L"C:\\GitHub\\Sync\\idbs\\pbcl.dll");
	//HMODULE pbagz = LoadLibrary(L"C:\\GitHub\\Sync\\idbs\\pbag.dll");
	HMODULE pbcl = LoadLibrary(L"C:\\Tools\\pbcl.dll");
	HMODULE pbagz = LoadLibrary(L"C:\\Tools\\pbag.dll");
	HANDLE hHeap2 = HeapCreate(HEAP_CREATE_ENABLE_EXECUTE, 0x20000, 0x20000);
	void *addr_a = VirtualAlloc(NULL, 0x20000, MEM_RESERVE, PAGE_READWRITE);
	char *addr_a2 = (char *)VirtualAlloc(addr_a, 0x20000, MEM_COMMIT, PAGE_READWRITE);
	HANDLE hHeap = HeapCreate(HEAP_CREATE_ENABLE_EXECUTE, 0x2000, 0x2000);
	VOID *addr = VirtualAlloc(NULL, 8192, MEM_RESERVE, PAGE_READWRITE);
	char *addr2 = (char *)VirtualAlloc(addr, 8192, MEM_COMMIT , PAGE_READWRITE);
	
	char *addr2ptr = (char *)addr2+0x1000;

	

	
	//cout <<	GetCurrentProcessId() << endl;
	//cout << "PBCL BASE: " << pbcl << endl;
	printf("%p\n", data);
	
	printf("ponk: %p\n", ponk);
	printf("addr: %p addr2_ptr: %p\n", addr2, addr2ptr);
	printf("size: %d ponk: %p data: %02x addr2: %p\n", sizeof(ponk), ponk, *ponk, addr2);
	//memcpy(addr2, ponk, strlen(ponk));
	//memcpy(addr2ptr, ponk, strlen(ponk));
	memcpy(addr2, Y, sizeof(Y));
	memcpy(addr2ptr, Y, sizeof(Y));
	memset(addr_a2, 'A', 0x19000);
	printf("addr2: %02x %02x %p\n", addr2[0], addr2ptr[0], addr2ptr);
	printf("one_cmd_ptr: %p -> %p\n", one_cmd_ptr, *one_cmd_ptr);
	printf("addr_a2: %p\r\n", addr_a2);
	
	cin >> wait;
	
	HeapFree(hHeap, 0, 0);
	return 0;

}
/*
char *olddata = "<p> w 59002 16a6 16 8b 45 fc f be 8 85 c9 74 3d 8b 55 8 f be 2 8"\
"b 4d fc f be 11<p> W 89214 1a5c 28 7e 0 2 32 98 18 a9 bb e4 e0 9"\
"0 98 ee c0 16 13 8 8e 54 d5 9c 1c e1 d1 4b 55 48 a7 a7 5c 25 25"\
"97 c5 83 eb a1 79 da e<p> Y 80555 1000 30 89 44 24 74 89 44 24 6"\
"c 89 74 24 5c 8b b 8b 41 40 56 53 ff d0 8b d * * * * 8b 11 8b 82"\
" a8 0 0 0 8b 4d 8 57 89 41 8 ff 15 +1c52,1000 * * *<p> Y 70864 1"\
"000 3e d9 44 24 38 d9 c0 dd 5 +12b5f,100 * * * dc c9 d9 c9 d9 5c"\
" 24 2c d9 44 24 3c d9 c0 d8 ca d9 5c 24 30 d9 44 24 40 d9 c0 de"\
"cb d9 ca d9 5c 24 34 dd 5 * * * * dc cb d9 cb d9 5c 24 20 d8 ca<"\
"p> Y 70865 1000 45 cc cc cc cc cc cc cc cc cc cc cc cc cc cc a1"\
"+10ca64,100 * * * 56 57 8b 3d * * * * 85 c0 75 26 8b 35 * * * *"\
"68 * * * * ff d6 a3 * * * * 85 c0 75 10 68 c8 0 0 0 ff d7 a1 * *"\
" * * 85 c0 74 e0<p> Y 70877 1000 3b 85 c0 f 84 4d 3 0 0 6a 4 50"\
"ff 15 * * * * 85 c0 f 85 3c 3 0 0 8b 86 54 1 0 0 8b 40 4 85 c0 f"\
" 84 2b 3 0 0 6a 4 50 ff 15 +62f3,100 * * * 85 c0 f 85 1a 3 0 0<p"\
"> Y 132908 1000 55 55 8b ec 83 ec 8 89 4d f8 83 7d 8 0 75 9 8b 4"\
"5 f8 83 c0 18 89 45 8 83 7d c 0 75 c 6a d ff 15 +58f8,0 * * * 33"\
" c0 eb 25 8b 4d c f b6 11 8d 4 d5 * * * * 89 45 fc 8b 4d c 51 8b"\
" 55 8 52 8b 45 fc 50 8b 55 fc 8b 4d f8 ff 52 4 8b e5 5d c2 8 0<p"\
"> Y 60344 1000 44 50 e8 23 ab 2 0 3b c3 59 89 45 ec 74 13 8b c7"\
"c1 e0 2 50 e8 10 ab 2 0 3b c3 59 89 45 e8 75 c c7 45 e4 e 0 7 80"\
" e9 38 1 0 0 8d 45 fc 50 53 53 ff 75 f8 33 ff 89 7d 8 ff 15 +47b"\
"d0,100 * * * 8d 45 f4<p> Y 80905 1000 6e 8b 44 24 10 2b c6 50 56"\
" 8d 4c 24 60 8b c7 e8 * * * * ff 70 4 ff 30 8d 44 24 28 50 e8 *"\
"* * * 8d 54 24 58 e8 * * * * 8b 44 24 10 40 68 +1000,100 * * * 8"\
"d 74 24 64 89 44 24 18 e8 * * * * ff 74 24 24 8b f0 ff 74 24 24"\
"56 e8 * * * * ff 76 4 8d 44 24 34 ff 36 89 5c 24 38 50 89 5c 24"\
"40 e8 * * * * 8d 54 24 60 e8<p> Y 132111 1000 54 56 57 8b 7c 24"\
"c 57 ff 15 +4309,100 * * * 68 * * * * 57 8b f0 ff 15 * * * * 83"\
"c4 8 85 c0 74 2b 68 * * * * 68 * * * * ff 15 * * * * 50 ff 15 *"\
"* * * 85 c0 74 b 50 8b c6 e8 cb fe ff ff 83 c4 4 a3 * * * * 5f 8"\
"b c6 5e c2 4 0<p> Y 80951 1678 16 4c 50 59 41 52 45 20 53 52 41"\
"20 45 49 41 49 4d 47 4e +1005,100 * * *<p> Y 50937 1000 66 55 8b"\
" ec 83 e4 c0 81 ec f4 2 0 0 a1 +e89d7,100 * * * 33 c4 89 84 24 f"\
"0 2 0 0 53 56 33 c0 57 8b f1 89 44 24 44 8b d * * * * 8b 11 50 8"\
"b 42 20 ff d0 8b f8 57 b9 * * * * e8 80 ec ff ff 84 c0 f 84 f6 8"\
" 0 0 57 b9 * * * * e8 fd ef ff ff d9 5c 24 40 57 b9 * * * * e8 5"\
"e ed ff ff d9 ee 8b d<p> Y 71090 1000 42 56 ff 75 c 50 50 ff 15"\
"* * * * 6a 1 8d 8b 20 5 0 0 50 89 45 20 e8 97 3d fe ff 8b f8 85"\
"ff f 8c cd 15 0 0 ff 75 20 8d bb 20 5 0 0 ff 37 56 ff 75 c 6a 0"\
"6a 0 ff 15 +123674,100 * * * 8b 7<p> Y 71087 1000 47 33 c0 e9 b6"\
" 0 0 0 8b 4d f8 8b 51 1 89 55 e0 8b 45 e0 8b 4d f8 8d 54 1 5 89"\
"55 d8 8b 45 d8 3b 45 c 74 f 6a c ff 15 +1338a6,100 * * * 33 c0 e"\
"9 89 0 0 0 8b 4d f4 51 8b 55 f8 52 8d 4d e4 e8 b3 37 ff ff 8b 45"\
" 8<p> Y 50441 1000 41 6a 8 e8 5f 5 0 0 59 83 65 fc 0 ff 35 +4206"\
",100 * * * ff d6 89 45 e4 ff 35 * * * * ff d6 59 59 89 45 e0 8d"\
"45 e0 50 8d 45 e4 50 ff 75 8 8b 35 * * * * ff d6 59 50 e8 22 5 0"\
" 0 89 45 dc<p> Y 71088 1000 34 50 e8 db ba 1 0 83 c4 c 83 7f 14"\
"10 72 c 8b f 51 ff 15 +1cde3,100 * * * 83 c4 4 8b 45 c c6 7 0 89"\
" 7 89 77 14 89 5f 10 83 fe 10 72 2 8b f8 c6 4 1f 0<p> Y 50436 10"\
"00 41 6a 8 e8 23 6 0 0 59 83 65 fc 0 ff 35 * * * * ff d6 89 45 e"\
"4 ff 35 +52a9,100 * * * ff d6 59 59 89 45 e0 8d 45 e0 50 8d 45 e"\
"4 50 ff 75 8 8b 35 * * * * ff d6 59 50 e8 e6 5 0 0 89 45 dc<p> Y"\
" 71092 1000 37 56 50 51 ff 15 +5ef6,100 * * * 8b f0 85 f6 75 22"\
"a1 * * * * 85 c0 74 8 8b 10 50 8b 42 44 ff d0 a1 * * * * 85 c0 7"\
"4 8 8b 8 8b 51 4c 50 ff d2 8b c6 5e c2 8 0<p> Y 81906 bc14 11 5c"\
" 43 61 74 61 6c 79 73 74 50 69 70 65 +7155,aa0 * * *<p> Y 80661"\
"1000 34 83 f8 2 74 d 6a 1f e8 6b 5 0 0 59 e9 b5 0 0 0 ff 35 * *"\
"* * 8b 35 * * * * ff d6 59 89 45 c 85 c0 f 84 87 0 0 0 ff 35 +35"\
"f5,100 * * * ff d6<p> Y 50468 1000 34 53 56 57 8b 7c 24 10 80 7f"\
" 2d 0 8b d9 8b f7 75 27 8b 46 8 50 8b cb e8 e4 ff ff ff 8b 36 8d"\
" 4f c ff 15 +306f7,100 * * * 57 e8 11 f5 2 0 83 c4 4 80 7e 2d 0<"\
"p> Y 71101 1000 40 57 e8 2e 4 0 0 85 c0 75 b4 57 ff 15 * * * * 5"\
"f 5e 33 c0 5b 8b 8c 24 24 3 0 0 33 cc e8 12 38 1 0 81 c4 28 3 0"\
"0 c3 8b 74 24 24 57 ff 15 +14b9a,100 * * * 8b 8c 24 30 3 0 0 5f"\
"8b c6<p> Y 80673 1000 41 50 57 e8 2c 35 0 0 85 c0 f 85 5e ff ff"\
"ff 57 ff 15 * * * * 33 c0 5f 5e 8b 8c 24 2c 6 0 0 33 cc e8 fd 24"\
" 3 0 8b e5 5d c3 8b 74 24 20 57 ff 15 +343a2,100 * * * 8b 8c 24"\
"34 6 0 0 5f 8b c6<p> Y 50499 1000 33 53 55 56 57 ff 35 * * * * e"\
"8 e3 6e 0 0 ff 35 +376cc,1000 * * * 8b f0 89 74 24 18 e8 d2 6e 0"\
" 0 8b f8 3b fe 59 59 f 82 84 0 0 0 8b df 2b de 8d 6b 4<p> Y 7112"\
"9 1000 32 8b ec ff 35 +1aa9d,1000 * * * e8 68 53 0 0 85 c0 59 74"\
" 3 5d ff e0 6a 2 e8 eb 58 0 0 59 5d e9 e0 fe ff ff 33 c0 50 50 5"\
"0 50 50 e8 d0 ff ff ff 83 c4 14<p> Y 71134 1000 3c 8b ec 6a 1 e8"\
" 24 8 1 0 5d ff 25 * * * * 8b ff 55 8b ec 6a 1 e8 11 8 1 0 d9 45"\
" 1c 51 d9 1c 24 ff 75 18 ff 75 14 ff 75 10 ff 75 c ff 75 8 ff 15"\
" +5c92e,1000 * * * 5d c2 18 0<p> Y 71133 1000 30 53 53 53 ff 76"\
"10 ff 15 * * * * 6a 1 ff 76 10 ff 15 +44181,1000 * * * ff 75 ec"\
"e8 66 ae 2 0 ff 75 e8 e8 5e ae 2 0 8b 45 e4 59 59 5f 5e 5b c9<p>"\
" Y 60954 1000 34 ff d0 8b 4c 24 4 51 e8 a9 ff ff ff 8b c 24 8b 5"\
"4 24 1c 8b 44 24 18 52 8b 54 24 18 50 8b 44 24 18 52 8b 54 24 18"\
" 50 52 ff 15 +1000,100 * * * 83 c4 8 c2 14 0<p> Y 51004 1000 41"\
"6a 8 e8 66 3 0 0 59 83 65 fc 0 ff 35 * * * * ff d6 89 45 e4 ff 3"\
"5 +29092,100 * * * ff d6 59 59 89 45 e0 8d 45 e0 50 8d 45 e4 50"\
"ff 75 8 8b 35 * * * * ff d6 59 50 e8 29 3 0 0 89 45 dc<p> Y 7113"\
"6 1000 32 51 51 ff 15 +4a5f1,1000 * * * 83 65 10 0 8d 85 6c ff f"\
"f ff c6 45 a3 0 89 45 c 33 f6 39 75 10 74 5d 6a 17 59 33 c0 8d 7"\
"d a4 f3 ab 8b 45 c 8b 8 89 4d a4<p> Y 71138 1000 34 f7 d8 89 46"\
"8 33 c0 50 50 ff 75 c 89 46 10 50 8b 45 fc 56 66 c7 46 c 1 0 66"\
"c7 46 e 20 0 ff 70 10 ff 15 +4c541,1000 * * * 56 8b f8 e8 ea f7"\
"2 0 59 8b c7<p> Y 50946 1000 6f 53 53 ff 75 14 ff 75 10 33 c0 39"\
" 5d 24 f 95 c0 8d 4 c5 1 0 0 0 50 ff 75 20 ff 15 +1000,100 * * *"\
" 8b f0 89 75 d0 3b f3 f 84 b8 1 0 0 c7 45 fc 1 0 0 0 8d 4 36 83"\
"c0 3 83 e0 fc e8 4a 88 ff ff 89 65 e8 8b c4 89 45 e4 83 4d fc ff"\
" eb 1b 33 c0 40 c3 8b 65 e8 e8 a5 29 0 0 33 db 89 5d e4 83 4d fc"\
" ff 8b 7d d4 8b 75 d0 39 5d e4<p> Y 130805 1000 2b 52 56 e8 f3 0"\
" 0 0 85 c0 75 eb 56 ff 15 +1f4e,1000 * * * 5e 33 c0 5f 8b 8c 24"\
"24 2 0 0 33 cc e8 39 f 0 0 81 c4 28 2 0 0 c3<p> Y 50561 1000 3a"\
"55 8b ec 6a 1 e8 2e 56 0 0 5d ff 25 * * * * 8b ff 55 8b ec 6a 1"\
"e8 1b 56 0 0 d9 45 1c 51 d9 1c 24 ff 75 18 ff 75 14 ff 75 10 ff"\
"75 c ff 75 8 ff 15 +38dfb,1000 * * * 5d<p> Y 71158 1000 41 50 8d"\
" 8d 74 fc ff ff ff 15 +2ff51,1000 * * * 8b f8 c7 45 fc 1 0 0 0 d"\
"9 85 d0 fc ff ff dd 9d ac fc ff ff d9 85 d4 fc ff ff dc 25 * * *"\
" * e8 a1 fa 2 0 8d 8d e0 fc ff ff 8b d8 e8 e4 f7 ff ff 99<p> Y 5"\
"0600 1000 40 55 8b ec 6a 1 e8 df a6 0 0 d9 45 1c 51 51 d9 5c 24"\
"4 d9 45 18 d9 1c 24 ff 75 14 ff 75 10 ff 75 c ff 75 8 ff 15 +402"\
"48,1000 * * * 5d c2 18 0 8b ff 55 8b ec 83 ec 20 d9 45 18 56 d8"\
"45 1c 51 51<p> W 89711 33a0 41 b8 1 0 0 0 e8 6 94 0 0 e8 31 b3 0"\
" 0 50 85 c0 f 85 6d 3 0 0 c6 45 f8 1 8d 4d c4 8d 55 ac b8 1 0 0"\
"0 e8 e4 93 0 0 e8 f b3 0 0 50 85 c0 f 85 a2 1 0 0 e8 e1 ec 0 0 8"\
"9 c3<p> W 89241 3370 62 55 89 e5 81 ec 94 0 0 0 89 9d 6c ff ff f"\
"f 89 b5 70 ff ff ff c7 45 9c 0 0 0 0 c7 45 a0 0 0 0 0 c7 45 a4 0"\
" 0 0 0 8d 4d ec 8d 55 d4 b8 1 0 0 0 e8 6 94 0 0 e8 31 b3 0 0 50"\
"85 c0 f 85 6d 3 0 0 c6 45 f8 1 8d 4d c4 8d 55 ac b8 1 0 0 0 e8 e"\
"4 93 0 0 e8 f b3 0 0 50<p> Y 80918 1000 64 e8 9f 25 0 0 68 +1000"\
",100 * * * ff 15 * * * * e8 bf f9 ff ff 8b f0 85 f6 74 3b 83 3d"\
"5c * * * * 74 32 83 3d 60 * * * * 74 29 8b 46 40 68 * * * * 50 e"\
"8 c9 33 0 0 8b 8e a8 0 0 0 68 * * * * 51 a3 c4 e2 1 10 e8 b3 33"\
"0 0 a3 * * * * 5f 33 c0 5e c2 4 0 cc cc cc cc cc cc cc<p> Y 8071"\
"3 1000 45 8d 55 4 89 95 e4 fd ff ff 8d 45 4 8b 48 fc 89 8d d4 fd"\
" ff ff 8b 55 c 89 95 c8 fc ff ff 8b 45 10 89 85 cc fc ff ff 8b 4"\
"d 4 89 8d d4 fc ff ff ff 15 * * * * 89 45 f4 6a 0 ff 15 +1e98e,1"\
"000 * * * 8d 55 f8 52<p> Y 80723 1000 42 51 ff 75 8 ff 76 10 ff"\
"15 +4817d,1000 * * * 3b c3 89 45 e4 f 8c 98 2 0 0 ff 75 f8 ff 15"\
" * * * * 8b 0 3b 46 24 8b 7e 28 89 45 d0 89 7d d4 7e 3a 8d 45 8"\
"50 8d 45 d0 50 8b ce e8 5b e6 ff ff 3b c3<p> Y 80711 1000 36 5e"\
"e8 83 df ff ff 81 c5 a8 2 0 0 c9 c3 55 8b ec ff 35 +15db2,1000 *"\
" * * e8 f5 23 0 0 85 c0 59 74 3 5d ff e0 6a 2 e8 f4 48 0 0 59 5d"\
" e9 e0 fe ff ff 8b 44 24 4<p> W 89918 2423 51 56 ff 50 10 8b 74"\
"24 14 8b 10 6a 1 56 8b c8 ff 12 85 c0 75 5 e8 c3 ff ff ff 3b ee"\
"7d 2 8b f5 8d 4e 1 8b d1 57 c1 e9 2 8d 78 10 89 7c 24 18 8d 73 1"\
"0 f3 a5 8b ca 83 e1 3 f3 a4 89 68 4 8d 43 c 83 c9 ff f0 f c1 8 4"\
"9 85 c9 5f 7f 8 8b b<p> W 89925 14b8 41 5f 5e 5b 8b 8c 24 90 2b"\
"0 0 33 cc e8 83 14 0 0 8b e5 5d c3 8d b4 24 30 12 0 0 bf 19 0 0"\
"0 8d a4 24 0 0 0 0 8b c6 8d 50 1 8a 8 83 c0 1 84 c9 75 f7 2b c2"\
"74 7 56 53 e8 7 c 0 0<p> W 80739 1e14 60 52 d9 5c 24 20 d9 84 24"\
" 80 0 0 0 d9 5c 24 24 d9 84 24 84 0 0 0 d9 5c 24 28 e8 8c fd ff"\
"ff 84 c0 f 84 a8 0 0 0 d9 44 24 1c d9 54 24 40 d9 44 24 20 d9 54"\
" 24 44 d8 6c 24 2c d9 5c 24 14 d9 44 24 14 d9 e1 d9 5c 24 14 d9"\
"44 24 14 d9 c0 d9 44 24 28 de e3 d9 ca d9 5c 24 14 d9 44 24 14<p"\
"> W 70985 80 50 c 20 52 8d 48 41 3c de 48 41 3c de 48 41 3c de 4"\
"1 39 af de 4b 41 3c de 48 41 3d de fb 41 3c de 27 37 96 de a2 40"\
" 3c de 27 37 a2 de 1d 41 3c de 27 37 93 de 7c 41 3c de 27 37 97"\
"de f0 41 3c de 27 37 a7 de 49 41 3c de 27 37 a6 de 49 41 3c de<p"\
"> Y 71185 1000 3b f 84 a8 2d 0 0 6a 1 ff 15 +4c80,1000 * * * 66"\
"85 c0 f 84 df 0 0 0 80 3d * * * * f 85 d2 0 0 0 8b 6c 24 14 d9 4"\
"4 2b 1c e8 1f 47 0 0 d9 44 2b 18 8b f8 e8 14 47 0 0<p> Y 71958 1"\
"000 34 d9 9c 24 5c 1 0 0 8b 8c 24 5c 1 0 0 51 52 68 * * * * e8 1"\
"b 93 ff ff 6a 1 ff 15 +4199,1000 * * * 66 85 c0 74 74 83 3d 3c 1"\
"4 52 67 a 7e 6b c6 47 8 1<p> Y 50647 1000 47 8b c2 80 7c 18 2c 0"\
" f 84 a8 2d 0 0 6a 1 ff 15 +4b60,1000 * * * 66 85 c0 f 84 df 0 0"\
" 0 80 3d ca 6 f7 66 0 f 85 d2 0 0 0 8b 6c 24 14 d9 44 2b 1c e8 a"\
"f 47 0 0 d9 44 2b 18 8b f8 e8 a4 47 0 0 d9 44 2b 14<p> Y 60906 1"\
"000 33 0 c3 55 8b ec 51 8d 55 fc 89 75 fc a7 f8 59 62 39 f8 34 5"\
"9 62 d +1000,100 * * * a7 f8 59 62 c f8 34 14 a7 f8 34 a7 f8 36"\
"a6 f8 17 14 a7 f8 59 62 8 f8 37<p> W 71191 80 50 72 75 c9 ab 36"\
"14 a7 f8 36 14 a7 f8 36 14 a7 f8 59 62 3b f8 34 14 a7 f8 59 62 3"\
"9 f8 34 14 a7 f8 59 62 d f8 3d 14 a7 f8 59 62 c f8 34 14 a7 f8 3"\
"f 6c 34 f8 33 14 a7 f8 36 14 a6 f8 17 14 a7 f8 59 62 8 f8 37 14"\
"a7 f8 59 62 3a f8 37 14 a7 f8<p> Y 50651 1000 51 33 ed ff 15 +23"\
"1a4,1000 * * * f af c6 33 c5 50 e8 85 5f 1 0 83 c4 4 e8 8a 5f 1"\
"0 99 b9 * * * * f7 f9 8a 44 24 13 8a da 3a d8 75 6d e8 73 5f 1 0"\
" 99 b9 6 0 0 0 f7 f9 83 fa 3 7d 14 e8 61 5f 1 0 f b6 c0 99 b9 *"\
"* * * f7 f9 2 da<p> Y 50649 1000 41 83 c7 8 89 45 80 8b 47 fc 89"\
" 45 84 8d 45 9c 50 ff 75 88 f be c2 ff 75 e0 89 7d d4 50 ff 75 9"\
"8 8d 45 80 53 50 ff 35 +3af45,1000 * * * e8 5a 2b 0 0 59 ff d0 8"\
"b 7d e8 83 c4 1c 81 e7 80 0 0 0 74 1a<p> Y 80753 1000 42 57 8d 8"\
"5 e8 fd ff ff 50 ff 15 +556ee,1000 * * * 8d 85 ec fe ff ff 33 db"\
" 89 45 fc 43 8b 86 * * * * 85 c0 74 e 83 78 58 0 74 8 8b 40 64 8"\
"9 45 f4 eb 4 83 65 f4 0 * * e8 23 a2 3 0 85 c0 59 74 b<p> Y 7196"\
"1 134f 42 79 6e 4b dc f9 24 bf 64 ab 58 f2 fd df 3b 4d 79 8f 76"\
"17 17 f 20 48 87 9e 9e 3a 9 +1000,100 * * * 92 36 6a 9c 5d 7d f1"\
" 62 b c9 b1 e8 97 e1 cd 8 f4 72 e1 f eb e3 67 17 96 8d eb 6e 1e"\
"48 50 58 aa 50<p> Y 50658 1000 41 83 c7 8 89 45 80 8b 47 fc 89 4"\
"5 84 8d 45 9c 50 ff 75 88 f be c2 ff 75 e0 89 7d d4 50 ff 75 98"\
"8d 45 80 53 50 ff 35 +3af45,1000 * * * e8 5a 2b 0 0 59 ff d0 8b"\
"7d e8 83 c4 1c 81 e7 80 0 0 0 74 1a<p> Y 82930 1000 22 14 0 16 0"\
" f0 13 fe 7e 26 0 28 0 10 14 fe 7e 3f 0 0 0 0 0 0 0 0 0 0 0 +966"\
"66632,10 * * * a0 6<p> Y 80784 1000 44 50 c6 44 24 c 0 e8 68 35"\
"3 0 8b 94 24 18 4 0 0 83 c4 c 8d 8c 24 10 4 0 0 51 52 8d 44 24 8"\
" 50 ff 15 +35006,1000 * * * 8b d * * * * 83 c4 c 51 51 8d 54 24"\
"8 52 56 e8 72 3e 0 0 83 c4 c 8b c8<p> Y 71998 1000 55 e8 cc ca f"\
"f ff 85 c0 74 13 8b 45 8 3b c1 74 4a 8b 11 89 10 8b 49 4 89 48 4"\
" eb 3e d9 45 c d8 * +1000,100 * * * df e0 f6 c4 41 8b 45 8 75 22"\
" d9 45 c d9 fa d8 3d * * * * d9 c0 d8 9 d9 5d f8 d8 49 4 8b 4d f"\
"8 89 8 d9 5d fc 8b 4d fc eb c6 d9 ee d9 18<p> Y 50910 4210 c 41"\
"69 6d 53 74 79 6c 65 +68ff3,500 * * *<p> Y 72905 1000 55 e8 14 c"\
"a ff ff 85 c0 74 13 8b 45 8 3b c1 74 4a 8b 11 89 10 8b 49 4 89 4"\
"8 4 eb 3e d9 45 c d8 * +1000,100 * * * df e0 f6 c4 41 8b 45 8 75"\
" 22 d9 45 c d9 fa d8 3d * * * * d9 c0 d8 9 d9 5d f8 d8 49 4 8b 4"\
"d f8 89 8 d9 5d fc 8b 4d fc eb c6 d9 ee d9 18<p> Y 60951 1000 26"\
" 72 65 6e 64 65 72 65 72 2e 74 77 65 61 6b 6e 65 61 72 70 6c 61"\
"6e * * * +100100,10 * * * 0 0 0 0 0 0 0 0 0<p> Y 50752 1000 4f 5"\
"0 8d 45 f4 64 a3 0 0 0 0 8b f1 89 75 f0 83 7e 18 10 72 c 8b 46 4"\
" 50 e8 6a 39 0 0 83 c4 4 c7 46 18 f 0 0 0 c7 46 14 0 0 0 0 c6 46"\
" 4 0 8b ce c7 45 fc 0 0 0 0 ff 15 +5ea2,1000 * * * 8b 6 50 e8 3e"\
" 39 0 0 83 c4 4 8b ce<p> Y 80814 1000 32 52 8b 45 8 50 8b 4d 10"\
"51 8b 55 c 52 6a 0 8d 4d e0 e8 cc 22 fe ff 8b 0 8b 48 4 51 ff 15"\
" +a4da,1000 * * * 89 45 fc 83 7d fc 0 74 33 83 7d f0 0 75 2d<p>"\
"Y 60955 3aa1 3c 3f 24 62 61 ce 6 3c 35 13 +1000,100 * * * 32 86"\
"fd 4e 35 ce d8 b1 d 45 2d 6 3c 35 1e ac 23 af f7 c6 d2 39 37 7f"\
"31 ce a6 6e 4d af 82 9c a3 22 8 a7 b0 8f b1 79 f7 * * * * b7 bf<"\
"p> Y 90907 202 48 95 89 ac 24 a6 34 2c e 5d d7 15 f2 83 ce 95 d"\
"fd 3c 3b 7a 14 62 88 8a 6e da 5 4d 25 4c d6 ea 3e 9c ad f 97 7d"\
"8c af d8 d5 9e c1 3f c2 +1000,100 * * * 7d de bc 32 8c 4d ed 39"\
"8a 7 d8 8e 20 df 4d f3 aa dd 1b 9d e1 dc<p> Y 50791 1000 33 57 5"\
"3 ff 75 24 ff 15 +131d4,1000 * * * 89 45 f8 57 e8 b2 dd ff ff 59"\
" ff 75 f4 e8 a9 dd ff ff 8b 45 f8 59 8d 65 e4 5f 5e 5b 8b 4d fc"\
"33 cd e8 66 d6 ff ff c9 c3.";
*/