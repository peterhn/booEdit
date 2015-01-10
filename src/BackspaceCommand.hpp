#ifndef BACKSPACECOMMAND_HPP
#define BACKSPACECOMMAND_HPP
#include "Command.hpp"
#include "EditorException.hpp"

class BackspaceCommand : public Command
{
    public:
    virtual void execute(Editor& editor)
    {
        previousLine = editor.cursorLine();
        previousCol = editor.cursorColumn();
        previousLineCount = editor.lineCount();
        
        //for(int i = 1; i <= previousLineCount; i++)
        //{
          //  previousLines.push_back(editor.line(i));
        //}
        previousLines = editor.getText();
        if(editor.cursorLine() == 1 && editor.cursorColumn() == 1)
        {
            throw EditorException("Can't backspace character");
        }
        else if(editor.cursorColumn() == 1)
        {
            
            previousBackspaceLine = previousLine -1;
            int previousLineLength = editor.textLineLength(previousBackspaceLine);
            std::string text = editor.line(editor.cursorLine());
            std::string previousLineText = editor.line(previousBackspaceLine);
            std::string newLine = previousLineText + text; 
            editor.removeLine(editor.cursorLine());
            editor.insertLine(newLine, previousBackspaceLine);
            editor.setCursor(previousBackspaceLine, previousLineLength+1);
            editor.decrementLineCount();

        }
        else
        {
            std::string text = editor.line(editor.cursorLine());
            text.erase(text.begin() + (editor.cursorColumn() -2));
            editor.insertLine(text, editor.cursorLine());
            editor.decrementCol();
        }
    }
    virtual void undo(Editor& editor)
    {
        editor.setLineCount(previousLineCount);
        for(int i = 1; i <= previousLineCount; i++)
        {
            editor.insertLine(previousLines[i-1], i);
        }
        previousLines.clear();
        editor.setCursor(previousLine, previousCol);
    }
    private:
        int previousBackspaceLine;
        int previousLine;
        int previousCol;
        int previousLineCount;
        std::string previousText;
        std::vector<std::string> previousLines;

};
#endif
