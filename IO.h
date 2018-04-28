#ifndef IO_H_INCLUDED
#define IO_H_INCLUDED

#include "InputHandler.h"

namespace IO
{
    void StartThread(InputHandler* input);
    void KillThread();
}

#endif // IO_H_INCLUDED
