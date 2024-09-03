/**
 * @file cJSON.h
 * @author HeCoding180
 * @brief cJSON library c header file
 * @version 0.1.0
 * @date 2024-08-10
 */

#ifndef CJSON_DEFINED
#define CJSON_DEFINED

#include <string.h>

#include "cJSON_Constants.h"
#include "cJSON_GenericStack.h"
#include "cJSON_Types.h"

//   ---   Function Prototypes   ---

// - Structural Functions -
#pragma region Structural Functions

/**
 * @brief   Function used to try and append a generic object to a dictionary in a generic object.
 * 
 * @param   GObjPtr 
 * @param   key Key string.
 * @param   valObj Value cJSON generic object.
 * @return  cJSON_Result_t Returns the result of this operation. Can be one of the following: cJSON_Ok, cJSON_Datatype_Error
 */
cJSON_Result_t cJSON_tryAppendToDict(cJSON_Generic_t *GObjPtr, const cJSON_Key_t key, cJSON_Generic_t valObj);
/**
 * @brief   Function used to try and append a generic object to a list in a generic object.
 * 
 * @param   GObjPtr 
 * @param   obj 
 * @return  cJSON_Result_t Returns the result of this operation. Can be one of the following: cJSON_Ok, cJSON_Datatype_Error 
 */
cJSON_Result_t cJSON_tryAppendToList(cJSON_Generic_t *GObjPtr, cJSON_Generic_t obj);

/**
 * @brief   Function that deletes a generic object together with all of its children (recursive).
 * @param   GObj cJSON_Generic_t object that is to be deleted.
 * @return  cJSON_Result_t deletion result.
 */
cJSON_Result_t cJSON_delGenObj(cJSON_Generic_t GObj);

#pragma endregion

// - Parser Function -
#pragma region Parser Function

/**
 * @brief   cJSON parser functon. Function used to retrieve and build a cJSON structure from a string (str).
 * 
 * @param   GOptr cJSON_Generic pointer, where the parsed structure will be saved in.
 * @param   str String containing the JSON data.
 * @return  cJSON_Result_t Returns cJSON_Ok by default. Can return one of the following errors: cJSON_DepthOutOfRange_Error, cJSON_Structure_Error, cJSON_InvalidCharacterSequence_Error.
 */
cJSON_Result_t cJSON_parseStr(cJSON_Generic_t *GObjPtr, const char *str);

#pragma endregion

// - Getter Functions -
#pragma region Getter Functions

/**
 * @brief   Function used to try and retrieve the dictionary object stored in GObj's dataContainer.
 * 
 * @param   GObj cJSON_Generic_t object.
 * @param   dict Pointer to a user variable, where the dictionary's contents are to be stored.
 * @return  cJSON_Result_t Returns cJSON_Ok by default. Returns cJSON_Datatype_Error if the GObj's type isn't a dictionary.
 */
cJSON_Result_t cJSON_tryGetDict(cJSON_Generic_t GObj, cJSON_Dict_t *dict);
/**
 * @brief   Function used to try and retrieve the list object stored in GObj's dataContainer.
 * 
 * @param   GObj cJSON_Generic_t object.
 * @param   list Pointer to a user variable, where the list's contents are to be stored.
 * @return  cJSON_Result_t Returns cJSON_Ok by default. Returns cJSON_Datatype_Error if the GObj's type isn't a list.
 */
cJSON_Result_t cJSON_tryGetList(cJSON_Generic_t GObj, cJSON_List_t *list);
/**
 * @brief   Function used to try and retrieve the string stored in GObj's dataContainer.
 * 
 * @param   GObj cJSON_Generic_t object.
 * @param   str Pointer to a user variable, where the string's contents are to be stored.
 * @return  cJSON_Result_t Returns cJSON_Ok by default. Returns cJSON_Datatype_Error if the GObj's type isn't a string.
 */
cJSON_Result_t cJSON_tryGetString(cJSON_Generic_t GObj, cJSON_String_t *str);
/**
 * @brief   Function used to try and retrieve the integer stored in GObj's dataContainer.
 * 
 * @param   GObj cJSON_Generic_t object.
 * @param   intVal Pointer to a user variable, where the integer value is to be stored.
 * @return  cJSON_Result_t Returns cJSON_Ok by default. Returns cJSON_Datatype_Error if the GObj's type isn't a integer.
 */
cJSON_Result_t cJSON_tryGetInt(cJSON_Generic_t GObj, cJSON_Int_t *intVal);
/**
 * @brief   Function used to try and retrieve the float stored in GObj's dataContainer.
 * 
 * @param   GObj cJSON_Generic_t object.
 * @param   floatVal Pointer to a user variable, where the float value is to be stored.
 * @return  cJSON_Result_t Returns cJSON_Ok by default. Returns cJSON_Datatype_Error if the GObj's type isn't a float.
 */
cJSON_Result_t cJSON_tryGetFloat(cJSON_Generic_t GObj, cJSON_Float_t *floatVal);
/**
 * @brief   Function used to try and retrieve the boolean stored in GObj's dataContainer.
 * 
 * @param   GObj cJSON_Generic_t object.
 * @param   boolVal Pointer to a user variable, where the boolean value is to be stored.
 * @return  cJSON_Result_t Returns cJSON_Ok by default. Returns cJSON_Datatype_Error if the GObj's type isn't a boolean.
 */
cJSON_Result_t cJSON_tryGetBool(cJSON_Generic_t GObj, cJSON_Bool_t *boolVal);

#pragma endregion

// - Pointer Getter Functions
#pragma region Pointer Getter Functions

/**
 * @brief 
 * 
 * @param GObj cJSON_Generic_t object.
 * @param dictPtr Pointer to a user pointer variable, where the pointer to the dictionary is to be stored.
 * @return cJSON_Result_t Returns cJSON_Ok by default. Returns cJSON_Datatype_Error if the GObj's type isn't a dictionary.
 */
cJSON_Result_t cJSON_tryGetDictPtr(cJSON_Generic_t GObj, cJSON_Dict_t **dictPtr);
/**
 * @brief 
 * 
 * @param GObj cJSON_Generic_t object.
 * @param listPtr Pointer to a user pointer variable, where the pointer to the list is to be stored.
 * @return cJSON_Result_t Returns cJSON_Ok by default. Returns cJSON_Datatype_Error if the GObj's type isn't a list.
 */
cJSON_Result_t cJSON_tryGetListPtr(cJSON_Generic_t GObj, cJSON_List_t **listPtr);
/**
 * @brief 
 * 
 * @param GObj cJSON_Generic_t object.
 * @param strPtr Pointer to a user pointer variable, where the pointer to the string is to be stored.
 * @return cJSON_Result_t Returns cJSON_Ok by default. Returns cJSON_Datatype_Error if the GObj's type isn't a string.
 */
cJSON_Result_t cJSON_tryGetStringPtr(cJSON_Generic_t GObj, cJSON_String_t *strPtr);
/**
 * @brief 
 * 
 * @param GObj cJSON_Generic_t object.
 * @param intValPtr Pointer to a user pointer variable, where the pointer to the integer is to be stored.
 * @return cJSON_Result_t Returns cJSON_Ok by default. Returns cJSON_Datatype_Error if the GObj's type isn't a integer.
 */
cJSON_Result_t cJSON_tryGetIntPtr(cJSON_Generic_t GObj, cJSON_Int_t **intValPtr);
/**
 * @brief 
 * 
 * @param GObj cJSON_Generic_t object.
 * @param floatValPtr Pointer to a user pointer variable, where the pointer to the float is to be stored.
 * @return cJSON_Result_t Returns cJSON_Ok by default. Returns cJSON_Datatype_Error if the GObj's type isn't a float.
 */
cJSON_Result_t cJSON_tryGetFloatPtr(cJSON_Generic_t GObj, cJSON_Float_t **floatValPtr);
/**
 * @brief 
 * 
 * @param GObj cJSON_Generic_t object.
 * @param boolValPtr Pointer to a user pointer variable, where the pointer to the boolean is to be stored.
 * @return cJSON_Result_t Returns cJSON_Ok by default. Returns cJSON_Datatype_Error if the GObj's type isn't a boolean.
 */
cJSON_Result_t cJSON_tryGetBoolPtr(cJSON_Generic_t GObj, cJSON_Bool_t **boolValPtr);

#pragma endregion

// - Analytical Functions
#pragma region Analytical Functions

/**
 * @brief   Function used to get the data type of the data stored in GObj.
 * 
 * @param   GObj cJSON_Generic_t object.
 * @param   dataType Datatype of the container stored in GObj
 * @return  cJSON_Result_t Always returns cJSON_Ok.
 */
cJSON_Result_t cJSON_getType(cJSON_Generic_t GObj, cJSON_ContainerType_t *dataType);

/**
 * @brief   Function used to get the maximum depth relative to startDepth.
 * 
 * @param   GObj cJSON_Generic_t object.
 * @param   maxDepth Pointer to a variable, where the max depth will be stored in. If maxDepth is equal to the startDepth means that GObj does not have any child containers like dictionaries and/or lists.
 * @param   startDepth Relative start depth of for example the parent container's depth.
 * @return  cJSON_Result_t Returns the result of the function (Default: cJSON_Ok). Can return cJSON_DepthOutOfRange_Error if the maximum depth is reached.
 */
cJSON_Result_t cJSON_getRelDepth(cJSON_Generic_t GObj, cJSON_depth_t *maxDepth, cJSON_depth_t startDepth);

/**
 * @brief   Returns the absolute depth of the structure stored in GObj. This function does not consider parent containers! This function does the same as cJSON_getRelDepth(GObj, maxDepth, 0).
 * 
 * @param   GObj cJSON_Generic_t object.
 * @param   maxDepth Pointer to a variable, where the max depth will be stored in. A maxDepth of 0 means that GObj does not have any child containers like dictionaries and/or lists.
 * @return  cJSON_Result_t Returns the result of the function (Default: cJSON_Ok). Can return cJSON_DepthOutOfRange_Error if the maximum depth is reached.
 */
cJSON_Result_t cJSON_getAbsDepth(cJSON_Generic_t GObj, cJSON_depth_t *maxDepth);

#pragma endregion

#endif
