/// A C style interface for logic graph to be used with DLL imports.
#ifndef Logic_Interface
#define Logic_Interface

#include "LogicGraph.h"

namespace LogicGraph
{
    static LogicGraph* Instance = nullptr;
}

/// <summary>
/// Creates the LogicGraph instance.
/// </summary>
extern "C" __declspec(dllexport) void CreateLogicGraph(int inputCount,int outputCount)
{
    if(LogicGraph::Instance != nullptr) delete LogicGraph::Instance;
    LogicGraph::Instance = new LogicGraph::LogicGraph(inputCount,outputCount);
}

/// <summary>
/// Destroys the LogicGraph instance.
/// </summary>
extern "C" __declspec(dllexport) void DestroyLogicGraph()
{
    if(LogicGraph::Instance != nullptr) delete LogicGraph::Instance;
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
extern "C" __declspec(dllexport) LogicGraph::LogicGraph::Key addGate(int type)
{
    switch(type){
    case  0: return LogicGraph::Instance->addGate(LogicGraph::LogicGraph::Gates::AND);
    case  1: return LogicGraph::Instance->addGate(LogicGraph::LogicGraph::Gates::OR);
    case  2: return LogicGraph::Instance->addInverter();
    case  3: return LogicGraph::Instance->addGate(LogicGraph::LogicGraph::Gates::NAND);
    case  4: return LogicGraph::Instance->addGate(LogicGraph::LogicGraph::Gates::NOR);
    case  5: return LogicGraph::Instance->addGate(LogicGraph::LogicGraph::Gates::XOR);
    default: return 0;
    }
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
extern "C" __declspec(dllexport) LogicGraph::LogicGraph::SByte connectGates(LogicGraph::LogicGraph::Key gate,LogicGraph::LogicGraph::Key input)
{
    return LogicGraph::Instance->connectGates(gate,input);
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
extern "C" __declspec(dllexport) LogicGraph::LogicGraph::SByte disconnectGates(LogicGraph::LogicGraph::Key gate,LogicGraph::LogicGraph::Key input)
{
    return LogicGraph::Instance->disconnectGates(gate,input);
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
extern "C" __declspec(dllexport) LogicGraph::LogicGraph::SByte removeGate(LogicGraph::LogicGraph::Key gate)
{
    return LogicGraph::Instance->removeGate(gate);
}

/// <summary>
/// Gets the key of the indexed input gate.
/// </summary>
extern "C" __declspec(dllexport) LogicGraph::LogicGraph::Key getInputKey(int index)
{
    return LogicGraph::Instance->getInputKey(index);
}

/// <summary>
/// Creates a key.
/// </summary>
extern "C" __declspec(dllexport) LogicGraph::LogicGraph::Key createKey()
{
    return LogicGraph::Instance->createKey();
}

/// <summary>
/// Sets the value of the indexed input.
/// </summary>
extern "C" __declspec(dllexport) void setInputVal(int index,bool value)
{
    LogicGraph::Instance->setInputVal(index,value);
}

/// <summary>
/// Sets the gate to be the indexed output.
/// </summary>
extern "C" __declspec(dllexport) void collectOutput(LogicGraph::LogicGraph::Key gate,int index)
{
    LogicGraph::Instance->collectOutput(gate,index);
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
extern "C" __declspec(dllexport) LogicGraph::LogicGraph::SByte getOutput(int index)
{
    return LogicGraph::Instance->getOutput(index);
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
extern "C" __declspec(dllexport) LogicGraph::LogicGraph::SByte testOutput(LogicGraph::LogicGraph::Key gate)
{
    return LogicGraph::Instance->testOutput(gate);
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
extern "C" __declspec(dllexport) LogicGraph::LogicGraph::SByte inputToGate(LogicGraph::LogicGraph::Key gate,int index)
{
    return LogicGraph::Instance->inputToGate(gate,index);
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
extern "C" __declspec(dllexport) LogicGraph::LogicGraph::SByte removeInputToGate(LogicGraph::LogicGraph::Key gate,int index)
{
    return LogicGraph::Instance->removeInputToGate(gate,index);
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
extern "C" __declspec(dllexport) LogicGraph::LogicGraph::SByte removeConnection(LogicGraph::LogicGraph::Key gate0,LogicGraph::LogicGraph::Key gate1)
{
    return LogicGraph::Instance->removeConnection(gate0,gate1);
}

#endif//Logic_Interface
