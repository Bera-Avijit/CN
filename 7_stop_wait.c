#include <stdio.h>
#include <stdlib.h>

int main()
{
    int i = 1, nf, ack, wt;

    nf = rand() % 5 + 5;

    printf("Number of Frames: %d\n", nf);

    while(i <= nf)
    {
        printf("\nSending Frame %d", i);

        ack = rand() % 2;

        if(ack == 1)
        {
            printf("\nACK received for Frame %d\n", i);

            i++;
        }
        else
        {
            printf("\nTimeout...\n");

            for(wt = 1; wt <= 3; wt++)
            {
                printf("Waiting %d sec\n", wt);
            }

            printf("Resending Frame %d\n", i);
        }
    }

    printf("\nEnd of Stop and Wait Protocol\n");

    return 0;
}
