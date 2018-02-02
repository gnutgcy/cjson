/*
  Copyright (c) 2009-2017 Dave Gamble and cJSON contributors

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in
  all copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
  THE SOFTWARE.
*/

#include "cJSON.h"
#include <string.h>


unsigned int gcy_json_decode_arr(char* json_str, char* key, char* val, size_t val_sz)
{
    cJSON* json_root    = NULL;
    cJSON* json_item    = NULL;
    char*  json_arr_str = NULL;

    if (NULL == json_str)
    {
        return 1;
    }

    if (NULL == key)
    {
        return 2;
    }

    if (NULL == val)
    {
        return 3;
    }

    json_root = cJSON_Parse(json_str);
    if (NULL == json_root)
    {
        return 4;
    }

    json_item = cJSON_GetObjectItem(json_root, key);
    if (NULL == json_item)
    {
        cJSON_Delete(json_root);
        return 5;
    }

    if (cJSON_Array != json_item->type)
    {
        cJSON_Delete(json_root);
        return 6;
    }

    json_arr_str = cJSON_PrintUnformatted(json_item);
    cJSON_Delete(json_root);
    if (strlen(json_arr_str) + 1 > val_sz)
    {
        cJSON_free(json_arr_str);
        return 7;
    }

    (void)strcpy(val, json_arr_str);

    cJSON_free(json_arr_str);

    return 0;
}


unsigned int gcy_json_decode_str(char* json_str, char* key, char* val, size_t val_sz)
{
    cJSON* json_root = NULL;
    cJSON* json_item = NULL;

    if (NULL == json_str)
    {
        return 1;
    }

    if (NULL == key)
    {
        return 2;
    }

    if (NULL == val)
    {
        return 3;
    }

    json_root = cJSON_Parse(json_str);
    if (NULL == json_root)
    {
        return 4;
    }

    json_item = cJSON_GetObjectItem(json_root, key);
    if (NULL == json_item)
    {
        cJSON_Delete(json_root);
        return 5;
    }

    if (cJSON_String != json_item->type)
    {
        cJSON_Delete(json_root);
        return 6;
    }

    if (strlen(json_item->valuestring) + 1 > val_sz)
    {
        cJSON_Delete(json_root);
        return 7;
    }

    (void)strcpy(val, json_item->valuestring);

    cJSON_Delete(json_root);

    return 0;
}


unsigned int gcy_json_decode_int(char* json_str, char* key, int* val)
{
    cJSON* json_root = NULL;
    cJSON* json_item = NULL;

    if (NULL == json_str)
    {
        return 1;
    }

    if (NULL == key)
    {
        return 2;
    }

    if (NULL == val)
    {
        return 3;
    }

    json_root = cJSON_Parse(json_str);
    if (NULL == json_root)
    {
        return 4;
    }

    json_item = cJSON_GetObjectItem(json_root, key);
    if (NULL == json_item)
    {
        cJSON_Delete(json_root);
        return 5;
    }

    if (cJSON_Number != json_item->type)
    {
        cJSON_Delete(json_root);
        return 6;
    }

    *val = json_item->valueint;

    cJSON_Delete(json_root);

    return 0;
}

