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
            LogicSharp.LogicGraph logicGraph = new LogicSharp.LogicGraph(2,1);

            var keyOr0 = logicGraph.addGate(LogicSharp.GateType.Or);
            var keyOr1 = logicGraph.addGate(LogicSharp.GateType.Or);

            logicGraph.connectGates(keyOr1,keyOr0);

            Console.WriteLine("out: {0}",logicGraph.testOutput(keyOr1));

            Console.ReadLine();
        }
    }
}
