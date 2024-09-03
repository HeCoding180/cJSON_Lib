/**
 * @file cJSON_StringDoubleBuffer.h
 * @author HeCoding180
 * @brief Header file of the cJSON string double buffer
 * @version 0.1.0
 * @date 2024-09-03
 * 
 */

#ifndef CJSON_SDB_DEFINED
#define CJSON_SDB_DEFINED

#include "cJSON_Constants.h"

//   ---   Typedefs   ---

/**
 * @brief   Two stage buffer used by the parser's StringBuilder. Used to minimize the use of memory reallocations (realloc).
 *
 */
typedef struct cJSON_StringDoubleBuffer
{
    char *buffer;
    size_t bufferSize;
    char preBuffer[CJSON_PARSE_STRING_PB_SIZE];
    uint8_t preBufferSize;
} cJSON_SDB_t;



//   ---   Function Prototypes   ---

/**
 * @brief   Function used to add a character to a double buffer.
 *
 * @param   SDb StringBuilder DoubleBuffer pointer of the buffer the char is to be added to.
 * @param   c Character that is to be added to the buffer
 */
void SDB_AddChar(cJSON_SDB_t *SDb, const char c);
/**
 * @brief   Function used to get a string from a StringDoubleBuffer struct.
 *
 * @param   SDb StringDoubleBuffer struct that contains an unfinished string.
 * @return  char* completely assembled string from the StringDoubleBuffer struct. Dynamically allocated pointer, needs to be freed before discard.
 */
char* SDB_BuildString(cJSON_SDB_t SDb);
/**
 * @brief   Function used to free potentially allocated memory in a StringDoubleBuffer struct.
 *
 * @param   SDb StringDoubleBuffer struct pointer.
 */
void SDB_Free(cJSON_SDB_t *SDb);

#endif
