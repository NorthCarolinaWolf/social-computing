#include "stdio.h"
#include "malloc.h"
#include "string.h"


#define SIZE_OF_FILE 1000
#define AUTOMOBILE 1
#define ELECTRICAL 2
#define PLUMBING   3
#define NO_MATCH   0
#define LINE_SIZE 10000

#define DEBUG_ON        0
#define WINDOWS         0
#define UNIX            1

#if WINDOWS
#define AUTO_INDEX              3
#define PLUMBING_INDEX          1000
#define ELECTRICAL_INDEX        1042
#else /* UNIX */
#define AUTO_INDEX              2
#define PLUMBING_INDEX          2002
#define ELECTRICAL_INDEX        2084
#endif

#if WINDOWS
#define AUTOMOBILE_FILE ".\\lib\\Project-Data\\Dictionaries\\automobile.txt"
#define ELECTRICAL_FILE ".\\lib\\Project-Data\\Dictionaries\\electrician.txt"
#define PLUMBING_FILE   ".\\lib\\Project-Data\\Dictionaries\\plumbing.txt"
#define SOCbusinessDataCSV ".\\lib\\Project-Data\\SOC-businessDataCSV.csv"
#else /* UNIX */
#define AUTOMOBILE_FILE "./lib/Project-Data/Dictionaries/automobile.txt"
#define ELECTRICAL_FILE "./lib/Project-Data/Dictionaries/electrician.txt"
#define PLUMBING_FILE   "./lib/Project-Data/Dictionaries/plumbing.txt"
#define SOCbusinessDataCSV "./lib/Project-Data/SOC-BusinessDataCSV.csv"
#endif

int main(int argc, char *argv[])
{
        //read string
        char *string_to_tokenize;
        int i;
        char *tkn, *pch, *Linetkn;
        int no_of_tokens = 0, no_of_linetokens =0;
        char *token[100], *Linetoken[100];
        FILE *fp, *fp1;
        char buff[SIZE_OF_FILE];
        int found_a_match =0;
        char *line;

        found_a_match = NO_MATCH;

        line = (char *) malloc(LINE_SIZE);
        sprintf(line, "None\n");
        string_to_tokenize = (char *) malloc(1000);

        if (argc < 2)
                return -1;
#if WINDOWS
        sprintf(string_to_tokenize, "%S", argv[1]);
#else
        sprintf(string_to_tokenize, "%s", argv[1]);
#endif


#if DEBUG_ON
        printf("Step 1 String_to_tokenize is %s\n", argv[1]);
#endif

        tkn = strtok(string_to_tokenize, " ");
        token[no_of_tokens] = (char *) malloc(1000);

#if DEBUG_ON
        printf("Step 2 tkn is %s\n", tkn);
#endif
        strcpy(token[no_of_tokens], tkn);
        no_of_tokens++;


        while (tkn != NULL)
        {
#if DEBUG_ON
                printf ("%s\n", tkn);
#endif
                tkn = strtok(NULL, " ");
                // skip certain tokens. The skip list needs to be updated
                if (tkn != NULL) {
                                if (!strcmp(tkn, "is") || !strcmp(tkn, "was") || !strcmp (tkn, "very"))
                                                continue;
                }
                if (tkn != NULL)
                {
                        token[no_of_tokens] = (char *) malloc(100);
                        strcpy(token[no_of_tokens], tkn);
                        no_of_tokens++;
                }
        }

#if DEBUG_ON
        for (i =0; i < no_of_tokens; i++)
                printf("%s\n", token[i]);
#endif



        //for each token open the three files and compare

        //open the file automobile.txt and check if the token matches

        fp = fopen(AUTOMOBILE_FILE, "r");
        if (fp == NULL)
                printf("Automobile token files not found\n");
        if (fp != NULL) {
                fread(buff, sizeof(char), SIZE_OF_FILE, fp);

                for (i=0; i < no_of_tokens; i++) {
                        pch = strstr(buff, token[i]);
                        if (pch != NULL) {
                                found_a_match = AUTOMOBILE;
                                break;
                        }
                }
        }
        if(fp)
                fclose(fp);

        if (!found_a_match) {
                fp = fopen(PLUMBING_FILE, "r");
                if (fp != NULL) {
                        fread(buff, sizeof(char), SIZE_OF_FILE, fp);

                        for (i=0; i < no_of_tokens; i++) {
                                pch = strstr(buff, token[i]);
                                if (pch != NULL)  {
                                        found_a_match = PLUMBING;
                                        break;
                                }
                        }
                }
        if(fp)
                fclose(fp);
        }

        if (!found_a_match) {
                fp = fopen(ELECTRICAL_FILE, "r");
                if (fp != NULL) {
                        fread(buff, sizeof(char), SIZE_OF_FILE, fp);

                        for (i=0; i < no_of_tokens; i++) {
                                pch = strstr(buff, token[i]);
                                if (pch != NULL) {
                                        found_a_match = ELECTRICAL;
                                        break;
                                }
                        }
                }
                if(fp)
                        fclose(fp);
        }

        if (!found_a_match) {   //We did not find a match
                printf("%s\n", line);
                return -3;
        }

#if DEBUG_ON
        printf (" Step 3: Match found: %d\n", found_a_match);
#endif

        //We did find a match. Now open the SOC-businessDataCSV and get the name of business and return the same.
        // automobile is 3-2000; plumbing 2001- 2085; electrician 2085-2123
        line = (char *) malloc(LINE_SIZE);
        fp1 = fopen(SOCbusinessDataCSV, "r");
        if (fp1 == NULL) {
                printf("Unable to open the BusinessDataCSV file...exiting\n");
                return -4;

        }

        if (fgets(line, LINE_SIZE, fp1) != NULL) {

                if (found_a_match == AUTOMOBILE) {
                        // get the third line
                        for (i =0; i < AUTO_INDEX; i++) {

                                fgets(line, LINE_SIZE, fp1);
#if DEBUG_ON
                                printf("Step 4: line is %s\n", line);
#endif
                        }

                }

                if (found_a_match == PLUMBING) {
                        // get the 1000th Line for Windows or 2001th Line in case of Linux
                        for (i=0; i < PLUMBING_INDEX; i++)  {
                                fgets(line, LINE_SIZE, fp1);
#if DEBUG_ON
                                printf("Step 4: line is %s\n", line);
#endif
                        }
                }

                if (found_a_match == ELECTRICAL) {
                  //get the 2085th Line.
                        for (i =0; i < ELECTRICAL_INDEX; i++)
                                fgets(line, LINE_SIZE, fp1);
                }


        }

#if DEBUG_ON
         printf(" Step 5 line is %s\n", line);  //line from the xlx csv file
#endif

                //return this line in CompanyName$contact(phone)$content(category) format

        if (!strcmp(line, "None")) {
                        printf("%s\n", line);
                        return 0;
        }



    // tokenize the line in 5 parts
        Linetkn = strtok(line, ",");
        Linetoken[no_of_linetokens] = (char *) malloc(100);
        strcpy(Linetoken[no_of_linetokens], Linetkn);
        no_of_linetokens++;

#if DEBUG_ON
                printf("Step 6: while Linetkn line is %s tkn is %s\n", line, tkn);
#endif
        while (Linetkn != NULL)
        {
                //printf ("%s\n", tkn);  debug
                Linetkn = strtok(NULL, ",");
                // skip certain tokens. The skip list needs to be updated
                if (Linetkn != NULL)
                {
                        Linetoken[no_of_linetokens] = (char *) malloc(100);
                        strcpy(Linetoken[no_of_linetokens], Linetkn);
                        no_of_linetokens++;
                }
        }

        sprintf(line, "%s$%s$%s", Linetoken[1], Linetoken[2], Linetoken[4]);

        printf("%s\n", line);
}