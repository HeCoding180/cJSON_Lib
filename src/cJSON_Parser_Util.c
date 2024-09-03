/**
 * @file cJSON_Parser_Util.c
 * @author HeCoding180
 * @brief cJSON library parser utility source file
 * @version 0.1.0
 * @date 2024-08-17
 * 
 */

#include "../inc/cJSON_Parser_Util.h"
#include "../inc/cJSON_StringDoubleBuffer.h"

//   ---   Function Implementations   ---

// - StringBuilder Functon Implementations -
#pragma region StringBuilder Functon Implementations

cJSON_Result_t cJSON_Parser_StringBuilder(char **refStrPtr, char **outputStrPtr)
{
    cJSON_SDB_t outBuf = {0};

    bool inEscapeSequence = false;

    int strBuilderCharNo = 0;

    char currentRefChar = *(*refStrPtr);

    // Loop through refStrPtr characters
    while (*((*refStrPtr)++))
    {
        if (inEscapeSequence)
        {
            // Add character according to escape sequence
            switch (**refStrPtr)
            {
            case 'N':
            case 'n':
                SDB_AddChar(&outBuf, '\n');
                break;
            case 'R':
            case 'r':
                SDB_AddChar(&outBuf, '\r');
                break;
            case 'T':
            case 't':
                SDB_AddChar(&outBuf, '\t');
                break;
            case '"':
                SDB_AddChar(&outBuf, '"');
                break;
            case '\\':
                SDB_AddChar(&outBuf, '\\');
                break;
            default:
                // Add unknown escape sequence to string using plain text
                SDB_AddChar(&outBuf, '\\');
                SDB_AddChar(&outBuf, **refStrPtr);
                break;
            }

            // End escape sequence
            inEscapeSequence = false;
        }
        else if (**refStrPtr == '"')
        {
            // Exit string environment

            // Write buffer pointer containing formatted extracted string to output string pointer
            *outputStrPtr = SDB_BuildString(outBuf);

            // Free StringDoubleBuffer
            SDB_Free(&outBuf);

            return cJSON_Ok;
        }
        else if (**refStrPtr == '\\')
        {
            // Start escape sequence
            inEscapeSequence = true;
        }
        else
        {
            // Add normal character to buffer
            SDB_AddChar(&outBuf, **refStrPtr);
        }
    }

    // Free StringDoubleBuffer
    SDB_Free(&outBuf);

    // String terminator reached before string finished
    return cJSON_Structure_Error;
}

#pragma endregion

// - Number Parser Function Implementation -
#pragma region Number Parser Function Implementation

cJSON_Generic_t cJSON_Parser_NumParser(char **refStrPtr)
{
    cJSON_Generic_t returnObj;

    uint8_t numStrLen = 0;
    bool numIsFloat = false;
    bool numIncomplete = true;

    while (numIncomplete)
    {
        switch (LOWER_CASE_CHAR(*(*refStrPtr + numStrLen)))
        {
        case '.':
        case 'e':
            numIsFloat = true;
        case '-':
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
            numStrLen++;
            break;
        default:
            numIncomplete = false;
        }
    }

    // Copy string of number to separate memory location
    char *numStrBuffer = (char*)malloc(1 + numStrLen);
    memcpy(numStrBuffer, *refStrPtr, numStrLen);
    numStrBuffer[numStrLen - 1] = '\0';

    if (numIsFloat)
    {
        // Build generic integer object
        returnObj = mallocGenObj(Float);
        AS_INT(returnObj) = (cJSON_Int_t)atoi(numStrBuffer);
    }
    else
    {
        // Build generic float object
        returnObj = mallocGenObj(Integer);
        AS_FLOAT(returnObj) = (cJSON_Float_t)atof(numStrBuffer);
    }

    // Skip number in reference string pointer's pointer
    *refStrPtr += numStrLen - 1;

    return returnObj;
}

#pragma endregion
