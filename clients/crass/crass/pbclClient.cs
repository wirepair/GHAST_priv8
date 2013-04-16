using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

/*
 * recvfrom [10]:
{
61 62 31 65 61 65 64 61  39 00                   ab1eaeda 9. <-- handshake
}
sendto [10]:
{
61 63 63 38 32 31 39 39  63 00                   acc82199 c. <--- pnkbstrb's session_id
}
recvfrom [10]:
{
68 62 34 61 30 64 64 39  37 00                   hb4a0dd9 7. <-- pbcl.dll's response + gimmie hash
}
sendto [34]:
{
68 34 41 39 44 34 35 33  43 46 38 44 43 38 36 37 h4A9D453 CF8DC867 <--- pnkbstrb responds with hash
42 34 37 36 33 30 46 45  32 37 42 43 35 32 41 43 B47630FE 27BC52AC
38 00                                            8.
}
recvfrom [78]:
{
65 63 63 38 32 31 39 39  63 20 0D 8B BD 3C D2 49 ecc82199 c....<.I <-- pbcl sends pnkbstrb sessionid + encoded data.
60 C6 E3 7D 93 28 D4 CA  EF 0E 9C 24 E1 B4 44 86 `..}.(.. ...$..D.
39 F8 D7 65 00 E0 8A 3F  2E 89 1A 7E BE CD A9 CF 9..e...? ...~....
E0 C6 14 53 6C A0 6C EB  2D E8 95 A2 94 15 F0 DF ...Sl.l. -.......
7D D0 19 27 A6 6A 3A 9D  62 4C 44 43 AD F5       }..'.j:. bLDC..
}
 * */
namespace crass
{
    class pbclClient : Client
    {
        byte[] pnkbstrb_sessionid = new byte[8];
        const string handshake = "ab1eaeda9{NULL}";
        byte[] pnkbstrb_hash = new byte[34];
        byte[] bytes = { 0x8C,0xD8,0x95,0xA2,0xFF,0xAA, // e<pnkbstr_sessionid> <data>
                         0x94,0x65,0x23,0x0D,0x66,0x06,0x60,0x99,0xBC,0x7E,0xAA,0xBB,0xD2,0xD6,0xFC,0x43,
                         0x86,0x19,0xCB,0x3A,0xDE,0x7C,0x95,0x98,0xF7,0xBC,0xC4,0x58,0xAB,0xFB,0x05,0xAA,
                         0x14,0x16,0x79,0x66,0x5E,0x1E,0x01,0x57,0x16,0xF7,0xA8,0xEE,0xB3,0x02,0xD5,0x07,
                         0xDE,0xDB,0x0D,0x60,0xE8,0xAC,0x73,0x4C,0x3A,0x66,0x09,0xC7,0x53};

        public pbclClient(int port) : base(port) {}

        public string SendHandshake()
        {
            byte[] out_buf = this.SendStringBufferGetBytes(handshake);
            // skip command part of the session id.
            Array.ConstrainedCopy(out_buf, 1, pnkbstrb_sessionid, 0, pnkbstrb_sessionid.Length); // remove null
            Console.WriteLine("Session Id Length: {0}", pnkbstrb_sessionid.Length);
            return Encoding.ASCII.GetString(pnkbstrb_sessionid);
        }

        public string GetPnkBstrBHash()
        {
            byte[] bnonce = new byte[10];
            StringBuilder sb = new StringBuilder();
            // buh++
            uint nonce = Convert.ToUInt32(Encoding.ASCII.GetString(pnkbstrb_sessionid), 16);

            nonce = unchecked(0x6EA383A * nonce - 0x270B0FC1); // their challenge/response algo.
            sb.Append('h');
            sb.Append(nonce.ToString("x"));
            sb.Append('\x00');
            Console.WriteLine("pbcl_gethash request: {0}", sb.ToString());
            byte[] out_buf = this.SendStringBufferGetBytes(sb.ToString());
            Array.ConstrainedCopy(out_buf, 1, pnkbstrb_hash, 0, pnkbstrb_hash.Length);
            return Encoding.ASCII.GetString(pnkbstrb_hash);
        }
        public string SendFirstEncryptedData()
        {
            int idx = 0;
            byte[] send_buf = new byte[1 + pnkbstrb_sessionid.Length + 1 + this.bytes.Length];
            send_buf[idx] = Convert.ToByte('e');
            Array.ConstrainedCopy(pnkbstrb_sessionid, 0, send_buf, 1, pnkbstrb_sessionid.Length);
            idx += pnkbstrb_sessionid.Length + 1;
            send_buf[idx] = Convert.ToByte(' ');
            Array.ConstrainedCopy(this.bytes, 0, send_buf, idx, this.bytes.Length); 
            byte[] out_buf = this.SendByteBufferGetBytes(send_buf);
            return "";
        }
        public byte[] Decrypt(byte[] input)
        {
            byte[] output = new byte[input.Length];
            uint nonce = Convert.ToUInt32(Encoding.ASCII.GetString(pnkbstrb_sessionid), 16);
            uint key = 0x24A7AC37 - 0x345A59E0 * nonce;
            if (key == 0x24A7AC37)
            {
                key = 2304;
            }
            Console.WriteLine("Decryption key is: {0:x}", key);
            return output;
        }
        public byte[] Encrypt(byte[] input)
        {
            byte[] output = new byte[input.Length];
            return output;
        }

        public void TestDecrypt(byte[] input)
        {
            
        }
    }
}
