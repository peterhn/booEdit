// Editor.cpp
//
// ICS 45C Winter 2014
// Project #4: People Just Love to Play with Words
//
// Implementation of the Editor class

#include "Editor.hpp"
#include "EditorException.hpp"

Editor::Editor()
    :numOfLines{1}, currentCol{1}, currentLine{1}
{
    text.push_back("");
}


int Editor::cursorLine() const
{
    return currentLine;
}


int Editor::cursorColumn() const
{
    return currentCol;
}


int Editor::lineCount() const
{
    return numOfLines;
}

void Editor::incrementCol()
{
    currentCol++;
}
void Editor::decrementCol()
{
    currentCol--;
}

void Editor::incrementLine()
{
    currentLine++;
}

void Editor::decrementLine()
{
    currentLine--;
}

void Editor::incrementLineCount()
{
    numOfLines++;
}

void Editor::decrementLineCount()
{
    numOfLines--;
}

void Editor::setCursor(int line, int column)
{
    currentLine = line;
    currentCol = column;
}

void Editor::insertLine(std::string s, int lineNum)
{
    text[lineNum-1] = s;
}
void Editor::insertNewLine()
{
    if(text.size() == 0)
    {
        text.push_back("");
        return;
    }
    std::string s = line(cursorLine());
    text.push_back("");
    std::string splitString =  s.substr(cursorColumn()-1, textLineLength(cursorLine()));
    s.erase(cursorColumn()-1, textLineLength(cursorLine()));
    text[cursorLine()-1] = s;
    text.insert(text.begin() + cursorLine(), splitString);
}

void Editor::removeLine(int lineNum)
{
    text.erase(text.begin() + (lineNum - 1));
}

void Editor::setLineCount(int count)
{
    numOfLines = count;
}
int Editor::textLineLength(int lineNum)
{
    return text[lineNum-1].length();
}

std::vector<std::string> Editor::getText()
{
    return text;
}

const std::string& Editor::line(int lineNumber) const
{
    return text[lineNumber-1];
}

