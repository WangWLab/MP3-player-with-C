#include <stdio.h>
#include <string.h>
#include <Windows.h>
#include <mmsystem.h>	// mci库头文件
#pragma comment(lib, "winmm.lib")	// 指定MCI库，mciSendString函数的定义在winmm.lib中
#define PLAY(path) play(path, NULL)


void play(const char* path)          //播放音乐
{
	char cmd[512] = {0};
	char pathName[512] = {0};
	strcpy(pathName, path);
	GetShortPathName(pathName, pathName, MAX_PATH);
	strcpy(cmd, "open ");
	strcat(cmd, pathName);
	mciSendString(cmd, "", 0, NULL);
	strcpy(cmd, "play ");
	strcat(cmd, pathName);
	mciSendString(cmd, "", 0, NULL);
}



void pause(const char* path)        // 暂停播放
{
	char cmd[512] = {0};
	char pathName[512] = {0};
	strcpy(pathName, path);
	GetShortPathName(pathName, pathName, MAX_PATH);
	strcpy(cmd, "pause ");
	strcat(cmd, pathName);
	mciSendString(cmd, "", 0, NULL);
}


void stop(const char* path)
{
	char cmd[512] = {0};
	char pathName[512] = {0};
	strcpy(pathName, path);
	GetShortPathName(pathName, pathName, MAX_PATH);
	strcpy(cmd, "stop ");
	strcat(cmd, pathName);
	mciSendString(cmd, "", 0, NULL);
	strcpy(cmd, "close ");
	strcat(cmd, pathName);
	mciSendString(cmd, "", 0, NULL);
}
