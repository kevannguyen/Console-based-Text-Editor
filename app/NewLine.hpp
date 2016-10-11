#ifndef NEWLINE_HPP
#define NEWLINE_HPP

#include "Command.hpp"

class NewLine : public Command
{
public:

	NewLine()
	{
		setExecutionState(true);
	}
	
	virtual void execute(EditorModel& model)
	{
		initialCursorLine = model.currentCursorLine;
		initialCursorColumn = model.currentCursorColumn;
		model.createNewLine();
	}
    virtual void undo(EditorModel& model)
    {
    	if (didExecute)
    	{
    		// Move new line back to end of original line
    		std::string textToMove = model.line(model.currentCursorLine);
    		model.textLines.at(initialCursorLine-1) += textToMove;
    		// Remove the new line now
    		model.textLines.erase(model.textLines.begin() + model.currentCursorLine - 1);
    		model.currentCursorLine = initialCursorLine;
    		model.currentCursorColumn = initialCursorColumn;
    	}
    }

private:
	// Initial cursor line and column before excuting move
	int initialCursorLine;
	int initialCursorColumn;

};

#endif // NEWLINE_HPP


