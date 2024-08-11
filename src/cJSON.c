/**
 * @file cJSON.c
 * @author HeCoding180
 * @brief cJSON library c source file
 * @version 0.1
 * @date 2024-08-10
 * 
 */

#include "../inc/cJSON.h"

//   ---   Private Function Prototypes   ---

/**
 * @brief   Function that allocates the required memory for a cJSON_Generic_t object together with its specified data container specified in the containerType parameter.
 * @param   containerType Specifies the type of the object stored in the generic object.
 * @return  Returns the memory address of a newly allocated cJSON_Generic_t already containing the type and pointer to the object of the specified type.
 */
cJSON_Generic_t *cJSON_mallocGenObj(cJSON_DataType_t containerType);

//   ---   Private Function Implementations   ---

cJSON_Generic_t *cJSON_mallocGenObj(cJSON_DataType_t containerType)
{
    cJSON_Generic_t *genObj = (cJSON_Generic_t *)malloc(sizeof(cJSON_Generic_t));

    genObj->type = containerType;

    size_t containerSize;

    // Select container pointer size
    switch(containerType)
    {
    case Null:
        genObj->dataStruct = NULL;
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
    genObj->dataStruct = malloc(containerSize);
    
    // Set allocated memory to 0
    if (genObj->dataStruct != NULL) memset(genObj->dataStruct, 0, containerSize);
    
    return genObj;
}

//   ---   Public Function Implementations   ---

cJSON_Result_t cJSON_delGenObj(cJSON_Generic_t *GOptr)
{
    // Check if object is already deleted.
    if (GOptr->dataStruct != NULL)
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
            free(GOptr->dataStruct);
            break;
        case List:
            for (cJSON_object_size_size_t i = 0; i < AS_LIST_PTR(GOptr)->length; i++)
            {
                // Delete the cJSON_Generic_t object stored at index i
                cJSON_delGenObj(&(AS_LIST_PTR(GOptr)->data[i]));
            }

            // Free the memory of the data container itself.
            free(GOptr->dataStruct);
            break;
        default:
            // Remaining types: Null, String, Integer, Float, Boolean.
            // Free memory of the value.
            free(GOptr->dataStruct);
            break;
        }
    }
}
