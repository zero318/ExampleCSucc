#ifndef SOURCE_H
#define SOURCE_H
#define play_async_song(song_file) PlaySound(TEXT(song_file), NULL, (SND_FILENAME+SND_LOOP+SND_ASYNC));
#define stop_async_song() PlaySound(NULL, 0, 0);
#endif