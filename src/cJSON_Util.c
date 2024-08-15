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
