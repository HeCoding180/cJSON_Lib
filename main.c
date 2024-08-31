#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Include cJSON Library
#include "inc/cJSON.h"

// - Testing Constant Variables -

// - Testing Function Prototypes -
cJSON_String_t readFileContents(const char* fileName);
void printBtcValue(const char* JSONstr);

int main()
{
    printf("cJSON library test script\n\n");

    // Get test type
    printf("   ---   Enter Test Type   ---\n");

    //printf("\"a\": Parse JSON string\n");
    //printf("\"A\": Parse JSON file\n");
    printf("\"b\": Bitcoin value from coinbase API's JSON string\n");           //https://api.coinbase.com/v2/prices/spot?currency=USD
    //printf("\"B\": Bitcoin value from coinbase API's JSON string (file)\n");    //https://api.coinbase.com/v2/prices/spot?currency=USD

    // Get test type
    char testType = getchar();
    // Discard remaining characters in input
    while (getchar() != '\n' && getchar() != EOF);

    switch(testType)
    {
    case 'a':
        printf("Test not implemented!\n");
        break;
    case 'A':
        printf("Test not implemented!\n");
        break;
    case 'b':;
        char JSON_BtcStr[100];

        // Get string
        printf("Enter string from bitcoin API:");
        fgets(JSON_BtcStr, 100, stdin);

        printBtcValue(JSON_BtcStr);
        break;
    case 'B':
        printf("Test not implemented!\n");
        break;
    default:
        printf("Invalid test type \"%c\"\n", testType);
        break;
    }

    return 0;
}

// - Testing Function Implementations -
cJSON_String_t readFileContents(const char* fileName)
{
    FILE *fPtr = fopen(fileName, "r");
    if (!fPtr) {
        perror("Failed to open file");
        return NULL;
    }

    // Seek to the end of the file to get the file size
    fseek(fPtr, 0, SEEK_END);
    long fileSize = ftell(fPtr);
    rewind(fPtr);

    // Allocate memory for the file content plus the null terminator
    cJSON_String_t buffer = (cJSON_String_t)malloc((fileSize + 1) * sizeof(char));
    if (!buffer) {
        perror("Failed to allocate memory");
        fclose(fPtr);
        return NULL;
    }

    // Read the file contents into the buffer
    size_t bytesRead = fread(buffer, sizeof(char), fileSize, fPtr);
    buffer[bytesRead] = '\0';  // Null-terminate the string

    // Clean up and return the buffer
    fclose(fPtr);
    return buffer;
}

void printBtcValue(const char* JSONstr)
{
    // Create empty cJSON generic container
    cJSON_Generic_t Base_cJSON_Tree = {0};

    // Parse string into variable
    cJSON_Result_t funcResult = cJSON_parseStr(&Base_cJSON_Tree, JSONstr);
    if (funcResult != cJSON_Ok)
    {
        printf("Parse failed with error code %d!\n", (int)funcResult);
        return;
    }

    printf("\nSuccessfully parsed string!\n");

    // Write base cJSON tree to relative cJSON tree
    cJSON_Generic_t Rel_cJSON_Tree = Base_cJSON_Tree;

    // Temporary dictionary object
    cJSON_Dict_t dictObj = {0};

    funcResult = cJSON_tryGetDict(Rel_cJSON_Tree, &dictObj);
    if (funcResult != cJSON_Ok)
    {
        printf("Base is not a dictionary!\n");
        return;
    }

    // Get generic object at "data" key
    for (int i = 0; i < dictObj.length; i++)
    {
        if (!strcmp(dictObj.keyData[i], "data"))
        {
            Rel_cJSON_Tree = dictObj.valueData[i];
            break;
        }
        else if (i == (dictObj.length - 1))
        {
            printf("Missing \"data\" key in dictionary!\n");
            return;
        }
    }

    funcResult = cJSON_tryGetDict(Rel_cJSON_Tree, &dictObj);
    if (funcResult != cJSON_Ok)
    {
        printf("Generic object at \"data\" key is not a dictionary!\n");
        return;
    }

    // Get generic object at "data" -> "amount" key
    for (int i = 0; i < dictObj.length; i++)
    {
        if (!strcmp(dictObj.keyData[i], "amount"))
        {
            Rel_cJSON_Tree = dictObj.valueData[i];
            break;
        }
        else if (i == (dictObj.length - 1))
        {
            printf("Missing \"amount\" key in dictionary!\n");
            return;
        }
    }

    cJSON_String_t btcStr;

    // Try get bitcoin amount string
    funcResult = cJSON_tryGetString(Rel_cJSON_Tree, &btcStr);
    if (funcResult != cJSON_Ok)
    {
        printf("Generic object at \"amount\" key is not a string!\n");
        return;
    }

    // Print bitcoin amount
    printf("Bicoin value in USD: $%s\n", btcStr);

    cJSON_delGenObj(Base_cJSON_Tree);
}
