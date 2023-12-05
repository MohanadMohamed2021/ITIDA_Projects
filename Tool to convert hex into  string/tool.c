#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>

void convert(FILE *input, FILE *output);

int main(int argc, char *argv[]) 
{
    char *input_file;
    char *output_file;

    const char *short_options = "i:o:";
    int option;
    
    while ((option = getopt(argc, argv, short_options)) != -1)
	{
        switch (option) 
		{
            case 'i':
            {    input_file = optarg;
                break;
			}	
            case 'o':
			{
                output_file = optarg;
                break;
			}	
            case '?':
			{
				fprintf(stderr,"Wrong Format");
			}
        }
    }
    FILE *input = fopen(input_file, "r");
    FILE *output = fopen(output_file, "w");
    convert(input, output);
    fclose(input);
    fclose(output);
    return 0;
}

void convert(FILE *input, FILE *output)
{
    int i, j = 0;
    char hexString[100];
    fgets(hexString, sizeof(hexString), input);
    int hexLength = strlen(hexString);
    if (hexLength % 2 != 0)
	{
        fprintf(stderr, "Add or remove one character.\n");
    }
    int strLength = hexLength / 2;
    char final_str[strLength];
    for (i = 0; i < strLength; i++)
	{
        char byte[3];
        byte[0] = hexString[i * 2];
        byte[1] = hexString[i * 2 + 1];
        byte[2] = '\0';
        char value;
        sscanf(byte,"%hhx", &value); 
        final_str[j] = value;
        j++;
    }
    final_str[j] = '\0';
    fprintf(output, "%s", final_str);
}