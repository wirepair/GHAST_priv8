using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace FnkBstrA
{
    class Program
    {
        static void Main(string[] args)
        {
            FnkBstrA service = new FnkBstrA(44301);
            service.SetRegistryKeys();
            service.StartListening();
        }
    }
}
