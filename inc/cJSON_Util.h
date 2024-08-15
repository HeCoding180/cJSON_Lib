/**
 * @file cJSON_Util.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2024-08-15
 * 
 */

#include "cJSON_Types.h"

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



//   ---   Function Prototypes   ---

/**
 * @brief   Function that allocates the required memory for a cJSON_Generic_t object together with its specified data container specified in the containerType parameter.
 * @param   containerType Specifies the type of the object stored in the generic object.
 * @return  Returns the memory address of a newly allocated cJSON_Generic_t already containing the type and pointer to the object of the specified type.
 */
cJSON_Generic_t mallocGenObj(cJSON_ContainerType_t containerType);
