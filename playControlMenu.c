//
// Created by Wang wei on 2017/6/28.
//
#include <stdlib.h>
#include <stdio.h>
#include "play.h"
#include <string.h>
#include "PlayInterface.h"
enum STATUS {
    STATUS_PLAY = 1,
    STATUS_PAUSE = 2,
    STATUS_STOP = 3,
};

void playControl(int* no, char* listPath, char* pathPath){
    char* path = (char*)malloc(512);
    char* name = (char*)malloc(512);
    char p[512] = {0};
    int len = 0;
    int input = 0;

	system("cls");
    printf("1. ����\n");
    printf("2. ��ͣ\n");
    printf("3. ֹͣ\n");
    printf("0. �˳�\n");

    input = getch();
    input -= 48;
    getPath(no, path, pathPath);
    strcpy(p, path);
    len = (int)strlen(p);
    p[len - 1] = 0;
    while (input) {
        switch (input) {
            case STATUS_PLAY:
                play(p);
				break;
            case STATUS_PAUSE:
                pause(p);
                break;
            case STATUS_STOP:
                stop(p);
                break;
            default:
                printf("������������\n");
                break;
        }
        system("cls");
        printf("1. ����\n");
        printf("2. ��ͣ\n");
        printf("3. ֹͣ\n");
        printf("0. �˳�\n");
        input = getch();
        input -= 48;
    }
}