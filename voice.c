//
// Created by Wang wei on 2017/6/27.
//

#include <stdio.h>

void increase() {
//    keybd_event (0xAF, 0, 0, 0);
//    keybd_event (0xAF, 0, KEYEVENTF_KEYUP, 0)
}

void decrease() {
//    keybd_event (0xAE, 0, 0, 0);
//    keybd_event (0xAE, 0, KEYEVENTF_KEYUP, 0)
}

void volume(){
    int input = 0;

    system("cls");
    printf("1. ��������\n");
    printf("2. ��С����\n");
    printf("0. ����\n");
    input = getch();
    input -= 48;
    //scanf("%d", &input);
    while (input != 0){
        switch (input) {
            case 1:
                increase();
                break;
            case 2:
                decrease();
                break;
            default:
                break;
        }
        system("cls");
        printf("1. ��������\n");
        printf("2. ��С����\n");
        printf("0. ����\n");
        input = getch();
        input -= 48;
        //scanf("%d", &input);
    }
}