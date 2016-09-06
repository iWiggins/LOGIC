#include "LogicM.h"

#define PLATFORM_ANDROID 0
#define PLATFORM_IOS 1

char * LogicM::getTemplateInfo()
{
#if PLATFORM == PLATFORM_IOS
	static char info[] = "Platform for iOS";
#elif PLATFORM == PLATFORM_ANDROID
	static char info[] = "Platform for Android";
#else
	static char info[] = "Undefined platform";
#endif

	return info;
}

LogicM::LogicM()
{
    Instance = nullptr;
}

LogicM::~LogicM()
{
    if(Instance != nullptr) DestroyLogicGraph();
}

void LogicM::CreateLogicGraph(int inputCount,int outputCount)
{
    if(Instance != nullptr) delete Instance;
    Instance = new LogicGraph::LogicGraph(inputCount,outputCount);
}

void LogicM::DestroyLogicGraph()
{
    if(Instance != nullptr) delete Instance;
    Instance = nullptr;
}

LogicGraph::LogicGraph::Key LogicM::addGate(int type)
{
    switch(type){
    case  0: return Instance->addGate(LogicGraph::LogicGraph::Gates::AND);
    case  1: return Instance->addGate(LogicGraph::LogicGraph::Gates::OR);
    case  2: return Instance->addInverter();
    case  3: return Instance->addGate(LogicGraph::LogicGraph::Gates::NAND);
    case  4: return Instance->addGate(LogicGraph::LogicGraph::Gates::NOR);
    case  5: return Instance->addGate(LogicGraph::LogicGraph::Gates::XOR);
    default: return 0;
    }
}

LogicGraph::LogicGraph::SByte LogicM::connectGates(LogicGraph::LogicGraph::Key gate,LogicGraph::LogicGraph::Key input)
{
    return Instance->connectGates(gate,input);
}

LogicGraph::LogicGraph::SByte LogicM::disconnectGates(LogicGraph::LogicGraph::Key gate,LogicGraph::LogicGraph::Key input)
{
    return Instance->disconnectGates(gate,input);
}

LogicGraph::LogicGraph::SByte LogicM::removeGate(LogicGraph::LogicGraph::Key gate)
{
    return Instance->removeGate(gate);
}

LogicGraph::LogicGraph::Key LogicM::getInputKey(int index)
{
    return Instance->getInputKey(index);
}

LogicGraph::LogicGraph::Key LogicM::createKey()
{
    return Instance->createKey();
}

void LogicM::setInputVal(int index,bool value)
{
    Instance->setInputVal(index,value);
}

void LogicM::collectOutput(LogicGraph::LogicGraph::Key gate,int index)
{
    Instance->collectOutput(gate,index);
}

LogicGraph::LogicGraph::SByte LogicM::getOutput(int index)
{
    return Instance->getOutput(index);
}

LogicGraph::LogicGraph::SByte LogicM::testOutput(LogicGraph::LogicGraph::Key gate)
{
    return Instance->testOutput(gate);
}

LogicGraph::LogicGraph::SByte LogicM::inputToGate(LogicGraph::LogicGraph::Key gate,int index)
{
    return Instance->inputToGate(gate,index);
}

LogicGraph::LogicGraph::SByte LogicM::removeInputToGate(LogicGraph::LogicGraph::Key gate,int index)
{
    return Instance->removeInputToGate(gate,index);
}

LogicGraph::LogicGraph::SByte LogicM::removeConnection(LogicGraph::LogicGraph::Key gate0,LogicGraph::LogicGraph::Key gate1)
{
    return Instance->removeConnection(gate0,gate1);
}
