/**
 * @file cJSON_GenericStack.c
 * @author HeCoding180
 * @brief cJSON library GenericStack source file.
 * @version 0.1
 * @date 2024-08-17
 * 
 */

#include "../inc/cJSON_GenericStack.h"

//   ---   Function Implementations   ---

// - GenericStack Function Implementations -
#pragma region GenericStack Functions

cJSON_GenericStack_t GS_Create(cJSON_depth_t stackSize)
{
    cJSON_GenericStack_t tempTS;

    // Initialize with default values
    tempTS.stackSize = stackSize;
    tempTS.index = 0;
    tempTS.isEmpty = true;
    tempTS.stack = (cJSON_Generic_t*)malloc(stackSize * sizeof(cJSON_Generic_t));

    return tempTS;
}
void GS_Delete(cJSON_GenericStack_t *TSptr)
{
    // Free stack memory
    free(TSptr->stack);

    // Reset TS struct variables
    TSptr->stackSize = 0;
    TSptr->index = 0;
    TSptr->isEmpty = true;
}

cJSON_GenericStack_Result_t GS_Push(cJSON_GenericStack_t *TSptr, cJSON_Generic_t type)
{
    if (GS_PTR_IS_FULL(TSptr)) return GS_StackOverflow_Error;
    else if (GS_PTR_IS_EMPTY(TSptr))
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

    return GS_Ok;
}
cJSON_GenericStack_Result_t GS_Pop(cJSON_GenericStack_t *TSptr)
{
    if (TSptr->isEmpty) return GS_StackUnderflow_Error;
    else if (TSptr->index == 0)
    {
        TSptr->isEmpty = true;
    }
    else
    {
        TSptr->index--;
    }

    return GS_Ok;
}
cJSON_GenericStack_Result_t GS_Top(cJSON_GenericStack_t *TSptr, cJSON_Generic_t *type)
{
    if (TSptr->isEmpty) return GS_StackIsEmpty;
    else
    {
        *type = GS_PTR_TOP(TSptr);
        return GS_Ok;
    }
}
bool GS_IsEmpty(cJSON_GenericStack_t *TSptr)
{
    return GS_PTR_IS_EMPTY(TSptr);
}
bool GS_IsFull(cJSON_GenericStack_t *TSptr)
{
    return GS_PTR_IS_FULL(TSptr);
}

#pragma endregion
