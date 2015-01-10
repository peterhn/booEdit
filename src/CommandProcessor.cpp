// CommandProcessor.cpp
//
// ICS 45C Winter 2014
// Project #4: People Just Love to Play with Words
//
// Implementation of the CommandProcessor class

#include "CommandProcessor.hpp"
#include "EditorException.hpp"
#include "Keypress.hpp"
#include "MoveCursorRight.hpp"
#include "MoveCursorLeft.hpp"
#include "MoveCursorUp.hpp"
#include "MoveCursorDown.hpp"
#include "NewLineCommand.hpp"
#include "MoveCursorHome.hpp"
#include "MoveCursorEnd.hpp"
#include "BackspaceCommand.hpp"
#include "DeleteLineCommand.hpp"
#include "InsertKey.hpp"

CommandProcessor::CommandProcessor(Editor& editor, EditorView& view)
    : editor{editor}, view{view}
{
}


namespace
{
    // An "enum class" defines a type that has one of the constant values
    // specified.  So, in this case, a variable of type UserInteractionType
    // could have the value UserInteractionType::command,
    // UserInteractionType::undo, etc.
    enum class UserInteractionType
    {
        command,
        undo,
        redo,
        quit
    };


    // A UserInteraction describes one interaction that the user undertakes
    // with BooEdit.  There are four different kinds of interactions:
    //
    // * Commands, which attempt to affect some kind of change on the editor
    // * Undo, which asks for the previous change to be undone
    // * Redo, which asks for the most-recently undone change to be redone
    // * Quit, which asks for the editor to be stopped altogether
    //
    // A Command* is included for the case where UserInteractionType::command
    // is the specified type; otherwise, it will be nullptr.
    struct UserInteraction
    {
        UserInteractionType type;
        Command* command;
    };



    // You'll want these three functions, but I'm commenting them out for now,
    // so that this will compile without warnings.

    UserInteraction makeCommandInteraction(Command* command)
    {
        return UserInteraction{UserInteractionType::command, command};
    }


    UserInteraction makeUndoInteraction()
    {
        return UserInteraction{UserInteractionType::undo, nullptr};
    }


    UserInteraction makeRedoInteraction()
    {
        return UserInteraction{UserInteractionType::redo, nullptr};
    }


    
    UserInteraction makeQuitInteraction()
    {
        return UserInteraction{UserInteractionType::quit, nullptr};
    }


    // You will need to update this function to watch for the right keypresses
    // and build the right kinds of user interactions.  I've added handling
    // for "quit" here, but you'll need to add the others.
    UserInteraction nextUserInteraction()
    {
        while (true)
        {
            Keypress keypress = nextKeypress();

            if (keypress.ctrl)
            {
                // The user pressed a Ctrl key (e.g., Ctrl+X); react accordingly

                switch (keypress.c)
                {
                case 'X':
                    return makeQuitInteraction();
                case 'O':
                    return makeCommandInteraction(new MoveCursorRight);
                case 'U':
                    return makeCommandInteraction(new MoveCursorLeft);
                case 'I':
                    return makeCommandInteraction(new MoveCursorUp);
                case 'K':
                    return makeCommandInteraction(new MoveCursorDown);
                case 'M':
                    return makeCommandInteraction(new NewLineCommand);
                case 'J':
                    return makeCommandInteraction(new NewLineCommand);
                case 'Y':
                    return makeCommandInteraction(new MoveCursorHome);
                case 'P':
                    return makeCommandInteraction(new MoveCursorEnd);
                case 'H':
                    return makeCommandInteraction(new BackspaceCommand);
                case 'D':
                    return makeCommandInteraction(new DeleteLineCommand);
                case 'Z':
                    return makeUndoInteraction();
                case 'A':
                    return makeRedoInteraction();
                }
            }
            else
            {
                // The user pressed a normal key (e.g., 'h') without holding
                // down Ctrl; react accordingly
                return makeCommandInteraction(new InsertKey{keypress.c});
            }
        }
    }
}


// This function implements command execution, but does not handle "undo"
// and "redo"; you'll need to add that handling.

void CommandProcessor::run()
{
    view.refresh();
    std::vector<UserInteraction> undo;
    std::vector<UserInteraction> redo;
    while (true)
    {
        UserInteraction interaction = nextUserInteraction();

        if (interaction.type == UserInteractionType::quit)
        {
            for(int i = 0 ; i < undo.size(); i++)
            {
                delete undo[i].command;
            }
            for(int i = 0 ; i < redo.size(); i++)
            {
                delete redo[i].command;
            }
            undo.clear();
            redo.clear();
            break;
        }
        else if (interaction.type == UserInteractionType::undo)
        {
            if(undo.size() > 0)
            {
                UserInteraction lastUndo = undo.back();
                undo.pop_back();
                redo.push_back(lastUndo);
                lastUndo.command->undo(editor);
            }
            view.refresh();
        }
        else if (interaction.type == UserInteractionType::redo)
        {
            if(redo.size() > 0)
            {
                UserInteraction lastRedo = redo.back();
                redo.pop_back();
                undo.push_back(lastRedo);
                try
                {
                    lastRedo.command->execute(editor);
                    view.clearErrorMessage();
                }
                catch(EditorException& e)
                {
                    view.showErrorMessage(e.getReason());
                }
            }
            view.refresh();
        }
        else if (interaction.type == UserInteractionType::command)
        {
            try
            {
                redo.clear();
                undo.push_back(interaction);
                interaction.command->execute(editor);
                view.clearErrorMessage();
            }
            catch (EditorException& e)
            {
                view.showErrorMessage(e.getReason());
            }

            view.refresh();

            // Note that you'll want to be more careful about when you delete
            // commands once you implement undo and redo.  For now, since
            // neither is implemented, I've just deleted it immediately
            // after executing it.  You'll need to wait to delete it until
            // you don't need it anymore.
           // delete interaction.command;
        }
    }
}

