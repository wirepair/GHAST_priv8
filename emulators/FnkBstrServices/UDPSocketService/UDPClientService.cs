using System;
using System.Net;
using System.Net.Sockets;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;

namespace SocketService
{
    public abstract class UDPClientService : UDPServices
    {
        public UDPClientService(int port)
            : base(port)
        { }

        public UDPClientService(IPEndPoint iep)
            : base(iep)
        { }

        #region Client Code
        public StateObject Connect()
        {
            StateObject so = new StateObject();
            EndPoint remoteEp = (EndPoint)_iep;
            try
            {
                Socket remote = new Socket(AddressFamily.InterNetwork,
                                           SocketType.Dgram,
                                           ProtocolType.Udp);
                so.workSocket = remote;
                so.endPoint = remoteEp;
            }
            catch (Exception e)
            {
                Console.WriteLine(e.ToString());
                return null;
            }
            return so;
        }

        public override void OnSent(IAsyncResult asyncResult)
        {
            StateObject so = (StateObject)asyncResult.AsyncState;
            if (so != null)
            {
                // sent
                Socket s = so.workSocket;
                int sent = s.EndSendTo(asyncResult);
                GetResponse(so);
                return;
            }
        }

        public void GetResponse( StateObject so )
        {
            EndPoint remoteEp = (EndPoint)_iep;
            StateObject newso = new StateObject();
            newso.endPoint = remoteEp;
            newso.workSocket = so.workSocket;
            while ( true )
            {
                allDone.Reset();              
                IAsyncResult result = newso.workSocket.BeginReceiveFrom(newso.buffer,
                    0,
                    StateObject.BUFFER_SIZE,
                    SocketFlags.None,
                    ref remoteEp,
                    new AsyncCallback(this.OnReceive), newso);
                allDone.WaitOne();
            }
        }
        #endregion
    }
}
