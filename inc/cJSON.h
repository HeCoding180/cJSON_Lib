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
 * @brief   cJSON data structure for a list object
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
 * @brief   cJSON data container for a dictionary object
 * 
 */
typedef struct cJSON_Dict
{
    cJSON_object_size_size_t length;
    cJSON_Key *keyData;
    cJSON_Generic_t *valueData;
} cJSON_Dict_t;

//   ---   Function Prototypes   ---

/**
 * @brief   Function that allocates the required memory for a cJSON_Generic_t object together with its specified data container specified in the containerType parameter.
 * @param   containerType Specifies the type of the object stored in the generic object.
 * @return  Returns the memory address of a newly allocated cJSON_Generic_t already containing the type and pointer to the object of the specified type.
 */
cJSON_Generic_t *cJSON_malloc_generic_object(cJSON_DataType_t containerType);


