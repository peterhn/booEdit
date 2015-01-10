#ifndef INSERTKEY_HPP
#define INSERTKEY_HPP
#include "Command.hpp"
#include "EditorException.hpp"
#include <string>
#include <sstream>
class InsertKey : public Command
{   
    public:
        InsertKey(char c)
            :character{c}
        {
        }
        virtual void execute(Editor& editor)
        {
            std::stringstream ss;
            std::string s;
            ss << character;
            s = ss.str();
            
            std::string text = editor.line(editor.cursorLine());
            previousText = text;
            previousCol = editor.cursorColumn();
            previousLine = editor.cursorLine();
            lineCount = editor.lineCount();
            text.insert((editor.cursorColumn() -1), s);
            
            
            editor.insertLine(text, editor.cursorLine());
            editor.incrementCol();
        }
   
        virtual void undo(Editor& editor)
        {
            editor.insertLine(previousText, previousLine);
            editor.setCursor(previousLine, previousCol);
            editor.setLineCount(lineCount);
        }
    private:
    std::string previousText;
    int previousLine;
    int previousCol;
    int lineCount;
    char character;
};

#endif
