#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void vFunction (FILE **listCK, FILE **checkin1)
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

void hFunction (FILE **listCK)
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

char *copyString (char *string)
{   
    char *copy = malloc(strlen(string)+1);
    if (copy != NULL)
    {
        //do premennej copy sa narve obsah premennej string 
        strcpy(copy, string);
    } 
    return copy;
}


void freeStringArray (char ***array, int size)
{
    if (*array == NULL)
    {
        return;
    }
    for (int i = 0; i < size; i++)
    {
        free((*array)[i]);
    }
    free(*array);
    *array = NULL;
}

void freeDoubleArray (double ***array, int size)
{
    if (*array == NULL)
    {
        return;
    }
    for (int i = 0; i < size; i++)
    {
        free((*array)[i]);
    }
    free(*array);
    *array = NULL;
}

void freeIntArray (int **array)
{
    free(*array);
    *array = NULL;
}

void freeListCK (int *lcCount, char ***lcFlights, char ***lcNames, char ***lcSurnames, int **lcBirthdates, char ***lcSeats, int **lcLuggageCounts)
{
    freeStringArray(lcFlights, *lcCount);
    freeStringArray(lcNames, *lcCount);
    freeStringArray(lcSurnames, *lcCount);
    freeIntArray(lcBirthdates);
    freeStringArray(lcSeats, *lcCount);
    freeIntArray(lcLuggageCounts);
    *lcCount = 0;
}

void freeCheckin (int *ciCount, char ***ciFlights, char ***ciSeats, int **ciLuggageCounts, double ***ciLuggageWeights)
{
    freeStringArray(ciFlights, *ciCount);        
    freeStringArray(ciSeats, *ciCount);          
    freeIntArray(ciLuggageCounts);
    freeDoubleArray(ciLuggageWeights, *ciCount);  
    *ciCount = 0;                                 
}

void nFunction (FILE *listCK, FILE *checkin1, 
    int *lcCount, char ***lcFlights, char ***lcNames, char ***lcSurnames, 
    int **lcBirthdates, char ***lcSeats, int **lcLuggageCounts,

    int *ciCount, char ***ciFlights, char ***ciSeats, 
    int **ciLuggageCounts, double ***ciLuggageWeights
)
{
    if (listCK == NULL || checkin1 == NULL)
    {   
        printf("N: Neotvoreny subor.\n");
        return;
    }

    char lcTmpFlight[7];
    char lcTmpName[16];
    char lcTmpSurname[26];
    int lcTmpBirthdate;
    char lcTmpSeat[4];
    int lcTmpLuggageCount;

    freeListCK(lcCount, lcFlights, lcNames, lcSurnames, lcBirthdates, lcSeats, lcLuggageCounts);

    rewind(listCK);
    
    int lcRecords = 0;
    while (fscanf(listCK, " # %6s %15s %25s %8d %3s %d", lcTmpFlight, lcTmpName, lcTmpSurname, &lcTmpBirthdate, lcTmpSeat, &lcTmpLuggageCount) == 6)
    {
        lcRecords++;
    }

    *lcFlights = calloc(lcRecords, sizeof(char *));
    *lcNames = calloc(lcRecords, sizeof(char *));
    *lcSurnames = calloc(lcRecords, sizeof(char *));
    *lcBirthdates = malloc(lcRecords * sizeof(int));
    *lcSeats = calloc(lcRecords, sizeof(char *));
    *lcLuggageCounts = malloc(lcRecords * sizeof(int));
    *lcCount = lcRecords;

    if (*lcFlights == NULL || *lcNames == NULL || *lcSurnames == NULL || *lcBirthdates == NULL || *lcSeats == NULL || *lcLuggageCounts == NULL)
    {
        freeListCK(lcCount, lcFlights, lcNames, lcSurnames, lcBirthdates, lcSeats, lcLuggageCounts);
        return;
    }

    rewind(listCK);

    int i = 0;
    while (i < lcRecords && fscanf(listCK, " # %6s %15s %25s %8d %3s %d", lcTmpFlight, lcTmpName, lcTmpSurname, &lcTmpBirthdate, lcTmpSeat, &lcTmpLuggageCount) == 6)
    {
        // pri typu char musim robit copy lebo potrebujem adresu a keby tam dam iba tmpFlight tak by sa vsetky flights rovnali rovnakej adrese a to tmpFlight
        (*lcFlights)[i] = copyString(lcTmpFlight);
        (*lcNames)[i] = copyString(lcTmpName);
        (*lcSurnames)[i] = copyString(lcTmpSurname);
        (*lcBirthdates)[i] = lcTmpBirthdate;
        (*lcSeats)[i] = copyString(lcTmpSeat);
        (*lcLuggageCounts)[i] = lcTmpLuggageCount;
        i++;
    }

    char line[256];
    char ciTmpFlight[7];
    char ciTmpSeat[4];
    int ciTmpLuggageCount;
    int pos;
    
    freeCheckin(ciCount, ciFlights, ciSeats, ciLuggageCounts, ciLuggageWeights);
    
    int ciRecords = 0;
    rewind(checkin1);
    while (fgets(line, sizeof(line),checkin1) != NULL)
    {
        if (sscanf(line, " %6[^#]#%3[^#]#%d%n", ciTmpFlight, ciTmpSeat, &ciTmpLuggageCount, &pos) == 3)
        {
            ciRecords++;
        }
    }
    
    if (ciRecords == 0)
    {
        return;
    }

    *ciFlights = calloc(ciRecords, sizeof(char *));
    *ciSeats = calloc(ciRecords, sizeof(char *));
    *ciLuggageCounts = malloc(ciRecords * sizeof(int));
    *ciLuggageWeights = calloc(ciRecords, sizeof(double *));
    *ciCount = ciRecords;

    if (*ciFlights == NULL || *ciSeats == NULL || *ciLuggageCounts == NULL || *ciLuggageWeights == NULL)
    {
        freeCheckin(ciCount, ciFlights, ciSeats, ciLuggageCounts, ciLuggageWeights);
        return;
    }

    rewind(checkin1);
    i = 0;
    while (i < ciRecords && fgets(line, sizeof(line), checkin1) != NULL)
    {
        if (sscanf(line, " %6[^#]#%3[^#]#%d%n", ciTmpFlight, ciTmpSeat, &ciTmpLuggageCount, &pos) != 3)
        {
            continue;
        }

        (*ciFlights)[i] = copyString(ciTmpFlight);
        (*ciSeats)[i] = copyString(ciTmpSeat);
        (*ciLuggageCounts)[i] = ciTmpLuggageCount;

        if (ciTmpLuggageCount > 0)
        {
            (*ciLuggageWeights)[i] = malloc(ciTmpLuggageCount * sizeof(double));
            for (int j = 0; j < ciTmpLuggageCount; j++)
            {
                int n;
                if (sscanf(line + pos, "#%lf%n", &(*ciLuggageWeights)[i][j], &n) != 1)
                {
                    break;
                }
                pos += n;
            }
        }
        i++;
    }
}

int main()
{
    FILE *listCK = NULL;
    FILE *checkin1 = NULL;

    int sizeListCK = 0;
    char **flights = NULL;
    char **names = NULL;
    char **surNames = NULL;
    int *bdays = NULL;
    char **seats = NULL;
    int *luggagesCounts = NULL;

    int sizeCheckin = 0;
    char **ckFlights = NULL;
    char **ckSeats = NULL;
    int *ckLuggageCounts = NULL;
    double **ckWeights = NULL;
    
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
        case 'n':
            nFunction(&listCK, &checkin1, &sizeListCK, &flights, &names, &surNames, 
                &bdays, &seats, &luggagesCounts, &sizeCheckin, &ckFlights, &ckSeats, &ckLuggageCounts, &ckWeights);
            break;
        case 'q':
            
            break;
        default:
            break;
        }
    }

    fclose(listCK);
    fclose(checkin1);
    
    return 0;
}