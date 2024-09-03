/**
 * @file cJSON_StringDoubleBuffer.c
 * @author HeCoding180
 * @brief Source file of the cJSON string double buffer
 * @version 0.1.0
 * @date 2024-09-03
 * 
 */

#include <stdlib.h>

#include "../inc/cJSON_StringDoubleBuffer.h"

//   ---   Function Implementations    ---

void SDB_AddChar(cJSON_SDB_t *SDb, const char c)
{
    // Add char to preBuffer
    SDb->preBuffer[SDb->preBufferSize++] = c;

    // Check if preBuffer is full
    if (SDb->preBufferSize >= CJSON_PARSE_STRING_PB_SIZE)
    {
        // Reallocate buffer memory and append prebuffer contents to buffer
        if (SDb->bufferSize > 0)   SDb->buffer = (char*)realloc(SDb->buffer, SDb->bufferSize + CJSON_PARSE_STRING_PB_SIZE);
        else                       SDb->buffer = (char*)malloc(CJSON_PARSE_STRING_PB_SIZE);
        memcpy(&SDb->buffer[SDb->bufferSize], SDb->preBuffer, CJSON_PARSE_STRING_PB_SIZE);

        // Update buffer sizes
        SDb->bufferSize += CJSON_PARSE_STRING_PB_SIZE;
        SDb->preBufferSize = 0;
    }
}

char* SDB_BuildString(cJSON_SDB_t SDb)
{
    char *OutBuffer;

    if (SDb.bufferSize)
    {
        if (SDb.preBufferSize)   // Both pre-buffer and buffer contain data
        {
            // Allocate output buffer memory and append prebuffer and string terminator
            OutBuffer = (char*)malloc(1 + SDb.bufferSize + SDb.preBufferSize);
            memcpy(&OutBuffer, SDb.buffer, SDb.bufferSize);
            memcpy(&OutBuffer[SDb.bufferSize], SDb.preBuffer, SDb.preBufferSize);
            OutBuffer[SDb.bufferSize + SDb.preBufferSize] = '\0';
        }
        else                        // Only the buffer contains data
        {
            // Reallocate buffer memory and append string terminator
            OutBuffer = (char*)malloc(1 + SDb.bufferSize);
            memcpy(&OutBuffer, SDb.buffer, SDb.bufferSize);
            OutBuffer[SDb.bufferSize] = '\0';
        }
    }
    else
    {
        if (SDb.preBufferSize)   // Only the pre-buffer contains data
        {
            // Allocate buffer memory, copy contents from pre-buffer to buffer and append string terminator
            OutBuffer = (char*)malloc(1 + SDb.preBufferSize);
            memcpy(OutBuffer, SDb.preBuffer, SDb.preBufferSize);
            OutBuffer[SDb.preBufferSize] = '\0';
        }
        else                        // Neither of the two buffer contains data
        {
            // Allocate 1 byte and set it to string terminator
            OutBuffer = (char*)malloc(1);
            OutBuffer[0] = '\0';
        }
    }
}

void SDB_Free(cJSON_SDB_t *SDb)
{
    // Check if any memory has been allocated
    if (SDb->bufferSize > 0)
    {
        // Free buffer memory
        free(SDb->buffer);
        SDb->bufferSize = 0;
    }
}
