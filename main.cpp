#include <stdio.h>
#include <iostream>
#include <array>
#include <Windows.h>
#include <math.h>
#include <vector>
#include <time.h>
#include <cstdlib>
#include <sstream>
#include <string>
#include <algorithm>
#include <iterator>
#include <map>
#include "utils.cpp"


static bool running = true;
std::vector<int> solution;
std::vector<int> solutionCopy;
std::vector<int> attemptedSolution;
std::vector<int> attemptedSolutionCopy;
int circleArray[4] = { 0, 0, 0, 0 };
int circleArrayPos = 0;
int rectColor = 0;
int row = 0;
int column = 1;

struct RenderState {
	int Height, Width;
	void* Memory;

	BITMAPINFO BitmapInfo;
};

static RenderState renderState;

#include "renderer.cpp"

LRESULT CALLBACK window_callback(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	LRESULT result = 0;
	switch (uMsg)
	{
		case WM_CREATE:
		{
			CreateWindow(TEXT("BUTTON"), TEXT("special"), WS_CHILD | WS_VISIBLE, 600, 530, 50, 50, hwnd, (HMENU) SPECIAL, NULL, NULL);
			CreateWindow(TEXT("BUTTON"), TEXT("star"), WS_CHILD | WS_VISIBLE, 670, 530, 50, 50, hwnd, (HMENU) STAR, NULL, NULL);
			CreateWindow(TEXT("BUTTON"), TEXT("spade"), WS_CHILD | WS_VISIBLE, 740, 530, 50, 50, hwnd, (HMENU) SPADE, NULL, NULL);
			CreateWindow(TEXT("BUTTON"), TEXT("club"), WS_CHILD | WS_VISIBLE, 810, 530, 50, 50, hwnd, (HMENU) CLUB, NULL, NULL);
			CreateWindow(TEXT("BUTTON"), TEXT("diamond"), WS_CHILD | WS_VISIBLE, 880, 530, 50, 50, hwnd, (HMENU) DIAMOND, NULL, NULL);
			CreateWindow(TEXT("BUTTON"), TEXT("heart"), WS_CHILD | WS_VISIBLE, 950, 530, 50, 50, hwnd, (HMENU) HEART, NULL, NULL);
			CreateWindow(TEXT("BUTTON"), TEXT("enter"), WS_CHILD | WS_VISIBLE, 1020, 530, 50, 50, hwnd, (HMENU) ENTER, NULL, NULL);
			CreateWindow(TEXT("BUTTON"), TEXT("delete"), WS_CHILD | WS_VISIBLE, 1090, 530, 50, 50, hwnd, (HMENU) DELETE, NULL, NULL);
			CreateWindow(TEXT("BUTTON"), TEXT("check"), WS_CHILD | WS_VISIBLE, 1160, 530, 50, 50, hwnd, (HMENU) 9, NULL, NULL);
			break;
		}
		case WM_COMMAND:
		{
			
			if (LOWORD(wParam) == SPECIAL)
			{
				if (attemptedSolution.size() < 4)
				{
					attemptedSolution.push_back(1);
						row++;
					rectColor = 1;
				}
			}
			
			if (LOWORD(wParam) == STAR)
			{
				if (attemptedSolution.size() < 4)
				{
					attemptedSolution.push_back(2);
					rectColor = 2;
					row++;
				}
			}
			
			if (LOWORD(wParam) == SPADE)
			{
				if (attemptedSolution.size() < 4)
				{
					attemptedSolution.push_back(3);
					rectColor = 3;
					row++;
				}
			}
			
			if (LOWORD(wParam) == CLUB)
			{
				if (attemptedSolution.size() < 4)
				{
					attemptedSolution.push_back(4);
					rectColor = 4;
					row++;
				}
			}
			
			if (LOWORD(wParam) == DIAMOND)
			{
				if (attemptedSolution.size() < 4)
				{
					attemptedSolution.push_back(5);
					rectColor = 5;
					row++;
				}
			}
			
			if (LOWORD(wParam) == HEART)
			{
				if (attemptedSolution.size() < 4)
				{
					attemptedSolution.push_back(6);
					rectColor = 6;
					row++;
				}
			}
			
			if (LOWORD(wParam) == ENTER)
			{


				if (attemptedSolution.size() != 4)
				{
					MessageBox(hwnd, (LPCSTR)"Add symbol first", (LPCSTR)"Attempt not valid", MB_ICONINFORMATION);
				}
				else
				{	
					for (int i = 0; i < 4; i++)
					{
						circleArray[i] = 0;
					}

					for (auto i = attemptedSolution.begin(); i != attemptedSolution.end(); ++i)
					{
						attemptedSolutionCopy.push_back(*i);
					}

					for (auto i = solution.begin(); i != solution.end(); ++i)
					{
						solutionCopy.push_back(*i);
					}

					for (auto i = solutionCopy.begin(); i != solutionCopy.end(); ++i)
					{
						for (auto j = attemptedSolutionCopy.begin(); j != attemptedSolutionCopy.end(); ++j)
						{
							if (std::distance(solutionCopy.begin(), i) == std::distance(attemptedSolutionCopy.begin(), j) && *i == *j && *i != 0 && *j != 0)
							{
								circleArray[circleArrayPos] = 1;
								circleArrayPos++;
								*i = 0;
								*j = 0;
							}
						}
					}

					for (auto i = solutionCopy.begin(); i != solutionCopy.end(); ++i)
					{
						for (auto j = attemptedSolutionCopy.begin(); j != attemptedSolutionCopy.end(); ++j)
						{

							if (*i != 0 && *j != 0 && *i == *j)
							{
								circleArray[circleArrayPos] = 2;
								circleArrayPos++;
								*i = 0;
								*j = 0;
							}
						}
					}
					
					solutionCopy.pop_back();
					solutionCopy.pop_back();
					solutionCopy.pop_back();
					solutionCopy.pop_back();
					attemptedSolution.pop_back();
					attemptedSolution.pop_back();
					attemptedSolution.pop_back();
					attemptedSolution.pop_back();
					attemptedSolutionCopy.pop_back();
					attemptedSolutionCopy.pop_back();
					attemptedSolutionCopy.pop_back();
					attemptedSolutionCopy.pop_back();
					circleArrayPos = 0;
					row = 0;
					++column;					
					
				}
				
			}
			
			if (LOWORD(wParam) == DELETE)
			{
				if (attemptedSolution.size() > 0)
				{
					attemptedSolution.pop_back();
					rectColor = 0;
					row--;
				}
				else
				{
					MessageBox(hwnd, (LPCSTR)"Nothing to remove", (LPCSTR)"Value removed", MB_ICONINFORMATION);
				}
			}
			// optional 9th button for showing solution
			/*if (LOWORD(wParam) == 9)
			{
								
					std::stringstream ss;
					copy(solution.begin(), solution.end(), std::ostream_iterator<int>(ss, " "));
					std::string str = ss.str();
					str = str.substr(0, str.length() - 1);
					MessageBox(hwnd, (LPCSTR) str.c_str(), (LPCSTR)"Vector value", MB_ICONINFORMATION);				

			}*/
			break;
		}
		case WM_CLOSE:
		case WM_DESTROY:
		{
			running = false;
		} break;
		case WM_SIZE:
		{
			RECT rect;
			GetClientRect(hwnd, &rect);
			renderState.Width = rect.right - rect.left;
			renderState.Height = rect.bottom - rect.top;
			int bufferSize = renderState.Width * renderState.Height * sizeof(unsigned int);

			if (renderState.Memory) VirtualFree(renderState.Memory, 0, MEM_RELEASE);
			renderState.Memory = VirtualAlloc(0, bufferSize, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);

			renderState.BitmapInfo.bmiHeader.biSize = sizeof(renderState.BitmapInfo.bmiHeader);
			renderState.BitmapInfo.bmiHeader.biWidth = renderState.Width;
			renderState.BitmapInfo.bmiHeader.biHeight = renderState.Height;
			renderState.BitmapInfo.bmiHeader.biPlanes = 1;
			renderState.BitmapInfo.bmiHeader.biBitCount = 32;
			renderState.BitmapInfo.bmiHeader.biCompression = BI_RGB;
		}
		default:
		{
			result = DefWindowProc(hwnd, uMsg, wParam, lParam);
		}
	}
	return result;
}

int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	srand(time(0));

	for (int i = 0; i < 4; i++)
	{
		solution.push_back((rand() % 6) + 1);
	}

	// create window class
	WNDCLASS window_class = {};
	window_class.style = CS_HREDRAW | CS_VREDRAW;
	window_class.lpszClassName = "Game Window Class";
	window_class.lpfnWndProc = window_callback;

	// register class
	RegisterClass(&window_class);

	// create window
	HWND window = CreateWindow(window_class.lpszClassName, "Skocko", WS_VISIBLE | WS_OVERLAPPED | WS_MINIMIZEBOX | WS_SYSMENU, CW_USEDEFAULT, CW_USEDEFAULT, 1280, 720, 0, 0, hInstance, 0);
	HDC hdc = GetDC(window);

	clear_screen(0x0080ff);
	set_board();

	// game loop
	while (running)
	{
		MSG message;
		while (PeekMessage(&message, window, 0, 0, PM_REMOVE))
		{

			TranslateMessage(&message);
			DispatchMessage(&message);
		}
		if (column > 1)
		{
			for (int i = 0; i < 4; i++)
			{
				switch (circleArray[i])
				{
				case 0:
				{
					draw_circle(625 + 70 * i, 625 - 70 * (column - 2), 25, 0x000000);
				}
				break;
				case 1:
				{
					draw_circle(625 + 70 * i, 625 - 70 * (column - 2), 25, 0xff0000);
				}
				break;
				case 2:
				{
					draw_circle(625 + 70 * i, 625 - 70 * (column - 2), 25, 0xf0ff00);
				}
				break;
				}
			}
		}

		
		switch (rectColor)
		{
			case 0:
			{
				if (row == 0)
				{
					draw_rect(100 + 70 * row, 600 - 70 * (column - 1), 150 + 70 * row, 650 - 70 * (column - 1), 0x99ccff);
				}
				else
				{
					draw_rect(100 + 70 * row, 600 - 70 * (column - 1), 150 + 70 * row, 650 - 70 * (column - 1), 0x99ccff);
				}
			}
			break;
			case 1:
			{
				if (row == 0)
				{
					draw_rect(100 + 70 * (row - 1), 600 - 70 * (column - 1), 150 + 70 * (row - 1), 650 - 70 * (column - 1), 0x0080ff);
				}
				else
				{
					draw_rect(100 + 70 * (row - 1), 600 - 70 * (column - 1), 150 + 70 * (row - 1), 650 - 70 * (column - 1), 0x000000);
				}

			}
			break;
			case 2:
			{
				if (row == 0)
				{
					draw_rect(100 + 70 * (row - 1), 600 - 70 * (column - 1), 150 + 70 * (row - 1), 650 - 70 * (column - 1), 0x0080ff);
				}
				else
				{
					draw_rect(100 + 70 * (row - 1), 600 - 70 * (column - 1), 150 + 70 * (row - 1), 650 - 70 * (column - 1), 0xff0000);
				}

			}
			break;
			case 3:
			{
				if (row == 0)
				{
					draw_rect(100 + 70 * (row - 1), 600 - 70 * (column - 1), 150 + 70 * (row - 1), 650 - 70 * (column - 1), 0x0080ff);
				}
				else
				{
					draw_rect(100 + 70 * (row - 1), 600 - 70 * (column - 1), 150 + 70 * (row - 1), 650 - 70 * (column - 1), 0x00ff00);
				}

			}
			break;
			case 4:
			{
				if (row == 0)
				{
					draw_rect(100 + 70 * (row - 1), 600 - 70 * (column - 1), 150 + 70 * (row - 1), 650 - 70 * (column - 1), 0x0080ff);
				}
				else
				{
					draw_rect(100 + 70 * (row - 1), 600 - 70 * (column - 1), 150 + 70 * (row - 1), 650 - 70 * (column - 1), 0x0000ff);
				}

			}
			break;
			case 5:
			{
				if (row == 0)
				{
					draw_rect(100 + 70 * (row - 1), 600 - 70 * (column - 1), 150 + 70 * (row - 1), 650 - 70 * (column - 1), 0x0080ff);
				}
				else
				{
					draw_rect(100 + 70 * (row - 1), 600 - 70 * (column - 1), 150 + 70 * (row - 1), 650 - 70 * (column - 1), 0xffff00);
				}

			}
			break;
			case 6:
			{
				if (row == 0)
				{
					draw_rect(100 + 70 * (row - 1), 600 - 70 * (column - 1), 150 + 70 * (row - 1), 650 - 70 * (column - 1), 0x0080ff);
				}
				else
				{
					draw_rect(100 + 70 * (row - 1), 600 - 70 * (column - 1), 150 + 70 * (row - 1), 650 - 70 * (column - 1), 0xff00ff);
				}

			}
			break;
			default:
			{
				if (row == 0)
				{
					draw_rect(100 + 70 * (row - 1), 600 - 70 * (column - 1), 150 + 70 * (row - 1), 650 - 70 * (column - 1), 0x0080ff);
				}
				else
				{
					draw_rect(100 + 70 * (row - 1), 600 - 70 * (column - 1), 150 + 70 * (row - 1), 650 - 70 * (column - 1), 0xffffff);
				}
			}
		}

		// render
		StretchDIBits(hdc, 0, 0, renderState.Width, renderState.Height, 0, 0, renderState.Width, renderState.Height, renderState.Memory, &renderState.BitmapInfo, DIB_RGB_COLORS, SRCCOPY);
	
		if (circleArray[0] == 1 && circleArray[1] == 1 && circleArray[2] == 1 && circleArray[3] == 1)
		{
			MessageBox(window, (LPCSTR)"You won!", (LPCSTR)"Game over", MB_ICONINFORMATION);
			running = false;
		}

		if (column > 6 && running == true)
		{
			MessageBox(window, (LPCSTR)"You lost!", (LPCSTR)"Game over", MB_ICONINFORMATION);
			running = false;
		}
	}
	 
	return 0;
}