#include <stdio.h>
#include <string.h>
#include <Windows.h>
#include <mmsystem.h>	// mci��ͷ�ļ�
#pragma comment(lib, "winmm.lib")	// ָ��MCI�⣬mciSendString�����Ķ�����winmm.lib��
#define PLAY(path) play(path, NULL)


void play(const char* path)          //��������
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



void pause(const char* path)        // ��ͣ����
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
