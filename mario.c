#include <stdio.h>
#include <cs50.h>

int main (void)
{

    //declaring a int variable for the height of the pyramid

    int height;

    //Running a do-while loop to prompt and check to stop the loop for invalid condition

    do
    {
        printf("Please enter your desired height: ");
        height = get_int();
    }
    
    while (height > 23 || height < 0);

    //Check and tell user for invalid input
    if (height > 23 || height < 0)
    {
        printf("Wrong height! Please enter a correct value.\n");
    }


    //otherwise running the program as detailed in problem
    else
    {
        // first iteration. It ensures for n number or # for n number of input.
        //i.e. if the user inputs 8 then there will be 8 # printed at the bottom of line.
        //if j<height provided as condition then atleast 1 " " and n-1 # will be printed.
        // Use tracing to understand further

        for (int j = 0; j <= height -1; j++)
        {
            //this iteration prints n-1 of spaces before the # for left pyramid

            for (int i = height-1 ; i > j; i-- )
            {
                printf (" ");
            }
            //prints n number of row for nth row(by the rule of 1 indexing)

            for (int k = 0 ; k <= j; k++)
            {
                printf("#");
            }
            
            //the double spaces between

            printf("  ");
            

            //the right pyramid

            for (int m = 0 ; m <= j; m++)
            {
                printf("#");
            }
        
            printf("\n");
        }
    }
}
    
        