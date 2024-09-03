/**
 * @file cJSON_Util.c
 * @author HeCoding180
 * @brief cJSON library utility source file. Contains function implementations for utility functions that are not needed by the user.
 * @version 0.1.0
 * @date 2024-08-15
 * 
 */

#include "../inc/cJSON_Util.h"

//   ---   Function Implementations   ---

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
    case NullType:
        genObj.dataContainer = NULL;
        return genObj;
    case Dictionary:
        containerSize = sizeof(cJSON_Dict_t);
        break;
    case List:
        containerSize = sizeof(cJSON_List_t);
        break;
    case String:
        // Return object, no memory needs to be allocated, since a string is a pointer of itself and can be stored in the generic object on its own
        return genObj;
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

// - Structural Functions -
#pragma region Structural Functions

void cJSON_appendToDict(cJSON_Dict_t *dictPtr, const cJSON_Key_t key, cJSON_Generic_t valObj)
{
    if (dictPtr->length > 0)
    {
        dictPtr->keyData = (cJSON_Key_t*)realloc(dictPtr->keyData, (1 + dictPtr->length) * sizeof(cJSON_Key_t));
        dictPtr->valueData = (cJSON_Generic_t*)realloc(dictPtr->valueData, (1 + dictPtr->length) * sizeof(cJSON_Generic_t));
    }
    else
    {
        dictPtr->keyData = (cJSON_Key_t*)malloc(sizeof(cJSON_Key_t));
        dictPtr->valueData = (cJSON_Generic_t*)malloc(sizeof(cJSON_Generic_t));
    }

    // Allocate memory for key string and store key
    dictPtr->keyData[dictPtr->length] = (cJSON_Key_t)malloc(1 + strlen(key));
    strcpy(dictPtr->keyData[dictPtr->length], key);

    // Store value object
    dictPtr->valueData[dictPtr->length] = valObj;

    // Update length
    dictPtr->length++;
}
void cJSON_appendToList(cJSON_List_t *listPtr, cJSON_Generic_t obj)
{
    if (listPtr->length > 0)
    {
        listPtr->data = (cJSON_Generic_t*)realloc(listPtr->data, (1 + listPtr->length) * sizeof(cJSON_Generic_t));
    }
    else
    {
        listPtr->data = (cJSON_Generic_t*)malloc(sizeof(cJSON_Generic_t));
    }

    // Store object in list
    listPtr->data[listPtr->length] = obj;

    // Update length
    listPtr->length++;
}

#pragma endregion
