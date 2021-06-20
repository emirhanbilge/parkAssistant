
#include <LiquidCrystal.h>
#include <TimeLib.h>

unsigned long DEFAULT_TIME = 1623696918; // https://www.epochconverter.com/ From here we can get the current time and paste it (it's very easy for TimeLib to get it as Epoc time and parse it) / https://www.epochconverter.com/ Buradan şimdiki zamanı alıp yapıştırabiliriz (Epoc time olarak alıp parse etmek TimeLib için çok kolay)
int trigger_pin = 8;
int echo_pin = 9;
float timeS;
int distance;
int oldDistance;
int sleepVoiceTime = 100;
int buzzerPin = 13;
int doThin = 523;                      // blap blap sound
int timeCount = 1;                     // for 2 second control
bool work = true;                      // if we crash our system should stop working
LiquidCrystal lcd(12, 11, 5, 4, 3, 2); // lcd object create

String makeDouble(int param) //The function that I wrote in the previous lab that allows us to add 0 in the beginning if the hours and days are less than 10 /  Bir önceki lab da yazdığım , saat ve günlerin 10 dan küçük olması durumunda başına 0 eklememizi sağlayan fonksiyon
{
    if (param < 10)
        return "0" + String(param);
    return String(param);
}

void setup()
{
    Serial.begin(9600);           // Serial communication starting (baud rate 9600 bit per second)
    lcd.begin(16, 2);             // Lcd starting
    pinMode(trigger_pin, OUTPUT); // Trigger pin set
    pinMode(echo_pin, INPUT);     // Echo pin set
    /// Firstly ,  I calculated distance
    digitalWrite(trigger_pin, HIGH);      // sound wave is sent
    delay(500);                           // waiting half second , this is like broadcast
    digitalWrite(trigger_pin, LOW);       // stop send
    timeS = pulseIn(echo_pin, HIGH);      // We calculate the return time of the sound wave.
    distance = (int)((timeS / 2) / 29.1); // we calculate distance
}

String printDisplay(int dist) // The function that return the required information message and how often the buzzer sounds according to the distances.
{
    if (dist > 100)
    {
        sleepVoiceTime = 600;
        return "Too Far";
    }
    else if (dist > 50 && dist < 101)
    {
        sleepVoiceTime = 300;
        return "Far";
    }
    else if (dist > 20 && dist < 51)
    {
        sleepVoiceTime = 150;
        return "Close";
    }
    else if (dist > 4 && dist < 21)
    {
        sleepVoiceTime = 75;
        return "Too Close";
    }
    else if (dist < 5)
    {
        sleepVoiceTime = 25;
        return "Crashed";
    }
}

void gameOverSound() /// Game over music reference https://gist.github.com/gskielian/6135641
{
    tone(buzzerPin, 480, 80);
    delay(330);
    tone(buzzerPin, 450, 100);
    delay(150);
    tone(buzzerPin, 430, 100);
    delay(300);
    tone(buzzerPin, 380, 100);
    delay(200);
    tone(buzzerPin, 660, 80);
    delay(200);
    tone(buzzerPin, 760, 50);
    delay(150);
    tone(buzzerPin, 860, 100);
    delay(300);
    tone(buzzerPin, 700, 80);
    delay(150);
    tone(buzzerPin, 760, 50);
    delay(350);
    tone(buzzerPin, 660, 80);
    delay(350);
    tone(buzzerPin, 900, 80);
}

void mainFunction()
{
    while (work)
    {
        setTime(DEFAULT_TIME);                          //update process of time
        digitalWrite(trigger_pin, HIGH);                // sound wave is sent
        delay(1000 - sleepVoiceTime);                   // waiting  , this is like broadcast sound wave
        digitalWrite(trigger_pin, LOW);                 // stop send
        timeS = pulseIn(echo_pin, HIGH);                // We calculate the return time of the sound wave.
        distance = (int)((timeS / 2) / 29.1);           // we calculate distance
        if (distance < 1000 && oldDistance != distance) //If it is at the previous distance, we do not need to update the screen. Also, the status of greater than '1000' is set due to the sensor malfunctioning sometimes.
        {
            lcd.setCursor(0, 0); //Clearing the past
            lcd.print("    ");
            lcd.setCursor(0, 0); // printing current values  (distance )
            lcd.print(String(distance) + " cm");
            lcd.setCursor(0, 1);
            lcd.print("               ");
            lcd.setCursor(0, 1); // print second information
            lcd.print(printDisplay(distance));
        }
        if (distance < 5) // if distance less than 5 , we had an accident.
        {
            gameOverSound(); // playing game over music
            work = false;    // stop working
        }
        String b = printDisplay(distance); // print serial monitor setting
        b.toLowerCase();                   // lower return string
        if (timeCount % 2 == 1)
            Serial.println(" Date: " + makeDouble(day()) + "." + makeDouble(month()) + "." + String(year()) + " - Hour: " + makeDouble(hour()) + ":" + makeDouble(minute()) + ":" + makeDouble(second()) + " - Distance : " + String(distance) + " cm.\n" + "It is " + b + "."); // Printing serial monitör
        DEFAULT_TIME = DEFAULT_TIME + 1;                                                                                                                                                                                                                                         // time increasing 1 second  , we waited 1 second up
        timeCount = timeCount + 1;                                                                                                                                                                                                                                               // every 2 seconds we update the variable that we control that we will press the screen.
        oldDistance = distance;                                                                                                                                                                                                                                                  // we will assign the current value to the old value and use it in the comparison in the new measurement
        tone(buzzerPin, doThin);                                                                                                                                                                                                                                                 // 'creation of the beep voice '
        delay(sleepVoiceTime);
        noTone(buzzerPin);
    }
}

void loop()
{
    if (work) // if no accident the system will work
        mainFunction();
}

/*
References : 
    LCD ekran bağlantısını https://www.tinkercad.com/ üzerinden aldım.
    Epoc time kullanımını ise :  https://www.youtube.com/watch?v=NxieXXSnJ9U // A project made with RTC that I consulted for Epoc Time
    TimeLib Library : https://github.com/PaulStoffregen/Time
*/