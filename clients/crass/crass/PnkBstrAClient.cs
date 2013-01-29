using System;
using System.Net;
using System.Net.Sockets;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace crass
{
    class PnkBstrAClient
    {
        private IPAddress PnkBstrAIP = IPAddress.Loopback;
        private IPEndPoint ep = null;
        private EndPoint localep = new IPEndPoint(IPAddress.Loopback, 0);
        private Socket s = null;
        private int port = 44301;
        public PnkBstrAClient(int port)
        {
            this.port = port;
            this.ep = new IPEndPoint(this.PnkBstrAIP, this.port);
            this.s = new Socket(AddressFamily.InterNetwork, SocketType.Dgram, ProtocolType.Udp);
            this.s.Bind(localep);
        }

        public string sendCommand(string cmd)
        {
            byte[] out_buf = new byte[1400];
            if (this.ep != null)
            {
                Console.WriteLine("Sending...");
                
                this.s.SendTo(this.Format(cmd), this.ep);
                this.s.Receive(out_buf);
                return Encoding.ASCII.GetString(out_buf);
            }
            return "";
        }
        public byte[] Format(string cmd)
        {
            string cmd_buf = cmd.Replace("{NULL}", "\0");
            return Encoding.ASCII.GetBytes(cmd_buf);
        }
    }
}
