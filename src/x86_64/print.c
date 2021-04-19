#include "print.h"

const static size_t NUM_COLS = 80; // Number of console columns
const static size_t NUM_ROWS = 25; // Number of console rows

// structure to represent a character
struct Char {
  uint8_t character; // defines what character this Char represents
  uint8_t color; // defines foreground and background color for this Char
};

struct Char* buffer = (struct Char*) 0xb8000; // Char pointer to VRAM, as an array 
size_t col = 0; // Current column
size_t row = 0; // Current row
uint8_t color = PRINT_COLOR_WHITE | PRINT_COLOR_BLACK << 4; // Defines foreground as white and background as black
// Shifted PrintColorBlack left by 4 in order to fit it inside uint8_t

void clear_row(size_t row) {
  struct Char empty = (struct Char) {
    character: ' ',
    color: color,
  };
  
  for (size_t col = 0; col < NUM_COLS; col++) {
    buffer[col + NUM_ROWS * ROW] = empty; // This is how index into vram is calculated! col + NUM_ROWS * row will get the index in
    // vram for the current col and row.
    // this also sets the buffer at row, col to the empty char defined above.
  }
}

void print_clear() {
  for (size_t i = 0; i < NUM_ROWS; i++) {
    clear_row(i); // Go over every row and clear it
  }
}

void print_newline() {
  col = 0; // Set the column to 0, returning to beginning of line

  if (row < NUM_ROWS - 1) { // If the row number is LESS then NUM_ROWS - 1 (if we are NOT out of rows),
      row++; // just increase the row number.
      return; // Then return from function, no further processing is required
  }
  
  // If we are here, we are OUT OF ROWS.

  for (size_t row = 1; row < NUM_ROWS; row++) { // for every row on the screen, starting from the SECOND row:
      for (size_t col = 0; col < NUM_COLS; col++) { // for every column in the row:
          struct Char character = buffer[col + NUM_COLS * row]; // set character to be the Char in the buffer for the current col, row
          buffer[col + NUM_COLS * (row - 1)] = character; // set the character in col, row - 1 to the current character
      }
  } // this loop moves every line on the screen up by one

  clear_row(NUM_ROWS - 1); // Change to NUM_COLS if this does not work for some reason
}

void print_char(char character) {
  if (character == '\n') {
    // This is a newline, so just print_newline();
    print_newline();
    return; // Since it's a newline, we dont need any more processing
  }
  
  if (col > NUM_COLS) {
    // Out of columns on this row, so print a newline
    print_newline();
    // Still haven't printed the character yet, so no return statement
  }
  
  buffer[col + NUM_COLS * row] = (struct Char) { // Remember col+NUM_COLS*row? Set that to a new Char with the character as character
    character: (uint8_t) character, // char can be directly casted to uint8_t!
    color: color, // Use the set color.
  };
  
  col++; // Add 1 to col, we just printed a char
}

void print_str(char* str) {
  // Takes in a null-terminated cstr and prints it to the screen
  for (size_t i = 0; true; i++) { // Loop continues infinitley until break or return
    char character = (uint8_t) str[i]; // Set character to the current index in the c_str
    
    if (character == "\0") {
      // Null-terminated, exit loop
      return;
    }
    
    print_char(character); // print the character
  }
}

void print_set_color(uint8_t foreground, uint8_t background) {
  color = foreground + (background << 4);
}
