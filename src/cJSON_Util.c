/**
 * @file cJSON_Util.c
 * @author HeCoding180
 * @brief 
 * @version 0.1
 * @date 2024-08-15
 * 
 */

#include "../inc/cJSON_Util.h"

//   ---   Function Implementations   ---

// - TypeStack Functions -
#pragma region TypeStack Functions

cJSON_TypeStack_t TS_Create(cJSON_depth_t stackSize)
{
    cJSON_TypeStack_t tempTS;

    // Initialize with default values
    tempTS.stackSize = stackSize;
    tempTS.index = 0;
    tempTS.isEmpty = true;
    tempTS.stack = (cJSON_ContainerType_t*)malloc(stackSize * sizeof(cJSON_ContainerType_t));

    return tempTS;
}
void TS_Delete(cJSON_TypeStack_t *TSptr)
{
    // Free stack memory
    free(TSptr->stack);

    // Reset TS struct variables
    TSptr->stackSize = 0;
    TSptr->index = 0;
    TSptr->isEmpty = true;
}

cJSON_TypeStack_Result_t TS_Push(cJSON_TypeStack_t *TSptr, cJSON_ContainerType_t type)
{
    if (TS_PTR_IS_FULL(TSptr)) return TS_StackOverflow_Error;
    else if (TS_PTR_IS_EMPTY(TSptr))
    {
        // Push to empty stack
        TSptr->isEmpty = false;
        TSptr->stack[0] = type;
    }
    else
    {
        // Push to stack, that already contains data
        TSptr->stack[++TSptr->index] = type;
    }

    return TS_Ok;
}
cJSON_TypeStack_Result_t TS_Pop(cJSON_TypeStack_t *TSptr)
{
    if (TSptr->isEmpty) return TS_StackUnderflow_Error;
    else if (TSptr->index == 0)
    {
        TSptr->isEmpty = true;
    }
    else
    {
        TSptr->index--;
    }

    return TS_Ok;
}
cJSON_TypeStack_Result_t TS_Top(cJSON_TypeStack_t *TSptr, cJSON_ContainerType_t *type)
{
    if (TSptr->isEmpty) return TS_StackIsEmpty;
    else
    {
        *type = TS_PTR_TOP(TSptr);
        return TS_Ok;
    }
}
bool TS_IsEmpty(cJSON_TypeStack_t *TSptr)
{
    return TS_PTR_IS_EMPTY(TSptr);
}
bool TS_IsFull(cJSON_TypeStack_t *TSptr)
{
    return TS_PTR_IS_FULL(TSptr);
}

#pragma endregion

// - Memory Management Functions -
#pragma region Memory Management Functions

cJSON_Generic_t mallocGenObj(cJSON_ContainerType_t containerType)
{
    cJSON_Generic_t genObj;
    genObj.type = containerType;

    size_t containerSize;

    // Select container pointer size
    switch(containerType)
    {
    case Null:
        genObj.dataContainer = NULL;
        return genObj;
    case Dictionary:
        containerSize = sizeof(cJSON_Dict_t);
        break;
    case List:
        containerSize = sizeof(cJSON_List_t);
        break;
    case String:
        containerSize = sizeof(cJSON_String_t);
        break;
    case Integer:
        containerSize = sizeof(cJSON_Int_t);
        break;
    case Float:
        containerSize = sizeof(cJSON_Float_t);
        break;
    case Boolean:
        containerSize = sizeof(cJSON_Bool_t);
        break;
    }

    // Allocate memory for data container
    genObj.dataContainer = malloc(containerSize);
    
    // Set allocated memory to 0
    if (genObj.dataContainer != NULL) memset(genObj.dataContainer, 0, containerSize);
    
    return genObj;
}

#pragma endregion
