/**
 * @file cJSON_Parser_Util.h
 * @author HeCoding180
 * @brief cJSON library parser utility header
 * @version 0.1
 * @date 2024-08-17
 * 
 */

#ifndef CJSON_PARSER_UTIL_DEFINED
#define CJSON_PARSER_UTIL_DEFINED

#include "../inc/cJSON_Constants.h"
#include "../inc/cJSON_GenericStack.h"
#include "../inc/cJSON_Types.h"
#include "../inc/cJSON_Util.h"

//   ---   Defines   ---

// - Flag Defines -
#pragma region Flag Defines

#define CJP_DICT_END_POSSIBLE       0x01    // "}" possible
#define CJP_LIST_END_POSSIBLE       0x02    // "]" possible
#define CJP_ITEM_SEPT_POSSIBLE      0x04    // "," possible
#define CJP_DICT_KEY_POSSIBLE       0x08    // Dictionary key (string) possible
#define CJP_DICT_SEPT_POSSIBLE      0x10    // ":" possible
#define CJP_DICT_VALUE_POSSIBLE     0x20    // Value possible (top of object stack is a dictionary)
#define CJP_LIST_VALUE_POSSIBLE     0x40    // Value possible (top of object stack is a list)

#pragma endregion



//   ---   Macros   ---

// - Character Case Macros -
#pragma region Character Case Macros

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

#pragma endregion



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
cJSON_Result_t cJSON_Parser_StringBuilder(char **refStrPtr, char **outputStrPtr);

/**
 * @brief   Function used to add a character to a double buffer.
 * 
 * @param   SbDb StringBuilder DoubleBuffer pointer of the buffer the char is to be added to.
 * @param   c Character that is to be added to the buffer
 */
static void SB_DB_AddChar(cJSON_SB_DB_t *SbDb, const char c);

#pragma endregion

// - Number Parser Function Prototypes -
#pragma region Number Parser Function Prototypes

/**
 * @brief   Function used to extract a number from the current location of the refStrPtr
 * 
 * @param   refStrPtr Pointer to the start location of the number that is to be extracted inside of the original string that is to be parsed. Pointer pointer is also used to skip that segment of the string by incrementing the original string pointer.
 * @return  cJSON_Generic_t Generic object containing the parsed integer or float.
 */
cJSON_Generic_t cJSON_Parser_NumParser(char **refStrPtr);

#pragma endregion

#endif
