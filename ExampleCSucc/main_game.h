#ifndef SOURCE_H
#define SOURCE_H
//#include "taco.c"
#define BGMUSIC "taco.wav"
#define async_song() PlaySound(TEXT(BGMUSIC), NULL, (SND_FILENAME+SND_LOOP+SND_ASYNC));
#endif