//
// Created by Wang wei on 2017/6/27.
//


#include <stdio.h>
#include <string.h>
#include <direct.h>
#include "play.h"
#include "listofsongs.h"
#include "voice.h"
#include "playControlMenu.h"

void mainmenu(){
    FILE* fp = 0;
    int input = 0;
    int noOfSongs[1] = {0};
    static int pp = 1;
	char str[25] = {0};
    char path[512] = {0};
    char listPath[512] = {0};
    char pathPath[512] = {0};
    char noPath[512] = {0};

    _getcwd(path, sizeof(path));
    strcpy(listPath, path);
    strcat(listPath, "/listOfSongs.txt");
    strcpy(pathPath, path);
    strcat(pathPath, "/pathOfSongs.txt");
    strcpy(noPath, path);
    strcat(noPath, "/noPath.txt");

    printf("1. �����б�\n");
    printf("2. ��һ��\n");
    printf("3. ���ſ���\n");
    printf("4. ��һ��\n");
    printf("5. ����ģʽ\n");
    printf("6. ��������\n");
    printf("0. �˳�\n");

    if((fp = fopen(listPath, "r")) == NULL) {
        printf("List file doesn't exist\n");
        fp = fopen(listPath, "w");
    }
    fclose(fp);
    if ((fp = fopen(pathPath, "r")) == NULL) {
        printf("Path file doesn't exist\n");
        fp = fopen(pathPath, "w");
    }
    fclose(fp);
    if ((fp = fopen(noPath, "r")) == NULL) {
        printf("noPath file doesn't exist\n");
        fp = fopen(noPath, "w+");
        fputs("3", fp);
        fseek(fp, 0, SEEK_SET);
    }
	fgets(str, sizeof(str), fp);
    noOfSongs[0] = atoi(str);
    fclose(fp);

    input = getch();
    input -= 48;
    //scanf("%d", &input);
    /*ʹ�ø�ѭ��ʵ�����˵�����ʾ�������Ը������ŵĿ��ƣ�
    *��ȡ�����б���˳�����
    */
    while (input) {
        switch (input) {
            case 1:
                listOfSongs(noOfSongs, listPath, pathPath);
                break;
            case 2:
                lastSong(noOfSongs, listPath, pathPath);
                break;
            case 3:
                playControl(noOfSongs, listPath, pathPath);
                break;
            case 4:
                nextSong(noOfSongs, listPath, pathPath);
                break;
            case 6:
                volume();
                break;
            default:
                break;
        }

        system("cls");
        printf("1. �����б�\n");
        printf("2. ��һ��\n");
        printf("3. ���ſ���\n");
        printf("4. ��һ��\n");
        printf("5. ����ģʽ\n");
        printf("6. ��������\n");
        printf("0. �˳�\n");
        input = getch();
        input -= 48;
        //scanf("%d", &input);
    }
    fp = fopen(noPath, "r+");
	sprintf(str, "%d", noOfSongs[0]);
    fputs(str, fp);
    fclose(fp);
}