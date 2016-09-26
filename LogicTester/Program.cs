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

            var keyNot = logicGraph.addGate(LogicSharp.GateType.Not);
            var keyAnd = logicGraph.addGate(LogicSharp.GateType.And);
            var keyOr = logicGraph.addGate(LogicSharp.GateType.Or);

            logicGraph.connectGates(keyOr,keyAnd);

            logicGraph.inputToGate(keyAnd,0);

            logicGraph.inputToGate(keyOr,1);

            logicGraph.connectGates(keyNot,keyOr);

            var code = logicGraph.connectGates(keyAnd,keyNot);

            //Action<string> act = (string s) => {

            //    logicGraph.feedInputString(s);

            //    var outNot = logicGraph.testOutput(keyNot);
            //    var outAnd = logicGraph.testOutput(keyAnd);

            //    Console.WriteLine("x0={0} x1={1}",s[0],s[1]);
            //    Console.WriteLine("Notx1={0}",outNot);
            //    Console.WriteLine("x0 and Notx1={0}",outAnd);
            //};

            //act("11");

            Console.ReadLine();
        }
    }
}
