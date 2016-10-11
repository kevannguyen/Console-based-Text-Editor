// InteractionProcessor.cpp
//
// ICS 45C Fall 2015
// Project #4: People Just Love to Play with Words
//
// Implementation of the InteractionProcessor class

#include "InteractionProcessor.hpp"
#include "EditorException.hpp"
#include "Interaction.hpp"


// This function implements command execution, but does not handle "undo"
// and "redo"; you'll need to add that handling.

void InteractionProcessor::run()
{
    // Undo and redo command stacks
    std::vector<Command*> undoStack;
    std::vector<Command*> redoStack;

    // Checks to see if we performed any undo actions
    // from the undo stack yet.
    // This is important because it'll allow us to know when
    // to clear/reset our undoStack.
    bool performedUndoStack = false;

    view.refresh();

    while (true)
    {
        Interaction interaction = interactionReader.nextInteraction();

        if (interaction.type() == InteractionType::quit)
        {
            break;
        }
        else if (interaction.type() == InteractionType::undo)
        {
            // Check to see if there are any more commands to undo
            if (undoStack.size() > 0)
            {
                performedUndoStack = true;
                // Add to redo stack
                redoStack.push_back(undoStack.back());
                undoStack.back()->undo(model);
                view.refresh();
                undoStack.pop_back();
            }
        }
        else if (interaction.type() == InteractionType::redo)
        {
            // Check to see if there are any more commands to redo
            if (redoStack.size() > 0)
            {
                // Add to undo stack
                undoStack.push_back(redoStack.back());
                redoStack.back()->execute(model);
                view.refresh();
                redoStack.pop_back();
            }
        }
        else if (interaction.type() == InteractionType::command)
        {
            Command* command = interaction.command();

            try
            {
                command->execute(model);
                model.clearErrorMessage();
                undoStack.push_back(command);
                if (performedUndoStack)
                {
                    // Delete/deallocate all commands in the
                    // redo stack and clear it.
                    for (int i = 0; i < redoStack.size(); i++)
                    {
                        delete redoStack.at(i);
                    }
                    redoStack.clear();
                    performedUndoStack = false;
                }
            }
            catch (EditorException& e)
            {
                model.setErrorMessage(e.getReason());
            }

            view.refresh();

            // Note that you'll want to be more careful about when you delete
            // commands once you implement undo and redo.  For now, since
            // neither is implemented, I've just deleted it immediately
            // after executing it.  You'll need to wait to delete it until
            // you don't need it anymore.
        }
    }

    // Delete/deallocate every command in the redo and undo stack
    for (int i = 0; i < undoStack.size(); i++)
    {
        delete undoStack.at(i);
    }
    undoStack.clear();

    for (int i = 0; i < redoStack.size(); i++)
    {
        delete redoStack.at(i);
    }
    redoStack.clear();
}

