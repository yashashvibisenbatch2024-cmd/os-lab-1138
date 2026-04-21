#include <stdio.h>

int main()
{
    int a[50], f[10];
    int n, frame_size;
    int i, j, k;
    int page_faults = 0;
    int pos = 0;
    int found;

    printf("Enter number of pages: ");
    scanf("%d", &n);

    printf("Enter page reference string:\n");
    for(i = 0; i < n; i++)
    {
        scanf("%d", &a[i]);
    }

    printf("Enter frame size: ");
    scanf("%d", &frame_size);

    for(i = 0; i < frame_size; i++)
    {
        f[i] = -1;
    }

    printf("\nPage\tFrames\t\tStatus\n");

    for(i = 0; i < n; i++)
    {
        found = 0;

        // check if page already exists
        for(j = 0; j < frame_size; j++)
        {
            if(f[j] == a[i])
            {
                found = 1;
                break;
            }
        }

        if(found == 0)
        {
            f[pos] = a[i];
            pos = (pos + 1) % frame_size;
            page_faults++;
        }

        printf("%d\t", a[i]);

        for(k = 0; k < frame_size; k++)
        {
            if(f[k] != -1)
                printf("%d ", f[k]);
            else
                printf("- ");
        }

        if(found)
            printf("\tHit");
        else
            printf("\tFault");

        printf("\n");
    }

    printf("\nTotal Page Faults = %d\n", page_faults);
    printf("Total Hits = %d\n", n - page_faults);

    return 0;
}
