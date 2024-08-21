/**
 * @file cJSON.c
 * @author HeCoding180
 * @brief cJSON library c source file.
 * @version 0.1
 * @date 2024-08-10
 * 
 */

#include "../inc/cJSON.h"
#include "../inc/cJSON_Parser_Util.h"
#include "../inc/cJSON_Util.h"

//   ---   Function Implementations   ---

// - Structural Functions -
#pragma region Structural Functions

cJSON_Result_t cJSON_tryAppendToDict(cJSON_Generic_t *GObjPtr, const cJSON_Key_t key, cJSON_Generic_t valObj)
{
    if (GObjPtr->type == Dictionary)
    {
        return cJSON_appendToDict(AS_DICT_PTR(*GObjPtr), key, valObj);
    }
    else
    {
        return cJSON_Datatype_Error;
    }
}
cJSON_Result_t cJSON_tryAppendToList(cJSON_Generic_t *GObjPtr, cJSON_Generic_t obj)
{
    if (GObjPtr->type == List)
    {
        return cJSON_appendToList(AS_LIST_PTR(*GObjPtr), obj);
    }
    else
    {
        return cJSON_Datatype_Error;
    }
}

cJSON_Result_t cJSON_delGenObj(cJSON_Generic_t GObj)
{
    // Check if object is already deleted.
    if (GObj.dataContainer != NULL)
    {
        switch(GObj.type)
        {
        case Dictionary:
            // Delete all cJSON_Generic_t objects and free the memory of all key strings stored in this cJSON_Dict_t object.
            for (cJSON_object_size_size_t i = 0; i < AS_DICT_PTR(GObj)->length; i++)
            {
                // Free the key string pointer (char**) stored at index i.
                free(AS_DICT_PTR(GObj)->keyData[i]);
                // Delete the cJSON_Generic_t object stored at index i.
                cJSON_delGenObj((AS_DICT_PTR(GObj)->valueData[i]));
            }

            // Free the memory of the key and value arrays.
            free(AS_DICT_PTR(GObj)->keyData);
            free(AS_DICT_PTR(GObj)->valueData);

            // Free the memory of the data container itself.
            free(GObj.dataContainer);
            break;
        case List:
            for (cJSON_object_size_size_t i = 0; i < AS_LIST_PTR(GObj)->length; i++)
            {
                // Delete the cJSON_Generic_t object stored at index i
                cJSON_delGenObj((AS_LIST_PTR(GObj)->data[i]));
            }

            // Free the memory of the data container itself.
            free(GObj.dataContainer);
            break;
        default:
            // Remaining types: Null, String, Integer, Float, Boolean.
            // Free memory of the value.
            free(GObj.dataContainer);
            break;
        }
    }
}

#pragma endregion

// - Parser Function -
#pragma region Parser Function

cJSON_Result_t cJSON_parseStr(cJSON_Generic_t *GObjPtr, const char *str)
{
    // Create object stack
    cJSON_GenericStack_t ObjectStack = GS_Create(CJSON_MAX_DEPTH);
    

    /*enum valueEnironmentType
    {
        None,
        StringValue,
        NumericValue
    } valEnvType;*/

    bool ObjectIsEmpty = true;

    // Loop through string's contents
    while (*str)
    {
        if (ObjectIsEmpty)
        {
            if (*str == '{')        *GObjPtr = mallocGenObj(Dictionary);
            else if (*str == '[')   *GObjPtr = mallocGenObj(List);
            else
            {
                // Skip invalid characters
                str++;
                continue;
            }

            GS_Push(&ObjectStack, *GObjPtr);
            ObjectIsEmpty = false;
        }
        else
        {
            switch (*str)
            {
            case ' ':   // Ignore space character
            case '\t':  // Ignore tab character
            case '\n':  // Ignore newline character
                break;
            case '{':
                // Start dictionary
                break;
            case '}':
                // End dictionary
                break;
            case '[':
                // Start list
                break;
            case ']':
                // End list
                break;
            case '"':
                break;
            case ':':
                break;
            case ',':
                // Next item
                break;
            default:
                // Unexpected character
                return cJSON_Structure_Error;
            }
        }

        // Handle next character
        str++;
    }

    // Delete object stack
    GS_Delete(&ObjectStack);
}

#pragma endregion

// - Data Container Getter Functions -
#pragma region Getter Functions

cJSON_Result_t cJSON_tryGetDict(cJSON_Generic_t GObj, cJSON_Dict_t *dict)
{
    if (GObj.type == Dictionary)
    {
        *dict = AS_DICT(GObj);
        return cJSON_Ok;
    }
    
    return cJSON_Datatype_Error;
}
cJSON_Result_t cJSON_tryGetList(cJSON_Generic_t GObj, cJSON_List_t *list)
{
    if (GObj.type == List)
    {
        *list = AS_LIST(GObj);
        return cJSON_Ok;
    }
    
    return cJSON_Datatype_Error;
}
cJSON_Result_t cJSON_tryGetString(cJSON_Generic_t GObj, cJSON_String_t *str)
{
    if (GObj.type == String)
    {
        if (*str != NULL) free(*str);
        *str = malloc(strlen(AS_STRING(GObj)) + 1);
        strcpy(*str, AS_STRING(GObj));
        return cJSON_Ok;
    }
    
    return cJSON_Datatype_Error;
}
cJSON_Result_t cJSON_tryGetInt(cJSON_Generic_t GObj, cJSON_Int_t *intVal)
{
    if (GObj.type == Integer)
    {
        *intVal = AS_INT(GObj);
        return cJSON_Ok;
    }
    
    return cJSON_Datatype_Error;
}
cJSON_Result_t cJSON_tryGetFloat(cJSON_Generic_t GObj, cJSON_Float_t *floatVal)
{
    if (GObj.type == Float)
    {
        *floatVal = AS_FLOAT(GObj);
        return cJSON_Ok;
    }
    
    return cJSON_Datatype_Error;
}
cJSON_Result_t cJSON_tryGetBool(cJSON_Generic_t GObj, cJSON_Bool_t *boolVal)
{
    if (GObj.type == Boolean)
    {
        *boolVal = AS_BOOL(GObj);
        return cJSON_Ok;
    }
    
    return cJSON_Datatype_Error;
}

#pragma endregion

// - Pointer Getter Functions -
#pragma region Pointer Getter Functions

cJSON_Result_t cJSON_tryGetDictPtr(cJSON_Generic_t GObj, cJSON_Dict_t **dictPtr)
{
    if (GObj.type == Dictionary)
    {
        *dictPtr = AS_DICT_PTR(GObj);
        return cJSON_Ok;
    }
    
    return cJSON_Datatype_Error;
}
cJSON_Result_t cJSON_tryGetListPtr(cJSON_Generic_t GObj, cJSON_List_t **listPtr)
{
    if (GObj.type == List)
    {
        *listPtr = AS_LIST_PTR(GObj);
        return cJSON_Ok;
    }
    
    return cJSON_Datatype_Error;
}
cJSON_Result_t cJSON_tryGetStringPtr(cJSON_Generic_t GObj, cJSON_String_t *strPtr)
{
    if (GObj.type == String)
    {
        *strPtr = AS_STRING(GObj);
        return cJSON_Ok;
    }
    
    return cJSON_Datatype_Error;
}
cJSON_Result_t cJSON_tryGetIntPtr(cJSON_Generic_t GObj, cJSON_Int_t **intValPtr)
{
    if (GObj.type == Integer)
    {
        *intValPtr = AS_INT_PTR(GObj);
        return cJSON_Ok;
    }
    
    return cJSON_Datatype_Error;
}
cJSON_Result_t cJSON_tryGetFloatPtr(cJSON_Generic_t GObj, cJSON_Float_t **floatValPtr)
{
    if (GObj.type == Float)
    {
        *floatValPtr = AS_FLOAT_PTR(GObj);
        return cJSON_Ok;
    }
    
    return cJSON_Datatype_Error;
}
cJSON_Result_t cJSON_tryGetBoolPtr(cJSON_Generic_t GObj, cJSON_Bool_t **boolValPtr)
{
    if (GObj.type == Boolean)
    {
        *boolValPtr = AS_BOOL_PTR(GObj);
        return cJSON_Ok;
    }
    
    return cJSON_Datatype_Error;
}

#pragma endregion

// - Analytical Functions -
#pragma region Analytical Functions

cJSON_Result_t cJSON_getType(cJSON_Generic_t GObj, cJSON_ContainerType_t *dataType)
{
    *dataType = GObj.type;
    return cJSON_Ok;
}

cJSON_Result_t cJSON_getRelDepth(cJSON_Generic_t GObj, cJSON_depth_t *maxDepth, cJSON_depth_t startDepth)
{
    switch(GObj.type)
    {
    case List:
        // Check if depth is still in range with this cJSON container
        if (startDepth < CJSON_MAX_DEPTH)
        {
            // Update current depth and maximum depth reached if current depth is higher than max depth.
            startDepth++;
            *maxDepth = MAX(*maxDepth, startDepth);

            for (cJSON_object_size_size_t i = 0; i < AS_LIST_PTR(GObj)->length; i++)
            {
                cJSON_Result_t relativeResult = cJSON_getRelDepth(AS_LIST_PTR(GObj)->data[i], maxDepth, startDepth);
                if (relativeResult != cJSON_Ok) return relativeResult;
            }

            return cJSON_Ok;
        }
        else return cJSON_DepthOutOfRange_Error;
    case Dictionary:
        // Check if depth is still in range with this cJSON container
        if (startDepth < CJSON_MAX_DEPTH)
        {
            // Update current depth and maximum depth reached if current depth is higher than max depth.
            startDepth++;
            *maxDepth = MAX(*maxDepth, startDepth);

            for (cJSON_object_size_size_t i = 0; i < AS_DICT_PTR(GObj)->length; i++)
            {
                cJSON_Result_t relativeResult = cJSON_getRelDepth(AS_DICT_PTR(GObj)->valueData[i], maxDepth, startDepth);
                if (relativeResult != cJSON_Ok) return relativeResult;
            }

            return cJSON_Ok;
        }
        else return cJSON_DepthOutOfRange_Error;
    default:
        *maxDepth = MAX(*maxDepth, startDepth);
        return cJSON_Ok;
    }
}

cJSON_Result_t cJSON_getAbsDepth(cJSON_Generic_t GObj, cJSON_depth_t *maxDepth)
{
    return cJSON_getRelDepth(GObj, maxDepth, 0);
}

#pragma endregion
