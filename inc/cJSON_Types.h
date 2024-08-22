/**
 * @file cJSON_Types.h
 * @author HeCoding180
 * @brief cJSON library types header file. Contains macros and typedefs for types that are needed everywhere (base library cJSON.h/.c, cJSON_Util.h/.c as well as user header and source files).
 * @version 0.1
 * @date 2024-08-15
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#ifndef CJSON_TYPES_DEFINED
#define CJSON_TYPES_DEFINED

#include <stdbool.h>
#include <inttypes.h>

//   ---   Macros   ---

// - Type Casting Macros -
#pragma region Type Casting Macros

/**
 * @brief   Returns a pointer of type cJSON_Dict_t, pointing to the dataContainer of obj. Use with care!
 * @param   obj cJSON_Generic_t.
 */
#define AS_DICT_PTR(obj) ((cJSON_Dict_t*)((obj).dataContainer))
/**
 * @brief   Returns the reference of the cJSON_Dict_t object stored in the dataContainer of obj. Use with care!
 * @param   obj cJSON_Generic_t.
 */
#define AS_DICT(obj) (*AS_DICT_PTR(obj))
/**
 * @brief   Returns a pointer of type cJSON_List_t, pointing to the dataContainer of obj. Use with care!
 * @param   obj cJSON_Generic_t.
 */
#define AS_LIST_PTR(obj) ((cJSON_List_t*)((obj).dataContainer))
/**
 * @brief   Returns the reference of the cJSON_List_t object stored in the dataContainer of obj. Use with care!
 * @param   obj cJSON_Generic_t.
 */
#define AS_LIST(obj) (*AS_LIST_PTR(obj))
/**
 * @brief   Returns obj.dataContainer as a cJSON_String_t. Use with care!
 * @param   obj cJSON_Generic_t.
 */
#define AS_STRING(obj) ((cJSON_String_t)((obj).dataContainer))
/**
 * @brief   Returns obj.dataContainer as a cJSON_Int_t pointer. Use with care!
 * @param   obj cJSON_Generic_t.
 */
#define AS_INT_PTR(obj) ((cJSON_Int_t*)((obj).dataContainer))
/**
 * @brief   Returns obj.dataContainer as a cJSON_Int_t. Use with care!
 * @param   obj cJSON_Generic_t.
 */
#define AS_INT(obj) (*AS_INT_PTR(obj))
/**
 * @brief   Returns obj.dataContainer as a cJSON_Float_t pointer. Use with care!
 * @param   obj cJSON_Generic_t.
 */
#define AS_FLOAT_PTR(obj) ((cJSON_Float_t*)((obj).dataContainer))
/**
 * @brief   Returns obj.dataContainer as a cJSON_Float_t. Use with care!
 * @param   obj cJSON_Generic_t.
 */
#define AS_FLOAT(obj) (*AS_FLOAT_PTR(obj))
/**
 * @brief   Returns obj.dataContainer as a cJSON_Bool_t. Use with care!
 * @param   obj cJSON_Generic_t.
 */
#define AS_BOOL_PTR(obj) ((cJSON_Bool_t*)((obj).dataContainer))
/**
 * @brief   Returns obj.dataContainer as a cJSON_Bool_t. Use with care!
 * @param   obj cJSON_Generic_t.
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
 * @brief   Type used for variables which measure JSON structure depth.
 * 
 */
typedef uint8_t cJSON_depth_t;

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
    NullType = 0,
    Dictionary,
    List,
    String,
    Integer,
    Float,
    Boolean
} cJSON_ContainerType_t;

typedef enum cJSON_Result
{
    cJSON_Ok,
    cJSON_Datatype_Error,
    cJSON_DepthOutOfRange_Error,
    cJSON_InvalidCharacterSequence_Error,
    cJSON_NotAllocated_Error,
    cJSON_Structure_Error,
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
    cJSON_ContainerType_t type;
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
typedef cJSON_String_t cJSON_Key_t;

/**
 * @brief   cJSON data container for a dictionary object.
 * 
 */
typedef struct cJSON_Dict
{
    cJSON_object_size_size_t length;
    cJSON_Key_t *keyData;
    cJSON_Generic_t *valueData;
} cJSON_Dict_t;

#pragma endregion

#endif
