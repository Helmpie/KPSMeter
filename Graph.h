#ifndef GRAPH_H_INCLUDED
#define GRAPH_H_INCLUDED

#include "WindowInterface.h"
#include "InputHandler.h"
#include "Settings.h"
#include <deque>
//static const short graph_precision = 100;

class Graph
{
    public:
        Graph();
        ~Graph();

        void addDot(const short& dot);

        std::deque<short>* getDotPtr();

    private:
        std::deque<short> dots;
};

#endif // GRAPH_H_INCLUDED
