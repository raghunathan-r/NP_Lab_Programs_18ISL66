#include <stdio.h>

struct node{
    int dist[20];
    int from[20];
} routing_table[20];

int main(){

    int total_nodes;
    printf("total nodes ? : "); scanf("%d", &total_nodes);

    printf("enter cost matrix :\n");
    int cost_matrix[20][20];
    for(int i = 0; i < total_nodes; i++){
        for(int j = 0; j < total_nodes; j++){

            cost_matrix[i][i] = 0;
            scanf("%d", &cost_matrix[i][j]);

            routing_table[i].dist[j] = cost_matrix[i][j];
            routing_table[i].from[j] = j;
        }
    }

    // finding the closest distance
    for(int i = 0; i < total_nodes; i++){
        for(int j = 0; j < total_nodes; j++){
            for(int k = 0; k < total_nodes; k++){

                if(routing_table[i].dist[j] > (routing_table[i].dist[k] + routing_table[k].dist[j])){
                    routing_table[i].dist[j] = routing_table[i].dist[k] + routing_table[k].dist[j];
                    routing_table[i].from[j] = k;
                }
            }
        }
    }

    // displaying the table
    for(int i = 0; i < total_nodes; i++){
        printf("\nrouting table for node %d\n", i + 1);
        printf("node\tvia\tdistance\n");
        for(int j = 0; j < total_nodes; j++){
            printf("%d\t%d\t%d\n", j + 1, routing_table[i].from[j], routing_table[i].dist[j]);
        }
        printf("\n");
    }

    return 0;

}
