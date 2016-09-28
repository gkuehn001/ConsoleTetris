// ConsoleTetris.cpp : Definiert den Einstiegspunkt für die Konsolenanwendung.
//

#include "stdafx.h"

#include <iostream>
#include <curses.h>
#include <windows.h>
#include <chrono>
#include <thread>


#include "BaseDefinitions.h"
#include "TileVariation.h"
#include "Board.h"
#include "Debug.h"



using namespace std;
using namespace std::chrono;

class Timer
{
public:
	Timer() : beg_(clock_::now()) {}
	void reset() { beg_ = clock_::now(); }
	double elapsed() const {
		return std::chrono::duration_cast<second_>
			(clock_::now() - beg_).count();
	}

private:
	typedef std::chrono::high_resolution_clock clock_;
	typedef std::chrono::duration<double, std::ratio<1> > second_;
	std::chrono::time_point<clock_> beg_;
};

static void Render(const CBoard & _board)
{
	CDebug::Render();
	//clear();
	_board.Render();
	//CDebug::Output();
	refresh();
}

static int ConsoleTetris()
{
	initscr();
	noecho();
	//cbreak();
	// setup curses
	curs_set(0);
	keypad(stdscr, true);
	refresh();
	nodelay(stdscr, true);
	//timeout(1);
	int row = 3;
	int col = 3;
	bool running = true;

	CBoard myBoard(BaseDefinitions::FieldPositionX, BaseDefinitions::FieldPositionY, BaseDefinitions::FieldWidth, BaseDefinitions::FieldHeight);

	Timer t;
	double elapsed = 0.0;
	double elapsedLast = 0.0;

	t.reset();
	long gameStep = 0;
	bool bPaused = false;

	CDebug::SetDebugOutput("\nMove - Left, Right\nTurn - Up, Down\nDrop - Space\n\nToggle Next - t\nToggle Pause - p\n\nExit - Escape");

	while (running)
	{

		if (!bPaused && (t.elapsed() - elapsedLast) > 0.01)
		{
			elapsedLast += 0.01;
			myBoard.Update(++gameStep);
			//CDebug::SetDebugOutput("%d", gameStep);
		}

		int ch = wgetch(stdscr);
		switch (ch)
		{
		case VK_ESCAPE:
			running = false;
			break;
		case KEY_UP:
			if (!bPaused) myBoard.OnKeyUp();
			break;
		case KEY_DOWN:
			if (!bPaused) myBoard.OnKeyDown();
			break;
		case KEY_RIGHT:
			if (!bPaused) myBoard.OnKeyRight();
			break;
		case KEY_LEFT:
			if (!bPaused) myBoard.OnKeyLeft();
			break;
		case VK_SPACE:
			if (!bPaused) myBoard.OnKeySpace(gameStep);
			break;
		case 'p':
			if (bPaused == false)
			{
				bPaused = true;
			}
			else
			{
				bPaused = false;
				elapsedLast = elapsedLast - (double)((int)elapsedLast);
				t.reset();
			}
			break;
		case 't':
			myBoard.ToggleNext();
			break;
		}
		if (!bPaused) Render(myBoard);
	}

	endwin();

	return 0;
}

int main()
{
	return ConsoleTetris();
}

