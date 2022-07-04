// Q1A. Design a C program in which sender module should count the no of bytes in the frame and receive module should display each frame received.

#include <stdio.h>
#include <string.h>

// a variable to store all the frames. this is made global cause passing it is corrupting the values
char frames[1024];

void sender(){

    // we take the total number of frames that the user wants to send
    int total_frames;
    printf("how many frames to send ? : "); scanf("%d", &total_frames);

    // taking all the frames and adding to the frames using a buffer
    char buffer[256];
    bzero(buffer, 256);
    for(int i = 0; i < total_frames; i++){
        
        printf("enter frame : "); scanf("%s", buffer);

        // DEBUGGING
        int buffer_length = strlen(buffer);
        printf("\n=> the length of entered frame -> %d\n", buffer_length);
        buffer_length += 1;
        printf("\n=> the length of entered frame including the first length indicating bit -> %d\n", buffer_length);


        /* 
            -> now while framing we will add the length of the given frame from buffer as the first bit
            for eg.
            buffer = 10110 -> length is 5
            then the frame will be 5 its after first bit. so 5 + 1 = 6
            so, the frame becomes
            frame = 6 10110 
        */
        char length[10];
        sprintf(length, "%d", buffer_length);
        strcat(frames, length);
        strcat(frames, buffer);
    }

    // DEBUGGING
    printf("\n=> the entered frames are ->\n");
    for(int i = 0; frames[i] != '\0'; i++) printf("%c", frames[i]);
    printf("\n");

}

void receiver(){
    printf("the received frame is ...");
    for(int i = 0; frames[i] != '\0'; i++) printf("%c", frames[i]); printf("\n");

    int total_length = strlen(frames);
    for(int i = 0; i < total_length; i++){

        // the frame length is stored in the first bit when sent from the sender
        int frame_length = frames[i] - '0';

        // now we will have to iterate through that block of frame and print it. then move i to point to the starting bit of the next block of frame
        for(int j = i + 1; j <= (i + frame_length); j++) printf("%c", frames[j]);
        printf("\n");

        i = i + frame_length;
    }
}

int main(){
    sender();

    receiver();

    return 0;
}