#include "Beep.h"
#include "Debug.h"
#include "Arduino.h"
#include "globalConfig.h"
#include "melody_player.h"
#include "melody_factory.h"

const char* melodyString[5] = {"Pokemon:d=16,o=5,b=112:32p,f,a#,c6,c#6,c6,c#6,d#6,2f6,a#,c6,8c#6,8f6,8d#6,32c#.6,32d#.6,32c#.6,8c6,8g#.,f,a#,c6,c#6,c6,c#6,d#6,2f6,8a#,c#6,8f6,a,d#6,4g#6",
                             "15:d=4,o=5,b=100:16c#7,8c#7,8c#7,8c#7,8c#7,8d#7,16d#7,8d#7,8d#7,16d#6,8c#7,8c#7,8g#7,8a#6,p,16e#6,16e#6,8f#6,16f#6,8f#6,16p,8f#6,8g#6,8g#6,8e#6,8e#6,8c#6",
                             "AaliaRe:d=4,o=5,b=180:a,8a,e.6,d6,8e6,8f6,e6,c6,8c6,8b,a,b,8b,8c6,2d6,8c6,8b,8a,8g,a,8a,8a,e6,f.6,g.,a,a,2a,8c6,8b,8a,8g,a,8a,8a,e6,f.6,g.,a,a,a",
                             "3ramkSha:d=4,o=6,b=200:e.,g.,e.,p,8a5,c,a5,d#.,f#.,b.5,p,8b5,8g,8f#,8e,8b5,e.,g.,e.,p,8a5,c,a5,d#.,f#.,d#,e.",
                             "8a,b.,8f#,1eHark:d=4,o=5,b=100:8a.,16a,8a,8g,8f,8e,f,8d,16e,16f,8g,8c,2c,2d,2c"};

static MelodyPlayer Beep(BuzzerPin);
static Melody melody;

void Beep_Init(void){
    melody = MelodyFactory.loadRtttlString(melodyString[0]);
    pinMode(BuzzerPin, OUTPUT);
    digitalWrite(BuzzerPin, LOW);
    if(!melody){
        SCLOCK_LOGLN("[BEEP ERROR] load file failed!");
    }
}


bool Beep_isPlaying(void)
{
    return Beep.isPlaying();
}

void Beep_Play(void)
{
    if (!Beep_isPlaying())
        Beep.play(melody);  
}

void Beep_Shutdown(void)
{
    if (Beep_isPlaying())
        Beep.stop();
    digitalWrite(BuzzerPin, LOW);
}

// void Beep_ChangeRtttl(void)
// {
//     melody = MelodyFactory.loadRtttlString(melodyString[0]);
// }