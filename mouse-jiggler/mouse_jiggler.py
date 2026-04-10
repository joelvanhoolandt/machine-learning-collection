"""
Mouse Jiggler for Microsoft Teams
Moves the mouse pointer every 2 minutes to prevent Teams from showing
an idle/away status, keeping your presence indicator as Busy (red).

Usage:
    python mouse_jiggler.py          # default: jiggle every 120 seconds
    python mouse_jiggler.py --interval 90   # custom interval in seconds

Press Ctrl+C to stop.

Requirements:
    pip install pyautogui
"""

import argparse
import random
import sys
import time

import pyautogui

# Disable pyautogui's fail-safe pause
pyautogui.PAUSE = 0.1


def jiggle_mouse():
    """Move the mouse by a small random offset, then back."""
    x, y = pyautogui.position()
    dx = random.choice([-3, -2, -1, 1, 2, 3])
    dy = random.choice([-3, -2, -1, 1, 2, 3])
    pyautogui.moveTo(x + dx, y + dy, duration=0.2)
    pyautogui.moveTo(x, y, duration=0.2)


def main():
    parser = argparse.ArgumentParser(description="Mouse jiggler to keep Teams status active.")
    parser.add_argument(
        "--interval",
        type=int,
        default=120,
        help="Seconds between jiggles (default: 120)",
    )
    args = parser.parse_args()

    print(f"Mouse jiggler started (every {args.interval}s). Press Ctrl+C to stop.")

    try:
        while True:
            jiggle_mouse()
            time.sleep(args.interval)
    except KeyboardInterrupt:
        print("\nStopped.")
        sys.exit(0)


if __name__ == "__main__":
    main()
