//
// Created by Wang wei on 2017/6/27.
//

#ifndef PLAYER_PLAY_H
#define PLAYER_PLAY_H
extern void playSongs(int* no, char* listPath, char* pathPath);
//extern void playControl(int* no, int pp, char* listPath, char* pathPath);
extern void lastSong(int* no, char* listPath, char* pathPath);
extern void nextSong(int* no, char* listPath, char* pathPath);
extern void getPath(int* no, char* path, char* pathPath);
#endif //PLAYER_PLAY_H
