# include <stdio.h>
# include <cs50.h>

int main (void)
{
    printf("Length of your shower in minutes: ");
    int length = get_int();
    
    if (length > 0)
    {
        int bottle = length*12;
        printf("No. of bottle used is %i\n", bottle);
    }
    else 
    {
        printf ("We can't time travel yet. Please Retry\n");
    }
}