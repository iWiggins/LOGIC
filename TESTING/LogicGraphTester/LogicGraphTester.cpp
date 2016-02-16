// LogicGraphTester.cpp : Defines the entry point for the console application.
#include "LogicInterface.h"
#include <iostream>

#define wait for(char c = std::cin.get(); c != '\n'; c = std::cin.get())

int main()
{
    std::cout << "Building.\n";
    wait;
    CreateLogicGraph(2,1);
    std::cout << "Destroying.\n";
    wait;
    DestroyLogicGraph();
    wait;
    return 0;
}

