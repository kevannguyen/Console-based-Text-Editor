#ifndef DELETER_HPP
#define DELETER_HPP

#include "Command.hpp"

class Deleter : public Command
{
public:
	Deleter(char command)
		: command{command}
	{
		// Initialize its execution state to true. Will change
		// itself to false if command cannot be executed (error)
		setExecutionState(true);
	}

	virtual void execute(EditorModel& model)
	{
		initialCursorLine = model.currentCursorLine;
		initialCursorColumn = model.currentCursorColumn;
		switch (command)
		{
		// DELETE single character
		case 'H':
			if (model.currentCursorLine == 1 && model.currentCursorColumn == 1)
			{
				setExecutionState(false);
			}
			deletedLine = model.deleteCharAtCurrentPosition();
			break;
		case 'D':
			if (model.lineCount() == 1 && model.getNumCharactersInLine(1) == 0)
			{
				setExecutionState(false);
			}
			deletedLine = model.deleteLine();
			break;
		}
	}
    virtual void undo(EditorModel& model)
    {
    	if (didExecute)
    	{
    		switch(command)
    		{
    		// UNDOS deleted single character (rewrite the character again)
    		case 'H':
    			// If the cursor was originally at column 1 before executing,
    			// that means it must've moved its original line up one line and
    			// appended itself to the previous line.
    			//
    			// Undoing this action means to move it all back to a new line. 
    			if (initialCursorColumn == 1 && initialCursorLine > 1)
    			{
    				// From the current cursor position onwards (to the end of the line)
    				std::string textToMove = model.line(model.currentCursorLine).substr(model.currentCursorColumn-1, 
                        model.getNumCharactersInLine(model.currentCursorLine) - model.currentCursorColumn - 1);
  					// Remove/undo "textToMove" segment from the current line
    				model.textLines.at(model.currentCursorLine-1).erase(model.textLines.at(model.currentCursorLine-1).begin()+model.currentCursorColumn-1);
    				
    				// Insert "textToMove" to its original position now
    				std::vector<std::string>::iterator pos = model.textLines.begin() + initialCursorLine - 1;
    				model.textLines.insert(pos, textToMove);
    				model.currentCursorLine = initialCursorLine;
    				model.currentCursorColumn = initialCursorColumn;
    			}

    			// If the cursor didnt move from line to line, just add back 
    			// the deleted character from its original position
    			else
    			{
    				model.textLines.at(model.currentCursorLine-1).insert(model.currentCursorColumn-1, deletedLine);
    				model.currentCursorLine = initialCursorLine;
    				model.currentCursorColumn = initialCursorColumn;
    			}
    			break;

    		// UNDOS deleted lines
    		case 'D':
    			// If text area completely empty
    			if (model.lineCount() == 1 && model.getNumCharactersInLine(1) == 0)
    			{
    				model.textLines.at(0) = deletedLine;
    			}
    			else
    			{
    				// Line position to insert the deleted line back
    				std::vector<std::string>::iterator pos = model.textLines.begin() + initialCursorLine - 1;
    				model.textLines.insert(pos, deletedLine);
    			}
    			// Move cursor back to original/initial position
    			model.currentCursorLine = initialCursorLine;
    			model.currentCursorColumn = initialCursorColumn;
    		}
    	}
    }

private:
	char command;

	// Initial cursor line and column before excuting move
	int initialCursorLine;
	int initialCursorColumn;


	// Stores the deleted string of text
	std::string deletedLine;

};

#endif // DELETER_HPP


