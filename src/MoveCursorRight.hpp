#ifndef MOVECURSORRIGHT_HPP
#define MOVECURSORRIGHT_HPP
#include "Command.hpp"
#include "EditorException.hpp"

class MoveCursorRight : public Command
{
    public:
        virtual void execute(Editor& editor)
        {
            previousLine = editor.cursorLine();
            previousCol = editor.cursorColumn();
            if((editor.cursorColumn() >= editor.textLineLength(editor.cursorLine())+ 1) &&(editor.cursorLine() == editor.lineCount()))
            {
                throw EditorException("Can't move cursor right");
            }
            else if(editor.cursorColumn() >= editor.textLineLength(editor.cursorLine()) + 1)
            {
                int nextLine = editor.cursorLine() +1;
                editor.setCursor(nextLine, 1);
            }
            else
            {
            editor.incrementCol();
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
