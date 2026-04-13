<#
.SYNOPSIS
    Mouse Jiggler for Microsoft Teams
.DESCRIPTION
    Moves the mouse pointer every 2 minutes to prevent Teams from showing
    an idle/away status, keeping your presence indicator as Busy (red).
    No dependencies required — runs natively on any Windows machine.
.USAGE
    Right-click > Run with PowerShell
    — or —
    powershell -ExecutionPolicy Bypass -File mouse_jiggler.ps1
    — or —
    powershell -ExecutionPolicy Bypass -File mouse_jiggler.ps1 -IntervalSeconds 90
.NOTES
    Press Ctrl+C to stop.
#>

param(
    [int]$IntervalSeconds = 1
)

Add-Type -TypeDefinition @"
using System;
using System.Runtime.InteropServices;

public class MouseJiggler
{
    [DllImport("user32.dll")]
    public static extern bool GetCursorPos(out POINT lpPoint);

    [DllImport("user32.dll")]
    public static extern bool SetCursorPos(int X, int Y);

    [StructLayout(LayoutKind.Sequential)]
    public struct POINT
    {
        public int X;
        public int Y;
    }
}
"@

Write-Host "============================================"
Write-Host "  Mouse Jiggler for Microsoft Teams"
Write-Host "  Interval: every $IntervalSeconds seconds"
Write-Host "  Press Ctrl+C to stop"
Write-Host "============================================"
Write-Host ""

$random = New-Object System.Random

while ($true) {
    $point = New-Object MouseJiggler+POINT
    [MouseJiggler]::GetCursorPos([ref]$point) | Out-Null

    $dx = $random.Next(-3, 4)
    if ($dx -eq 0) { $dx = 1 }
    $dy = $random.Next(-3, 4)
    if ($dy -eq 0) { $dy = 1 }

    # Move away
    [MouseJiggler]::SetCursorPos($point.X + $dx, $point.Y + $dy) | Out-Null
    Start-Sleep -Milliseconds 200

    # Move back
    [MouseJiggler]::SetCursorPos($point.X, $point.Y) | Out-Null

    $timestamp = Get-Date -Format "HH:mm:ss"
    Write-Host "[$timestamp] Jiggled mouse (dx=$dx, dy=$dy)"

    Start-Sleep -Seconds $IntervalSeconds
}
