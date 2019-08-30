#include <stdio.h>
#include <stdlib.h>

int main()
{

    int n;
    printf("Enter number of pairs: ");
    scanf("%d", &n);

    int enter_time[n], exit_time[n];

    printf("Enter pairs: ");

    for (int i = 0; i < n; i++)
    {
        scanf("%d %d", &enter_time[i], &exit_time[i]);
    }
    int count=0;
    for (int i = 0; i < n - 1; i++)
    {

        for (int j = i + 1; j < n; j++)
        {
            if((enter_time[j]>=enter_time[i] && enter_time[j]<=exit_time[i]) || (enter_time[j]<=enter_time[i] && exit_time[j]>=enter_time[i]))
                count++;
        }
    }

    return 0;
}
