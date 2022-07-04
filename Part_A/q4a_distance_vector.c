// Q4A. Design and implement a C program to route the packet in a network using Distance Vector Algorithm.

/*
    THEORY

    https://www.geeksforgeeks.org/distance-vector-routing-dvr-protocol/

    - it is a intra domain routing protocol
    - make the table
    - only share the distance vector with the neighbour

    - first we create a local routing table for each node
    - in the first iteration we will only know the information about the neighboring nodes
    - then we only share the distance vectors with the neighbour
    - next round, we update all the distance vectors
    - in the new routing tables we use the distance vectors from the shared tables only

*/

#include <stdio.h>


// creating a node containing the from node and the distance information. From this we are making an array of structure called routing table
struct node{
    int distance[20];
    int from[20];
} routing_table[10];

int main(){

    int total_nodes; 
    printf("how many nodes ?: "); scanf("%d", &total_nodes);

    int cost_matrix[20][20];
    printf("enter the cost matrix :-\n");
    
    for(int i = 0; i < total_nodes; i++){
        for(int j = 0; j < total_nodes; j++){
            
            scanf("%d", &cost_matrix[i][j]);
            cost_matrix[i][i] = 0;
            routing_table[i].distance[j] = cost_matrix[i][j];
            routing_table[i].from[j] = j;
        }
    }

    // updating all the routing tables with the minimum distance    
    int count;
    do{
        count = 0;

        for(int i = 0; i < total_nodes; i++){
            for(int j = 0; j < total_nodes; j++){
                for(int k = 0; k < total_nodes; k++){

                    if(routing_table[i].distance[j] > routing_table[i].distance[k] + routing_table[k].distance[j]){
                        routing_table[i].distance[j] = routing_table[i].distance[k] + routing_table[k].distance[j];
                        routing_table[i].from[j] = k;
                        count++;
                    }

                }
            }
        }
    } while(count != 0);

    for(int i = 0; i < total_nodes; i++){
        printf("\nstate value for router %d is :\n", i + 1);
        printf("\nnode\tvia\tdist");

        for(int j = 0; j < total_nodes; j++){
            printf("\n%d\t%d\t%d", j + 1, routing_table[i].from[j] + 1, routing_table[i].distance[j]);
        }
    }

    printf("\n");
}

/*

input
5 x 5

0 3 99 2 5
3 0 2 4 99
99 2 0 99 1
2 4 99 0 99
5 99 1 99 0





*/