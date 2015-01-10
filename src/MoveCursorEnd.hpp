#ifndef MOVECURSOREND_HPP
#define MOVECURSOREND_HPP
#include "Command.hpp"

class MoveCursorEnd : public Command
{
    public:
    virtual void execute(Editor& editor)
    {   
        previousLine = editor.cursorLine();
        previousCol = editor.cursorColumn();
        int line = editor.cursorLine();
        editor.setCursor(line, editor.textLineLength(line) +1);
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
