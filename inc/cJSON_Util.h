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

// - TypeStack Macros -
#pragma region TypeStack Macros

/**
 * @brief   Macro used to check if a cJSON_TypeStack_t stack is empty.
 * 
 * @param   TS cJSON_TypeStack_t struct.
 * 
 * @return  true if typestack is empty
 * @return  false if typestack is not empty
 * 
 */
#define TS_IS_EMPTY(TS) ((TS).isEmpty)
/**
 * @brief   Macro used to check if a cJSON_TypeStack_t pointer's stack is empty.
 * 
 * @param   TS cJSON_TypeStack_t struct pointer.
 * 
 * @return  true if typestack is empty
 * @return  false if typestack is not empty
 * 
 */
#define TS_PTR_IS_EMPTY(TS) ((TS)->isEmpty)

/**
 * @brief   Macro used to check if a cJSON_TypeStack_t stack is full.
 * 
 * @param   TS cJSON_TypeStack_t struct.
 * 
 * @return  true if typestack is full
 * @return  false if typestack is not full
 * 
 */
#define TS_IS_FULL(TS) ((TS).index == ((TS).stackSize - 1))
/**
 * @brief   Macro used to check if a cJSON_TypeStack_t pointer's stack is full.
 * 
 * @param   TS cJSON_TypeStack_t struct pointer.
 * 
 * @return  true if typestack is full
 * @return  false if typestack is not full
 * 
 */
#define TS_PTR_IS_FULL(TS) ((TS)->index == ((TS)->stackSize - 1))

/**
 * @brief   Unsafe macro used to get the top item from a cJSON_TypeStack_t stack.
 * 
 * @param   TS cJSON_TypeStack_t struct.
 * 
 */
#define TS_TOP(TS) ((TS).stack[(TS).index])
/**
 * @brief   Unsafe macro used to get the top item from a cJSON_TypeStack_t pointer's stack.
 * 
 * @param   TS cJSON_TypeStack_t struct pointer.
 * 
 */
#define TS_PTR_TOP(TS) ((TS)->stack[(TS)->index])

#pragma endregion



//   ---   Typedefs   ---

// - Enum Typedefs -
#pragma region Enum Typedefs

/**
 * @brief   Result for cJSON Typestack (cJSON_TypeStack_t) operation functions.
 * 
 */
typedef enum cJSON_TypeStack_Result
{
    /**
     * @brief   Default result.
     * 
     */
    TS_Ok,
    /**
     * @brief   Returned on TS_Push operation of a full stack.
     * 
     */
    TS_StackOverflow_Error,
    /**
     * @brief   Returned on TS_Pop operation of an empty stack.
     * 
     */
    TS_StackUnderflow_Error,
    /**
     * @brief   Returned on TS_Top of an empty stack.
     * 
     */
    TS_StackIsEmpty
} cJSON_TypeStack_Result_t;

#pragma endregion

// - Struct Typedefs -
#pragma region Struct Typedefs

/**
 * @brief   cJSON_TypeStack_t is a struct for a stack used for 
 * 
 */
typedef struct cJSON_TypeStack
{
    /**
     * @brief   Size of the stack.
     * 
     */
    cJSON_depth_t stackSize;
    /**
     * @brief   Index of the topmost cJSON_ContainerType_t of the stack. Is zero for both cases of the stack containing one and zero items!
     * 
     */
    cJSON_depth_t index;
    /**
     * @brief   True if the stack contains zero items.
     * 
     */
    bool isEmpty;
    /**
     * @brief   Pointer to a cJSON_ContainerType_t array.
     * 
     */
    cJSON_ContainerType_t *stack;
} cJSON_TypeStack_t;

#pragma endregion



//   ---   Function Prototypes   ---

// - TypeStack Functions -
#pragma region TypeStack Functions

/**
 * @brief   Function used to create and allocate memory for a cJSON_TypeStack_t struct. 
 * 
 * @param   stackSize Size of the stack in number of items.
 * @return  cJSON_TypeStack_t Struct with allocated stack memory.
 */
cJSON_TypeStack_t TS_Create(cJSON_depth_t stackSize);
/**
 * @brief   Resets and frees stack memory of a cJSON_TypeStack_t struct. Needs to be used on discarding of the struct to avoid memory leaks.
 * 
 * @param   TSptr Pointer to a cJSON_TypeStack_t struct.
 */
void TS_Delete(cJSON_TypeStack_t *TSptr);

/**
 * @brief   Used to push a cJSON_ContainerType_t value to the stack.
 * 
 * @param   TSptr Pointer to a cJSON_TypeStack_t struct.
 * @param   type cJSON_ContainerType_t type that is to be pushed to the stack.
 * @return  cJSON_TypeStack_Result_t Returns TS_Ok by default. Returns TS_StackOverflow_Error if stack was already full before the push operation (type not pushed to stack).
 */
cJSON_TypeStack_Result_t TS_Push(cJSON_TypeStack_t *TSptr, cJSON_ContainerType_t type);
/**
 * @brief   Used to remove the top item from the stack.
 * 
 * @param   TSptr Pointer to a cJSON_TypeStack_t struct.
 * @return  cJSON_TypeStack_Result_t Returns TS_Ok by default. Returns TS_StackUnderflow_Error if stack was already empty before the pop operation (nothing changed).
 */
cJSON_TypeStack_Result_t TS_Pop(cJSON_TypeStack_t *TSptr);
/**
 * @brief   Used to retreive the top value from the stack.
 * 
 * @param   TSptr Pointer to a cJSON_TypeStack_t struct.
 * @param   type Pointer to a cJSON_ContainerType_t variable, the stack's top type is to be stored in.
 * @return  cJSON_ContainerType_t Returns TS_Ok by default. Returns TS_StackIsEmpty if stack is empty (type pointer's contents are left untouched).
 */
cJSON_TypeStack_Result_t TS_Top(cJSON_TypeStack_t *TSptr, cJSON_ContainerType_t *type);
/**
 * @brief   Function used to check if stack is empty.
 * 
 * @param   TSptr Pointer to a cJSON_TypeStack_t struct.
 * @return  true if stack is empty.
 * @return  false if stack is not empty.
 */
bool TS_IsEmpty(cJSON_TypeStack_t *TSptr);
/**
 * @brief   Used to check if stack is full.
 * 
 * @param   TSptr Pointer to a cJSON_TypeStack_t struct.
 * @return  true if stack is full.
 * @return  false if stack is not full.
 */
bool TS_IsFull(cJSON_TypeStack_t *TSptr);

#pragma endregion

// - Memory Management Functions -
#pragma region Memory Management Functions

/**
 * @brief   Function that allocates the required memory for a cJSON_Generic_t object together with its specified data container specified in the containerType parameter.
 * @param   containerType Specifies the type of the object stored in the generic object.
 * @return  Returns the memory address of a newly allocated cJSON_Generic_t already containing the type and pointer to the object of the specified type.
 */
cJSON_Generic_t mallocGenObj(cJSON_ContainerType_t containerType);

#pragma endregion

#endif
