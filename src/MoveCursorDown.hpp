#ifndef MOVECURSORDOWN_HPP
#define MOVECURSORDOWN_HPP
#include "Command.hpp"
#include "EditorException.hpp"
class MoveCursorDown : public Command
{
    public:
    virtual void execute(Editor& editor)
    {
        previousLine = editor.cursorLine();
        previousCol = editor.cursorColumn();
        if(editor.cursorLine() + 1 > editor.lineCount())
        {
            throw EditorException("Can't move cursor down");
        }
        else
        {
            int nextLineCount = editor.textLineLength(editor.cursorLine() +1);
            //int currentLineCount = editor.textLineLength(editor.cursorLine());
            if(editor.cursorColumn() > nextLineCount)
            {
                editor.setCursor(editor.cursorLine() +1 , nextLineCount +1);    
            }
            else
            {
                editor.incrementLine();
            }
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
