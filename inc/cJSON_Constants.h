/**
 * @file cJSON_Constants.h
 * @author HeCoding180
 * @brief cJSON library constants header file.
 * @version 0.1.0
 * @date 2024-08-16
 * 
 */

#include "cJSON_Types.h"

/**
 * @brief   Highest possible depth that is allowed by the specified depth type (cJSON_depth_t)
 * 
 */
#define CJSON_MAX_DEPTH                 ((cJSON_depth_t) 0xFFFFFFFFFFFFFFFF)

/**
 * @brief   Maximum length of a string containing a number
 * 
 */
#define CJSON_MAX_NUM_LEN               32u

/**
 * @brief   Size of the cJSON parser StringBuilder's preBuffer. Max: 255U
 * 
 */
#define CJSON_PARSE_STRING_PB_SIZE      10U