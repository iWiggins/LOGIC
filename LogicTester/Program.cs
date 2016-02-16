using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace LogicTester
{
    class Program
    {
        static void Main(string[] args)
        {
            Console.WriteLine("Starting.");
            Console.ReadLine();
            LogicSharp.LogicSimulator.CreateLogicGraph(2,1);
            Console.WriteLine("Deleting.");
            Console.ReadLine();
            LogicSharp.LogicSimulator.DestroyLogicGraph();
            Console.ReadLine();
        }
    }
}
