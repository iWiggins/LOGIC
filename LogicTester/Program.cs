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
            LogicSharp.LogicSimulator.CreateLogicGraph(2,1);

            var keyNot = LogicSharp.LogicSimulator.addGate(LogicSharp.GateType.Not);
            var keyAnd = LogicSharp.LogicSimulator.addGate(LogicSharp.GateType.And);
            var keyOr = LogicSharp.LogicSimulator.addGate(LogicSharp.GateType.Or);

            LogicSharp.LogicSimulator.connectGates(keyOr,keyAnd);

            LogicSharp.LogicSimulator.inputToGate(keyAnd,0);

            LogicSharp.LogicSimulator.inputToGate(keyOr,1);

            LogicSharp.LogicSimulator.connectGates(keyNot,keyOr);

            var code = LogicSharp.LogicSimulator.connectGates(keyAnd,keyNot);

            //Action<string> act = (string s) => {

            //    LogicSharp.LogicSimulator.feedInputString(s);

            //    var outNot = LogicSharp.LogicSimulator.testOutput(keyNot);
            //    var outAnd = LogicSharp.LogicSimulator.testOutput(keyAnd);

            //    Console.WriteLine("x0={0} x1={1}",s[0],s[1]);
            //    Console.WriteLine("Notx1={0}",outNot);
            //    Console.WriteLine("x0 and Notx1={0}",outAnd);
            //};

            //act("11");

            Console.ReadLine();
        }
    }
}
