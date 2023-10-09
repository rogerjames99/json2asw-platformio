#include <cstdio>
#include <cstdlib>
#include <filesystem>
#include <iostream>

using namespace std;

int main(int argc, char** argv)
{
    if (argc < 2)
    {
        printf("No filename supplied\n");
        return -1;
    }

    /**
     * Use sed to strip out PROGMEM
    */
    char command[128];
    if (snprintf(command, 128, "get-sizes") < 0)
    {
        printf("Unable to create command string\n");
        return -1;
    }

    int ret = system(command);
    if (ret < 0)
    {
        printf("get-sizes command failed %d\n", ret);
        return -1;
    }    
}