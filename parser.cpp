#include <cstdio>
#include <cstdlib>
#include <filesystem>
#include <iostream>

using namespace std;

int main(int argc, char** argv)
{
    char tempfile[L_tmpnam];

    if (argc < 2)
    {
        printf("No filename supplied\n");
        return -1;
    }

    /**
     * Create a temporary file to work on.
    */
    if (nullptr == tmpnam(tempfile))
    {
        printf("Unable to create temporary file\n");
        return -1;
    }

    printf("Temporary file name %s\n", tempfile);

    /**
     * Use sed to strip out PROGMEM
    */
    char command[128];
    if (snprintf(command, 128, "sed -e s/PROGMEM//g %s >%s", argv[1], tempfile) < 0)
    {
        printf("Unable to create command string\n");
        return -1;
    }

    int ret = system(command);
    if (ret < 0)
    {
        printf("sed command failed %d\n", ret);
        return -1;
    }    
}