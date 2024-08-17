/**
 * @file cJSON_Parser_Util.h
 * @author HeCoding180
 * @brief cJSON library parser utility header
 * @version 0.1
 * @date 2024-08-17
 * 
 */

#include "../inc/cJSON_Constants.h"
#include "../inc/cJSON_GenericStack.h"
#include "../inc/cJSON_Types.h"
#include "../inc/cJSON_Util.h"

//   ---   Macros   ---

/**
 * @brief   Macro used to change an alphabetical character to lower case
 * 
 */
#define LOWER_CASE_CHAR(c) ((((c) > 0x40) && ((c) < 0x5B)) ? ((c) | 0x20) : (c))
/**
 * @brief   Macro used to change an alphabetical character to upper case
 * 
 */
#define UPPER_CASE_CHAR(c) ((((c) > 0x40) && ((c) < 0x5B)) ? ((c) & 0xDF) : (c))



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



//   ---   Function Prototypes   ---

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
