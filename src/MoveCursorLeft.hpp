#ifndef MOVECURSORLEFT_HPP
#define MOVECURSORLEFT_HPP
#include "Command.hpp"
#include "EditorException.hpp"

class MoveCursorLeft : public Command
{
    public:
        virtual void execute(Editor& editor)
        {
            previousLine = editor.cursorLine();
            previousCol = editor.cursorColumn();
            if(editor.cursorColumn() == 1 && editor.cursorLine() == 1)
            {
                throw EditorException("Can't move cursor left");
            }
            else if(editor.cursorColumn() == 1)
            {
                int previousLine = editor.cursorLine() -1;
                int previousLineLength = editor.textLineLength(previousLine) + 1;
                editor.setCursor(previousLine, previousLineLength);
            }
            else
            {
            editor.decrementCol();
            }
        }
        virtual void undo(Editor& editor)
        {
            editor.setCursor(previousLine, previousCol);
        }
    private:
        int previousLine;
        int previousCol;
};

#endif
