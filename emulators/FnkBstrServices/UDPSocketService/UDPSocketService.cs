using System;
using System.Net;
using System.Net.Sockets;
using System.Text;
using System.Threading;


namespace SocketService
{
    // State object for reading client data asynchronously
    public class StateObject
    {
        public EndPoint endPoint = null;
        public Socket workSocket = null;
        public const int BUFFER_SIZE = 1400;
        public byte[] buffer = new byte[BUFFER_SIZE];
        // Received data as a string.
        public StringBuilder sb = new StringBuilder();
    }

    public abstract class UDPSocketService
    {
        public ManualResetEvent allDone = new ManualResetEvent(false);
        protected int _port = 44301;
        protected IPEndPoint _ilocalEp = null;

        public UDPSocketService( ) { }
        public UDPSocketService( int port )
        {
            _port = port;
            _ilocalEp = new IPEndPoint( IPAddress.Loopback, _port );
        }
        public UDPSocketService( int port, IPEndPoint ep )
        {
            _port = port;
            _ilocalEp = ep;
        }

        // must be implemented by FnkBstr{A|B}
        public abstract void ProcessBuffer( StateObject state );

        // Socket handling codez
        public void StartListening()
        {
            EndPoint localEp = ( EndPoint )_ilocalEp;
            Socket listener = new Socket( AddressFamily.InterNetwork,
                                          SocketType.Dgram, 
                                          ProtocolType.Udp );
            try
            {
                listener.Bind( localEp );
                while ( true )
                {
                    allDone.Reset();
                    StateObject so = new StateObject();
                    so.workSocket = listener;
                    Console.WriteLine( "Waiting for a connection..." );
                    IAsyncResult result = 
                    listener.BeginReceiveFrom( so.buffer,
                                              0,
                                              StateObject.BUFFER_SIZE,
                                              SocketFlags.None,
                                              ref localEp,
                                              new AsyncCallback( this.OnReceive ), so );
                    allDone.WaitOne();
                }

            }
            catch ( Exception e )
            {
                Console.WriteLine( e.ToString() );
            }
        }
        public void OnReceive( IAsyncResult asyncResult )
        {
            try
            {
                Console.WriteLine( "Got some data..." );
                StateObject so = ( StateObject )asyncResult.AsyncState;
                Socket s = so.workSocket;
                IPEndPoint sender = new IPEndPoint( IPAddress.Any, 0 );
                EndPoint tempRemoteEP = ( EndPoint )sender;
                int read = s.EndReceiveFrom( asyncResult, ref tempRemoteEP );
                Console.WriteLine( "Read is {0}", read );
                if ( read > 0 )
                {
                    StateObject processState = new StateObject();
                    processState.endPoint = tempRemoteEP;
                    processState.buffer = so.buffer;
                    processState.sb.Append( Encoding.ASCII.GetString( so.buffer, 0, read ) );
                    ProcessBuffer(processState);
                }
            }
            catch ( Exception e )
            {
                Console.WriteLine( "Exception occurred in OnReceive {0}", e.Message );
            }
            finally
            {
                allDone.Set();
            }
        }
        public void SendData( StateObject sendState, AsyncCallback callback )
        {
            sendState.workSocket.BeginSendTo( sendState.buffer, 0, sendState.buffer.Length, SocketFlags.None, sendState.endPoint, callback, sendState );
        }

        public void SendData( StateObject sendState, int offset, AsyncCallback callback )
        {
            sendState.workSocket.BeginSendTo( sendState.buffer, offset, sendState.buffer.Length, SocketFlags.None, sendState.endPoint, callback, sendState );
        }

        // Only for testing really so like, Don't use it
        public void OnSent( IAsyncResult asyncResult )
        {
            StateObject so = ( StateObject )asyncResult.AsyncState;
            if ( so != null )
            {
                // sent
                Socket s = so.workSocket;
                int sent = s.EndSendTo( asyncResult );
                Console.WriteLine( "The size of the message sent was :" + sent.ToString() );
                return;
            }
            
        }

    }
}

