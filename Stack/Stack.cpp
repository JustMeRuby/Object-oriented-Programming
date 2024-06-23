#include "Stack.h"

bool stack::Push(Item x)
{
    if (isFull())return false;
    *top++ = x;
    return true;
}

bool stack::Pop(Item* px)
{
    if (isEmpty()) return false;
    *px = *-- top;
    return true;
}
