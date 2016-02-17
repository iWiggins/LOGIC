// LogicGraphTester.cpp : Defines the entry point for the console application.
#include "LogicInterface.h"
#include <iostream>

#define wait for(char c = std::cin.get(); c != '\n'; c = std::cin.get())

void test1()
{
    std::cout << "TEST 1\n\n";

    CreateLogicGraph(2,1);

    LogicGraph::LogicGraph::Key kAnd = addGate(0);
    LogicGraph::LogicGraph::Key kNot = addGate(2);

    connectGates(kAnd,kNot);

    inputToGate(kAnd,0);
    inputToGate(kNot,1);

    auto act = [&](int in0,int in1){
        setInputVal(0,in0);
        setInputVal(1,in1);

        std::cout << "x0=" << in0 << " x1=" << in1 << '\n';

        auto outNot = testOutput(kNot);
        auto outAnd = testOutput(kAnd);

        std::cout << "Not x1=" << (int)outNot << '\n';
        std::cout << "x0 And Not x1 =" << (int)outAnd << "\n\n";
    };

    act(0,0);
    act(0,1);
    act(1,0);
    act(1,1);
    wait;
}

void test2()
{
    std::cout << "TEST 2\n\n";

    CreateLogicGraph(2,1);

    LogicGraph::LogicGraph::Key kAnd = addGate(0);
    LogicGraph::LogicGraph::Key kNot = addGate(2);

    connectGates(kAnd,kNot);

    inputToGate(kAnd,0);
    inputToGate(kNot,1);

    auto act = [&](int in0,int in1){
        setInputVal(0,in0);
        setInputVal(1,in1);

        std::cout << "x0=" << in0 << " x1=" << in1 << '\n';

        auto outNot = testOutput(kNot);
        auto outAnd = testOutput(kAnd);

        std::cout << "Not x1=" << (int)outNot << '\n';
        std::cout << "x0 And Not x1 =" << (int)outAnd << "\n\n";
    };

    act(1,1);
    wait;
}

int main()
{
    test1();
    test2();
    return 0;
}

