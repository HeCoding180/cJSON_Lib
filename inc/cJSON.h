/**
 * @file cJSON.h
 * @author HeCoding180
 * @brief cJSON library c header file
 * @version 0.1
 * @date 2024-08-10
 */

#include <inttypes.h>
#include <stdbool.h>

//   ---   Defines   ---


//   ---   Typedefs   ---

// Basic Typedefs

/**
 * @brief Type defining the data type of the "size" value contained in cJSON data container structs.
 * 
 */
typedef uint32_t cJSON_object_size_t;

/**
 * @brief Type defining the data type for integer values saved in any cJSON data container structs.
 * 
 */
typedef int32_t cJSON_Int_t;

/**
 * @brief Type defining the data type for floating point values saved in any cJSON data container structs.
 * 
 */
typedef float cJSON_Float_t;

/**
 * @brief Type defining the data type for floating point values saved in any cJSON data container structs.
 * 
 */
typedef bool cJSON_Bool_t;

// Enum Typedefs

/**
 * @brief cJSON data container structure type.
 * 
 */
typedef enum cJSON_DataType
{
    Dictionary,
    List,
    String,
    Integer,
    Float
} cJSON_DataType_t;

typedef enum cJSON_Result
{
    cJSON_Ok,
    cJSON_Datatype_Error,
    cJSON_Structure_Error,
    cJSON_Unknown_Error
} cJSON_Result_t;

// Struct Typedefs

/**
 * @brief cJSON generic data structure. Used to link values or list items to other data containers or values.
 * 
 */
typedef struct cJSON_Generic
{
    cJSON_DataType_t type;
    void *dataStruct;
} cJSON_Generic_t;

/**
 * @brief cJSON data structure for a string object
 * 
 */
typedef struct cJSON_String
{
    uint32_t length;
    char *data;
} cJSON_String_t;

/**
 * @brief cJSON data structure for a list object
 * 
 */
typedef struct cJSON_List
{
    uint32_t length;
    cJSON_Generic_t *data;
} cJSON_List_t;

/**
 * @brief cJSON dictionary key type.
 * 
 */
typedef cJSON_String_t cJSON_Key;

/**
 * @brief cJSON data container for a dictionary object
 * 
 */
typedef struct cJSON_Dict
{
    uint32_t length;
    cJSON_Key *keyData;
    cJSON_Generic_t *valueData;
} cJSON_Dict_t;

//   ---   Function Prototypes   ---
