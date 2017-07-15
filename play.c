//
// Created by Wang wei on 2017/6/27.
//
#include "PlayInterface.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>


void playSongs(int* no, char* listPath, char* pathPath);

void getPath(int* no, char* path, char* pathPath){
    FILE* fp = NULL;
    int i = 3;
    fp = fopen(pathPath, "r");

    if(fp == NULL) {
        printf("打开错误，请清空歌曲列表重新添加歌曲");
        return;
    }
    while (!feof(fp) &&  i <= *no) {
        if (fgets(path, 512, fp) != NULL) {
            i++;
        }
    }
    fclose(fp);
}

void getName(int* no, char* name, char* listPath) {
    FILE* fp = NULL;
    int i = 3;
    fp = fopen(listPath, "r");
    if(fp == NULL) {
        printf("打开错误，请清空歌曲列表重新添加歌曲");
        return;
    }
    while (!feof(fp) &&  i <= *no) {
        if (fgets(name, 512, fp) != NULL) {
            i++;
        }
    }
    fclose(fp);
}

int getCount(char* listPath){
    FILE* fp = NULL;
    int i = 0;
    char name[300] = {0};
    if((fp = fopen(listPath, "r")) == NULL) {
        printf("打开错误，请清空歌曲列表重新添加歌曲");
        return -1;
    }
    while (!feof(fp)) {
        if (fgets(name, 300, fp) != NULL) {
            i++;
        }
    }
    return i;
}

void lastSong (int* no, char* listPath, char* pathPath){
	char* path = (char*)malloc(512);
	char p[512] = {0};
    int len = 0;

    getPath(no, path, pathPath);
    strcpy(p, path);
    len = (int)strlen(p);
    p[len-1] = 0;
    if(*no > 3){
		stop(p);
        no[0]--;
        playSongs(no, listPath, pathPath);
    } else {
        printf("已经是第一首。");
    }
}

void playSongs (int* no, char* listPath, char* pathPath) {
    char* path = (char*)malloc(512);
    char p[512] = {0};
    int len = 0;

    getPath(no, path, pathPath);
    strcpy(p, path);
    len = (int)strlen(p);
    p[len-1] = 0;
    printf("%s\n", p);

    play(p);
}

void nextSong (int* no, char* listPath, char* pathPath) {
    int num = getCount(listPath);
	char* path = (char*)malloc(512);
	char p[512] = {0};
    int len = 0;

    getPath(no, path, pathPath);
    strcpy(p, path);
    len = (int)strlen(p);
    p[len-1] = 0;
    if(*no - 2 < num && num > 1){
		stop(p);
        no[0]++;
        playSongs(no, listPath, pathPath);
    }
	else {
		printf("已是最后一首\n");
		system("pause");
	}
}
