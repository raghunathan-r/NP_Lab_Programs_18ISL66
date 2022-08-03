#include <stdio.h>
#include <string.h>

char frames[1000];

int main(){

    int total_frames;
    printf("total frames ? : "); scanf("%d", &total_frames);

    char buffer[255];
    for(int i = 0; i < total_frames; i++){

        printf("enter frame : "); scanf("%s", buffer);
        int buffer_len = strlen(buffer);

        char length[10];
        sprintf(length, "%d", buffer_len);
        strcat(frames, length);
        strcat(frames, buffer);

    }

    printf("\nthe byte stuffed frame to be sent : %s\n", frames);

    char recived_frame[1000]; strcpy(recived_frame, frames);
    printf("\nthe recived frame is : %s\n", frames);

    for(int i = 0; i < strlen(recived_frame); i++){

        int frame_length = recived_frame[i] - '0';

        for(int j = i + 1; j <= (i + frame_length); j++){
            printf("%c", recived_frame[j]);
        }

        printf("\n");
        i = i + frame_length;
    }


    return 0;


}
