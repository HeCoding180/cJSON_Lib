/**
 * @file cJSON_Parser.c
 * @author HeCoding180
 * @brief cJSON library parser source file.
 * @version 0.1
 * @date 2024-08-16
 * 
 */

#include "../inc/cJSON_Parser.h"
#include "../inc/cJSON_Parser_Util.h"

//   ---   Parser Function Implementation   ---

cJSON_Result_t cJSON_parseStr(cJSON_Generic_t *GObjPtr, const char *str)
{
    // Check if GObjPtr is allocated. If so delete old data structure
    if (GObjPtr->dataContainer != NULL) cJSON_delGenObj(*GObjPtr);

    

    enum valueEnironmentType
    {
        None,
        StringValue,
        NumericValue
    } valEnvType;

    // Loop through string's contents
    while (*str)
    {
        if (0)
        {

        }
        else
        {
            switch (*str)
            {
            case ' ':   // Ignore space character
            case '\n':  // Ignore newline character
                continue;
            case '{':
                // Start dictionary
                break;
            case '}':
                // End dictionary
                break;
            case '[':
                // Start list
                break;
            case ']':
                // End list
                break;
            case '"':
                break;
            case ':':
                break;
            case ',':
                // Next item
                break;
            }
        }

        // Handle next character
        str++;
    }
}
