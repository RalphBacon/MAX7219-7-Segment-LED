#define MAX2719_DIN	8
#define MAX2719_CS	9
#define MAX2719_CLK	10

void setup()
{
  initialise();

  // For test mode (all digits on) set to 0x01. Normally we want this off (0x00)
  output(0x0f, 0x0);

  // Set all digits off initially
  output(0x0c, 0x0);

  // Set brightness for the digits to high(er) level than default minimum (Intensity Register Format)
  output(0x0a, 0x02);

  // Set decode mode for ALL digits to output actual ASCII chars rather than just
  // individual segments of a digit
  output(0x09, 0xFF);

  // Set first digit (right most) to '5'
  output(0x01, 0x05);

  // Set next digits to 8 7 6 (Code B Font)
  output(0x02, 0x06);
  output(0x03, 0x07);
  output(0x04, 0x08);

  // If first four digits not set it will display rubbish data (Code B Font) so use 'blank' from Register Data
  output(0x05, 0x0F);
  output(0x06, 0x0F);
  output(0x07, 0x0F);
  output(0x08, 0x0F);

  // Ensure ALL digits are displayed (Scan Limit Register)
  output(0x0b, 0x07);

  // Turn display ON (boot up = shutdown display)
  output(0x0c, 0x01);
}

void loop()
{
  for (int cnt = 0; cnt < 10; cnt++) {
    output(0x08, cnt);
    output(0x07, getDigitValue(cnt, 1));
    output(0x06, getDigitValue(cnt, 2));
    output(0x05, getDigitValue(cnt, 3));
    output(0x04, getDigitValue(cnt, 4));
    output(0x03, getDigitValue(cnt, 5));
    output(0x02, getDigitValue(cnt, 6));
    output(0x01, getDigitValue(cnt, 7));
    delay(500);
  }
}

int getDigitValue(int seed, int inc) {
  if (seed + inc > 9) {
    return seed + inc - 10;
  }
  return seed + inc;
}

void initialise()
{
  digitalWrite(MAX2719_CS, HIGH);
  pinMode(MAX2719_DIN, OUTPUT);
  pinMode(MAX2719_CS, OUTPUT);
  pinMode(MAX2719_CLK, OUTPUT);
}

void output(byte address, byte data)
{
  digitalWrite(MAX2719_CS, LOW);

  // Send out two bytes (16 bit)
  // parameters: shiftOut(dataPin, clockPin, bitOrder, value)
  shiftOut(MAX2719_DIN, MAX2719_CLK, MSBFIRST, address);
  shiftOut(MAX2719_DIN, MAX2719_CLK, MSBFIRST, data);
  digitalWrite(MAX2719_CS, HIGH);
}
