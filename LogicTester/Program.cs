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

            var andGate = logicGraph.addGate(LogicSharp.GateType.And);

            logicGraph.inputToGate(andGate,0);
            logicGraph.inputToGate(andGate,1);

            logicGraph.feedInputString("00");
            Console.WriteLine("out: {0}",logicGraph.testOutput(andGate));

            logicGraph.feedInputString("01");
            Console.WriteLine("out: {0}",logicGraph.testOutput(andGate));

            logicGraph.feedInputString("11");
            Console.WriteLine("out: {0}",logicGraph.testOutput(andGate));

            Console.ReadLine();
        }
    }
}
