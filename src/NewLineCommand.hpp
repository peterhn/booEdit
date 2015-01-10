#ifndef NEWLINECOMMAND_HPP
#define NEWLINECOMMAND_HPP
#include "Command.hpp"
#include "EditorException.hpp"

class NewLineCommand : public Command
{
    public:
        virtual void execute(Editor& editor)
        {
            previousLine = editor.cursorLine();
            previousCol = editor.cursorColumn();
            previousLineCount = editor.lineCount();
            previousText = editor.line(editor.cursorLine());
            editor.insertNewLine();
            editor.incrementLineCount();
            editor.setCursor(editor.cursorLine() + 1, 1);
        }
        virtual void undo(Editor& editor)
        {
            editor.insertLine(previousText, previousLine);
            editor.removeLine(previousLine +1);
            editor.setCursor(previousLine, previousCol);
            editor.setLineCount(previousLineCount);
        }
   private:
        int previousLine;
        int previousCol;
        int previousLineCount;
        std::string previousText;
};

#endif
