/**
 * @file cJSON_Parser.c
 * @author HeCoding180
 * @brief cJSON library parser source file.
 * @version 0.1
 * @date 2024-08-16
 * 
 */

#include "../inc/cJSON_Parser.h"

#include "../inc/cJSON_Constants.h"
#include "../inc/cJSON_Util.h"

//   ---   Macros   ---

#define LOWER_CASE_CHAR(c) ((((c) > 0x40) && ((c) < 0x5B)) ? ((c) | 0x20) : (c))



//   ---   Typedefs   ---

// - StringBuilder Typedefs -
#pragma region StringBuilder Typedefs

/**
 * @brief   Two stage buffer used by the parser's StringBuilder. Used to minimize the use of memory reallocations (realloc).
 * 
 */
typedef struct cJSON_StringBuilder_DoubleBuffer
{
    char *buffer;
    size_t bufferSize;
    char preBuffer[CJSON_PARSE_STRING_PB_SIZE];
    uint8_t preBufferSize;
} cJSON_SB_DB_t;

#pragma endregion

//   ---   Parser Utility Function Prototypes   ---

// - StringBuilder Functon Prototypes -
#pragma region StringBuilder Functon Prototypes

/**
 * @brief   Function used to extract and format the contents of a string contained
 * 
 * @param   refStrPtr Pointer to the start location of the string that is to be extracted inside of the original string that is to be parsed. Pointer pointer is also used to skip that segment of the string by incrementing the original string pointer.
 * @param   outputStrPtr Pointer to a string pointer variable where the extracted and formatted string should be stored.
 * @return  char* Returns 
 */
static cJSON_Result_t cJSON_Parser_StringBuilder(char **refStrPtr, char **outputStrPtr);

/**
 * @brief   Function used to add a character to a double buffer.
 * 
 * @param   SbDb StringBuilder DoubleBuffer pointer of the buffer the char is to be added to.
 * @param   c Character that is to be added to the buffer
 */
static void SB_DB_AddChar(cJSON_SB_DB_t *SbDb, const char c);

#pragma endregion

//   ---   Parser Function Implementation   ---

cJSON_Result_t cJSON_parseStr(cJSON_Generic_t *GObjPtr, const char *str)
{
    // Check if GObjPtr is allocated. If so delete old data structure
    if (GObjPtr->dataContainer != NULL) cJSON_delGenObj(*GObjPtr);

    

    enum valueEnironmentType
    {
        None,
        StringValue,
        NumericValue,
        
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

//   ---   Parser Utility Function Implementations

// - StringBuilder Functon Implementations -
#pragma region StringBuilder Functon Implementations

static cJSON_Result_t cJSON_Parser_StringBuilder(char **refStrPtr, char **outputStrPtr)
{
    cJSON_SB_DB_t outBuf = {0};

    bool inEscapeSequence = false;

    while (**refStrPtr)
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
            case '\"':
                SB_DB_AddChar(&outBuf, '\"');
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
        else if (**refStrPtr == '\"')
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
            outputStrPtr = outBuf.buffer;

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

        // Increment parser's input string pointer
        (*refStrPtr)++;
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
