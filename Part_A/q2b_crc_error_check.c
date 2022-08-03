// Q2A. Design and implement CRC error detection method used in data link layer.

/*

    https://www.youtube.com/watch?v=5Q-Yv6_0Qcw

    - this is used to find single, double and odd number of errors
    - it can detect burst error of length equal to the degree of the polynomial being used

    now why do we use this ?
    - in real life we cant always send pure data as the message, we will have to add some redundant bits.
    hence making the total_bits = no_of_message_bits + no_of_redundant_bits

    Algorithm
    - so the input will bits like 1010101010 is the devedend
    and the polynomial given like x4 + x3 + 1 is the devisor
    - we should divide them and find the CRC bits
    - the number of redundant bits [0 s] that has to be appended to the pure message is equal to the maximum power of the polynomial. [ in the above example it is 4]
    - [ so the example becomes 1010101010 -> 1010101010'0000']
    - now to find the devisor from the given polynomial
    it will be coefficients
    [ in the above example,
        x4 + x3 + 1
        can be written as
        -> 1 x4 + 1 x3 + 0 x2 + 0 x1 + 1 x0

        the devisor is then, 1 1 0 0 1
    ]
    - now we have to perform binary division, in this we use XOR operation [ XOR means - same values = 0, different values = 1]
    - here we dont have to care about the quotient, we only care about the reminder
    - what we get as the last n bits of reminder will now be appended to the message by replacing the redundant bits [ the 0s we added before]
    - That is it ! you now have your message with the redundant bits    


    Now in the reviver end
    - the received data will be deviced by the devisor again. 
    - the reminder will come as 0. this means that there has been no error
    - even if the reminder is not 0 that means some error has occurred.


*/

#include <stdio.h>

// this perform binary division and returns the reminder [ ie. XOR operation]
int XOR(int x, int y){
    if(x == y)
        return 0;
    else
        return 1;
}

int main(){

    // taking the message related information. this will be the dividend after adding the redundant bits
    int message_length = 0;
    printf("message length ? : "); scanf("%d", &message_length);

    int message[10];
    printf("enter message [for eg. 1 0 1 0 1 0 1 0 1 0]: ");
    for(int i = 0; i < message_length; i++) scanf("%d", &message[i]);

    // taking the devisor data, we will take it directly in bits so the power will be length - 1
    int devisor_length;
    printf("devisor length ?: "); scanf("%d", &devisor_length);

    int devisor[5];
    printf("divisor [for eg. 1 1 0 0 1] ? : "); 
    for(int i = 0; i < devisor_length; i++) scanf("%d", &devisor[i]);

    // adding the redundant bits [ 0 s ] at the end of the message based on the length of divisor - 1
    int new_message[15];
    int new_message_length = message_length + devisor_length - 1;
    for(int i = 0; i < (message_length + devisor_length - 1); i++){
        if(i < message_length)
            new_message[i] = message[i];
        else
            new_message[i] = 0;
    }

    // DEBUGGING
    printf("\n=> the new message after adding 0s ->\n");
    for(int i = 0; i < (message_length + devisor_length - 1); i++) printf("%d", new_message[i]); printf("\n");


    // what are we doing now I think ..
    // now we find the CRC by dividing the new message with the devisor
    int crc[5];

    for(int i = 0; i <= message_length; i++){

        for(int j = 0; j < devisor_length; j++){
            crc[j] = new_message[i + j];
            if(crc[0] == 1)
                new_message[i + j] = XOR(new_message[i + j], devisor[j]);
            else
                new_message[i + j] = XOR(new_message[i + j], 0);
        }

        // DEBUGGING
        printf("\n=> the CRC after division is ->\n");
        for(int j = 0; j < (devisor_length - 1); j++) printf("%d", crc[j]); printf("\n");
    }

    // creating a new variable and storing the data after the new CRC obtained after division
    // DEBUGGING
    printf("\n=> the data to be sent after adding crc is ->\n");

    int message_with_crc[15];
    for(int i = 0; i < (message_length + devisor_length - 1); i++){
        if(i < message_length)
            message_with_crc[i] = message[i];
        else
            message_with_crc[i] = crc[i - message_length];
        
        printf("%d ", message_with_crc[i]);
    }
    printf("\n\n");


    // RECEIVER SIDE CODE

    int received_message[15];
    printf("received message ?: "); for(int i = 0; i < new_message_length; i++) scanf("%d", &received_message[i]);

    // performing the division operation with the received message and the devisor. then we see if the reminder is 0


    int reminder[5];
    for(int i = 0; i < new_message_length; i++){

        for(int j = 0; j < devisor_length; j++){
            reminder[j] = received_message[i + j];

            if(reminder[0] == 1)
                received_message[i + j] = XOR(received_message[i + j], devisor[i]);
            else
                reminder[i + j] = XOR(received_message[i + j], 0);
        }

        printf("\n=> the reminder after division is ->\n");
        for(int i = 0; i < (devisor_length - 1); i++) printf("%d", reminder[i]); printf("\n");
    }

    // checking if reminder is 0
    int data_is_correct = 1;
    for(int i = 0; i < (devisor_length - 1); i++){
        printf("\nreminder[i] != 0\n -> i = %d -> %d\n", i, reminder[i]);
        if(reminder[i] != 0){
            data_is_correct = 0;
            break;
        }
    }

    if(data_is_correct == 1){
        printf("the received message is error free\n");
    }else{
        printf("the message has errors\n");
    }

    return 0;
}