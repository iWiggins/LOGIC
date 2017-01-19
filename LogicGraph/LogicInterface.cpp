#include "LogicInterface.h"

void* CreateLogicGraph(int inputCount,int outputCount)
{
    return new LogicGraph::LogicGraph(inputCount,outputCount);
}

void DestroyLogicGraph(void* logicGraph)
{
    delete logicGraph;
}

LogicGraph::LogicGraph::Key addGate(void*logicGraph, int type)
{
    LogicGraph::LogicGraph*instance = (LogicGraph::LogicGraph*)logicGraph;
    switch(type){
    case  0: return instance->addGate(LogicGraph::LogicGraph::Gates::AND);
    case  1: return instance->addGate(LogicGraph::LogicGraph::Gates::OR);
    case  2: return instance->addInverter();
    case  3: return instance->addGate(LogicGraph::LogicGraph::Gates::NAND);
    case  4: return instance->addGate(LogicGraph::LogicGraph::Gates::NOR);
    case  5: return instance->addGate(LogicGraph::LogicGraph::Gates::XOR);
    default: return 0;
    }
}

LogicGraph::LogicGraph::SByte connectGates(void*logicGraph,LogicGraph::LogicGraph::Key gate,LogicGraph::LogicGraph::Key input)
{
    LogicGraph::LogicGraph*instance = (LogicGraph::LogicGraph*)logicGraph;
    return instance->connectGates(gate,input);
}

LogicGraph::LogicGraph::SByte disconnectGates(void*logicGraph, LogicGraph::LogicGraph::Key gate,LogicGraph::LogicGraph::Key input)
{
    LogicGraph::LogicGraph*instance = (LogicGraph::LogicGraph*)logicGraph;
    return instance->disconnectGates(gate,input);
}

LogicGraph::LogicGraph::SByte removeGate(void* logicGraph,LogicGraph::LogicGraph::Key gate)
{
    LogicGraph::LogicGraph*instance = (LogicGraph::LogicGraph*)logicGraph;
    return instance->removeGate(gate);
}

LogicGraph::LogicGraph::Key getInputKey(void* logicGraph,int index)
{
    LogicGraph::LogicGraph*instance = (LogicGraph::LogicGraph*)logicGraph;
    return instance->getInputKey(index);
}

LogicGraph::LogicGraph::Key createKey(void* logicGraph)
{
    LogicGraph::LogicGraph*instance = (LogicGraph::LogicGraph*)logicGraph;
    return instance->createKey();
}

void setInputVal(void* logicGraph,int index,bool value)
{
    LogicGraph::LogicGraph*instance = (LogicGraph::LogicGraph*)logicGraph;
    return instance->setInputVal(index,value);
}

void openOutput(void* logicGraph,LogicGraph::LogicGraph::Key gate,int index)
{
    LogicGraph::LogicGraph*instance = (LogicGraph::LogicGraph*)logicGraph;
    return instance->openOutput(gate,index);
}

void closeOutput(void* logicGraph,int index)
{
    LogicGraph::LogicGraph*instance = (LogicGraph::LogicGraph*)logicGraph;
    return instance->closeOutput(index);
}

LogicGraph::LogicGraph::SByte getOutput(void* logicGraph,int index)
{
    LogicGraph::LogicGraph*instance = (LogicGraph::LogicGraph*)logicGraph;
    return instance->getOutput(index);
}

LogicGraph::LogicGraph::SByte testOutput(void* logicGraph,LogicGraph::LogicGraph::Key gate)
{
    LogicGraph::LogicGraph*instance = (LogicGraph::LogicGraph*)logicGraph;
    return instance->testOutput(gate);
}

LogicGraph::LogicGraph::SByte inputToGate(void* logicGraph,LogicGraph::LogicGraph::Key gate,int index)
{
    LogicGraph::LogicGraph*instance = (LogicGraph::LogicGraph*)logicGraph;
    return instance->inputToGate(gate,index);
}

LogicGraph::LogicGraph::SByte removeInputToGate(void* logicGraph,LogicGraph::LogicGraph::Key gate,int index)
{
    LogicGraph::LogicGraph*instance = (LogicGraph::LogicGraph*)logicGraph;
    return instance->removeInputToGate(gate,index);
}

LogicGraph::LogicGraph::SByte removeConnection(void* logicGraph,LogicGraph::LogicGraph::Key gate0,LogicGraph::LogicGraph::Key gate1)
{
    LogicGraph::LogicGraph*instance = (LogicGraph::LogicGraph*)logicGraph;
    return instance->removeConnection(gate0,gate1);
}