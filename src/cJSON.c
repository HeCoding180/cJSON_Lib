/**
 * @file cJSON.c
 * @author HeCoding180
 * @brief cJSON library c source file
 * @version 0.1
 * @date 2024-08-10
 * 
 */

#include "../inc/cJSON.h"

//   ---   Private Functions   ---

//   ---   Private Function Prototypes   ---
#pragma region Private Function Prototypes

/**
 * @brief   Function that allocates the required memory for a cJSON_Generic_t object together with its specified data container specified in the containerType parameter.
 * @param   containerType Specifies the type of the object stored in the generic object.
 * @return  Returns the memory address of a newly allocated cJSON_Generic_t already containing the type and pointer to the object of the specified type.
 */
cJSON_Generic_t cJSON_mallocGenObj(cJSON_DataType_t containerType);

#pragma endregion

//   ---   Private Function Implementations   ---
#pragma region Private Function Implementations

cJSON_Generic_t cJSON_mallocGenObj(cJSON_DataType_t containerType)
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



//   ---   Public Function Implementations   ---

// - Structure Modification Functions -
#pragma region Structure Modification Functions

cJSON_Result_t cJSON_delGenObj(cJSON_Generic_t *GOptr)
{
    // Check if object is already deleted.
    if (GOptr->dataContainer != NULL)
    {
        switch(GOptr->type)
        {
        case Dictionary:
            // Delete all cJSON_Generic_t objects and free the memory of all key strings stored in this cJSON_Dict_t object.
            for (cJSON_object_size_size_t i = 0; i < AS_DICT_PTR(GOptr)->length; i++)
            {
                // Free the key string pointer (char**) stored at index i.
                free(AS_DICT_PTR(GOptr)->keyData[i]);
                // Delete the cJSON_Generic_t object stored at index i.
                cJSON_delGenObj(&(AS_DICT_PTR(GOptr)->valueData[i]));
            }

            // Free the memory of the key and value arrays.
            free(AS_DICT_PTR(GOptr)->keyData);
            free(AS_DICT_PTR(GOptr)->valueData);

            // Free the memory of the data container itself.
            free(GOptr->dataContainer);
            break;
        case List:
            for (cJSON_object_size_size_t i = 0; i < AS_LIST_PTR(GOptr)->length; i++)
            {
                // Delete the cJSON_Generic_t object stored at index i
                cJSON_delGenObj(&(AS_LIST_PTR(GOptr)->data[i]));
            }

            // Free the memory of the data container itself.
            free(GOptr->dataContainer);
            break;
        default:
            // Remaining types: Null, String, Integer, Float, Boolean.
            // Free memory of the value.
            free(GOptr->dataContainer);
            break;
        }
    }
}

#pragma endregion

// - Data Container Getter Functions -
#pragma region Getter Functions

cJSON_Result_t cJSON_tryGetDict(cJSON_Generic_t *GOptr, cJSON_Dict_t *dict)
{
    if (GOptr->type == Dictionary)
    {
        *dict = AS_DICT(GOptr);
        return cJSON_Ok;
    }
    
    return cJSON_Datatype_Error;
}
cJSON_Result_t cJSON_tryGetList(cJSON_Generic_t *GOptr, cJSON_List_t *list)
{
    if (GOptr->type == List)
    {
        *list = AS_LIST(GOptr);
        return cJSON_Ok;
    }
    
    return cJSON_Datatype_Error;
}
cJSON_Result_t cJSON_tryGetString(cJSON_Generic_t *GOptr, cJSON_String_t *str)
{
    if (GOptr->type == String)
    {
        if (*str != NULL) free(*str);
        *str = malloc(strlen(AS_STRING(GOptr)) + 1);
        strcpy(*str, AS_STRING(GOptr));
        return cJSON_Ok;
    }
    
    return cJSON_Datatype_Error;
}
cJSON_Result_t cJSON_tryGetInt(cJSON_Generic_t *GOptr, cJSON_Int_t *intVal)
{
    if (GOptr->type == Integer)
    {
        *intVal = AS_INT(GOptr);
        return cJSON_Ok;
    }
    
    return cJSON_Datatype_Error;
}
cJSON_Result_t cJSON_tryGetFloat(cJSON_Generic_t *GOptr, cJSON_Float_t *floatVal)
{
    if (GOptr->type == Float)
    {
        *floatVal = AS_FLOAT(GOptr);
        return cJSON_Ok;
    }
    
    return cJSON_Datatype_Error;
}
cJSON_Result_t cJSON_tryGetBool(cJSON_Generic_t *GOptr, cJSON_Bool_t *boolVal)
{
    if (GOptr->type == Boolean)
    {
        *boolVal = AS_BOOL(GOptr);
        return cJSON_Ok;
    }
    
    return cJSON_Datatype_Error;
}

#pragma endregion

// - Pointer Getter Functions
#pragma region Pointer Getter Functions

cJSON_Result_t cJSON_tryGetDictPtr(cJSON_Generic_t *GOptr, cJSON_Dict_t **dictPtr)
{
    if (GOptr->type == Dictionary)
    {
        *dictPtr = AS_DICT_PTR(GOptr);
        return cJSON_Ok;
    }
    
    return cJSON_Datatype_Error;
}
cJSON_Result_t cJSON_tryGetListPtr(cJSON_Generic_t *GOptr, cJSON_List_t **listPtr)
{
    if (GOptr->type == List)
    {
        *listPtr = AS_LIST_PTR(GOptr);
        return cJSON_Ok;
    }
    
    return cJSON_Datatype_Error;
}
cJSON_Result_t cJSON_tryGetStringPtr(cJSON_Generic_t *GOptr, cJSON_String_t *strPtr)
{
    if (GOptr->type == String)
    {
        *strPtr = AS_STRING(GOptr);
        return cJSON_Ok;
    }
    
    return cJSON_Datatype_Error;
}
cJSON_Result_t cJSON_tryGetIntPtr(cJSON_Generic_t *GOptr, cJSON_Int_t **intValPtr)
{
    if (GOptr->type == Integer)
    {
        *intValPtr = AS_INT_PTR(GOptr);
        return cJSON_Ok;
    }
    
    return cJSON_Datatype_Error;
}
cJSON_Result_t cJSON_tryGetFloatPtr(cJSON_Generic_t *GOptr, cJSON_Float_t **floatValPtr)
{
    if (GOptr->type == Float)
    {
        *floatValPtr = AS_FLOAT_PTR(GOptr);
        return cJSON_Ok;
    }
    
    return cJSON_Datatype_Error;
}
cJSON_Result_t cJSON_tryGetBoolPtr(cJSON_Generic_t *GOptr, cJSON_Bool_t **boolValPtr)
{
    if (GOptr->type == Boolean)
    {
        *boolValPtr = AS_BOOL_PTR(GOptr);
        return cJSON_Ok;
    }
    
    return cJSON_Datatype_Error;
}

#pragma endregion

// - Analytical Functions
#pragma region Analytical Functions

cJSON_Result_t cJSON_getType(cJSON_Generic_t *GOptr, cJSON_DataType_t *dataType)
{
    *dataType = GOptr->type;
    return cJSON_Ok;
}

#pragma endregion
