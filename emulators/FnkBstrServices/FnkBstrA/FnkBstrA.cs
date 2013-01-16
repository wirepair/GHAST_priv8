using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using SocketService;
using System.Net.Sockets;
using Microsoft.Win32;


namespace FnkBstrA
{
    class FnkBstrA : UDPSocketService
    {
        protected int _version = 1033;
        protected const string pnkBstrASubKey = "SOFTWARE\\Even Balance\\";
        protected const string serviceKey = "PnkBstrA";
        protected const string returnOk = "l0";
        protected const string returnFail = "l1";
        protected const string returnTooManyLoads = "l2";

        public FnkBstrA( int port )
            : base( 44301 )
        {
            _port = port;
        }

        public FnkBstrA( int port, int version )
            : base( 44301 )
        {
            _port = port;
            _version = version;
        }

        public string[] ParseMemoryCommand( string command )
        {
            return command.ToString().Split( ' ' );
        }

        public void SetRegistryKeys()
        {
            try
            {
                var hEvenBalanceKey = Registry.LocalMachine.CreateSubKey( pnkBstrASubKey );
                var hServiceKey = hEvenBalanceKey.CreateSubKey( serviceKey );
                hServiceKey.SetValue( "Port", _port );
                hServiceKey.SetValue( "Version", _version );
            }
            catch( Exception e )
            {
                Console.WriteLine( "Probably couldn't set registry keys, no permz?" );
                Console.WriteLine( "Error: {0}", e.Message );
            }
        }
        public override void ProcessBuffer( StateObject state )
        {
            StateObject sendState = new StateObject();
            sendState.endPoint = state.endPoint; // Need this for sending data backsies.
            char command = Encoding.ASCII.GetChars( state.buffer, 0, 1 )[0];
            Console.WriteLine( "In ProcessBuffer, with a command of {0}", command );
            // only 'v' command will return something else.
            sendState.buffer = Encoding.ASCII.GetBytes( returnOk ); 
            switch( command )
            {
                case 'l':
                    Console.WriteLine( "Client sent a service load command: {0} starting PnkBstrB service.", state.sb.ToString() );
                    ServiceTools.ServiceInstaller.StartService( "PnkBstrB" );
                    break;
                case 'm':
                    try
                    {
                        string[] parameters = ParseMemoryCommand( state.sb.ToString() );
                        Console.WriteLine( "Stupid idiot asked us to dump {0} bytes of memory from process {1}, from base addr: {2:X}",
                                           parameters[2],
                                           parameters[0],
                                           parameters[1] );
                    }
                    catch( Exception e )
                    {
                        Console.WriteLine( "Error splitting up the m command values, stupid idiot sent: {0}", state.sb.ToString() );
                        Console.WriteLine( "Message {0}", e.Message );
                    }
                    break;
                case 'u':
                    Console.WriteLine( "Client sent a service unload command, just stopping PnkBstrB.exe." );
                    ServiceTools.ServiceInstaller.StopService( "PnkBstrB" );
                    break;
                case 'v':
                    sendState.buffer = Encoding.ASCII.GetBytes( string.Format( "v{0}", _version ) );
                    break;
            }
            sendState.workSocket = new Socket( AddressFamily.InterNetwork,
                                               SocketType.Dgram,
                                               ProtocolType.Udp );
            SendData( sendState, new AsyncCallback( OnSent ) );
        }
    }
}
