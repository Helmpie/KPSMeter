#include "Graph.h"
#include <iostream>
#include "DrawFunctions.h"

Graph::Graph(InputHandler* input)
: input(input)
{
    dots = std::deque<short>(Settings::getInstance()->getGraphPrecision(), 0);
}

Graph::~Graph()
{

}

void Graph::addDot(const short& dot)
{
    dots.pop_front();
    dots.push_back(dot);
}

std::deque<short>* Graph::getDotPtr()
{
    return &dots;
}
