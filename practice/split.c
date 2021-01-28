void split(char str[],char delims[])
{
    char *result = NULL;
    result = strtok( str, delims );
    while( result != NULL ) 
    {
        printf( "result is \"%s\"\n", result );
    }
    return 0;
}
