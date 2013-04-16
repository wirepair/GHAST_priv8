using System;
using System.Net;
using System.Net.Sockets;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace crass
{
    class PnkBstrAClient : Client
    {
       
        public PnkBstrAClient(int port) : base(port) {}

        public string SendCommand(string cmd)
        {
            return this.SendStringBufferGetString(cmd);
        }
        
    }
}
