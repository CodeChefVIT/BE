#include<stdio.h>  
#include<string.h>  

struct faculty
{
    char faculty[50];
    char slot[4];
    int f_priority;
};
typedef struct faculty Faculty;

struct course
{  
    char c_code[8];
    char c_name[100];
    int c_credit;
    int c_priority;
    int c_fac_no;
    Faculty c_fac_details[20];
};
typedef struct course Course;

typedef struct {
    char *name;
    int weight;
    int value;
} item_t;

item_t items[] = {
    {"software",      4,   3},
    {"internet",      4,   3},
    {"architecture",  3,   2},
    {"dsa",           4,   3},
    {"softskills",    1,   3},
    {"lean",          2,   2},
    {"discrete",      4,   3},
    {"calculus",      4,   3},
    {"projmanag",     4,   1}
};

int *knapsack (item_t *items, int n, int w);

int main()
{
    int i, j, k, n, counter = 0;  

    printf("\n Enter the number of courses that you wish to take:");
    scanf("%d", &n);
    Course c[20];
    Faculty temp;        //FOR TEMP IN FACULTY PRIORITY SORTING FUNCTION

    //FOR TIMETABLE INDEXING
    char tt_c_code[20][8];
    char tt_c_slot[20][4];
    int tt_c_credit[20];            //WEIGHT LIST
    int tt_c_priority[20];          //VALUE LIST

    //Faculty f1[20] = {["Graceline", "A1", 2], ["Hema", "A1", 3], ["Malini", "A1", 1]};
    //Course c[20]=[{"CSE3001", "SOFTWARE", 4, 1, 4, f1},{"CSE3002", "IWP", 4, 2, 4, f1}];

//###########################################################################################################################

    //INPUT COURSE DETAILS                                                                                       //O(n^2)
    for(i=0;i<n;i++)                                                                                               
    {
        printf("\nEnter Course Code:");
        scanf("%s", &c[i].c_code);
        //tt_c_code[i] = c[i].c_code;
        printf("\nEnter Course Name:");
        scanf("%s", &c[i].c_name);
        printf("\nEnter Course Credits:");
        scanf("%d", &c[i].c_credit);
        tt_c_credit[i] = c[i].c_credit;
        printf("\nEnter Course Priority:");
        scanf("%d", &c[i].c_priority);
        tt_c_priority[20] = c[i].c_priority;
        printf("\nInput the number of faculty and slots:");
        scanf("%d", &c[i].c_fac_no);
        for(j=0; j<c[i].c_fac_no; j++)
        {
            printf("\nEnter Faculty Name:");
            scanf("%s", &c[i].c_fac_details[j].faculty);
            printf("\nEnter Slot:");
            scanf("%s", &c[i].c_fac_details[j].slot);
            //if(counter == 0)
                //tt_c_slot[i] = c[i].c_fac_details[j].slot;
            printf("\nEnter Priority:");
            scanf("%d", &c[i].c_fac_details[j].f_priority);
        }
    }

//###########################################################################################################################

    //SORTING FACULTY PRIORITY
    for(i=0;i<n;i++)                                                                                           //O(n*(m^2))
    {
        for(j=0; j<c[i].c_fac_no; j++)                                                                         
        {
            for(k=j+1; k<c[i].c_fac_no; k++)
            {
                if(c[i].c_fac_details[j].f_priority < c[i].c_fac_details[k].f_priority)
                {
                    temp = c[i].c_fac_details[j];
                    c[i].c_fac_details[j] = c[i].c_fac_details[k];
                    c[i].c_fac_details[k] = temp;
                }
            }
        }
    }

//###########################################################################################################################

    //PRINTING COURSE c_fac_deta                                                                                   //O(n^2)
    printf("\nCourse Information List after sorting by Teacher Priority:");  
    for(i=0;i<n;i++)
    {
        printf("\nCourse Code:\t%s \nCourse Name:\t%s \nCourse Credits:\t%d \nCourse Priority:\t%d\n",c[i].c_code, c[i].c_name, c[i].c_credit, c[i].c_priority);
        for(j=0; j<c[i].c_fac_no; j++)
        {
            printf("\nFaculty Name: %s", c[i].c_fac_details[j].faculty);
            printf("\nSlot: %s", c[i].c_fac_details[j].slot);
            printf("\nPriority: %d", c[i].c_fac_details[j].f_priority);
        }
        printf("\n");
    }

//###########################################################################################################################

    //Knapsack of course priority and credits                                                                        //O(n)
    int tw = 0, tv = 0, *s;
    int W = 27;
    n = sizeof (items) / sizeof (item_t);
    s = knapsack(items, n, W);
    for (i = 0; i < n; i++) {
        if (s[i]) 
        {
            printf("%-22s %5d %5d\n", items[i].name, items[i].weight, items[i].value);
            tw += items[i].weight;
            tv += items[i].value;
        }
        printf("\n");
    }
    printf("%-22s %5d %5d\n\n", "totals:", tw, tv);

//###########################################################################################################################

    //Sorting Courses according to priority and print
    item_t tem;
    for(i=0; i<n; i++)                                                                                             //O(n^2)
    {
        for(j=0; j<n; j++)
        {
            if(items[i].value > items[j].value)
            {
                tem = items[i];
                items[i] = items[j];
                items[j] = tem;
            }
        }
    }
    for (i = 0; i < n; i++) 
    {
        if (s[i]) 
            printf("%-22s %5d %5d\n", items[i].name, items[i].weight, items[i].value);
        printf("\n");
    }
    printf("%-22s %5d %5d\n\n", "totals:", tw, tv);
    return 0;
}

//##########################################################################################################################

int *knapsack (item_t *items, int n, int w)                                                                       //O(n^2)
{
    int i, j, a, b, *mm, **m, *s;
    mm = calloc((n + 1) * (w + 1), sizeof (int));
    m = malloc((n + 1) * sizeof (int *));
    m[0] = mm;
    for (i = 1; i <= n; i++) {
        m[i] = &mm[i * (w + 1)];
        for (j = 0; j <= w; j++) {
            if (items[i - 1].weight > j) {
                m[i][j] = m[i - 1][j];
            }
            else {
                a = m[i - 1][j];
                b = m[i - 1][j - items[i - 1].weight] + items[i - 1].value;
                m[i][j] = a > b ? a : b;
            }
        }
    }
    s = calloc(n, sizeof (int));
    for (i = n, j = w; i > 0; i--) {
        if (m[i][j] > m[i - 1][j]) {
            s[i - 1] = 1;
            j -= items[i - 1].weight;
        }
    }
    free(mm);
    free(m);
    return s;
}



