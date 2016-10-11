// TestableBooEdit.hpp
//
// ICS 45C Fall 2015
// Project #4: People Just Want to Play with Words
//
// TestableBooEdit implements a version of BooEdit that can be unit tested,
// by building it using components that do not require a user interface.
//
// * Its EditorView is an InvisibleEditorView (i.e., one that displays nothing)
// * Its InteractionReader is a MockInteractionReader, which returns a
//   predefined sequence of interactions, rather than reading them from the
//   keyboard
//
// The TestableBooEdit constructor takes an initializer_list of Interactions,
// meaning that you feed it a sequence of the Interactions that you want a
// hypothetical user to perform.  For example:
//
//     TestableBooEdit booEdit{
//         Interaction::command(new InsertCharacterCommand('a')),
//         Interaction::undo(),
//         Interaction::redo()};
//
// There is no need to include an Interaction::quit(); that will always happen
// at the end, regardless.

#ifndef TESTABLEBOOEDIT_HPP
#define TESTABLEBOOEDIT_HPP

#include <initializer_list>
#include "BooEdit.hpp"
#include "InvisibleEditorView.hpp"
#include "MockInteractionReader.hpp"



class TestableBooEdit
{
public:
    TestableBooEdit(std::initializer_list<Interaction> interactions)
        : interactions{interactions},
          model_{}, view{}, interactionReader{interactions},
          editor_{model_, view, interactionReader}
    {
    }

    EditorModel& model() { return model_; }
    BooEdit& editor() { return editor_; }

private:
    std::vector<Interaction> interactions;
    EditorModel model_;
    InvisibleEditorView view;
    MockInteractionReader interactionReader;
    BooEdit editor_;
};



#endif // TESTABLEBOOEDIT_HPP

