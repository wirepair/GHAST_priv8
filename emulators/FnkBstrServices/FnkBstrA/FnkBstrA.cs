using System;
using System.Collections.Generic;
using System.Linq;
using System.IO;
using System.Text;
using SocketService;
using System.Net.Sockets;
using Microsoft.Win32;
using System.Security.Cryptography;
using System.Diagnostics;


namespace FnkBstrA
{
    class FnkBstrA : UDPServerService
    {
        public class ProxyData
        {
            public string pnkBstrBSubKey = "SOFTWARE\\Even Balance\\";
            public string pnkBstrBserviceKey = "PnkBstrB";
            public string pnkBstrBWow64SubKey = "SOFTWARE\\Wow6432Node\\Even Balance\\";
            //public string pnkDecrypt = "C:\\Tools\\PnkNetDecryptor.dll";
            public int source_port = 45301;
            public int destination_port = 45308;
            public string proxy_app = "UDPDP.exe";
            public string log_file = "pnkbstrb_packets.log";
            public string host = "127.0.0.1";

        }
        protected int _version = 1036;
        protected int _port = 44301;
        protected string _pnkbstrPath = "C:\\Tools\\";
        protected const string pnkBstrASubKey = "SOFTWARE\\Even Balance\\";
        protected const string pnkBstrAWow64SubKey = "SOFTWARE\\Wow6432Node\\Even Balance\\";
        protected const string serviceKey = "PnkBstrA";
        protected const string returnOk = "l0";
        protected const string returnFail = "l1";
        protected const string returnTooManyLoads = "l2";
        protected ProxyData proxy = null;
        public FnkBstrA( int port )
            : base ( 44301 )
        {
            _port = port;
        }

        public FnkBstrA( int port, int version )
            : base ( 44301 )
        {
            _port = port;
            _version = version;
        }

        public FnkBstrA( int port, int version, string path )
            : base( 44301 )
        {
            _port = port;
            _version = version;
            _pnkbstrPath = path;
        }
        public void ConfigureProxy()
        {
            // 45301 (default pnkbstrb port
            proxy = new ProxyData();
        }
        // reads in the port value that PnkBstrB set, then overwrites it
        // with our proxy port.
        public bool StartProxy()
        {
            try
            {
                LaunchProxyApp();
                System.Threading.Thread.Sleep(500);
                return true;
            }
            catch (Exception e)
            {
                Console.WriteLine("Error starting proxy service: {0}", e.Message);
                proxy = null;
            }
            return false;
        }

        public void OverwritePnkBstrBPort()
        {
            try
            {
                System.Threading.Thread.Sleep(200);
                var hEvenBalanceKey = Registry.LocalMachine.CreateSubKey(proxy.pnkBstrBSubKey);
                var hServiceKey = hEvenBalanceKey.CreateSubKey(proxy.pnkBstrBserviceKey);
                var hWowEvenBalanceKey = Registry.LocalMachine.CreateSubKey(proxy.pnkBstrBWow64SubKey);
                var hWowServiceKey = hWowEvenBalanceKey.CreateSubKey(proxy.pnkBstrBserviceKey);
                proxy.destination_port = (int)hWowServiceKey.GetValue("Port");

                Console.WriteLine("PnkBstrB wrote port: {0} to the registry, overwriting with {1}...", proxy.destination_port, proxy.source_port);
                hWowServiceKey.SetValue("Port", proxy.source_port);
                hServiceKey.SetValue("Port", proxy.source_port);
                Console.WriteLine("Wrote Port: {0} to registry.", proxy.source_port);
            }
            catch (Exception e)
            {
                Console.WriteLine("Error writing port to registry for proxy hijack: {0}", e.Message);
                proxy = null;
            }
        }

        private void LaunchProxyApp()
        {
            string args = string.Format("-s {0}:{1} -d {0}:{3} -o {4} -f json", proxy.host, proxy.source_port, proxy.host, proxy.destination_port, proxy.log_file);
            ProcessStartInfo startInfo = new ProcessStartInfo();
            startInfo.CreateNoWindow = true;
            startInfo.UseShellExecute = true;
            startInfo.FileName = proxy.proxy_app;
            startInfo.WorkingDirectory = "C:\\tools\\";
            Console.WriteLine("Starting UDPDP.exe {0}", args);
            startInfo.Arguments = args;
            Process p = Process.Start(startInfo);
            
        }
        public void InitPnkBstrB(string installCmd)
        {
            string pnkbstrInstallCmd = installCmd + _pnkbstrPath + "PnkBstrB.exe";
            UninstallPnkBstr("PnkBstrB");
            InstallPnkBstr(pnkbstrInstallCmd, "PnkBstrB");
            return;
        }

        public string[] ParseMemoryCommand( string command )
        {
            return command.ToString( ).Split( ' ' );
        }

        static void InstallPnkBstr( string pnkbstrInstallCmd, string serviceName )
        {
            if (ServiceTools.ServiceInstaller.ServiceIsInstalled(serviceName))
            {
                Console.WriteLine("Service is already installed!");
                return;
            }
            try
            {
                ServiceTools.ServiceInstaller.Install(serviceName, serviceName, pnkbstrInstallCmd);
                Console.WriteLine("PnkBstrB Service Installed as: ");
                Console.WriteLine(pnkbstrInstallCmd);

            }
            catch (System.ApplicationException e)
            {
                Console.WriteLine("Error installing service (do you have proper privileges?): {0}", e.Message);
            }
        }

        static void UninstallPnkBstr(string serviceName)
        {
            if (!ServiceTools.ServiceInstaller.ServiceIsInstalled(serviceName))
            {
                Console.WriteLine("Service is already uninstalled!");
                return;
            }
            ServiceTools.ServiceInstaller.Uninstall(serviceName);
            Console.WriteLine("Service Uninstalled!");
        }

        public void SetRegistryKeys( )
        {
            try
            {
                var hEvenBalanceKey = Registry.LocalMachine.CreateSubKey ( pnkBstrASubKey );
                var hServiceKey = hEvenBalanceKey.CreateSubKey ( serviceKey );
                var hWowEvenBalanceKey = Registry.LocalMachine.CreateSubKey(pnkBstrAWow64SubKey);
                var hWowServiceKey = hWowEvenBalanceKey.CreateSubKey(serviceKey);
                hServiceKey.SetValue ( "Port", _port );
                hServiceKey.SetValue ( "Version", _version );
                hWowServiceKey.SetValue("Port", _port);
                hWowServiceKey.SetValue("Version", _version);
                Console.WriteLine("Wrote Port: {0} and Version: {1} to registry.", _port, _version);
            }
            catch ( Exception e )
            {
                Console.WriteLine ( "Probably couldn't set registry keys, no permz?" );
                Console.WriteLine ( "Error: {0}", e.Message );
            }
        }

        public bool CopyNewPnkBstrB( string new_path )
        {
            string pnkbstrFile = _pnkbstrPath+"PnkBstrB.exe";
            string backupFile = null;
            if ( File.Exists ( pnkbstrFile ) )
            {
                try
                {
                    DateTime fileCreatedDate = File.GetCreationTime ( pnkbstrFile );
                    backupFile = string.Format( "{0}PnkBstrB.{1}-{2}-{3}.exe", _pnkbstrPath, fileCreatedDate.Year, fileCreatedDate.Month, fileCreatedDate.Day );
                    if (!File.Exists(backupFile))
                    {
                        File.Move(pnkbstrFile, backupFile);
                        Console.WriteLine("Moved old PnkBstrB {0} to {1}", pnkbstrFile, backupFile);
                    }
                }
                catch ( Exception ex )
                {
                    Console.WriteLine ( "Error backing up file from {0} to {1}. Reason: {2}", pnkbstrFile, backupFile, ex.Message );
                }
            }
            try
            {
                File.Copy ( new_path, pnkbstrFile, true );
                Console.WriteLine( "Copied new file {0} to {1}", new_path, pnkbstrFile );
                return true;
            }
            catch ( Exception ex )
            {
                Console.WriteLine ( "Error copying new file from {0} to {1}. Reason: {2}", new_path, pnkbstrFile, ex.Message );
            }
            return false;
        }

        public bool IsNewPnkBstrB( string new_path )
        {
            string pnkbstrbFile = _pnkbstrPath+"PnkBstrB.exe";
            if ( File.Exists( new_path ) && File.Exists( pnkbstrbFile ) )
            {
                byte[] new_hash = MD5.Create().ComputeHash( File.ReadAllBytes( new_path ) );
                byte[] old_hash = MD5.Create().ComputeHash( File.ReadAllBytes( pnkbstrbFile ) );
                if ( new_hash.SequenceEqual(old_hash) )
                {
                    return false;
                }
            }
            Console.WriteLine( "New PnkBstrB.exe detected, time to bust out IDA :(" );
            return true;
        }

        public override void ProcessBuffer( StateObject state )
        {
            StateObject sendState = new StateObject ( );
            // Need this for sending data backsies.
            sendState.endPoint = state.endPoint;
            // only 'v' command will return something else.
            sendState.buffer = Encoding.ASCII.GetBytes ( returnOk );

            char command = Encoding.ASCII.GetChars ( state.buffer, 0, 1 )[0];
            Console.WriteLine ( "In ProcessBuffer, with a command of {0}", command );
            switch ( command )
            {
                case 'l':
                    Console.WriteLine ( "Client sent a service load command: {0} copying & starting PnkBstrB service.", state.sb.ToString ( ) );
                    // Remove leading 'l' command character and make sure no nulls exist.
                    string newPnkbstrFile = state.sb.ToString().Substring(1).Replace("\0", string.Empty); ;
                    if ( IsNewPnkBstrB( newPnkbstrFile ) )
                    {
                        CopyNewPnkBstrB( newPnkbstrFile );
                    }

                    if (proxy != null)
                    {
                        StartProxy();
                        ServiceTools.ServiceInstaller.StartService("PnkBstrB");
                        OverwritePnkBstrBPort();
                    }
                    else
                    {
                        ServiceTools.ServiceInstaller.StartService("PnkBstrB");
                    }
                    break;
                case 'm':
                    try
                    {
                        string[] parameters = ParseMemoryCommand ( state.sb.ToString ( ) );
                        Console.WriteLine ( "Stupid idiot asked us to dump {0} bytes of memory from process {1}, from base addr: {2:X}",
                                           parameters[2],
                                           parameters[0],
                                           parameters[1] );
                    }
                    catch ( Exception e )
                    {
                        Console.WriteLine ( "Error splitting up the m command values, stupid idiot sent: {0}", state.sb.ToString ( ) );
                        Console.WriteLine ( "Message {0}", e.Message );
                    }
                    break;
                case 'u':
                    Console.WriteLine ( "Client sent a service unload command, just stopping PnkBstrB.exe." );
                    ServiceTools.ServiceInstaller.StopService ( "PnkBstrB" );
                    break;
                case 'v':
                    sendState.buffer = Encoding.ASCII.GetBytes ( string.Format ( "v{0}", _version ) );
                    break;
            }
            sendState.workSocket = new Socket(AddressFamily.InterNetwork,
                                               SocketType.Dgram,
                                               ProtocolType.Udp);
            SendData ( sendState, new AsyncCallback ( OnSent ) );
        }
        ~FnkBstrA()
        {
            UninstallPnkBstr("PnkBstrB");
        }
    }
}
