// KeypressInteractionReader.cpp
//
// ICS 45C Fall 2015
// Project #4: People Just Want to Play with Words
//
// Implementation of the KeypressInteractionReader
//
// YOU WILL NEED TO IMPLEMENT SOME THINGS HERE

#include "KeypressInteractionReader.hpp"

// ----------- INCLUDING MY OWN HEADER FILES ---------------
#include "CursorMove.hpp"
#include "Writer.hpp"
#include "Deleter.hpp"
#include "NewLine.hpp"


// You will need to update this member function to watch for the right
// keypresses and build the right kinds of Interactions as a result.
//
// The reason you'll need to implement things here is that you'll need
// to create Command objects, which you'll be declaring and defining
// yourself; they haven't been provided already.
//
// I've added handling for "quit" here, but you'll need to add the others.

Interaction KeypressInteractionReader::nextInteraction()
{
    CursorMove* move = nullptr;
    NewLine* newLine = nullptr;
    Writer* writer = nullptr;
    Deleter* deleter = nullptr;

    while (true)
    {
        Keypress keypress = keypressReader.nextKeypress();


        if (keypress.ctrl())
        {
            // The user pressed a Ctrl key (e.g., Ctrl+X); react accordingly

            switch (keypress.code())
            {
            // EXIT
            case 'X':
            {
                return Interaction::quit();
            }
            // UP CURSOR MOVE
            case 'I':
            {
                delete move;
                move = new CursorMove{'I'};
                return Interaction::command(move);
            }
            // DOWN CURSOR MOVE
            case 'K':
            {
                delete move;
                move = new CursorMove{'K'};
                return Interaction::command(move);
            }
            // LEFT CURSOR MOVE
            case 'U':
            {
                delete move;
                move = new CursorMove{'U'};
                return Interaction::command(move);
            }
            // RIGHT CURSOR MOVE
            case 'O':
            {
                delete move;
                move = new CursorMove{'O'};
                return Interaction::command(move);
            }
            // CURSOR HOME
            case 'Y':
            {
                delete move;
                move = new CursorMove{'Y'};
                return Interaction::command(move);
            }
            // CURSOR END
            case 'P':
            {
                delete move;
                move = new CursorMove{'P'};
                return Interaction::command(move);
            }
            // CREATE NEW LINE
            case 'J':
            case 'M':
            {
                delete newLine;
                newLine = new NewLine{};
                return Interaction::command(newLine);
            }
            // DELETE SINGLE CHARACTER
            case 'H':
            {
                delete deleter;
                deleter = new Deleter{'H'};
                return Interaction::command(deleter);
            }
            // DELETE LINE
            case 'D':
            {
                delete deleter;
                deleter = new Deleter{'D'};
                return Interaction::command(deleter);
            }


            // UNDO
            case 'Z':
            {
                return Interaction::undo();
            }

            // REDO
            case 'A':
            {
                return Interaction::redo();
            }

            }

        }
        else
        {
            // The user pressed a normal key (e.g., 'h') without holding
            // down Ctrl; react accordingly
            delete writer;
            writer = new Writer{keypress.code()};
            return Interaction::command(writer);
        }
    }

    // // Delete command objects here!
    delete move;
    delete newLine;
    delete writer;
    delete deleter;
}

