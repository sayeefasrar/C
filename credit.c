#include <stdio.h>
#include <cs50.h>
#include <math.h>

char credit_card_name(int digits, int n_digit);
int alternate_number_productsum(int nth_digit, int product);
int add_the_rest(int product, int nth_digit);

int main (void)
{
    // prompting for user input
    long long cc;
    do
    {
        printf("Enter Credit Card Number: ");
        cc = get_long_long();
    } while (cc <= 10);
    
    
    //Counting the number of digit in the user input.
    
    int digits;
    digits = floor( log10( cc ) ) + 1;
    //printf ("no. of digit is %i\n", digits);
        
        
    //Starting Luhn's Algorithm
    //separating each digit of number from the number stream
        
    int product = 0;
    char c;
    for (int i = 0; i < digits; i++)
    {
        long long n_digit = (cc / pow(10 , i));
        int nth_digit = n_digit % 10;
        //printf("%i\n", nth_digit);
        
        // Checking the first two digits to match with card type starting number
            
        if (i == digits - 2)
        {
            c = credit_card_name(digits, n_digit);
        }
        
        //Multiplying the alternate numbers from 2nd to last digit with 2 
        
        if ( digits % 2 != 0 && (digits - i) % 2 == 0)
        {
            product = alternate_number_productsum(nth_digit, product);
            //printf ("%i\n", product);
        }
        
        else if (digits % 2 !=0 && (digits - i) % 2 != 0) 
        {
            product = add_the_rest( product, nth_digit);
            //printf ("%i\n", product);
        }
        
        else if (digits % 2 == 0 && (digits - i) % 2 != 0)
        {
            product = alternate_number_productsum( nth_digit, product);
        }
        
        else if (digits % 2 == 0 && (digits - i) % 2 == 0)
        {
            product = add_the_rest( product, nth_digit);
        }
    } 
    
        if ((product % 10) == 0)
        {
            switch (c)
            {
                case  'A':
                    printf ("AMEX\n");
                    break;
                    
                case 'M':
                    printf ("MASTERCARD\n");
                    break;
                    
                case 'V':
                    printf ("VISA\n");
                    break;
            }

        }
        else
        {
            printf ("INVALID\n");
        }
    
}



int alternate_number_productsum(int nth_digit, int product)
{
    int alternate_digit = nth_digit * 2;
    
    //if the result of multiplied number is 10 or above separationg the each digits from that 2-digit number and adding them to the product sum.
            
    if (alternate_digit > 9)
    {
        
        alternate_digit = (alternate_digit / 10) + (alternate_digit % 10);
    }

    //if the result of multiplied number is less than 10, adding the number to the product sum.
    product = product + alternate_digit;
    return product;
    
}

int add_the_rest(int product, int nth_digit)
{
    product = product + nth_digit;
    return product;        
}



//function to check the starting two digits and their particular digit number to print the card's name

char credit_card_name(int digits, int n_digit)
{
    char c;
    if ((n_digit == 34 || n_digit == 37) && digits == 15)
    {
        c = 'A';
    }
        
    else if ((n_digit == 51 || n_digit == 52 || n_digit == 53 || n_digit == 54 || n_digit == 55) && digits == 16)
    {
        c = 'M';
    }
    else if (n_digit / 10 == 4 && (digits ==13 || digits ==16))
    {
        c = 'V';
      //printf ("VISA\n");
    }
    else 
    {
        return 0;
    }
    return c;
}