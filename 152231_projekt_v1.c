#include <stdio.h>

void vFunction(FILE **listCK, FILE **checkin1)
{
    int type;
    scanf("%d", &type);

    switch (type)
    {
    case 1: 
    {
        if (*listCK == NULL)
        {
            *listCK = fopen("zoznamCK.txt", "r");
        } 

        if (*checkin1 == NULL) 
        {
            *checkin1 = fopen("checkin1.txt", "r");
        }

        if (*listCK == NULL || *checkin1 == NULL)
        {
            printf("V1: Neotvorene txt subory.\n");
            break;
        }
        rewind(*listCK);
        rewind(*checkin1);

        char flight[7];
        char name[16];
        char surName[26];
        int day, month, year;
        char seat[4];
        int luggageCount;

        while (fscanf(*listCK, " # %6s %15s %25s %2d%2d%4d %3s %d", flight, name, surName, &day, &month, &year, seat, &luggageCount) == 8)
        {
            printf("Oznacenie letu: %s\n", flight);
            printf("Meno a Priezvisko [vek]: %s %s [%d]\n", name, surName, 2026 - year);
            printf("Oznacenie sedadla: %s\n\n", seat);
        }
        break;
    }
    case 2: 
    {
        break;
    }
    case 3:
    {
        break;
    }
    default:
        printf("V: Nespravna volba vypisu.\n");
        break;
    }
}

void hFunction(FILE **listCK)
{
    if (*listCK == NULL)
    {
        printf("H: Neotvoreny subor.\n");
        return;
    }

    rewind(*listCK);

    int numbers[10] = {0};
    int upperC[26] = {0};
    int lowerC[26] = {0};
    int c;

    while ((c = fgetc(*listCK)) != EOF)
    {
        if (c >= '0' && c <= '9')
        {
            numbers[c - '0']++;
        }
        else if (c >= 'A' && c <= 'Z')
        {
            upperC[c - 'A']++;
        }
        else if (c >= 'a' && c <= 'z')
        {
            lowerC[c - 'a']++;
        }
    }

    while (1)
    {
        int max = -1;

        for (int i = 0; i < 26; i++)
        {
            if (upperC[i] > 0 && (max == -1 || upperC[i] > upperC[max]))
            {
                max = i;
            }
        }

        if (max == -1)
        {
            break;
        }
        
        printf("%c : %d\n", (max + 'A'), upperC[max]);
        upperC[max] = 0;
    }
    
    
    for (int i = 0; i < 26; i++)
    {
        if (lowerC[i] != 0)
        {
            printf("%c : %d\n", (i + 'a'), lowerC[i]);
        }
    }

    while (1)
    {
        int max = -1;

        for (int i = 0; i < 10; i++)
        {
            if (numbers[i] > 0 && (max == -1 || numbers[i] > numbers[max]))
            {
                max = i;
            }
        }

        if (max == -1)
        {
            break;
        }
        
        printf("%c : %d\n", (max + '0'), numbers[max]);
        numbers[max] = 0;
    }
}

void nFuntion ()
{
    
}

int main()
{
    FILE *listCK = NULL;
    FILE *checkin1 = NULL;
    
    char command; 

    while (scanf(" %c", &command) == 1)
    {
        switch (command)
        {
        case 'v':
            vFunction(&listCK, &checkin1);
            break;
        case 'h':
            hFunction(&listCK);
            break; 
        default:
            break;
        }
    }

    fclose(listCK);
    fclose(checkin1);
    
    return 0;
}