# Keypad Interfacing with 8051

This repository contains an example of interfacing a **4×4 matrix keypad**
with the **8051 microcontroller** using the row-column scanning method.

## Description

A matrix keypad is used as an input device to enter numeric or alphanumeric
data. The 8051 scans the keypad by grounding one row at a time and reading
the column status to detect which key is pressed.

## Keypad Type

- 4×4 Matrix Keypad
- 4 Rows (R1–R4)
- 4 Columns (C1–C4)
- Total Keys: 16

## Working Logic

1. Configure rows as OUTPUT and columns as INPUT
2. Set all columns HIGH
3. Pull one row LOW at a time
4. Read column pins
5. If any column reads LOW, key is pressed
6. Identify key based on row and column
7. Apply debounce delay

## Hardware Used

- AT89C51 / AT89S52 (8051)
- 4×4 Matrix Keypad
- 11.0592 MHz Crystal
- 5V Power Supply
- Proteus (for simulation)

## Software Used

- Keil µVision (Embedded C)
- Proteus Design Suite

## Applications

- Password based systems
- Digital keypad locks
- Calculator projects
- Embedded menu systems

## Files

- keypad.c    → 8051 keypad scanning code
- keypad.hex  → Compiled HEX file
- README.md   → Project documentation

