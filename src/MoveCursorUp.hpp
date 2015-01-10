#ifndef MOVECURSORUP_HPP
#define MOVECURSORUP_HPP
#include "Command.hpp"
#include "EditorException.hpp"
class MoveCursorUp : public Command
{
    public:
       virtual void execute(Editor& editor)
       {
            previousLine = editor.cursorLine();
            previousCol = editor.cursorColumn();
            if(editor.cursorLine() == 1)
            {
                throw EditorException("Can't move cursor up");
            
            }
            else
            {
                int previousLine = editor.cursorLine() -1;
                if(editor.cursorColumn() > editor.textLineLength(previousLine))
                {
                editor.setCursor(previousLine, editor.textLineLength(previousLine) + 1);
                }
                else
                {
                    editor.decrementLine();
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
