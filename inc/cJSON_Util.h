/**
 * @file cJSON_Util.h
 * @author HeCoding180
 * @brief cJSON library utility header file. Contains macros, typedefs and function prototypes that are not needed by the user.
 * @version 0.1
 * @date 2024-08-15
 * 
 */

#ifndef CJSON_UTIL_DEFINED
#define CJSON_UTIL_DEFINED

#include <stdlib.h>
#include <string.h>

#include "cJSON_Constants.h"

//   ---   Macros   ---

// - Basic Macros -
#pragma region Basic Macros

#ifndef MIN
#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#endif

#ifndef MAX
#define MAX(a, b) (((a) > (b)) ? (a) : (b))
#endif

#pragma endregion



//   ---   Typedefs   ---

// - Enum Typedefs -
#pragma region Enum Typedefs



#pragma endregion

// - Struct Typedefs -
#pragma region Struct Typedefs



#pragma endregion



//   ---   Function Prototypes   ---

// - Memory Management Functions -
#pragma region Memory Management Functions

/**
 * @brief   Function that allocates the required memory for a cJSON_Generic_t object together with its specified data container specified in the containerType parameter.
 * @param   containerType Specifies the type of the object stored in the generic object.
 * @return  Returns the memory address of a newly allocated cJSON_Generic_t already containing the type and pointer to the object of the specified type.
 */
cJSON_Generic_t mallocGenObj(cJSON_ContainerType_t containerType);

#pragma endregion

// - Structural Functions -
#pragma region Structural Functions

/**
 * @brief   Function to append a generic object to a dictionary.
 * 
 * @param   dictPtr Pointer to the dictionary the generic object should be added to.
 * @param   key Key string.
 * @param   valObj Value cJSON generic object.
 * @return  cJSON_Result_t 
 */
cJSON_Result_t cJSON_appendToDict(cJSON_Dict_t *dictPtr, const cJSON_Key_t key, cJSON_Generic_t valObj);
/**
 * @brief   Function to append a generic object to a list.
 * 
 * @param   listPtr Pointer to the list the generic object should be added to.
 * @param   obj 
 * @return  cJSON_Result_t 
 */
cJSON_Result_t cJSON_appendToList(cJSON_List_t *listPtr, cJSON_Generic_t obj);

#pragma endregion

#endif
