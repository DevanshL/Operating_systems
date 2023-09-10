#include <stdio.h>                  // libraries
#include <stdlib.h>                 // standard library
#include <string.h>

int main()
{
    char a[100];
    FILE *ptr;                          // pointing to file
    ptr = fopen("Input1.txt","r");      // open and read text
    while(!feof(ptr))                   // to check text present till end of file
    {
        fgets(a,100,ptr);               // syntax(array,size,file ptr)
        
                                        
        for(int i=0;i<strlen(a);i++)        // used to change small to capital
        {
            if(a[i]>=97  && a[i]<=122)
            {
                a[i] = a[i]-32;
                
            }
            
            else if (a[i]>=65 && a[i]<=90)  // used to change  capital to small
            {
                a[i] = a[i] + 32;
                
            }
            printf("%c",a[i]);          // print
            
        }
    }
    
        fclose(ptr);            // close file
        
    return 0;
}