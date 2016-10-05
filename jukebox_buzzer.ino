/*

 PublicInfo:
 Jukebox_Buzzer by Jan
 Project started: 10.11.2015
 Versions+Changes:
 Public: yes
 GitHub: https://github.com/Sarlochin/Arduino_Jukebox_Buzzer
 Publisher: Sarlochin

 */


#define delay_decrementer 100  //Decrease the timings by a fixed value to be able to speed up the music with the potentiometer

//Define the Pins
const int Poti_Speed_pin = A0;

#define ledPin1  13    //Pin for LED1
#define ledPin2  12    //Pin for LED2
#define buzzerPin  4  //Pin for the ActiveBuzzer

//Define the notes for the Music Array

#define  C0  16
#define CI0 17
#define D0  18
#define DI0 19
#define E0  21
#define F0  22
#define FI0 23
#define G0  25
#define GI0 26
#define A0  28
#define AI0 29
#define B0  31
#define C1  33
#define CI1 35
#define D1  37
#define DI1 39
#define E1  41
#define F1  44
#define FI1 46
#define G1  49
#define GI1 52
#define A1  55
#define AI1 58
#define B1  62
#define C2  65
#define CI2 69
#define D2  73
#define DI2 78
#define E2  82
#define F2  87
#define FI2 93
#define G2  98
#define GI2 104
#define A2  110
#define AI2 117
#define B2  123
#define C3  131
#define CI3 139
#define D3  147
#define DI3 156
#define E3  165
#define F3  175
#define FI3 185
#define G3  196
#define GI3 208
#define A3  220
#define AI3 233
#define B3  247
#define C4  262
#define CI4 277
#define D4  294
#define DI4 311
#define E4  330
#define F4  349
#define FI4 370
#define G4  392
#define GI4 415
#define A4  440
#define AI4 466
#define B4  494
#define C5  523
#define CI5 554
#define D5  587
#define DI5 622
#define E5  659
#define F5  698
#define FI5 740
#define G5  784
#define GI5 831
#define A5  880
#define AI5 932
#define B5  988
#define C6  1047
#define CI6 1109
#define D6  1175
#define DI6 1245
#define E6  1319
#define F6  1397
#define FI6 1480
#define G6  1568
#define GI6 1661
#define A6  1760
#define AI6 1865
#define B6  1976
#define C7  2093
#define CI7 2217
#define D7  2349
#define DI7 2489
#define E7  2637
#define F7  2794
#define FI7 2960
#define G7  3136
#define GI7 3322
#define A7  3520
#define AI7 3729
#define B7  3951
#define C8  4186
#define CI8 4435
#define D8  4699
#define DI8 4978
#define E8  5274
#define F8  5588
#define FI8 5920
#define G8  6272
#define GI8 6645
#define A8  7040
#define AI8 7459
#define B8  7902
#define pause 0


//Arrays for music and timings: StarWars Imperial March

int musiC[] = {
  A4, A4, A4, F4, C5, A4, F4, C5, A4, pause, E5, E5, E5, F5, C5, GI4, F4, C5, A4, pause,   A5, A4, A4, A5, GI5, G5, FI5, F5, FI5, pause, AI4, DI5, D5, CI5, C5, B4, C5, pause,   F4, GI4, F4, A4, C5, A4, C5, E5, pause,    A5, A4, A4, A5, GI5, G5, FI5, F5, FI5, pause, AI4, DI5, D5, CI5, C5, B4, C5, pause, F4, GI4, F4, C5, A4, F4, C5, A4, pause};

int delayS[] = {
  500, 500, 500, 350, 150, 500, 350, 150, 650, 500, 500, 500, 500, 350, 150, 500, 350, 150, 650, 500,   500, 300, 150, 500, 325, 175, 125, 125, 250, 325, 250, 500, 325, 175, 125, 125, 250, 350,    250, 500, 350, 125, 500, 375, 125, 650, 500,    500, 300, 150, 500, 325, 175, 125, 125, 250, 325, 250, 500, 325, 175, 125, 125, 250, 350,    250, 500, 375, 125, 500, 375, 125, 650, 650};


int size1 = sizeof(musiC) / sizeof(int);  //Size of the array to determine how many notes to play
int size2 = sizeof(delayS) / sizeof(int);  //Debug only


int poti_delay = 0;  //additional timing delay for the music

void setup()
{
  //Setup pin modes
  pinMode(buzzerPin, OUTPUT);  //Setting the input and output modes
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);


   Serial.begin(9600); //Debug only

  if (size1 != size2)
  {
    Serial.println("Warning Size mismatch"); //Debug only
  } 
  else {
    Serial.println("Size Match"); //Debug only
    Serial.println(size1); //Debug only
    Serial.println(size2); //Debug only
    Serial.println("Setup Compleate"); //Debug only
  }


}

void loop()
{

  for (int i = 0; i < size1; i++)   //play the music
  {

    poti_delay = ((analogRead(Poti_Speed_pin) >> 2)- delay_decrementer); //Read the delay value from the Potentiometer (returns value from 0-1023 converted to the range from 0-255)

    Serial.println(poti_delay); //Debug only


    
    tone(buzzerPin, musiC[i], delayS[i] + poti_delay);  //Playing the note with calculated duration


    if (i % 2 == 0) //Switch between the LEDs every other note
    {
      digitalWrite(ledPin1, HIGH);
      delay(delayS[i] + poti_delay);
      digitalWrite(ledPin1, LOW);
    } 
    else
    {
      digitalWrite(ledPin2, HIGH);
      delay((delayS[i] - delay_decrementer) + poti_delay);
      digitalWrite(ledPin2, LOW);
    }

    noTone(buzzerPin);  //Mute the Buzzer

    delay(50);

  }



}
