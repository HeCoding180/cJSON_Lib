/**
 * @file cJSON.h
 * @author HeCoding180
 * @brief cJSON library c header file
 * @version 0.1
 * @date 2024-08-10
 */

#include <inttypes.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

//   ---   Constants   ---
#pragma region Constants



#pragma endregion



//   ---   Macros   ---

// - Type Casting Macros -
#pragma region Type Casting Macros

/**
 * @brief   Returns a pointer of type cJSON_Dict_t, pointing to the dataContainer of obj. Use with care!
 * @param   obj cJSON_Generic_t pointer.
 */
#define AS_DICT_PTR(obj) ((cJSON_Dict_t*)((obj)->dataContainer))
/**
 * @brief   Returns the reference of the cJSON_Dict_t object stored in the dataContainer of obj. Use with care!
 * @param   obj cJSON_Generic_t pointer.
 */
#define AS_DICT(obj) (*AS_DICT_PTR(obj))
/**
 * @brief   Returns a pointer of type cJSON_List_t, pointing to the dataContainer of obj. Use with care!
 * @param   obj cJSON_Generic_t pointer.
 */
#define AS_LIST_PTR(obj) ((cJSON_List_t*)((obj)->dataContainer))
/**
 * @brief   Returns the reference of the cJSON_List_t object stored in the dataContainer of obj. Use with care!
 * @param   obj cJSON_Generic_t pointer.
 */
#define AS_LIST(obj) (*AS_LIST_PTR(obj))
/**
 * @brief   Returns obj->dataContainer as a cJSON_String_t. Use with care!
 * @param   obj cJSON_Generic_t pointer.
 */
#define AS_STRING(obj) ((cJSON_String_t)((obj)->dataContainer))
/**
 * @brief   Returns obj->dataContainer as a cJSON_Int_t pointer. Use with care!
 * @param   obj cJSON_Generic_t pointer.
 */
#define AS_INT_PTR(obj) ((cJSON_Int_t*)((obj)->dataContainer))
/**
 * @brief   Returns obj->dataContainer as a cJSON_Int_t. Use with care!
 * @param   obj cJSON_Generic_t pointer.
 */
#define AS_INT(obj) (*AS_INT_PTR(obj))
/**
 * @brief   Returns obj->dataContainer as a cJSON_Float_t pointer. Use with care!
 * @param   obj cJSON_Generic_t pointer.
 */
#define AS_FLOAT_PTR(obj) ((cJSON_Float_t*)((obj)->dataContainer))
/**
 * @brief   Returns obj->dataContainer as a cJSON_Float_t. Use with care!
 * @param   obj cJSON_Generic_t pointer.
 */
#define AS_FLOAT(obj) (*AS_FLOAT_PTR(obj))
/**
 * @brief   Returns obj->dataContainer as a cJSON_Bool_t. Use with care!
 * @param   obj cJSON_Generic_t pointer.
 */
#define AS_BOOL_PTR(obj) ((cJSON_Bool_t*)((obj)->dataContainer))
/**
 * @brief   Returns obj->dataContainer as a cJSON_Bool_t. Use with care!
 * @param   obj cJSON_Generic_t pointer.
 */
#define AS_BOOL(obj) (*AS_BOOL_PTR(obj))

#pragma endregion



//   ---   Typedefs   ---

// Basic Typedefs
#pragma region Basic Typedefs

/**
 * @brief   Type defining the data type of the "size" value contained in cJSON data container structs.
 * 
 */
typedef uint32_t cJSON_object_size_size_t;

/**
 * @brief   Type defining the data type for string values saved in any cJSON data container structs as well as the array of keys used in dictionaries.
 * 
 */
typedef char* cJSON_String_t;

/**
 * @brief   Type defining the data type for integer values saved in any cJSON data container structs.
 * 
 */
typedef int32_t cJSON_Int_t;

/**
 * @brief   Type defining the data type for floating point values saved in any cJSON data container structs.
 * 
 */
typedef float cJSON_Float_t;

/**
 * @brief   Type defining the data type for floating point values saved in any cJSON data container structs.
 * 
 */
typedef bool cJSON_Bool_t;

#pragma endregion

// Enum Typedefs
#pragma region Enum Typedefs

/**
 * @brief   cJSON data container structure type.
 * 
 */
typedef enum cJSON_DataType
{
    Null = 0,
    Dictionary,
    List,
    String,
    Integer,
    Float,
    Boolean
} cJSON_DataType_t;

typedef enum cJSON_Result
{
    cJSON_Ok,
    cJSON_Datatype_Error,
    cJSON_Structure_Error,
    cJSON_Not_Allocated_Error,
    cJSON_Unknown_Error
} cJSON_Result_t;

#pragma endregion

// Struct Typedefs
#pragma region Struct Typedefs

/**
 * @brief   Generic JSON object. Used to link data containers or values to lists or dictionaries they are contained in.
 * 
 */
typedef struct cJSON_Generic
{
    cJSON_DataType_t type;
    void *dataContainer;
} cJSON_Generic_t;

/**
 * @brief   cJSON data structure for a list object.
 * 
 */
typedef struct cJSON_List
{
    cJSON_object_size_size_t length;
    cJSON_Generic_t *data;
} cJSON_List_t;

/**
 * @brief   cJSON dictionary key type.
 * 
 */
typedef cJSON_String_t cJSON_Key;

/**
 * @brief   cJSON data container for a dictionary object.
 * 
 */
typedef struct cJSON_Dict
{
    cJSON_object_size_size_t length;
    cJSON_Key *keyData;
    cJSON_Generic_t *valueData;
} cJSON_Dict_t;

#pragma endregion



//   ---   Public Function Prototypes   ---

// - Structure Modification Functions -
#pragma region Structure Modification Functions

/**
 * @brief   Function that deletes a generic object together with all of its children (recursive).
 * @param   GOptr Pointer to the cJSON_Generic_t object that is to be deleted.
 * @return  cJSON_Result_t deletion result.
 */
cJSON_Result_t cJSON_delGenObj(cJSON_Generic_t *GOptr);

#pragma endregion

// - Getter Functions -
#pragma region Getter Functions

/**
 * @brief   Function used to try and retrieve the dictionary object stored in GOptr's dataContainer.
 * 
 * @param   GOptr Pointer to a cJSON_Generic_t object.
 * @param   dict Pointer to a user variable, where the dictionary's contents are to be stored.
 * @return  cJSON_Result_t Returns cJSON_Ok by default. Returns cJSON_Datatype_Error if the GOptr's type isn't a dictionary.
 */
cJSON_Result_t cJSON_tryGetDict(cJSON_Generic_t *GOptr, cJSON_Dict_t *dict);
/**
 * @brief   Function used to try and retrieve the list object stored in GOptr's dataContainer.
 * 
 * @param   GOptr Pointer to a cJSON_Generic_t object.
 * @param   list Pointer to a user variable, where the list's contents are to be stored.
 * @return  cJSON_Result_t Returns cJSON_Ok by default. Returns cJSON_Datatype_Error if the GOptr's type isn't a list.
 */
cJSON_Result_t cJSON_tryGetList(cJSON_Generic_t *GOptr, cJSON_List_t *list);
/**
 * @brief   Function used to try and retrieve the string stored in GOptr's dataContainer.
 * 
 * @param   GOptr Pointer to a cJSON_Generic_t object.
 * @param   str Pointer to a user variable, where the strings's contents are to be stored.
 * @return  cJSON_Result_t Returns cJSON_Ok by default. Returns cJSON_Datatype_Error if the GOptr's type isn't a string.
 */
cJSON_Result_t cJSON_tryGetString(cJSON_Generic_t *GOptr, cJSON_String_t *str);
/**
 * @brief   Function used to try and retrieve the integer stored in GOptr's dataContainer.
 * 
 * @param   GOptr Pointer to a cJSON_Generic_t object.
 * @param   intVal Pointer to a user variable, where the integer value is to be stored.
 * @return  cJSON_Result_t Returns cJSON_Ok by default. Returns cJSON_Datatype_Error if the GOptr's type isn't a integer.
 */
cJSON_Result_t cJSON_tryGetInt(cJSON_Generic_t *GOptr, cJSON_Int_t *intVal);
/**
 * @brief   Function used to try and retrieve the float stored in GOptr's dataContainer.
 * 
 * @param   GOptr Pointer to a cJSON_Generic_t object.
 * @param   floatVal Pointer to a user variable, where the float value is to be stored.
 * @return  cJSON_Result_t Returns cJSON_Ok by default. Returns cJSON_Datatype_Error if the GOptr's type isn't a float.
 */
cJSON_Result_t cJSON_tryGetFloat(cJSON_Generic_t *GOptr, cJSON_Float_t *floatVal);
/**
 * @brief   Function used to try and retrieve the boolean stored in GOptr's dataContainer.
 * 
 * @param   GOptr Pointer to a cJSON_Generic_t object.
 * @param   boolVal Pointer to a user variable, where the boolean value is to be stored.
 * @return  cJSON_Result_t Returns cJSON_Ok by default. Returns cJSON_Datatype_Error if the GOptr's type isn't a boolean.
 */
cJSON_Result_t cJSON_tryGetBool(cJSON_Generic_t *GOptr, cJSON_Bool_t *boolVal);

#pragma endregion

// - Pointer Getter Functions
#pragma region Pointer Getter Functions

/**
 * @brief 
 * 
 * @param GOptr Pointer to a cJSON_Generic_t object.
 * @param dictPtr 
 * @return cJSON_Result_t Returns cJSON_Ok by default. Returns cJSON_Datatype_Error if the GOptr's type isn't a dictionary.
 */
cJSON_Result_t cJSON_tryGetDictPtr(cJSON_Generic_t *GOptr, cJSON_Dict_t **dictPtr);
/**
 * @brief 
 * 
 * @param GOptr Pointer to a cJSON_Generic_t object.
 * @param listPtr 
 * @return cJSON_Result_t Returns cJSON_Ok by default. Returns cJSON_Datatype_Error if the GOptr's type isn't a list.
 */
cJSON_Result_t cJSON_tryGetListPtr(cJSON_Generic_t *GOptr, cJSON_List_t **listPtr);
/**
 * @brief 
 * 
 * @param GOptr Pointer to a cJSON_Generic_t object.
 * @param strPtr 
 * @return cJSON_Result_t Returns cJSON_Ok by default. Returns cJSON_Datatype_Error if the GOptr's type isn't a string.
 */
cJSON_Result_t cJSON_tryGetStringPtr(cJSON_Generic_t *GOptr, cJSON_String_t *strPtr);
/**
 * @brief 
 * 
 * @param GOptr Pointer to a cJSON_Generic_t object.
 * @param intValPtr 
 * @return cJSON_Result_t Returns cJSON_Ok by default. Returns cJSON_Datatype_Error if the GOptr's type isn't a integer.
 */
cJSON_Result_t cJSON_tryGetIntPtr(cJSON_Generic_t *GOptr, cJSON_Int_t **intValPtr);
/**
 * @brief 
 * 
 * @param GOptr Pointer to a cJSON_Generic_t object.
 * @param floatValPtr 
 * @return cJSON_Result_t Returns cJSON_Ok by default. Returns cJSON_Datatype_Error if the GOptr's type isn't a float.
 */
cJSON_Result_t cJSON_tryGetFloatPtr(cJSON_Generic_t *GOptr, cJSON_Float_t **floatValPtr);
/**
 * @brief 
 * 
 * @param GOptr Pointer to a cJSON_Generic_t object.
 * @param boolValPtr 
 * @return cJSON_Result_t Returns cJSON_Ok by default. Returns cJSON_Datatype_Error if the GOptr's type isn't a boolean.
 */
cJSON_Result_t cJSON_tryGetBoolPtr(cJSON_Generic_t *GOptr, cJSON_Bool_t **boolValPtr);

#pragma endregion

// - Analytical Functions
#pragma region Analytical Functions

/**
 * @brief   Function used to get the data type of the data stored in GOptr.
 * 
 * @param   GOptr Pointer to a cJSON_Generic_t object.
 * @param   dataType 
 * @return  cJSON_Result_t 
 */
cJSON_Result_t cJSON_getType(cJSON_Generic_t *GOptr, cJSON_DataType_t *dataType);

#pragma endregion
