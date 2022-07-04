// Q9. Design a C program for congestion control using leaky bucket algorithm.

/*
    THEORY

    https://www.geeksforgeeks.org/leaky-bucket-algorithm/



*/ 

#include <stdio.h>
#include <stdlib.h>

#define MIN(x, y) (x < y)? x : y

int main(){

    int capacity;
    printf("bucket capacity [eg. 11] ? : "); scanf("%d", &capacity);

    int output_rate;
    printf("output rate [eg. 2] ? : "); scanf("%d", &output_rate);

    // taking the data flow information for every second
    int i = 0, input[10], choice;
    do{

        printf("\nno. of packets in second %d ? : ", i + 1); scanf("%d", &input[i]);

        if(input[i] > capacity){
            printf("bucket overflow !\npacket overflow !"); exit(0);
        }
        i++;
        printf("\ncontinue [y-1 | n-0] ? : "); scanf("%d", &choice);
    }while(choice == 1);

    // calculating the flow for every time interval
    int total_time = i, remaining_data = 0, dropped_data = 0;
    printf("\nsecond\treceived\tspend\tdropped\tremaining\n");
    for(int i = 0; remaining_data != 0 || i < total_time; i++){

        printf("%d\t", i + 1);
        printf("%d\t", input[i]);
        printf("%d\t", MIN(input[i] - output_rate, output_rate));

        int data;
        if((data = input[i] + remaining_data - output_rate) > 0){
            if(data > capacity){
                remaining_data = capacity;
                dropped_data = data - capacity;
            } else{
                remaining_data = data;
                dropped_data = 0;
            }
        } else{
            dropped_data = 0;
            remaining_data = 0;
        }

        printf("%d\t%d\n", dropped_data, remaining_data);
    }

    return 0;
}