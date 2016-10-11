#ifndef CURSORMOVE_HPP
#define CURSORMOVE_HPP

#include "Command.hpp"

class CursorMove : public Command
{
public:
	CursorMove(char direction)
		: direction{direction}
	{
		setExecutionState(true);
	}

	virtual void execute(EditorModel& model)
	{
		initialCursorLine = model.currentCursorLine;
		initialCursorColumn = model.currentCursorColumn;
		switch (direction)
		{
		// UP
		case 'I':
			if (model.currentCursorLine == 1)
			{
				setExecutionState(false);
			}
			model.moveCursorVertically(-1);
			break;
		// DOWN
		case 'K':
			if (model.currentCursorLine == model.lineCount())
			{
				setExecutionState(false);
			}
			model.moveCursorVertically(1);
			break;
		// LEFT
		case 'U':
			if (model.currentCursorLine == 1 && model.currentCursorColumn == 1)
			{
				setExecutionState(false);
			}
			model.moveCursorSideToSide(-1);
			break;
		// RIGHT
		case 'O':
			if (model.currentCursorLine == model.lineCount() && 
				model.currentCursorColumn == model.getNumCharactersInLine(model.currentCursorLine)+1)
			{
				setExecutionState(false);
			}
			model.moveCursorSideToSide(1);
			break;
		// CURSOR HOME
		case 'Y':
			model.moveCursorToBeginningOfLine();
			break;
		case 'P':
			model.moveCursorToEndOfLine();
			break;
		}
	}
    virtual void undo(EditorModel& model)
    {
    	if (didExecute)
    	{
    		// Move cursor back to its original position
    		model.currentCursorLine = initialCursorLine;
    		model.currentCursorColumn = initialCursorColumn;
    	}
    }


private:
	// Constructor Variables
	char direction;

	// Initial cursor line and column before excuting move
	int initialCursorLine;
	int initialCursorColumn;
};

#endif // CURSORMOVE_HPP


