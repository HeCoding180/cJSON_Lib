/**
 * @file cJSON_Parser_Util.c
 * @author HeCoding180
 * @brief cJSON library parser utility source file
 * @version 0.1.0
 * @date 2024-08-17
 * 
 */

#include "../inc/cJSON_Parser_Util.h"

//   ---   Function Implementations   ---

// - StringBuilder Functon Implementations -
#pragma region StringBuilder Functon Implementations

cJSON_Result_t cJSON_Parser_StringBuilder(char **refStrPtr, char **outputStrPtr)
{
    cJSON_SB_DB_t outBuf = {0};

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
                SB_DB_AddChar(&outBuf, '\n');
                break;
            case 'R':
            case 'r':
                SB_DB_AddChar(&outBuf, '\r');
                break;
            case 'T':
            case 't':
                SB_DB_AddChar(&outBuf, '\t');
                break;
            case '"':
                SB_DB_AddChar(&outBuf, '"');
                break;
            case '\\':
                SB_DB_AddChar(&outBuf, '\\');
                break;
            default:
                // Add unknown escape sequence to string using plain text
                SB_DB_AddChar(&outBuf, '\\');
                SB_DB_AddChar(&outBuf, **refStrPtr);
                break;
            }

            // End escape sequence
            inEscapeSequence = false;
        }
        else if (**refStrPtr == '"')
        {
            // Exit string environment

            // Make sure that the buffer also contains pre-buffered data as well as a string terminator
            if (outBuf.bufferSize)
            {
                if (outBuf.preBufferSize)   // Both pre-buffer and buffer contain data
                {
                    // Reallocate buffer memory and append prebuffer and string terminator
                    outBuf.buffer = (char*)realloc(outBuf.buffer, 1 + outBuf.bufferSize + outBuf.preBufferSize);
                    memcpy(&outBuf.buffer[outBuf.bufferSize], outBuf.preBuffer, outBuf.preBufferSize);
                    outBuf.buffer[outBuf.bufferSize + outBuf.preBufferSize] = '\0';
                }
                else                        // Only the buffer contains data
                {
                    // Reallocate buffer memory and append string terminator
                    outBuf.buffer = (char*)realloc(outBuf.buffer, 1 + outBuf.bufferSize);
                    outBuf.buffer[outBuf.bufferSize] = '\0';
                }
            }
            else
            {
                if (outBuf.preBufferSize)   // Only the pre-buffer contains data
                {
                    // Allocate buffer memory, copy contents from pre-buffer to buffer and append string terminator
                    outBuf.buffer = (char*)malloc(1 + outBuf.preBufferSize);
                    memcpy(outBuf.buffer, outBuf.preBuffer, outBuf.preBufferSize);
                    outBuf.buffer[outBuf.preBufferSize] = '\0';
                }
                else                        // Neither of the two buffer contains data
                {
                    // Allocate 1 byte and set it to string terminator
                    outBuf.buffer = (char*)malloc(1);
                    outBuf.buffer[0] = '\0';
                }
            }

            // Write buffer pointer containing formatted extracted string to output string pointer
            *outputStrPtr = outBuf.buffer;

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
            SB_DB_AddChar(&outBuf, **refStrPtr);
        }
    }

    // String terminator reached before string finished
    return cJSON_Structure_Error;
}

static void SB_DB_AddChar(cJSON_SB_DB_t *SbDb, const char c)
{
    // Add char to preBuffer
    SbDb->preBuffer[SbDb->preBufferSize++] = c;

    // Check if preBuffer is full
    if (SbDb->preBufferSize >= CJSON_PARSE_STRING_PB_SIZE)
    {
        // Reallocate buffer memory and append prebuffer contents to buffer
        if (SbDb->bufferSize > 0)   SbDb->buffer = (char*)realloc(SbDb->buffer, SbDb->bufferSize + CJSON_PARSE_STRING_PB_SIZE);
        else                        SbDb->buffer = (char*)malloc(CJSON_PARSE_STRING_PB_SIZE);
        memcpy(&SbDb->buffer[SbDb->bufferSize], SbDb->preBuffer, CJSON_PARSE_STRING_PB_SIZE);

        // Update buffer sizes
        SbDb->bufferSize += CJSON_PARSE_STRING_PB_SIZE;
        SbDb->preBufferSize = 0;
    }
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
