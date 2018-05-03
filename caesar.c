#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

int main(int argc, string argv[] )
{
    int key;
    if (argc == 2)
    {
        key = atoi (argv[1]); 
    }
    
    else
    {
        printf ("Command line arguement error!\n");
        return 1;
    }
    
    printf ("plaintext: ");
    string s = get_string();
    
    
    printf("ciphertext: ");
    
    for (int i =0, n = strlen(s); i < n; i++)
    {
        if (isalpha (s[i]) && isupper (s[i]))
        {
            int alphabet = ((int) s[i] - 65 + key) % 26;
            int ASCII = 65 + alphabet;
            printf ("%c", ASCII);
        }
        else if (isalpha(s[i]) && islower (s[i])) 
        {
            int alphabet = ((int) s[i] - 97 + key) % 26;
            int ASCII = 97 + alphabet;
            printf ("%c", ASCII);
        }
        else
        {
            printf("%c", s[i]);
        }
    }
    printf ("\n");
}