// BooEditTests.cpp
//
// ICS 45C Fall 2015
// Project #4: People Just Want to Play with Words
//
// Feel free to write unit tests for BooEdit here.  These are not required,
// but you might find this to be a useful way to verify that various parts
// of your program are working.  I've provided a couple of examples, so you
// can see roughly what these tests might look like.  See also the comments
// in TestableBooEdit.hpp for more details about how to use it.

#include <vector>
#include <gtest/gtest.h>
#include "TestableBooEdit.hpp"
#include "Writer.hpp"
#include "Deleter.hpp"
#include "CursorMove.hpp"
#include "NewLine.hpp"


TEST(BooEditTests, cursorBeginsOnLine1)
{
    TestableBooEdit edit{};
    edit.editor().run();

    EXPECT_EQ(1, edit.model().cursorLine());
}


TEST(BooEditTests, cursorBeginsOnColumn1)
{
    TestableBooEdit edit{};
    edit.editor().run();

    EXPECT_EQ(1, edit.model().cursorColumn());
}


TEST(BooEditTests, returnLineIsCorrect)
{
	TestableBooEdit edit{
		Interaction::command(new Writer('a')),
		Interaction::command(new Writer('b')),
		Interaction::command(new Writer('c')),
		Interaction::command(new Writer('d'))
	};
	edit.editor().run();

	ASSERT_EQ(edit.model().line(1), "abcd");
}

TEST(BooEditTests, deleteCharWorks)
{
	TestableBooEdit edit{
		Interaction::command(new Writer('a')),
		Interaction::command(new Writer('b')),
		Interaction::command(new Writer('c')),
		Interaction::command(new Deleter('H'))
	};
	edit.editor().run();

	ASSERT_EQ(edit.model().line(1), "ab");
}

TEST(BooEditTests, newLineWorks)
{
	TestableBooEdit edit{
		Interaction::command(new Writer('a')),
		Interaction::command(new Writer('b')),
		Interaction::command(new Writer('c')),
		Interaction::command(new NewLine()),
		Interaction::command(new Writer('a')),
		Interaction::command(new Writer('b'))
	};
	edit.editor().run();

	ASSERT_EQ(edit.model().line(1), "abc");
	ASSERT_EQ(edit.model().line(2), "ab");
}

TEST(BooEditTests, cursorMovesSideToSideWorks)
{
	TestableBooEdit edit{
		Interaction::command(new Writer('a')),
		Interaction::command(new Writer('b')),
		Interaction::command(new Writer('c')),
		Interaction::command(new CursorMove('U')),
		Interaction::command(new CursorMove('U'))
	};
	edit.editor().run();

	EXPECT_EQ(2, edit.model().cursorColumn());
}

TEST(BooEditTests, deleteLineWorks)
{
	TestableBooEdit edit{
		Interaction::command(new Writer('a')),
		Interaction::command(new Writer('b')),
		Interaction::command(new Writer('c')),
		Interaction::command(new Deleter('D'))
	};
	edit.editor().run();

	EXPECT_EQ(1, edit.model().cursorColumn());
	EXPECT_EQ(1, edit.model().cursorLine());
}

TEST(BooEditTests, undoWorks)
{
	TestableBooEdit edit{
		Interaction::command(new Writer('a')),
		Interaction::command(new Writer('b')),
		Interaction::command(new Writer('c')),
		Interaction::undo(),
		Interaction::undo()
	};
	edit.editor().run();

	ASSERT_EQ(edit.model().line(1), "a");
}

TEST(BooEditTests, redoWorks)
{
	TestableBooEdit edit{
		Interaction::command(new Writer('a')),
		Interaction::command(new Writer('b')),
		Interaction::command(new Writer('c')),
		Interaction::command(new Writer('d')),
		Interaction::command(new Writer('e')),
		Interaction::undo(),
		Interaction::undo(),
		Interaction::undo(),
		Interaction::undo(),
		Interaction::redo(),
		Interaction::redo()
	};
	edit.editor().run();

	ASSERT_EQ(edit.model().line(1), "abc");
}