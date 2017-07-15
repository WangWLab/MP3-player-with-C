//
// Created by Wang wei on 2017/6/27.
//
#include <stdio.h>
#include <stdlib.h>
#include "dirent.h"
#include <sys/stat.h>
#include <string.h>
#include <direct.h>
#include "unistd.h"
#include "play.h"
#include "PlayInterface.h"



void  addSongs(char* listPath, char* pathPath) {
    FILE* fp;
    char path[200];
    char** fileNameList = NULL;
    char** pathOfSongs = NULL;
    struct dirent* ent = NULL;
    DIR* pDir;
    char dir[5120];
    struct stat statbuf;
    int count = 0;
    int i = 0;

    printf("������·��, ȡ��������0:\n");
    scanf("%s", path);
    if(strcmp(path, "0") == 0)
        return;
    while ((_chdir(path)) == -1) {
        printf("�ļ��в����ڣ�����������");
        scanf("%s", path);
    }

    //��Ŀ¼
    if ((pDir = opendir(path)) == NULL){
        printf("Cannot open directory:%s\n", path);
    }

    _chdir(dir);

    //��ȡĿ¼
    while ((ent = readdir(pDir)) != NULL) {
        //ͳ���ļ�����
        _snprintf(dir, sizeof(dir), "%s/%s", path, ent->d_name);
        //�õ��ļ���Ϣ
        stat(dir, &statbuf);
        //�ж����ļ�����Ŀ¼
        if (!S_ISDIR(statbuf.st_mode)) {
            count++;
        }
    }
    //�ر�Ŀ¼
    closedir(pDir);

    //�����ַ�ָ�����飬������һ���Ŀ��������ļ����ַ����Ŀռ�
    fileNameList = (char**)malloc(sizeof(char*) * count);
    pathOfSongs = (char**)malloc(sizeof(char*) * count);
    if (fileNameList == NULL) {
        printf("Malloc heap failed!\n");
    }

    //��Ŀ¼
    if ((pDir = opendir(path)) == NULL){
        printf("Cannot open directory:%s\n", path);
    }

    //��ȡĿ¼
    for(i = 0; ((ent = readdir(pDir))!= NULL) && i < count;) {
        if (strlen(ent->d_name) <= 0){
            continue;
        }
        //��ȡ�ļ��ľ���·����
        _snprintf(dir, 512, "%s/%s", path, ent->d_name);
        //�ļ���Ϣ
        stat(dir, &statbuf);
        //�ж����ļ�����Ŀ¼
        if (!S_ISDIR(statbuf.st_mode)){
            if ((fileNameList[i] = (char*)malloc(strlen(ent->d_name)+1)) == NULL ||
                (pathOfSongs[i] = (char*)malloc(strlen(path)+strlen(ent->d_name)+8)) == NULL) {
                printf("malloc heap failed!\n");
            }
            if((strstr(ent->d_name, ".mp3")) != NULL) {
                memset(fileNameList[i], 0, sizeof(fileNameList[i]));
                memset(pathOfSongs[i], 0, sizeof(pathOfSongs[i]));
                strcpy(fileNameList[i], ent->d_name);
                strcpy(pathOfSongs[i], path);
                strcat(pathOfSongs[i], "\\");
                strcat(pathOfSongs[i], ent->d_name);
                printf("��%d���ļ�:%s\n", i, ent->d_name);
                printf("·��:%s\n", pathOfSongs[i]);
                i++;
            }
        }
    }
    //�ر�Ŀ¼
    closedir(pDir);

    fp = fopen(listPath, "a");
    for(i = 0; i < count; i++) {
        fputs(fileNameList[i], fp);
        fputc('\n', fp);
    }
    fclose(fp);
    fp = fopen(pathPath, "a");
    for(i = 0; i < count; i++) {
        fputs(pathOfSongs[i], fp);
        fputc('\n', fp);
    }
    fclose(fp);
}

void clearList(int* no, char* listPath, char* pathPath) {
    FILE* fp = fopen(listPath, "w");
    fclose(fp);
    fp = fopen(pathPath, "w");
    fclose(fp);
    no[0] = 3;
}

void listOfSongs(int* no, char* listPath, char* pathPath){
    FILE* fp = fopen(listPath, "r");
    int input = 0;
    int count = 3;
	int len = 0;
	static int times = 0;
    char str[300] = {0};
	char stopPath[512] = {0};

    system("cls");
    printf("1. ��Ӹ���\n");
    printf("2. ����б�\n");
    printf("0. �˳�\n");
    printf("�����б�\n");


    if(fp == NULL) {
        printf("file doesn't exist");
        return;
    }
    while (!feof(fp)) {
        if (fgets(str, 300, fp) != NULL) {
            printf("%d: %s\n", count, str);
            count++;
        }
    }
    count--;
    fclose(fp);

    input = getch();
    input -= 48;
    //scanf("%d", &input);
    while(input != 0){
        switch (input) {
            case 1:
                addSongs(listPath, pathPath);
                break;
            case 2:
                clearList(no, listPath, pathPath);
                break;
            default:
                if(input > count) {
                } else {
					if(times){
						getPath(no, stopPath, pathPath);
						len = (int)strlen(stopPath);
						stopPath[len-1] = 0;
						stop(stopPath);
					}
                    no[0] = input;
                    playSongs(no, listPath, pathPath);
					times++;
                }
                break;
        }

        system("cls");
        if(input > count) {
            printf("�������ѡ����ڣ�����������");
        }
        printf("1. ��Ӹ���\n");
        printf("2. ����б�\n");
        printf("0. �˳�\n");
        printf("�����б�\n");
        count = 3;
        fp = fopen(listPath, "r");
        if(fp == NULL) {
            printf("file doesn't exist");
            return;
        }
        while (!feof(fp)) {
            if (fgets(str, 300, fp) != NULL) {
                printf("%d: %s\n", count, str);
                count++;
            }
        }
        count--;
        fclose(fp);
        input = getch();
        input -= 48;
        //scanf("%d", &input);
    }
}