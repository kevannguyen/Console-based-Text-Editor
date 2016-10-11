// MockKeypressReader.cpp
//
// ICS 45C Fall 2015
// Project #4: People Just Want to Play with Words
//
// Implementation of the MockKeypressReader class
//
// DO NOT MODIFY THIS FILE

#include "MockKeypressReader.hpp"
#include "NoMoreKeypressesException.hpp"


MockKeypressReader::MockKeypressReader(const std::vector<Keypress>& keypresses)
    : keypresses{keypresses}, nextKeypressIndex{0}
{
}


Keypress MockKeypressReader::nextKeypress()
{
    if (nextKeypressIndex >= keypresses.size())
    {
        throw NoMoreKeypressesException{};
    }
    else
    {
        Keypress& next = keypresses[nextKeypressIndex];
        nextKeypressIndex++;
        return next;
    }
}

