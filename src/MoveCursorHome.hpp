#ifndef MOVECURSORHOME_HPP
#define MOVECURSORHOME_HPP
#include "Command.hpp"

class MoveCursorHome : public Command
{
    public:
    virtual void execute(Editor& editor)
    {
        previousLine = editor.cursorLine();
        previousCol = editor.cursorColumn();
        editor.setCursor(editor.cursorLine(), 1);
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
