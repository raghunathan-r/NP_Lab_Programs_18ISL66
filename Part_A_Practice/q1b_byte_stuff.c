#include <stdio.h>
#include <string.h>

int frames[255];

void sender();
void reciver(int *recived_frame, int frame_length);

void sender(){

    int buffer_length;
    printf("message length ? : "); scanf("%d", &buffer_length);

    int buffer[255];
    printf("enter frame : ");
    for(int i = 0; i < buffer_length; i++) scanf("%d", &buffer[i]);

    // adding the flags 01111110
    frames[0] = 0;
    frames[1] = 1;
    frames[2] = 1;
    frames[3] = 1;
    frames[4] = 1;
    frames[5] = 1;
    frames[6] = 1;
    frames[7] = 0;

    // adding the message with bit stuffing
    int is_zero = 0, ones_count = 0, zeros_added = 0; int j = 8;
    for(int i = 0; i < buffer_length; i++){
        if(buffer[i] == 0){
            is_zero = 1;
            frames[j++] = buffer[i];
            ones_count = 0;
        } else if((is_zero == 1) && (ones_count == 5)){
            frames[j] = 0;
            j++;
            frames[j] = buffer[i];
            j++;
            zeros_added++;
            ones_count = 0;
        } else {
            frames[j++] = buffer[i];
            ones_count++;
        }
    }

    // adding the end flag
    frames[j++] = 0;
    frames[j++] = 1;
    frames[j++] = 1;
    frames[j++] = 1;
    frames[j++] = 1;
    frames[j++] = 1;
    frames[j++] = 1;
    frames[j++] = 0;

    int stuffed_frame_length = 8 + buffer_length + zeros_added + 8;

    printf("\nstuffed frame sent : ");
    for(int i = 0; i < stuffed_frame_length; i++) printf("%d", frames[i]); printf("\n");

    reciver(frames, stuffed_frame_length);
}

void reciver(int *recived_frame, int frame_length){

    printf("\nrecived stuffed frame : ");
    for(int i = 0; i < frame_length; i++) printf("%d", recived_frame[i]);

    printf("\nthe extratcted frame : ");

    int extracted_frame[100];

    int is_zero = 0, ones_count = 0, j = 0;
    for(int i = 8; i < frame_length - 8; i++){

        if(recived_frame[i] == 0){
            if(ones_count == 5){
                extracted_frame[j++] = recived_frame[++i];
                ones_count = 0;
            } else{
                extracted_frame[j++] = recived_frame[i];
                ones_count = 0;
            }
        } else{
            extracted_frame[j++] = recived_frame[i];
            ones_count++;
        }
    }

    for(int i = 0; i < j; i++) printf("%d ", extracted_frame[i]); printf("\n");
};

int main(){

    sender();

    return 0;
}
