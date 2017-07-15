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

    printf("请输入路径, 取消请输入0:\n");
    scanf("%s", path);
    if(strcmp(path, "0") == 0)
        return;
    while ((_chdir(path)) == -1) {
        printf("文件夹不存在，请重新输入");
        scanf("%s", path);
    }

    //打开目录
    if ((pDir = opendir(path)) == NULL){
        printf("Cannot open directory:%s\n", path);
    }

    _chdir(dir);

    //读取目录
    while ((ent = readdir(pDir)) != NULL) {
        //统计文件数量
        _snprintf(dir, sizeof(dir), "%s/%s", path, ent->d_name);
        //得到文件信息
        stat(dir, &statbuf);
        //判断是文件还是目录
        if (!S_ISDIR(statbuf.st_mode)) {
            count++;
        }
    }
    //关闭目录
    closedir(pDir);

    //开辟字符指针数组，用于下一步的开辟容纳文件名字符串的空间
    fileNameList = (char**)malloc(sizeof(char*) * count);
    pathOfSongs = (char**)malloc(sizeof(char*) * count);
    if (fileNameList == NULL) {
        printf("Malloc heap failed!\n");
    }

    //打开目录
    if ((pDir = opendir(path)) == NULL){
        printf("Cannot open directory:%s\n", path);
    }

    //读取目录
    for(i = 0; ((ent = readdir(pDir))!= NULL) && i < count;) {
        if (strlen(ent->d_name) <= 0){
            continue;
        }
        //读取文件的绝对路径名
        _snprintf(dir, 512, "%s/%s", path, ent->d_name);
        //文件信息
        stat(dir, &statbuf);
        //判断是文件还是目录
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
                printf("第%d个文件:%s\n", i, ent->d_name);
                printf("路径:%s\n", pathOfSongs[i]);
                i++;
            }
        }
    }
    //关闭目录
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
    printf("1. 添加歌曲\n");
    printf("2. 清空列表\n");
    printf("0. 退出\n");
    printf("歌曲列表：\n");


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
            printf("您输入的选项不存在，请重新输入");
        }
        printf("1. 添加歌曲\n");
        printf("2. 清空列表\n");
        printf("0. 退出\n");
        printf("歌曲列表：\n");
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