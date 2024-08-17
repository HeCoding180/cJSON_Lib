/**
 * @file cJSON_Parser.h
 * @author HeCoding180
 * @brief cJSON library parser header file.
 * @version 0.1
 * @date 2024-08-16
 * 
 */

#ifndef CJSON_PARSER_DEFINED
#define CJSON_PARSER_DEFINED

#include "cJSON_Types.h"

//   ---   Parser Function Prototype   ---

/**
 * @brief   cJSON parser functon. Function used to retrieve and build a cJSON structure from a string (str).
 * 
 * @param   GOptr cJSON_Generic pointer, where the parsed structure will be saved in.
 * @param   str String containing the JSON data.
 * @return  cJSON_Result_t Returns cJSON_Ok by default. Can return the following errors: cJSON_Structure_Error, cJSON_DepthOutOfRange_Error.
 */
cJSON_Result_t cJSON_parseStr(cJSON_Generic_t *GObjPtr, char *str);

#endif
