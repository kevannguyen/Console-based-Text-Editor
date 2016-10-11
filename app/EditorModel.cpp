// EditorModel.cpp
//
// ICS 45C Fall 2015
// Project #4: People Just Love to Play with Words
//
// Implementation of the EditorModel class

#include "EditorModel.hpp"
#include "EditorException.hpp"


EditorModel::EditorModel()
{
	// Initalize first line of the vector that holds 
	// the text lines
	textLines.push_back("");

	// Initialize error message to nothing
	errorMessage = "";

	// Initialize cursor position
	currentCursorLine = 1;
	currentCursorColumn = 1;

	// Initialize total number of lines
	currentLineCount = 1;
}


int EditorModel::cursorLine() const
{
    return currentCursorLine;
}


int EditorModel::cursorColumn() const
{
    return currentCursorColumn;
}


int EditorModel::lineCount() const
{
    return textLines.size();
}


const std::string& EditorModel::line(int lineNumber) const
{
    return textLines.at(lineNumber-1);
}


const std::string& EditorModel::currentErrorMessage() const
{
    return errorMessage;
}


void EditorModel::setErrorMessage(const std::string& errorMessage)
{
	this->errorMessage = errorMessage;
}


void EditorModel::clearErrorMessage()
{
	errorMessage = "";
}



//------------------ MY OWN FUNCTIONS  ------------------
int EditorModel::getNumCharactersInLine(int lineNumber) const
{
	return textLines.at(lineNumber-1).length();
}

void EditorModel::moveCursorSideToSide(const int& direction)
{
	// Move right
	if (direction > 0)
	{
		if (currentCursorLine == lineCount() && currentCursorColumn == getNumCharactersInLine(currentCursorLine)+1)
		{
			throw EditorException("Already at end");
			return;
		}

		// If at the end of the line and theres a line below,
		// move to the beginning of the next line.
		if (currentCursorColumn == getNumCharactersInLine(currentCursorLine)+1)
		{
			currentCursorColumn = 1;
			currentCursorLine++;
		}
		else 
		{
			currentCursorColumn++;
		}
	}
	// Move left
	else if (direction < 0)
	{
		if (currentCursorLine == 1 && currentCursorColumn == 1)
		{
			throw EditorException("Already at beginning");
			return;
		}

		// If at the beginning of the line and theres a line above,
		// move to the end of th enext line.
		if (currentCursorColumn == 1)
		{
			currentCursorLine--;
			currentCursorColumn = getNumCharactersInLine(currentCursorLine) + 1;
		}
		else
		{
			currentCursorColumn--;
		}
	}
}

void EditorModel::moveCursorVertically(const int& direction)
{
	// Move down
	if (direction > 0)
	{
		if (currentCursorLine == lineCount())
		{
			throw EditorException("Already at bottom");
			return;
		}

		// If the current cursor's column position is greater
		// than the length+1 of the next line, jump straight
		// to the end of the next line.
		if (currentCursorColumn > getNumCharactersInLine(currentCursorLine+1)+1)
		{
			currentCursorColumn = getNumCharactersInLine(currentCursorLine+1)+1;
		}
		currentCursorLine++;
	}
	// Move up
	else if (direction < 0)
	{
		if (currentCursorLine == 1)
		{
			throw EditorException("Already at top");
			return;
		}

		// If the current cursor's column position is greater
		// than the length+1 of the previous line, jump straight
		// to the end of the previous line.
		if (currentCursorColumn > getNumCharactersInLine(currentCursorLine-1)+1)
		{
			currentCursorColumn = getNumCharactersInLine(currentCursorLine-1)+1;
		}
		currentCursorLine--;
	}
}

void EditorModel::moveCursorToBeginningOfLine()
{
	currentCursorColumn = 1;
}

void EditorModel::moveCursorToEndOfLine()
{
	currentCursorColumn = getNumCharactersInLine(currentCursorLine) + 1;
}

void EditorModel::writeCharAtCurrentPosition(const char& letter)
{
	// Write character at current position
	textLines.at(currentCursorLine-1).insert(textLines.at(currentCursorLine-1).begin() + 
		currentCursorColumn-1, letter);
	// Move cursor forward 1 position
	currentCursorColumn++;
}

void EditorModel::createNewLine()
{
	// Vector position of where we're going to create the new line
	std::vector<std::string>::iterator it = textLines.begin() + currentCursorLine;
	std::string newLine = textLines.at(currentCursorLine-1).substr(currentCursorColumn-1);
	textLines.insert(it, newLine);
	textLines.at(currentCursorLine-1).erase(textLines.at(currentCursorLine-1).begin()+currentCursorColumn-1, 
		textLines.at(currentCursorLine-1).end());
	currentCursorColumn = 1;
	currentCursorLine++;
}

std::string EditorModel::deleteCharAtCurrentPosition()
{
	if (currentCursorColumn > 1)
	{
		std::string deletedChar = line(currentCursorLine).substr(currentCursorColumn-2, 1);
		textLines.at(currentCursorLine-1).erase(currentCursorColumn-2, 1);
		currentCursorColumn--;
		return deletedChar;
	}

	// If our cursor is on the first column of a line, and there
	// exists a previous line, append every character from the current line
	// to the end of the previous line, and have the cursor move to the
	// end of the previous line's character (location before being appended to)
	else if (currentCursorLine > 1)
	{
		// Move cursor to previous line's column
		currentCursorColumn = getNumCharactersInLine(currentCursorLine-1) + 1;
		// Append to current line to previous line
		textLines.at(currentCursorLine-2) += line(currentCursorLine);
		//currentCursorLine--;
		// Delete the (ex) current line
		textLines.erase(textLines.begin()+currentCursorLine-1);
		// Move cursor to previous line
		currentCursorLine--;
		return "";	// Didn't delete a character, except for a a newline character
	}

	else
	{
		throw EditorException("Already at beginning");
		return "";
	}
}

std::string EditorModel::deleteLine()
{
	if (lineCount() == 1 && getNumCharactersInLine(1) == 0)
	{
		throw EditorException("Already empty");
		return "";
	}

	// If there's only one line that exists currently,
	// then delete it and set the line equal to ""
	// and move the cursor to the line 1, column 1
	else if (lineCount() == 1)
	{
		std::string deletedLine = line(1);
		textLines.at(0) = "";
		currentCursorColumn = 1;
		currentCursorLine = 1;
		return deletedLine;
	}

	else
	{
		std::string deletedLine = line(currentCursorLine);
		// Delete the current line
		textLines.erase(textLines.begin()+currentCursorLine-1);

		// If the line deleted was the last line, move cursor up
		// to previous line
		if (currentCursorLine > lineCount())
		{
			// If the current cursors column location is greater than the 
			// length+1 of the previous line, move the cursor to the very end
			//  of the previous line
			if (currentCursorColumn > getNumCharactersInLine(currentCursorLine-1) + 1)
			{
				currentCursorColumn = getNumCharactersInLine(currentCursorLine-1) + 1;
			}
			// Move cursor to the previous line
			currentCursorLine--;
		}

		// If the line deleted was not the last line, have the cursor remain in
		// the same line, but move the cursor's column if the current column
		// is greater than the length+1 ofthe line after the deleted line
		else
		{
			if (currentCursorColumn > getNumCharactersInLine(currentCursorLine) + 1)
			{
				currentCursorColumn = getNumCharactersInLine(currentCursorLine) + 1;
			}
		}
		return deletedLine;
	}
}