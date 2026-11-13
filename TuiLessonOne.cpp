
#include <iostream>
#include <string>
#include <conio.h>
#include <vector>
#include <iomanip>
#include <sstream>

// TUI C++ Lesson 1
// The Building Blocks of Terminal User Interface Coding
// Windows PowerShell Specific


//---BUILDING BLOCK VOID FUNCTIONS---
// Functions that do not give an output but rather serve a purpose


// clearScreen
void clearScreen() {
    std::cout << "\033[2J";
    std::cout << "\033[H";
}

// moveTo
void moveTo(int row, int col) {
    std::cout << "\033[" << row << ";" << col << "H";
}

// setColor
void setColor(int color) {
    std::cout << "\033[" << color << "m";
}

// drawText
void drawText(int row, int col, int color, std::string text) {
    moveTo(row, col);
    setColor(color);
    std::cout << text;
    setColor(0);
}

// enterScreen
void enterScreen() {
    std::cout << "\033[?1049h";
}

// exitScreen
void exitScreen() {
    std::cout << "\033[?1049l";
}

// hideCursor
void hideCursor() {
    std::cout << "\033[?25l";
}

// showCursor
void showCursor() {
    std::cout << "\033[?25h";
}

// drawBox
void drawBox(int row, int col, int width, int height) {
    // position top left
    moveTo(row, col);

    // top
    std::cout << std::string(width, '-');

    // sides
    for (int count = 0; count < (height - 2); count++) {
        moveTo((row + count + 1), col);
        std::cout << "|";
        std::cout << std::string(width - 2, ' ');
        std::cout << "|";
    }

    // position bottom left
    moveTo((row + height - 1), col);

    // bottom
    std::cout << std::string(width, '-');
}


//---STRUCT DATA FOR VECTORS---
struct Quote {
    std::string tenor;
    double bid;
    double ask;
};


//---FORMAT DATA---
std::string fmt(double x) {
    std::ostringstream out;
    out << std::fixed << std::setprecision(2) << x;
    return out.str();
}


// drawLadder
void drawLadder(std::vector<Quote> ladder) {
    for (int i = 0; i < ladder.size(); i++) {
        drawText(10 + i, 10, 32, ladder[i].tenor + " " + fmt(ladder[i].bid) + " " + fmt(ladder[i].ask));
    }
}


//---RENDER FOR UI---

// render
void render(int count, Quote q, std::vector<Quote> ladder) {
    clearScreen();
    drawBox(3, 10, 20, 5);
    drawText(5, 12, 36, "Count: " + std::to_string(count));
    drawText(6, 12, 32, q.tenor + " " + fmt(q.bid) + " " + fmt(q.ask));
    drawLadder(ladder);
}


//---MAIN---
int main() {
    // Enter Screen Function
    enterScreen();

    // Hide Curson Function
    hideCursor();

    // Clear Screen Function
    clearScreen();

    // drawBox COMMENTED OUT
    // drawBox(5, 11, 20, 5);

    // Count Integer
    int count = 0;


    // Structured Quote 10Y UST
    Quote tenYear = { "10Y", 4.25, 4.26 };


    //---DATA VECTOR---
    std::vector<Quote> ladder = {
        { "2Y", 3.95, 3.96 },
        { "5Y", 4.10, 4.11 },
        { "10Y", 4.25, 4.26 },
        { "30Y", 4.55, 4.56 }
    };


    //---FIRST RENDER, USING COUNT---
    render(count, tenYear, ladder);

    // setting bool running to true
    bool running = true;


    // While Loop For TUI
    while (running) {

        // input key
        char key = _getch();

        // If Statement To Make Loop False and Exit
        if (key == 'q') {
            running = false;
        }

        // If Statement to add with a
        if (key == 'a') {
            count++;
            render(count, tenYear, ladder);
        }

        // If Statement to subtract with b
        if (key == 'd') {
            count--;
            render(count, tenYear, ladder);
        }
    }


    // showCursor function
    showCursor();

    // exitScreen function
    exitScreen();

    //---RETURN 0---
    return 0;
}
