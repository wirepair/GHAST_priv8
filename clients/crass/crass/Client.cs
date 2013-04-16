using System;
using System.Net;
using System.Net.Sockets;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace crass
{
    class Client
    {
        protected IPAddress PnkBstrAIP = IPAddress.Loopback;
        protected IPEndPoint ep = null;
        protected EndPoint localep = new IPEndPoint(IPAddress.Loopback, 0);
        protected Socket s = null;
        protected int port = 44301;
        public Client(int port)
        {
            this.port = port;
            this.ep = new IPEndPoint(this.PnkBstrAIP, this.port);
            this.s = new Socket(AddressFamily.InterNetwork, SocketType.Dgram, ProtocolType.Udp);
            this.s.Bind(localep);
        }

        public byte[] Format(string cmd)
        {
            string cmd_buf = cmd.Replace("{NULL}", "\0");
            return Encoding.ASCII.GetBytes(cmd_buf);
        }

        public byte[] SendByteBufferGetBytes(byte[] buffer)
        {
            byte[] out_buf = new byte[1400];
            if (this.ep != null)
            {
                Console.WriteLine("Sending...");

                this.s.SendTo(buffer, this.ep);
                this.s.Receive(out_buf);
                return out_buf;
            }
            return null;
        }

        public string SendByteBufferGetString(byte[] buffer)
        {
            return Encoding.ASCII.GetString(SendByteBufferGetBytes(buffer));
        }

        public byte[] SendStringBufferGetBytes(string buffer)
        {
            return SendByteBufferGetBytes(this.Format(buffer));
        }
        
        public string SendStringBufferGetString(string buffer)
        {
            return Encoding.ASCII.GetString(SendStringBufferGetBytes(buffer));
        }
    }
}
