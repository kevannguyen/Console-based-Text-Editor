#ifndef WRITER_HPP
#define WRITER_HPP

#include "Command.hpp"

class Writer : public Command
{
public:

	Writer(char letter)
		: letter{letter}
	{
		setExecutionState(true);
	}
	
	virtual void execute(EditorModel& model)
	{
		initialCursorLine = model.currentCursorLine;
		initialCursorColumn = model.currentCursorColumn;
		model.writeCharAtCurrentPosition(letter);
	}
    virtual void undo(EditorModel& model)
    {
    	if (didExecute)
    	{
    		model.deleteCharAtCurrentPosition();
    	}
    }


private:
	char letter;

	// Initial cursor line and column before excuting move
	int initialCursorLine;
	int initialCursorColumn;
};

#endif // WRITER_HPP


