using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Mono.Options;
namespace crass
{
    class Program
    {
        static void Main(string[] args)
        {
            bool show_help = false;
            string cmd_string = null;


            int port = 44301; // Default
            var p = new OptionSet() {
                { "p|port=", "the {PORT} of of the PnkBstrA service.",
                   (int v) => port = v },
                { "c|cmd=", 
                   "the command string to send (cmd's with vars must be enclosed with quotes).",
                    v => cmd_string = v },
                { "h|?|help",  "show this message and exit", 
                   v => show_help = v != null },
            };
            try
            {
                p.Parse(args);
                if (show_help)
                {
                    ShowHelp(p, null);
                    return;
                }
                if (cmd_string == null || cmd_string.Equals("")) {
                    ShowHelp(p, "ERROR! -c is required!");
                    return;
                }
                PnkBstrAClient pnk = new PnkBstrAClient(port);
                Console.WriteLine("PnkBstr Client Created!");
                char cmd = cmd_string[0];
                if (!(cmd != 'l' || cmd != 'm' || cmd != 'u' || cmd != 'v'))
                {
                    ShowHelp(p, "ERROR! Unknown PnkBstrA command requested.");
                    return;
                }

                Console.WriteLine("Sending Command: {0}", cmd_string);
                try
                {
                    Console.WriteLine("Response: {0}\n", pnk.sendCommand(cmd_string));
                }
                catch (System.Net.Sockets.SocketException se)
                {
                    Console.WriteLine("Error Connecting to PnkBstrA, are you sure it's listening on port {0}?", port);
                    Console.WriteLine("Error: {0}", se.Message);
                }
            }
            catch (OptionException e)
            {
                Console.WriteLine("Try `crass --help' for more information {0}.", e.Message);
                return;
            }
        }

        static void ShowHelp (OptionSet p, string error)
        {
            
            if (error != null)
            {
                Console.WriteLine(error);
                Console.WriteLine();
            }
            Console.WriteLine("Usage: crass [OPTIONS]");
            Console.WriteLine("Used to send commands to the PnkBstrA service.");
            Console.WriteLine("Possible commands:");
            Console.WriteLine("\t\"v\" - Retrieves and prints the PnkBstrA version.");
            Console.WriteLine("\t\"u\" - Unloads the PnkBstrB service.");
            Console.WriteLine("\t\"l<path>\" - Creates a new PnkBstrB service and loads specified binary.");
            Console.WriteLine("\t\tExample: \"lC:\\windows\\syswow64\\PnkBstrB.xtr\"");
            Console.WriteLine("\t\"m<pid> <base_addr> <size>\" - Reads <size> bytes of memory at \n\t<base_addr> in the process <pid> to C:\\windows\\{0}\\.", Utils.GetSystemDirectory());

            Console.WriteLine ();
            Console.WriteLine ("Options:");
            p.WriteOptionDescriptions (Console.Out);
        }       
    }
}
