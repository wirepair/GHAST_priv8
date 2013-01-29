using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Runtime.InteropServices;

using Mono.Options;
using ServiceTools;

namespace AAA
{
    class Program
    {
        static void Main(string[] args)
        {
            bool showHelp = false;
            bool install = false;
            bool uninstall = false;
            string pnkbstrFile = null;
            string serviceName = null;
            var p = new OptionSet() {
                { "i|install", 
                  "install pnkbstrA|B.",
                   v => install = v != null },
                { "u|uninstall",
                  "uninstall pnkbstrA|B.",
                  v => uninstall = v != null},
                { "s|service=",
                  "service name pnkbstrA|B.",
                  v => serviceName = v},
                { "f|file=",
                  "the path to pnkbstrA|B.exe.",
                  v => pnkbstrFile = v },
                { "h|?|help",  "show this message and exit", 
                  v => showHelp = v != null },
            };
            try
            {
                p.Parse(args);
                if (showHelp || (install == false && uninstall == false))
                {
                    ShowHelp(p, null);
                    return;
                }
                if (serviceName == null || serviceName.Equals(""))
                {
                    ShowHelp(p, "ERROR! Service name is required (should be pnkbstra or pnkbstrb)");
                    return;
                }

                if (install)
                {
                    if ((pnkbstrFile == null || pnkbstrFile.Equals("")))
                    {
                        ShowHelp(p, "ERROR! Path to PnkBstrA|B.exe is required!");
                        return;
                    }
                    Console.WriteLine("Installing {0} using exe {1}", serviceName, pnkbstrFile);
                    InstallPnkBstr(p, pnkbstrFile, serviceName);
                }
                else if (uninstall)
                {
                    UninstallPnkBstr(serviceName);
                }
               
            }
            catch (OptionException e)
            {
                Console.WriteLine("Try `AAA --help' for more information {0}.", e.Message);
                return;
            }
        }

        static void InstallPnkBstr(OptionSet p, string pnkbstrFile, string serviceName)
        {
            if (ServiceTools.ServiceInstaller.ServiceIsInstalled(serviceName))
            {
                Console.WriteLine("Service is already installed!");
                return;
            }
            try
            {
                ServiceTools.ServiceInstaller.Install(serviceName, serviceName, pnkbstrFile);
                Console.WriteLine("Service Installed!");
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

        static void ShowHelp (OptionSet p, string error)
        {
            
            if (error != null)
            {
                Console.WriteLine(error);
                Console.WriteLine();
            }
            Console.WriteLine("Usage: AAA [OPTIONS]");
            Console.WriteLine("Used to install or uninstall the PnkBstrA|B service for debugging..");
            Console.WriteLine();
            Console.WriteLine("Options:");
            p.WriteOptionDescriptions(Console.Out);
            Console.WriteLine("Example Usage: AAA -i -s=PnkBstrB -f \"C:\\tools\\pin\\ia32\\bin\\pin.exe -t C:\\tools\\pin\\MemWatcher.dll -o C:\\tools\\pin\\MemWatcherB.log -- C:\\tools\\PnkBstrB.exe\"");        
        }
    }
}
