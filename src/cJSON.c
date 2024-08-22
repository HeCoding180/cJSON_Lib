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
        cJSON_appendToDict(AS_DICT_PTR(*GObjPtr), key, valObj);
        return cJSON_Ok;
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
        cJSON_appendToList(AS_LIST_PTR(*GObjPtr), obj);
        return cJSON_Ok;
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

    // Temporary storage
    // Active dictionary key temporary storage
    cJSON_Key_t activeKey;

    uint8_t pFlags = 0;

    // Loop through string's contents
    while (*str)
    {
        if (GS_IS_EMPTY(ObjectStack))
        {
            if (*str == '{')
            {
                *GObjPtr = mallocGenObj(Dictionary);
                pFlags = CJP_DICT_END_POSSIBLE | CJP_DICT_KEY_POSSIBLE;
            }
            else if (*str == '[')
            {
                *GObjPtr = mallocGenObj(List);
                pFlags = CJP_LIST_END_POSSIBLE | CJP_LIST_VALUE_POSSIBLE;
            }
            else
            {
                // Skip leading characters
                str++;
                continue;
            }

            GS_Push(&ObjectStack, *GObjPtr);
        }
        else
        {
            switch (LOWER_CASE_CHAR(*str))
            {
            case ' ':   // Ignore space character
            case '\t':  // Ignore tab character
            case '\n':  // Ignore newline character
                break;
            case '{':;
                // Start dictionary, allocate generic dictionary object
                cJSON_Generic_t dictObj;
                dictObj = mallocGenObj(Dictionary);

                // Check if start dictionary is possible
                if (pFlags & CJP_DICT_VALUE_POSSIBLE)
                {
                    cJSON_appendToDict(AS_DICT_PTR(GS_TOP(ObjectStack)), activeKey, dictObj);
                }
                else if (pFlags & CJP_LIST_VALUE_POSSIBLE)
                {
                    cJSON_appendToList(AS_LIST_PTR(GS_TOP(ObjectStack)), dictObj);
                }
                else
                {
                    // Dictionary at invalid location in structure, delete object stack, delete generic dictionary object and return error
                    GS_Delete(&ObjectStack);
                    cJSON_delGenObj(dictObj);
                    return cJSON_Structure_Error;
                }

                // Push dictionary object to stack, check if JSON structure is within depth range
                if (GS_Push(&ObjectStack, dictObj) != GS_Ok)
                {
                    // String's JSON structure depth is out of range, delete object stack and return error
                    GS_Delete(&ObjectStack);
                    return cJSON_DepthOutOfRange_Error;
                }

                // Update flags
                pFlags = CJP_DICT_END_POSSIBLE | CJP_DICT_KEY_POSSIBLE;
                break;
            case '}':
                // Check if end dictionary is possible
                if (pFlags & CJP_DICT_END_POSSIBLE)
                {
                    // End dictionary, remove generic dictionary object from stack
                    GS_Pop(&ObjectStack);

                    if (GS_IS_EMPTY(ObjectStack))
                    {
                        // Clear parser flags, stack is empty, parsing complete, wait for string terminator
                        pFlags = 0;
                    }
                    else if (GS_TOP(ObjectStack).type == Dictionary)
                    {
                        pFlags = CJP_DICT_END_POSSIBLE | CJP_ITEM_SEPT_POSSIBLE;
                    }
                    else
                    {
                        pFlags = CJP_LIST_END_POSSIBLE | CJP_ITEM_SEPT_POSSIBLE;
                    }
                }
                else
                {
                    // Dictionary end at invalid location, delete object stack and return error
                    GS_Delete(&ObjectStack);
                    return cJSON_Structure_Error;
                }
                break;
            case '[':;
                // Start list, allocate generic list object
                cJSON_Generic_t listObj;
                listObj = mallocGenObj(List);

                // Check if start list is possible
                if (pFlags & CJP_DICT_VALUE_POSSIBLE)
                {
                    cJSON_appendToDict(AS_DICT_PTR(GS_TOP(ObjectStack)), activeKey, listObj);
                }
                else if (pFlags & CJP_LIST_VALUE_POSSIBLE)
                {
                    cJSON_appendToList(AS_LIST_PTR(GS_TOP(ObjectStack)), listObj);
                }
                else
                {
                    // List at invalid location in structure, delete object stack, delete generic list object and return error
                    GS_Delete(&ObjectStack);
                    cJSON_delGenObj(listObj);
                    return cJSON_Structure_Error;
                }

                // Push list object to stack, check if JSON structure is within depth range
                if (GS_Push(&ObjectStack, listObj) != GS_Ok)
                {
                    // JSON structure depth is out of range, delete object stack and return error
                    GS_Delete(&ObjectStack);
                    return cJSON_DepthOutOfRange_Error;
                }

                // Update flags
                pFlags = CJP_DICT_END_POSSIBLE | CJP_DICT_KEY_POSSIBLE;
                break;
            case ']':
                // Check if end list is possible
                if (pFlags & CJP_DICT_END_POSSIBLE)
                {
                    // End list, remove generic list object from stack
                    GS_Pop(&ObjectStack);

                    if (GS_IS_EMPTY(ObjectStack))
                    {
                        // Clear parser flags, stack is empty, parsing complete, wait for string terminator
                        pFlags = 0;
                    }
                    else if (GS_TOP(ObjectStack).type == Dictionary)
                    {
                        pFlags = CJP_DICT_END_POSSIBLE | CJP_ITEM_SEPT_POSSIBLE;
                    }
                    else
                    {
                        pFlags = CJP_LIST_END_POSSIBLE | CJP_ITEM_SEPT_POSSIBLE;
                    }
                }
                break;
            case ',':
                // Item separator, check if allowed
                if (pFlags & CJP_ITEM_SEPT_POSSIBLE)
                {
                    // Item separator allowed, update flags
                    if (GS_TOP(ObjectStack).type == Dictionary)
                        pFlags = CJP_DICT_KEY_POSSIBLE;
                    else
                        pFlags = CJP_LIST_VALUE_POSSIBLE;
                }
                else
                {
                    // Item separator at invalid location detected, delete object stack and return error
                    GS_Delete(&ObjectStack);
                    return cJSON_Structure_Error;
                }
                break;
            case ':':
                // Dictionary key-value separator, check if allowed
                if (pFlags & CJP_DICT_SEPT_POSSIBLE)
                {
                    // Update parser flags
                    pFlags = CJP_DICT_VALUE_POSSIBLE;
                }
                else
                {
                    // Dictionary key-value separator at invalid location detected, delete object stack and return error
                    GS_Delete(&ObjectStack);
                    return cJSON_Structure_Error;
                }
                break;
            case '"':;
                // Start of string sequence
                cJSON_Result_t strBuilderResult;
                cJSON_Generic_t genericStrObj;

                // Check if string is possible
                if (pFlags & CJP_DICT_KEY_POSSIBLE)
                {
                    // String is a dictionary key, extract key string to activeKey variable
                    strBuilderResult = cJSON_Parser_StringBuilder(&str, &activeKey);
                    
                    pFlags = CJP_DICT_SEPT_POSSIBLE;
                }
                else if (pFlags & CJP_DICT_VALUE_POSSIBLE)
                {
                    // String is a dictionary value, extract string to generic object's data container
                    genericStrObj = mallocGenObj(String);
                    strBuilderResult = cJSON_Parser_StringBuilder(&str, (char**)(&(genericStrObj.dataContainer)));

                    cJSON_appendToDict(AS_DICT_PTR(GS_TOP(ObjectStack)), activeKey, genericStrObj);

                    pFlags = CJP_DICT_END_POSSIBLE | CJP_ITEM_SEPT_POSSIBLE;
                }
                else if (pFlags & CJP_LIST_VALUE_POSSIBLE)
                {
                    // String is a dictionary value, extract string to generic object's data container
                    genericStrObj = mallocGenObj(String);
                    strBuilderResult = cJSON_Parser_StringBuilder(&str, (char**)(&(genericStrObj.dataContainer)));

                    cJSON_appendToList(AS_LIST_PTR(GS_TOP(ObjectStack)), genericStrObj);

                    pFlags = CJP_LIST_END_POSSIBLE | CJP_ITEM_SEPT_POSSIBLE;
                }
                else
                {
                    // String at invalid location detected, delete object stack and return error
                    GS_Delete(&ObjectStack);
                    return cJSON_Structure_Error;
                }

                // Check if StringBuilder was successful
                if (strBuilderResult != cJSON_Ok)
                {
                    // StringBuilder exited unsuccessfully, delete object stack and return error
                    GS_Delete(&ObjectStack);
                    return strBuilderResult;
                }
                break;
            case '-':
            case '0':
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9':
                // Check if number is possible
                if (pFlags & CJP_DICT_VALUE_POSSIBLE)
                {
                    cJSON_appendToDict(AS_DICT_PTR(GS_TOP(ObjectStack)), activeKey, cJSON_Parser_NumParser(&str));

                    pFlags = CJP_DICT_END_POSSIBLE | CJP_ITEM_SEPT_POSSIBLE;
                }
                else if (pFlags & CJP_LIST_VALUE_POSSIBLE)
                {
                    // Top item in stack is a list, add null to list
                    cJSON_appendToList(AS_LIST_PTR(GS_TOP(ObjectStack)), cJSON_Parser_NumParser(&str));

                    pFlags = CJP_LIST_END_POSSIBLE | CJP_ITEM_SEPT_POSSIBLE;
                }
                else
                {
                    // Number at invalid location in structure, delete object stack and return error
                    GS_Delete(&ObjectStack);
                    return cJSON_Structure_Error;
                }
                break;
            case 't':;
            case 'f':;
                // Check if boolean is possible
                bool boolVal;
                cJSON_Generic_t boolObj;

                if ((LOWER_CASE_CHAR(*str) == 't')
                 && (LOWER_CASE_CHAR(*(str + 1)) == 'r')
                 && (LOWER_CASE_CHAR(*(str + 2)) == 'u')
                 && (LOWER_CASE_CHAR(*(str + 3)) == 'e'))
                {
                    // Bool value is "true", skip "true" character sequence, store result
                    str += 3;
                    boolVal = true;
                }
                else if ((LOWER_CASE_CHAR(*str) == 'f')
                      && (LOWER_CASE_CHAR(*(str + 1)) == 'a')
                      && (LOWER_CASE_CHAR(*(str + 2)) == 'l')
                      && (LOWER_CASE_CHAR(*(str + 3)) == 's')
                      && (LOWER_CASE_CHAR(*(str + 4)) == 'e'))
                {
                    // Bool value is "false", skip "false" character sequence, store result
                    str += 4;
                    boolVal = false;
                }
                else
                {
                    // Invalid character sequence, delete object stack and return error
                    GS_Delete(&ObjectStack);
                    return cJSON_InvalidCharacterSequence_Error;
                }

                // Create generic object from boolean
                boolObj = mallocGenObj(Boolean);
                AS_BOOL(boolObj) = boolVal;

                // Valid character sequence
                if (pFlags & CJP_DICT_VALUE_POSSIBLE)
                {
                    cJSON_appendToDict(AS_DICT_PTR(GS_TOP(ObjectStack)), activeKey, boolObj);

                    pFlags = CJP_DICT_END_POSSIBLE | CJP_ITEM_SEPT_POSSIBLE;
                }
                else if (pFlags & CJP_LIST_VALUE_POSSIBLE)
                {
                    cJSON_appendToList(AS_LIST_PTR(GS_TOP(ObjectStack)), boolObj);

                    pFlags = CJP_LIST_END_POSSIBLE | CJP_ITEM_SEPT_POSSIBLE;
                }
                else
                {
                    // Boolean at invalid location in structure, delete object stack, delete generic bool object and return error
                    GS_Delete(&ObjectStack);
                    cJSON_delGenObj(boolObj);
                    return cJSON_Structure_Error;
                }
                break;
            case 'n':
                // Extract null, check if whole string matches
                if ((LOWER_CASE_CHAR(*(str + 1)) == 'u') && (LOWER_CASE_CHAR(*(str + 2)) == 'l') && (LOWER_CASE_CHAR(*(str + 3)) == 'l'))
                {
                    // Skip null characters (3 + 1 at end of the while loop) (yes, 3 is correct)
                    str += 3;

                    if (pFlags & CJP_DICT_VALUE_POSSIBLE)
                    {
                        // Top item is a dictionary, add null to dictionary
                        cJSON_appendToDict(AS_DICT_PTR(GS_TOP(ObjectStack)), activeKey, mallocGenObj(NullType));

                        pFlags = CJP_DICT_END_POSSIBLE | CJP_ITEM_SEPT_POSSIBLE;
                    }
                    else if (pFlags & CJP_LIST_VALUE_POSSIBLE)
                    {
                        // Top item in stack is a list, add null to list
                        cJSON_appendToList(AS_LIST_PTR(GS_TOP(ObjectStack)), mallocGenObj(NullType));

                        pFlags = CJP_LIST_END_POSSIBLE | CJP_ITEM_SEPT_POSSIBLE;
                    }
                    else
                    {
                        // Null at invalid location in structure, delete object stack and return error
                        GS_Delete(&ObjectStack);
                        return cJSON_Structure_Error;
                    }
                }
                else
                {
                    // Invalid character sequence, delete object stack and return error
                    GS_Delete(&ObjectStack);
                    return cJSON_InvalidCharacterSequence_Error;
                }
                break;
            default:
                // Unknown character at current location detected, delete object stack and return error
                GS_Delete(&ObjectStack);
                return cJSON_Structure_Error;
            }
        }

        // Handle next character
        str++;
    }

    // Delete object stack
    GS_Delete(&ObjectStack);

    return cJSON_Ok;
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
