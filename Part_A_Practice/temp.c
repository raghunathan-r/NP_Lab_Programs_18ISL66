#include <stdio.h>

#define min(x, y) (x < y) ? x:y

int main(){

    int capacity;
    printf("max capacity ? : "); scanf("%d", &capacity);

    int output_rate;
    printf("output rate ? : "); scanf("%d", &output_rate);

    int input[10] = {0}, i = 0, choice;
    do{
        printf("enter no. of packets recived : ");
        scanf("%d", &input[i++]);

        printf("continute ? [ y-1|n-0] : "); scanf("%d", &choice);
    } while(choice != 0);

    int total_time = i;
    int dropped = 0, remaining = 0;

    printf("\ntime\trecived\tsent\tdropped\tremaining\n");
    for(int i = 0; i < total_time || remaining != 0; i++){
        printf("\n%d\t%d\t", i + 1, input[i]);
        printf("%d\t", min((input[i] + remaining), output_rate));

        int data;
        if((data = input[i] + remaining - output_rate) > 0){
            if(data > capacity){
                remaining = capacity;
                dropped = data - capacity;
            } else{
                remaining = data;
                dropped = 0;
            }
        } else{
            dropped = 0;
            remaining = 0;
        }

        printf("%d\t%d\n", dropped, remaining);
    }
}
