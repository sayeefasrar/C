#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

int main(int argc, string argv[] )
{
    // Checking for if command line comes with no arguement, k = 0
    if (argc != 2)
    {
        invalid_input: printf ("Command line arguement error!\n");
        return 1;
    }
    
    //keeping the length of command line arguement
    int argv1len = strlen(argv[1]);
    int keyascii[argv1len];

    // Saving the number of  how many steps should the each of the plaintext should move to become a ciphertext
    for (int j = 0; j < argv1len; j++)
    {
        if (isalpha(argv[1][j]) && isupper(argv[1][j]))
        {
            keyascii[j] = (int) (argv[1][j]) - 65;
        }
            
        else if (isalpha (argv[1][j]) && islower(argv[1][j]))
        {
            keyascii[j] = (int) (argv[1][j]) - 97;
        }
            
        else
        {
        goto invalid_input;
        }
    }

    // Taking plain text as input
    printf ("plaintext: ");
    string s = get_string();
    
    // Starting ciphering text
    printf("ciphertext: ");
    
    /*  i is the counter of the plain text which iterates over it.
        j keeps track of the alphabets of plain text.
        k is the position of the command line arguement text.
        if there is any non-alphabet in plaintext i iterates over it and increases its value but j does not increase its value.
        Hence, the command line argument does not changes the non-alphabets rather changes the alphabets.
    */
    for (int i =0, j = 0, n = strlen(s); i < n; i++)
    {
         
        int k = j % argv1len;
        
        if (isalpha (s[i]) && isupper (s[i]))
        {
            int alphabet = ((int) s[i] - 65 + keyascii[k]) % 26 ;
            int ASCII = 65 + alphabet;
            printf ("%c", ASCII);
            
            j++;
        }
        
        else if (isalpha(s[i]) && islower (s[i])) 
        {
            int alphabet = ((int) s[i] - 97 + keyascii[k]) % 26;
            int ASCII = 97 + alphabet;
            printf ("%c", ASCII);
            j++;
        }
        
        else
        {
            printf("%c", s[i]);
                
        }
        

    }
    printf ("\n");
}