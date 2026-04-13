/*
 * Mouse Jiggler for Microsoft Teams
 *
 * Moves the mouse pointer every 2 minutes to prevent Teams from showing
 * an idle/away status, keeping your presence indicator as Busy (red).
 *
 * Build (Visual Studio Developer Command Prompt):
 *     cl mouse_jiggler.cpp /Fe:mouse_jiggler.exe user32.lib
 *
 * Build (MinGW / g++):
 *     g++ mouse_jiggler.cpp -o mouse_jiggler.exe -luser32
 *
 * Usage:
 *     mouse_jiggler.exe              (default: every 120 seconds)
 *     mouse_jiggler.exe 90           (custom interval in seconds)
 *
 * Press Ctrl+C to stop.
 */

#include <cstdlib>
#include <ctime>
#include <iostream>
#include <windows.h>

int main(int argc, char* argv[])
{
    int interval = 120;
    if (argc > 1) {
        interval = std::atoi(argv[1]);
        if (interval <= 0) {
            std::cerr << "Invalid interval. Using default (120 seconds)." << std::endl;
            interval = 120;
        }
    }

    std::srand(static_cast<unsigned>(std::time(nullptr)));

    std::cout << "============================================" << std::endl;
    std::cout << "  Mouse Jiggler for Microsoft Teams" << std::endl;
    std::cout << "  Interval: every " << interval << " seconds" << std::endl;
    std::cout << "  Press Ctrl+C to stop" << std::endl;
    std::cout << "============================================" << std::endl;
    std::cout << std::endl;

    while (true) {
        POINT cursor;
        GetCursorPos(&cursor);

        int dx = (std::rand() % 6) - 3;
        if (dx == 0) dx = 1;
        int dy = (std::rand() % 6) - 3;
        if (dy == 0) dy = 1;

        // Move away
        SetCursorPos(cursor.x + dx, cursor.y + dy);
        Sleep(200);

        // Move back
        SetCursorPos(cursor.x, cursor.y);

        // Timestamp
        std::time_t now = std::time(nullptr);
        char buf[9];
        std::strftime(buf, sizeof(buf), "%H:%M:%S", std::localtime(&now));
        std::cout << "[" << buf << "] Jiggled mouse (dx=" << dx << ", dy=" << dy << ")" << std::endl;

        Sleep(interval * 1000);
    }

    return 0;
}
