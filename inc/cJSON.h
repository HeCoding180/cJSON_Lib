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

//   ---   Defines   ---


//   ---   Macros   ---

/**
 * @brief   Returns a pointer of type cJSON_Dict_t, pointing to the dataStruct of obj.
 * @param   obj cJSON_Generic_t pointer.
 */
#define AS_DICT_PTR(obj) ((cJSON_Dict_t*)((obj)->dataStruct))
/**
 * @brief   Returns a pointer of type cJSON_List_t, pointing to the dataStruct of obj.
 * @param   obj cJSON_Generic_t pointer.
 */
#define AS_LIST_PTR(obj) ((cJSON_List_t*)((obj)->dataStruct))
/**
 * @brief   Returns obj->dataStruct as a cJSON_String_t.
 * @param   obj cJSON_Generic_t pointer.
 */
#define AS_STRING(obj) ((cJSON_String_t)((obj)->dataStruct))
/**
 * @brief   Returns obj->dataStruct as a cJSON_Int_t.
 * @param   obj cJSON_Generic_t pointer.
 */
#define AS_INT(obj) (*((cJSON_Int_t*)((obj)->dataStruct)))
/**
 * @brief   Returns obj->dataStruct as a cJSON_Float_t.
 * @param   obj cJSON_Generic_t pointer.
 */
#define AS_FLOAT(obj) (*((cJSON_Float_t*)((obj)->dataStruct)))
/**
 * @brief   Returns obj->dataStruct as a cJSON_Bool_t.
 * @param   obj cJSON_Generic_t pointer.
 */
#define AS_BOOL(obj) (*((cJSON_Bool_t*)((obj)->dataStruct)))

//   ---   Typedefs   ---

// Basic Typedefs

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

// Enum Typedefs

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

// Struct Typedefs

/**
 * @brief   Generic JSON object. Used to link data containers or values to lists or dictionaries they are contained in.
 * 
 */
typedef struct cJSON_Generic
{
    cJSON_DataType_t type;
    void *dataStruct;
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

//   ---   Public Function Prototypes   ---

/**
 * @brief   Function that deletes a generic object together with all of its children (recursive).
 * @param   GOptr Pointer to the cJSON_Generic_t object that is to be deleted.
 * @return  cJSON_Result_t deletion result.
 */
cJSON_Result_t cJSON_delGenObj(cJSON_Generic_t *GOptr);
