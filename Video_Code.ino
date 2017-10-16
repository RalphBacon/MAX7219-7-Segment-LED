
// Three digital pins used to control the MAX7219
#define MAX7219_DIN 5 // Data In
#define MAX7219_CS 6  // Chip Select 
#define MAX7219_CLK 7 // Clock

// Common routine to talk to MAX7219
void display(byte address, byte value) {

  //-------------------------------------------
  //shiftOut(dataPin, clockPin, bitOrder, value)
  //-------------------------------------------
  digitalWrite(MAX7219_CS, LOW); // Always set LOW so chip knows it's being addressed
  shiftOut(MAX7219_DIN, MAX7219_CLK, MSBFIRST, address);
  shiftOut(MAX7219_DIN, MAX7219_CLK, MSBFIRST, value);
  digitalWrite(MAX7219_CS, HIGH); // Set high when finished
}

void setup() {

  // All digital pins are for transmitting data
  pinMode (MAX7219_DIN, OUTPUT);
  pinMode (MAX7219_CS, OUTPUT);
  pinMode (MAX7219_CLK, OUTPUT);
  digitalWrite(MAX7219_CS, HIGH);

  // Test mode off
  display (0x0F, 0);

  // Shutdown
  display (0x0C, 0);

  // Set decode mode for ALL digits to output actual ASCII chars rather than just
  // individual segments of a digit
  display (0x09, 0xFF);

  // Set all digits from #1 (rightmost) to #8 (leftmost) to a value
  display (0x01, 0x09); 
  display (0x02, 0x01);
  display (0x03, 0x02);
  display (0x04, 0x07);
  display (0x05, 0x0E); //P
  display (0x06, 0x0D); //L
  display (0x07, 0x0B); //E
  display (0x08, 0x0C); //H

  //Intensity (from 0 dimmest to FF brightest)
  display (0x0A, 0x08);

  // Ensure ALL 8 digits (numbered 0 thru 7) are displayed (Scan Limit Register)
  display (0x0B, 0x07);

  // Switch On all digits
  display (0x0C, 0x01);
}


void loop() {


}

