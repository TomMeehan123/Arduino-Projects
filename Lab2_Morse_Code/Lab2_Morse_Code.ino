/**
 * Name: Tom Meehan
 * ID: 18220975
 * Module: Sensors and Actuators
 * Module Code: ET4224
 * Lecturer: Bob Strunz
 * Purpose: To generate a morse code decoder
 */

char *letters[] = {
  // The letters A-Z in Morse code
  ".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..",
  ".---", "-.-", ".-..", "--", "-.", "---", ".--.", "--.-", ".-.",
  "...", "-", "..-", "...-", ".--", "-..-", "-.--", "--.."
};

/*
   Creates a pointer array of characters for the numbers and converts character into morse code
*/

char *numbers[] = {
  // The numbers 0-9 in Morse code
  "-----", ".----", "..---", "...--", "....-", ".....", "-....",
  "--...", "---..", "----."
};
/*
char *morsetable[] = {
    // Letters A-Z (indices 0-25)
    ".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....",
    "..", ".---", "-.-", ".-..", "--", "-.", "---", ".--.",
    "--.-", ".-.", "...", "-", "..-", "...-", ".--", "-..-",
    "-.--", "--..", 
    // Digits start here (indices 26-35)
    ".----", "..--", "...--", "....-", "....",
    "-...", "--...", "---..", "----.", "-----"
};
*/

/*
   Creates a pointer array of characters for the letters and converts each character into morse code
*/


/* Convert a character to an index into the morse code table.
    Rules:
      If it's an uppercase letter (A-Z) then return 0-25
      If it's a digit (0-9) then return 26-35
      Anything else return -1
    Assumption:
      The character has already been converted to uppercase if it's a letter.
*/ 
/**
  int lookup(char *c) {

  if (c == 32) return -1; // Modified to allow for space characters
    c = toUpperCase(c);

  // If the character is not a valid letter or digit then return -1
  if ( !isAlphaNumeric(c)) {
    return -1;
  }

  // Now we do a bit of ASCII trickery to convert letters & digits
  // into positions in our lookup table. See https://www.arduino.cc/reference/en/language/variables/data-types/char/
  // Letters are easier
  if ( isAlpha(c) ) {
    return c - 'A';
  }

  if ( isDigit(c) ) {
    // add on 25 because the digits come after the letters in the table, so we skip that far
    return (c - '0') + 25;
  }
  }

*/
//#define DEBUG_MODE              // Comment this out for no debugging messages

#define DLY_UNIT 100             // 50 Milliseconds for a dot,everything else is derived from this
#define DLY_UNIT_DSH 3*DLY_UNIT
#define DLY_UNIT_SPC 6*DLY_UNIT // NOT 7 because dots and dashes have a delay of 1 themselves
#define LED 12 // Defines pin 12 as LED

#define BUZZER_PIN 5            // Uncomment this for a buzzer, works on Nano and UNO
#define HAS_BUZZER              // Uncomment this for a buzzer

bool finished = false; // boolean for when the progame is not finished

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(LED, OUTPUT); // Sets LED as output
  digitalWrite(LED, LOW);

#ifdef HAS_BUZZER
  pinMode(BUZZER_PIN, OUTPUT); // Sets buzzer output as high
  analogWrite(BUZZER_PIN, 0);
#endif

}

void loop() {

  char ch;

  // waits for charters to be entered
  while (!finished) {
    // Check if characters are available
    if (Serial.available()) {

      // Read one character at a time
      ch = Serial.read();

      
      //Serial.println(morsetable[ch]);
      //displayMorse(morsetable[ch]);
      
      // Check for uppercase letters
      if (ch >= 'A' && ch <= 'Z') {
        Serial.println(ch);
        displayMorse(letters[ch - 'A']);
      }
      // Check for lowercase letters
      else  if (ch >= 'a' && ch <= 'z') {
        Serial.println(ch);
        displayMorse(letters[ch - 'a']);
      }
      // Check for numbers
      else if (ch >= '0' && ch <= '9') {
        Serial.println(ch);
        displayMorse(numbers[ch - '0']);
      }
      // Check for space between words
      else if (ch == ' ') {

        // Put space between two words in a message...equal to seven dots
        delay(DLY_UNIT_SPC);
      }
    }

  }
  while (true) {} // Do nothing
}

// Displays the morse code for each input
//@param morse_Display pointer to the morse code
void displayMorse(char *morse_Display) {

  int i = 0;
  // read (.) and (-) and flash LED
  while (morse_Display[i] != NULL) {
    delayMorse(morse_Display[i]);
    i++;
  }

  delay(DLY_UNIT_DSH);
}

//Delays for '.' or '-' in morse code
//@param char morse_Delay character that is '.' or '-'
void delayMorse(char *morse_Delay) {

  // Turn on LED
  digitalWrite(LED, HIGH);

  if (morse_Delay == '.') { // If dot
    delay(DLY_UNIT);
  }
  else if (morse_Delay == '-') { // if dash
    delay(DLY_UNIT_DSH);
  }

  else if (morse_Delay == ' ') { // if space
    delay(DLY_UNIT_SPC);
  }
  // turn off led
  digitalWrite(LED,LOW);

  delay(DLY_UNIT);

  // Turn on Buzzer
  digitalWrite(BUZZER_PIN, HIGH);

  if (morse_Delay == '.') { // If dot
    delay(DLY_UNIT);
  }
  else if (morse_Delay == '-') { // if dash
    delay(DLY_UNIT_DSH);
  }

  else if (morse_Delay == ' ') { // if space
    delay(DLY_UNIT_SPC);
  }

  // Turn off LED
  digitalWrite(BUZZER_PIN, LOW); 
  delay(DLY_UNIT);
  }
