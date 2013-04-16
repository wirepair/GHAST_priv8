using System;
using System.Net;
using System.Net.Sockets;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;

namespace SocketService
{
    // State object for reading client data asynchronously
    public class StateObject
    {
        #region Properties
        public EndPoint endPoint = null;
        public Socket workSocket = null;
        public const int BUFFER_SIZE = 1400;
        public int recvSize = 0;
        public byte[] buffer = new byte[BUFFER_SIZE];
        // Received data as a string.
        public StringBuilder sb = new StringBuilder();
        #endregion Properties
    }

    public abstract class UDPServices
    {
        #region Properties
        public ManualResetEvent allDone = new ManualResetEvent(false);
        protected IPEndPoint _iep = null;
        #endregion Properties

        #region Constructors
        public UDPServices( ) { }
        public UDPServices(int port)
        {
            _iep = new IPEndPoint(IPAddress.Loopback, port);
            
        }
        public UDPServices( IPEndPoint ep )
        {
            _iep = ep;
        }
        #endregion

        #region abstract Methods
        public abstract void ProcessBuffer(StateObject state);
        // server will just capture the event, client will immediately call BeginRecieveFrom
        public abstract void OnSent(IAsyncResult asyncResult);
        #endregion

        public void OnReceive(IAsyncResult asyncResult)
        {
            try
            {
                Console.WriteLine("Got some data...");
                StateObject so = (StateObject)asyncResult.AsyncState;
                Socket s = so.workSocket;
                IPEndPoint sender = new IPEndPoint(IPAddress.Any, 0);
                EndPoint tempRemoteEP = (EndPoint)sender;
                int read = s.EndReceiveFrom(asyncResult, ref tempRemoteEP);
                Console.WriteLine("Read is {0}", read);
                if (read > 0)
                {
                    StateObject processState = new StateObject();
                    processState.endPoint = tempRemoteEP;
                    processState.buffer = so.buffer;
                    processState.workSocket = s;
                    processState.recvSize = read;
                    processState.sb.Append(Encoding.ASCII.GetString(so.buffer, 0, read));
                    ProcessBuffer(processState);
                }
            }
            catch (Exception e)
            {
                Console.WriteLine("Exception occurred in OnReceive {0}", e.Message);
                Console.WriteLine(e.StackTrace);
            }
            finally
            {
                allDone.Set();
            }
        }
        public void SendData(StateObject sendState, AsyncCallback callback)
        {
            sendState.workSocket.BeginSendTo(sendState.buffer, 0, sendState.buffer.Length, SocketFlags.None, sendState.endPoint, callback, sendState);
        }

        public void SendData(StateObject sendState, int offset, AsyncCallback callback)
        {
            sendState.workSocket.BeginSendTo(sendState.buffer, offset, sendState.buffer.Length, SocketFlags.None, sendState.endPoint, callback, sendState);
        }

        
    }
}
