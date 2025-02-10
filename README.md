# Modular CLI Menu in c

## Overview
This C program provides a simple console-based menu system with navigation and selection capabilities. It allows users to navigate through menu options using numeric keys and select an option using the `ENTER` key. The selected option is then returned for further processing.

## Features
- Displays a formatted menu with a customizable header.
- Highlights the selected menu option in purple.
- Allows navigation using numeric keys.
- Detects and processes the `ENTER` key to confirm a selection.
- Clears the screen upon selection for a seamless user experience.

## Files
- `menu.c`: Contains the implementation of the menu system.
- `menu.h`: (Not provided, but expected to contain function prototypes and necessary macros.)

## Usage
### Function Definitions

#### `int menu(const char header[], const char menuElements[][50], const char endPhrase[], int numOfElements);`

This function displays a menu and allows the user to navigate and select an option.

**Parameters:**
- `header[]`: The title/header of the menu.
- `menuElements[][50]`: Array of menu options (strings).
- `endPhrase[]`: A closing phrase to be displayed when exiting the menu.
- `numOfElements`: Number of menu options available.

**Returns:**
- The selected menu option index (1-based).

#### `char getch();`

This function captures a single character input without requiring the user to press `ENTER`.

**Returns:**
- The numeric value of the key pressed.

## Compilation & Execution

To compile the program, use:
```sh
gcc menu.c -o menu
```

To execute:
```sh
./menu
```

## Example Usage

```c
#include "menu.h"

int main() {
    const char header[] = "Main Menu";
    const char menuElements[][50] = {"Option 1", "Option 2", "Exit"};
    const char endPhrase[] = "Goodbye!";
    int numOfElements = 3;

    int choice = menu(header, menuElements, endPhrase, numOfElements);
    printf("You selected option: %d\n", choice);
    return 0;
}
```

## Dependencies
- Standard C libraries: `<stdio.h>`, `<termios.h>`, `<unistd.h>`, `<stdlib.h>`, `<string.h>`.

## Notes
- The `system("clear")` command is used to refresh the console, which may need adjustment for non-UNIX systems.
- The function `getch()` modifies terminal attributes to allow single-character input.

## Author
Created by **HalfAsleepDev**

## Version
- **1.0** (Last update: February 10, 2025)

