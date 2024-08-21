/**
 * @file cJSON_GenericStack.h
 * @author HeCoding180
 * @brief cJSON library GenericStack header file.
 * @version 0.1
 * @date 2024-08-17
 * 
 */


#include "cJSON_Types.h"

//   ---   Macros   ---

// - GenericStack Macros -
#pragma region GenericStack Macros

/**
 * @brief   Macro used to check if a cJSON_GenericStack_t stack is empty.
 * 
 * @param   TS cJSON_GenericStack_t struct.
 * 
 * @return  true if GenericStack is empty
 * @return  false if GenericStack is not empty
 * 
 */
#define GS_IS_EMPTY(TS) ((TS).isEmpty)
/**
 * @brief   Macro used to check if a cJSON_GenericStack_t pointer's stack is empty.
 * 
 * @param   TS cJSON_GenericStack_t struct pointer.
 * 
 * @return  true if GenericStack is empty
 * @return  false if GenericStack is not empty
 * 
 */
#define GS_PTR_IS_EMPTY(TS) ((TS)->isEmpty)

/**
 * @brief   Macro used to check if a cJSON_GenericStack_t stack is full.
 * 
 * @param   TS cJSON_GenericStack_t struct.
 * 
 * @return  true if GenericStack is full
 * @return  false if GenericStack is not full
 * 
 */
#define GS_IS_FULL(TS) ((TS).index == ((TS).stackSize - 1))
/**
 * @brief   Macro used to check if a cJSON_GenericStack_t pointer's stack is full.
 * 
 * @param   TS cJSON_GenericStack_t struct pointer.
 * 
 * @return  true if GenericStack is full
 * @return  false if GenericStack is not full
 * 
 */
#define GS_PTR_IS_FULL(TS) ((TS)->index == ((TS)->stackSize - 1))

/**
 * @brief   Unsafe macro used to get the top item from a cJSON_GenericStack_t stack.
 * 
 * @param   TS cJSON_GenericStack_t struct.
 * 
 */
#define GS_TOP(TS) ((TS).stack[(TS).index])
/**
 * @brief   Unsafe macro used to get the top item from a cJSON_GenericStack_t pointer's stack.
 * 
 * @param   TS cJSON_GenericStack_t struct pointer.
 * 
 */
#define GS_PTR_TOP(TS) ((TS)->stack[(TS)->index])

#pragma endregion



//   ---   Typedefs   ---

// - Enum Typedefs -
#pragma region Enum Typedefs

/**
 * @brief   Result for cJSON GenericStack (cJSON_GenericStack_t) operation functions.
 * 
 */
typedef enum cJSON_GenericStack_Result
{
    /**
     * @brief   Default result.
     * 
     */
    GS_Ok,
    /**
     * @brief   Returned on GS_Push operation of a full stack.
     * 
     */
    GS_StackOverflow_Error,
    /**
     * @brief   Returned on GS_Pop operation of an empty stack.
     * 
     */
    GS_StackUnderflow_Error,
    /**
     * @brief   Returned on GS_Top of an empty stack.
     * 
     */
    GS_StackIsEmpty
} cJSON_GenericStack_Result_t;

#pragma endregion

// - Struct Typedefs -
#pragma region Struct Typedefs

/**
 * @brief   cJSON_GenericStack_t is a struct for a stack used for 
 * 
 */
typedef struct cJSON_GenericStack
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
} cJSON_GenericStack_t;

#pragma endregion



//   ---   Function Prototypes   ---

// - GenericStack Functions -
#pragma region GenericStack Functions

/**
 * @brief   Function used to create and allocate memory for a cJSON_GenericStack_t struct. 
 * 
 * @param   stackSize Size of the stack in number of items.
 * @return  cJSON_GenericStack_t Struct with allocated stack memory.
 */
cJSON_GenericStack_t GS_Create(cJSON_depth_t stackSize);
/**
 * @brief   Resets and frees stack memory of a cJSON_GenericStack_t struct. Needs to be used on discarding of the struct to avoid memory leaks.
 * 
 * @param   TSptr Pointer to a cJSON_GenericStack_t struct.
 */
void GS_Delete(cJSON_GenericStack_t *TSptr);

/**
 * @brief   Used to push a cJSON_ContainerType_t value to the stack.
 * 
 * @param   TSptr Pointer to a cJSON_GenericStack_t struct.
 * @param   type cJSON_ContainerType_t type that is to be pushed to the stack.
 * @return  cJSON_GenericStack_Result_t Returns GS_Ok by default. Returns GS_StackOverflow_Error if stack was already full before the push operation (type not pushed to stack).
 */
cJSON_GenericStack_Result_t GS_Push(cJSON_GenericStack_t *TSptr, cJSON_ContainerType_t type);
/**
 * @brief   Used to remove the top item from the stack.
 * 
 * @param   TSptr Pointer to a cJSON_GenericStack_t struct.
 * @return  cJSON_GenericStack_Result_t Returns GS_Ok by default. Returns GS_StackUnderflow_Error if stack was already empty before the pop operation (nothing changed).
 */
cJSON_GenericStack_Result_t GS_Pop(cJSON_GenericStack_t *TSptr);
/**
 * @brief   Used to retreive the top value from the stack.
 * 
 * @param   TSptr Pointer to a cJSON_GenericStack_t struct.
 * @param   type Pointer to a cJSON_ContainerType_t variable, the stack's top type is to be stored in.
 * @return  cJSON_ContainerType_t Returns GS_Ok by default. Returns GS_StackIsEmpty if stack is empty (type pointer's contents are left untouched).
 */
cJSON_GenericStack_Result_t GS_Top(cJSON_GenericStack_t *TSptr, cJSON_ContainerType_t *type);
/**
 * @brief   Function used to check if stack is empty.
 * 
 * @param   TSptr Pointer to a cJSON_GenericStack_t struct.
 * @return  true if stack is empty.
 * @return  false if stack is not empty.
 */
bool GS_IsEmpty(cJSON_GenericStack_t *TSptr);
/**
 * @brief   Used to check if stack is full.
 * 
 * @param   TSptr Pointer to a cJSON_GenericStack_t struct.
 * @return  true if stack is full.
 * @return  false if stack is not full.
 */
bool GS_IsFull(cJSON_GenericStack_t *TSptr);

#pragma endregion
