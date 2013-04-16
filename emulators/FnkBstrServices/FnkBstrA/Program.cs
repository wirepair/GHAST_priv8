using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Mono.Options;
namespace FnkBstrA
{
    class Program
    {
        static void ShowHelp(OptionSet p, string error)
        {
            if (error != null)
            {
                Console.WriteLine(error);
                Console.WriteLine();
            }
            Console.WriteLine("Usage: FnkBstrA [OPTIONS]");
            Console.WriteLine("Used to emulate the PnkBstrA service.");
            Console.WriteLine("Possible commands:");
            Console.WriteLine();
            p.WriteOptionDescriptions(Console.Out);
            Console.WriteLine("Example:\nFnkBstrA -i \"C:\\tools\\pin\\ia32\\bin\\pin.exe -t C:\\tools\\pin\\ia32\\bin\\NetLogger.dll -o C:\\tools\\pin\\ia32\\bin\\socketcall.log -- \"");
        }

        static void Main(string[] args)
        {
            FnkBstrA service = new FnkBstrA(44301);
            bool proxy = false;
            string install_string = null;
            bool show_help = false;
            var p = new OptionSet() 
            {
                { "i|install=", 
                   "How PnkBstrB should be installed.",
                    v => install_string = v },
                { "p|proxy",
                    "Start proxy to intercept PnkBstrB<->pbcl communications.",
                    v => proxy = v != null },
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
                Console.WriteLine("Shouldn't be here...");
                if (install_string != null)
                {
                    service.InitPnkBstrB(install_string);
                }
                else
                {
                     service.InitPnkBstrB("C:\\tools\\pin\\ia32\\bin\\pin.exe -t C:\\tools\\pin\\ia32\\bin\\MemWatcher.dll -o C:\\tools\\pin\\ia32\\bin\\memwrite.log -- ");
                }
                if (proxy != false)
                {
                    service.ConfigureProxy();
                }
                service.SetRegistryKeys();
                service.StartListening();
            }
            catch (Mono.Options.OptionException oe)
            {
                ShowHelp(p, oe.Message);
                return;
            }
            
        }
    }
}
