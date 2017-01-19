using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;

namespace LogicSharp
{
    public enum GateType
    {
        And = 0,
        Or = 1,
        Not = 2,
        Nand = 3,
        Nor = 4,
        Xor = 5
    }

    public unsafe class LogicGraph
    {
        #region DLL Imports

        /// <summary>
        /// Creates the LogicGraph instance.
        /// </summary>
        [DllImport("LogicGraph.dll",CallingConvention = CallingConvention.Cdecl)]
        private static extern void* CreateLogicGraph(int inputCount,int outputCount);

        /// <summary>
        /// Destroys the LogicGraph instance.
        /// </summary>
        [DllImport("LogicGraph.dll",CallingConvention = CallingConvention.Cdecl)]
        private static extern void DestroyLogicGraph(void* logicGraph);

        /// <summary>
        /// Adds a gate to the logic graph.
        /// </sumary>
        /// <params>
        /// type: The type of gate to add:
        /// 0: AND
        /// 1: OR
        /// 2: NOT
        /// 3: NAND
        /// 4: NOR
        /// 5: XOR
        /// </params>
        /// <returns>
        /// 0: Invalid type.
        /// Else: The key of the gate added.
        /// </returns>
        [DllImport("LogicGraph.dll",CallingConvention = CallingConvention.Cdecl)]
        private static extern uint addGate(void* logicGraph,int type);

        /// <summary>
        /// Connects two gates.
        /// </summary>
        /// <returns>
        ///  0: Success
        ///  1: Input already exists
        ///  2: Given key is an output
        ///  3: (for inverter) Already has an input
        /// -1: (for input) This is an input node, it cannot have an input added
        /// </returns>
        [DllImport("LogicGraph.dll",CallingConvention = CallingConvention.Cdecl)]
        private static extern sbyte connectGates(void* logicGraph,uint gate,uint input);

        /// <summary>
        /// Removes an input from the gate.
        /// </summary>
        /// <params>
        /// k: The key of the input to remove.
        /// remOut: Whether or not to remove this node from the outputs list of the input being removed.
        /// </params>
        /// <returns>
        ///  0: Success
        /// -1: Node has no inputs.
        /// -2: Passed key is not an input.
        /// -3: This gate is not an output to passed input.
        /// -4: (for input) This is an input node, it cannot have an input removed
        /// </returns>
        [DllImport("LogicGraph.dll",CallingConvention = CallingConvention.Cdecl)]
        private static extern sbyte disconnectGates(void* logicGraph,uint gate,uint input);

        /// <summary>
        /// Removes the gate from the graph.
        /// </summary>
        /// <returns>
        /// -3: That key does not exist.
        /// -2: An input does not list this as an output. (from Node.disconnect)
        /// -1: An output does not list this as an input. (from Node.disconnect)
        ///  0: Success
        /// </returns>
        [DllImport("LogicGraph.dll",CallingConvention = CallingConvention.Cdecl)]
        private static extern sbyte removeGate(void* logicGraph,uint gate);

        /// <summary>
        /// Gets the key of the indexed input gate.
        /// </summary>
        [DllImport("LogicGraph.dll",CallingConvention = CallingConvention.Cdecl)]
        private static extern uint getInputKey(void* logicGraph,int index);

        /// <summary>
        /// Creates a key.
        /// </summary>
        [DllImport("LogicGraph.dll",CallingConvention = CallingConvention.Cdecl)]
        private static extern uint createKey(void* logicGraph);

        /// <summary>
        /// Sets the value of the indexed input.
        /// </summary>
        [DllImport("LogicGraph.dll",CallingConvention = CallingConvention.Cdecl)]
        private static extern void setInputVal(void* logicGraph,int index,bool value);

        /// <summary>
        /// Sets the gate to be the indexed output.
        /// </summary>
        [DllImport("LogicGraph.dll",CallingConvention = CallingConvention.Cdecl)]
        private static extern void openOutput(void* logicGraph,uint gate,int index);

        /// <summary>
        /// Sets the gate to be the indexed output.
        /// </summary>
        [DllImport("LogicGraph.dll",CallingConvention = CallingConvention.Cdecl)]
        private static extern void closeOutput(void* logicGraph,int index);

        /// <summary>
        /// Returns the output with the given index.
        /// </summary>
        /// <returns>
        ///  0: False
        ///  1: True
        /// -1: No inputs (from Node.output)
        /// -2: A higher node returned an error (from Node.output)
        /// -3: An output does not exist.
        /// </returns>
        [DllImport("LogicGraph.dll",CallingConvention = CallingConvention.Cdecl)]
        private static extern sbyte getOutput(void* logicGraph,int index);

        /// <summary>
        /// Returns the output of the gate based on the inputs.
        /// </summary>
        /// <returns>
        ///  0: False
        ///  1: True
        /// -1: No inputs
        /// -2: A higher node returned an error
        /// </returns>
        [DllImport("LogicGraph.dll",CallingConvention = CallingConvention.Cdecl)]
        private static extern sbyte testOutput(void* logicGraph,uint gate);

        /// <summary>
        /// Connects the indexed input to the gate.
        /// </summary>
        /// <returns>
        ///  0: Success
        ///  1: Input already exists
        ///  2: Given key is an output
        ///  3: (for inverter) Already has an input
        /// -1: (for input) This is an input node, it cannot have an input added
        /// </returns>
        [DllImport("LogicGraph.dll",CallingConvention = CallingConvention.Cdecl)]
        public static extern sbyte inputToGate(void* logicGraph,uint gate,int index);

        /// <summary>
        /// Removes the indexed input from the gate.
        /// </summary>
        /// <params>
        /// k: The key of the input to remove.
        /// remOut: Whether or not to remove this node from the outputs list of the input being removed.
        /// </params>
        /// <returns>
        ///  0: Success
        /// -1: Node has no inputs.
        /// -2: Passed key is not an input.
        /// -3: This gate is not an output to passed input.
        /// -4: (for input) This is an input node, it cannot have an input removed
        /// </returns>
        [DllImport("LogicGraph.dll",CallingConvention = CallingConvention.Cdecl)]
        public static extern sbyte removeInputToGate(void* logicGraph,uint gate,int index);

        /// <summary>
        /// Removes the connection between two gates.
        /// </summary>
        /// <params>
        /// k: The key of the input to remove.
        /// remOut: Whether or not to remove this node from the outputs list of the input being removed.
        /// </params>
        /// <returns>
        ///  0: Success
        /// -1: Node has no inputs.
        /// -2: Passed key is not an input.
        /// -3: This gate is not an output to passed input.
        /// -4: (for input) This is an input node, it cannot have an input removed
        /// </returns>
        [DllImport("LogicGraph.dll",CallingConvention = CallingConvention.Cdecl)]
        public static extern sbyte removeConnection(void* logicGraph,uint gate0,uint gate1);

        #endregion

        private void* instance;

        public LogicGraph(int inputCount,int outputCount)
        {
            instance = CreateLogicGraph(inputCount,outputCount);
        }

        ~LogicGraph()
        {
            DestroyLogicGraph(instance);
        }

        /// <summary>
        /// Adds a gate to the logic graph.
        /// </sumary>
        /// <params>
        /// type: The type of gate to add:
        /// 0: AND
        /// 1: OR
        /// 2: NOT
        /// 3: NAND
        /// 4: NOR
        /// 5: XOR
        /// </params>
        /// <returns>
        /// 0: Invalid type.
        /// Else: The key of the gate added.
        /// </returns>
        public uint addGate(GateType type)
        {
            return addGate(instance,(int)type);
        }

        /// <summary>
        /// Connects two gates.
        /// </summary>
        /// <returns>
        ///  0: Success
        ///  1: Input already exists
        ///  2: Given key is an output
        ///  3: (for inverter) Already has an input
        /// -1: (for input) This is an input node, it cannot have an input added
        /// </returns>
        public sbyte connectGates(uint gate, uint input)
        {
            return connectGates(instance,gate,input);
        }

        /// <summary>
        /// Removes an input from the gate.
        /// </summary>
        /// <params>
        /// k: The key of the input to remove.
        /// remOut: Whether or not to remove this node from the outputs list of the input being removed.
        /// </params>
        /// <returns>
        ///  0: Success
        /// -1: Node has no inputs.
        /// -2: Passed key is not an input.
        /// -3: This gate is not an output to passed input.
        /// -4: (for input) This is an input node, it cannot have an input removed
        /// </returns>
        public sbyte disconnectGates(uint gate,uint input)
        {
            return disconnectGates(instance,gate,input);
        }

        /// <summary>
        /// Removes the gate from the graph.
        /// </summary>
        /// <returns>
        /// -3: That key does not exist.
        /// -2: An input does not list this as an output. (from Node.disconnect)
        /// -1: An output does not list this as an input. (from Node.disconnect)
        ///  0: Success
        /// </returns>
        public sbyte removeGate(uint gate)
        {
            return removeGate(instance,gate);
        }

        /// <summary>
        /// Gets the key of the indexed input gate.
        /// </summary>
        public uint getInputKey(int index)
        {
            return getInputKey(instance,index);
        }

        /// <summary>
        /// Creates a key.
        /// </summary>
        public uint createKey()
        {
            return createKey(instance);
        }

        /// <summary>
        /// Sets the value of the indexed input.
        /// </summary>
        public void setInputVal(int index,bool value)
        {
            setInputVal(instance,index,value);
        }

        /// <summary>
        /// Sets the gate to be the indexed output.
        /// </summary>
        public void openOutput(uint gate,int index)
        {
            openOutput(instance,gate,index);
        }

        /// <summary>
        /// Sets the indexed output to null.
        /// </summary>
        public void closeOutput(int index)
        {
            closeOutput(instance,index);
        }

        /// <summary>
        /// Returns the output with the given index.
        /// </summary>
        /// <returns>
        ///  0: False
        ///  1: True
        /// -1: No inputs (from Node.output)
        /// -2: A higher node returned an error (from Node.output)
        /// -3: An output does not exist.
        /// </returns>
        public sbyte getOutput(int index)
        {
            return getOutput(instance,index);
        }

        /// <summary>
        /// Returns the output of the gate based on the inputs.
        /// </summary>
        /// <returns>
        ///  0: False
        ///  1: True
        /// -1: No inputs
        /// -2: A higher node returned an error
        /// </returns>
        public sbyte testOutput(uint gate)
        {
            return testOutput(instance,gate);
        }

        /// <summary>
        /// Connects the indexed input to the gate.
        /// </summary>
        /// <returns>
        ///  0: Success
        ///  1: Input already exists
        ///  2: Given key is an output
        ///  3: (for inverter) Already has an input
        /// -1: (for input) This is an input node, it cannot have an input added
        /// </returns>
        public sbyte inputToGate(uint gate,int index)
        {
            return inputToGate(instance,gate,index);
        }

        /// <summary>
        /// Removes the indexed input from the gate.
        /// </summary>
        /// <params>
        /// k: The key of the input to remove.
        /// remOut: Whether or not to remove this node from the outputs list of the input being removed.
        /// </params>
        /// <returns>
        ///  0: Success
        /// -1: Node has no inputs.
        /// -2: Passed key is not an input.
        /// -3: This gate is not an output to passed input.
        /// -4: (for input) This is an input node, it cannot have an input removed
        /// </returns>
        public sbyte removeInputToGate(uint gate,int index)
        {
            return removeInputToGate(instance,gate,index);
        }

        /// <summary>
        /// Removes the connection between two gates.
        /// </summary>
        /// <params>
        /// k: The key of the input to remove.
        /// remOut: Whether or not to remove this node from the outputs list of the input being removed.
        /// </params>
        /// <returns>
        ///  0: Success
        /// -1: Node has no inputs.
        /// -2: Passed key is not an input.
        /// -3: This gate is not an output to passed input.
        /// -4: (for input) This is an input node, it cannot have an input removed
        /// </returns>
        public sbyte removeConnection(uint gate0,uint gate1)
        {
            return removeConnection(instance,gate0,gate1);
        }

        /// <summary>
        /// Sets the inputs based off of the passed string.
        /// </summary>
        public void feedInputString(string input)
        {
            for(int i = 0; i < input.Length; ++i)
            {
                setInputVal(
                    index: i,
                    value: input[i] == '1');
            }
        }
    }
}
