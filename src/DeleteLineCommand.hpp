#ifndef DELETELINECOMMAND_HPP
#define DELETELINECOMMAND_HPP
#include "Command.hpp"
#include <iostream>
class DeleteLineCommand : public Command
{
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
        if(editor.lineCount() == 1)
        {    
            editor.removeLine(1);
            editor.setCursor(1, 1); 
            editor.insertNewLine();
        }
        else if(editor.cursorLine() == 1)
        {
            //editor.setCursor(1,1);
            if(editor.cursorColumn() > editor.textLineLength(2))
            {
            editor.setCursor(1, editor.textLineLength(2) + 1);
            }
            editor.removeLine(1);
            editor.decrementLineCount();
        }
        else if(editor.cursorLine() == editor.lineCount())
        {
            
            editor.removeLine(editor.cursorLine());
            int previousLine = editor.cursorLine() - 1;
            if(editor.cursorColumn() > editor.textLineLength(previousLine))
            {
            editor.setCursor(previousLine, editor.textLineLength(previousLine) + 1);
            }
            else
            {
            editor.decrementLine();
            }
            editor.decrementLineCount();
        }
        else
        {
            int nextLine = editor.cursorLine() + 1;
            if(editor.textLineLength(nextLine) < editor.cursorColumn())
            {
                int nextLineLength = editor.textLineLength(nextLine) + 1;
                
                editor.removeLine(editor.cursorLine());
                editor.setCursor(editor.cursorLine(), nextLineLength);
                editor.decrementLineCount();
            }
            else
            {
                editor.removeLine(editor.cursorLine());
                editor.decrementLineCount();
            }
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
        int previousLine;
        int previousCol;
        int previousLineCount;
        std::vector<std::string> previousLines;

};

#endif
