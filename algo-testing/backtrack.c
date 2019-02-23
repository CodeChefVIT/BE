#include<stdio.h>
#define n 4

typedef struct
{
    char *course_list[4];

}courses;

courses slot_list[n] = {{"A1", "A1", "C1", "C1"},
                        {"A1", "B1", "C1", "D1"},
                        {"A1", "B1", "C1", "D1"},
                        {"A1", "B1", "C1", "D1"}
};

courses occupied_slot_list[n] = {{"n", "n", "n", "n"},
                                 {"n", "n", "n", "n"},
                                 {"n", "n", "n", "n"},
                                 {"n", "n", "n", "n"}
};

typedef struct
{
    char *s[12];
}timetable;

timetable base_tt[5] = {{"A1", "F1", "D1", "TB1", "TG1", "L6", "A2", "F2", "D2", "TB2", "TG2", "V3"},
                        {"B1", "G1", "E1", "TC1", "TAA1", "L12", "B2", "G2", "E2", "TC2", "TAA2", "V4"},
                        {"C1", "A1", "F1", "", "", "", "C2", "A2", "F2", "TD2", "TBB2", "L48"},
                        {"D1", "B1", "G1", "TE1", "TCC1", "", "D2", "B2", "G2", "TE2", "TCC2", "V6"},
                        {"E1", "C1", "TA1", "TF1", "TD1", "", "E2", "C2", "TA2", "TF2", "TDD2", "V7"}
};

timetable occupied_tt[5] = {{"n", "n", "n", "n", "n", "n", "n", "n", "n", "n", "n", "n"},
                            {"n", "n", "n", "n", "n", "n", "n", "n", "n", "n", "n", "n"},
                            {"n", "n", "n", "n", "n", "n", "n", "n", "n", "n", "n", "n"},
                            {"n", "n", "n", "n", "n", "n", "n", "n", "n", "n", "n", "n"},
                            {"n", "n", "n", "n", "n", "n", "n", "n", "n", "n", "n", "n"}
};

typedef struct
{
    int r;
    int c;
}INDEX;
INDEX index_list[4];

//BACKTRACKING ALGORITHM FOR SELECTING THE HIGHEST PRIORITY FACULTY
//PRINTING THE SOLUTION
void printsolution(int n_t)
{
    int i,j;
    printf("\n YOUR TIMETABLE - \n");
    for(i=0; i<n_t; i++)
    {
        for(j=0;j<12;j++)
        {
        	if(j==6)
        		printf("LUNCH!\t");
            if(occupied_tt[i].s[j] == "y")
            	printf("%s\t", base_tt[i].s[j]);
            else
            	printf("\t");
        }
        printf("\n");
    }

    printf("\n TEACHERS SELECTED - \n");
    for(i=0; i<n; i++)
    {
        for(j=0;j<4;j++)
        {
            printf("%s",occupied_slot_list[i].course_list[j]);
            printf("\t");
        }
        printf("\n");
    }
};

//FUNCTION TO CHECK THE CLASHING OF SLOTS
int sc = 0;
int issafe(int row, int col, int n_t)
{
    int i,j;
    for(i=0; i<n_t; i++)
    {
        for(j=0;j<12;j++)
        {
            if(slot_list[row].course_list[col] == base_tt[i].s[j])
            {
                index_list[sc].r = i;
                index_list[sc].c = j;
                //printf("\nr = %d, c = %d, value = %s\n", index_list[sc].r, index_list[sc].c, occupied_tt[i].s[j]);
                if(occupied_tt[i].s[j] == "y")
                    return 0;
                sc+=1;
            }
        }
    }
    return 1;
};

//MAIN BACKTRACKING FUNCTION
int solvebacktrackii(int col, int n_t)
{
    int i, z, xyz, zyx;
    if(col >= n)
        return 1;
    for(i=0; i<4; i++)
    {
        if(issafe(i, col, n_t))
        {
            for(z=0;z<sc;z++)
            {
                xyz = index_list[z].r;
                zyx = index_list[z].c;
                occupied_tt[xyz].s[zyx] = "y";  //set all similar slots to y
            }
            occupied_slot_list[i].course_list[col] = "y";
            if(solvebacktrackii(col+1, n_t))
                return 1;
            for(z=0;z<sc;z++)
            {
                xyz = index_list[z].r;
                zyx = index_list[z].c;
                printf("%d,%d",xyz, zyx);
                occupied_tt[xyz].s[zyx] = "n";  //set all similar slots to n
            }
            occupied_slot_list[i].course_list[col] = "n";
        }
    }
    return 0;
};

//FUNCTION CALL TO MAIN BACKTRACK FUNCTION
int solvebacktrack(int n_t)
{
    if(solvebacktrackii(0, n_t) == 0)
    {
        printf("No timetable can be framed!");
        return 0;
    }
    printsolution(n_t);
    return 1;
};

int main()
{
    int i, j;
    //PRINT (teachers X courses) MATRIX
    printf("TEACHERS x COURSES MATRIX - \n");
    for(i=0; i<n; i++)
    {
        for(j=0;j<4;j++)
        {
            printf("%s",slot_list[i].course_list[j]);
            printf("\t");
        }
        printf("\n");
    }
    printf("\n");

    //PRINT BASE TIMETABLE
    int n_t = 5;
    printf("GENERAL TIMETABLE - \n");
    for(i=0; i<n_t; i++)
    {
        for(j=0;j<12;j++)
        {
        	if(j==6)
        		printf("LUNCH!\t");
            printf("%s",base_tt[i].s[j]);
            printf("\t");
        }
        printf("\n");
    }

    //FUNCTION CALL TO BACKTRACK
    solvebacktrack(n_t);
    return 0;
}