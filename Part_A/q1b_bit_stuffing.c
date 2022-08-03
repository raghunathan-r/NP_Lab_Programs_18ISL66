// Q1B. Design a C program to implement Bit stuffing concept in data link layer.

/*
    Theory : 
    https://www.geeksforgeeks.org/bit-stuffing-in-computer-network/
    - this is in the data link layer

    - what we try to do in this is if the beginning and ending sequence is there within the data, to avoid any framing error we stuff a bit

    HDLC Format

    beginning_sequence(8 bit) header(16 bit) body cry(16 bit) ending sequence(8 bit)

    beginning_sequence = ending_sequence = 01111110

    011111110 1010101010'1011111110'10101010 011111110

    so message is =  1 0 1 0 1 0 1 0 1 0 1 0 1 1

    so if we get 5 consecutive 1 s a 0 is going to be stuffed so there is no 6 consecutive 1 s


*/

#include <stdio.h>
#include <string.h>

void sender(void);
void receiver(int*, int);

// the sender will do the bit stuffing of 0 is there are 5 consecutive ones found in the data
void sender(){

    int message_length;
    printf("how many bits in message ? : "); scanf("%d", &message_length);

    int message[50];
    printf("enter message bit by bit [eg. 1 1 1 0] :-\n"); 
    for(int i = 0; i < message_length; i++) scanf("%d", &message[i]);

    // DEBUGGING
    printf("\n=> the entered message is -> \n");
    for(int i = 0; i < message_length; i++) printf("%d", message[i]);
    printf("\n\n");

    // adding the begging_sequence of 8 bits that is 01111110 to the frame as this is the format supposed to be followed in HDLC
    int frames[50];
    frames[0] = 0; 
    frames[1] = 1; 
    frames[2] = 1; 
    frames[3] = 1; 
    frames[4] = 1; 
    frames[5] = 1; 
    frames[6] = 1; 
    frames[7] = 0; 

    // now adding the message after the beginning sequence and stuffing as needed

    int j = 8;
    // this is a flag variable to say if the starting bit of the frame is 0 or is it 1
    int is_zero = 0;
    // we keep track of the count of continues 1 s so when it reaches 5 we stuff a 0 bit
    int ones_count = 0;
    // we keep track of the number of zeros added so we can find the final length of the stuffed frame
    int zeros_added = 0;

    for(int i = 0; i < message_length; i++){

        if(message[i] == 0){
            frames[j] = message[i];
            j++;
            is_zero = 1;
            ones_count = 0;
        } else if((ones_count == 5) && (is_zero == 1)){
            // then there are 6 consecutive 1 s and we should stuff a 0 [ like if message is 0111111... ]
            frames[j] = 0;
            zeros_added++;
            j++;
            frames[j] = message[i];
            j++;
            ones_count = 0;
        } else{
            // if 1 is there but it is not followed by consecutive 5 1s
            frames[j] = message[i];
            j++;
            ones_count++;
        }

    }

    // now that all the bits are stuffed, we will bedding the end_sequence of 8 bits that is 01111110 to the frame as this is the format supposed to be followed in HDLC

    frames[j++] = 0;
    frames[j++] = 1;
    frames[j++] = 1;
    frames[j++] = 1;
    frames[j++] = 1;
    frames[j++] = 1;
    frames[j++] = 1;
    frames[j++] = 0;

    int frame_length = 8 + message_length + zeros_added + 8;

    // DEBUGGING
    printf("\n=> the length of the stuffed frame is %d\n", frame_length);
    printf("\n=> the stuffed frame is ->\n");
    for(int i = 0; i < frame_length; i++) printf("%d", frames[i]);
    printf("\n");

    // now lets send this frame to the receiver
    receiver(frames, frame_length);
}

// the receiver will have to remove all the stuffed bits
void receiver(int * stuffed_frame, int frame_length){
    
    // the length till which we can find the message will be everything except the end_sequence. so we subtract those 8 bits
    int message_length = frame_length - 8;

    // now we have find if there are 5 consecutive 1 s and we remove the next 0 bit in that case. so we start our iteration from the 8 the bit as that is were the beginning_sequence ends.
    // j will hold the current index of the extracted message
    int j = 0;
    int ones_count = 0;
    int message[100];
    for(int i = 8; i < message_length; i++){
        // if the current bit is 0 it will be a stuffed bit if the count of 1 s before it was 5
        if(stuffed_frame[i] == 0){
            if(ones_count == 5){
                // we have to remove the stuffed bit
                i++;
                message[j] = stuffed_frame[i];
                j++;
                ones_count = 0;
            } else{
                // if there we no consecutive 1 s we just add the 0 to the message
                message[j] = stuffed_frame[i];
                j++;
                ones_count = 0;
            }
        } else{
            // that bit is a 1 so have to add it and also increase the ones count
            message[j] = stuffed_frame[i];
            ones_count++;
            j++;
        }
    }

    // DEBUGGING
    printf("\n=> the received message is ->\n");
    for(int i = 0; i < j; i++) printf("%d", message[i]);
    
    printf("\n\n");
}


int main(){

    sender();

    return 0;
}