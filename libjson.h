#ifndef __LIB_JSON_H__
#define __LIB_JSON_H__

/**
 * @file libjson.h
 * @date 2018-06-11
 * 
 * A json library for handling a json data structure.
 * Inspired by Java's @c org.json .
 */

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdlib.h>

/*~ Data Structures ~*/

/**
 * The data type of a json value.
 */
typedef enum JSONType {
    object,  /**< {} */
    array,   /**< [] */
    boolean, /**< true/false */
    number,  /**< 3.14 */
    string,  /**< "" */
    null     /**< null */
} JSONType;

typedef struct JSONElement JSONElement;
typedef struct JSONPair JSONPair;

/**
 * A json object.
 * {}
 */ 
typedef struct JSONObject {
    JSONPair* elements;   /**< A sequence of key/value pairs. */
    int numberOfElements; /**< How many key/value pairs the object has. */
} JSONObject;

/**
 * A json array.
 * []
 */
typedef struct JSONArray {
    JSONElement* elements; /**< A sequence of values within the array. */
    int numberOfElements;  /**< How many values the array has. */
} JSONArray;

/**
 * A boolean.
 * true / false
 */
typedef enum bool {
    false, /**< False */
    true   /**< True  */
} bool;

/**
 * The value of a member contained in json.
 */
typedef struct JSONElement {
    JSONType type;     /**< The data type of the value. */

    JSONObject object;  /**< The value, if the type is an object. {} */
    JSONArray array;    /**< The value, if the type is an array. [] */
    bool boolean;       /**< The value, if the type is a boolean. true/false */
    long double number; /**< The value, if the type is a number (integer or double). 3.14 */
    char* string;       /**< The value, if the type is a string (not including quotes). "" */
} JSONElement;

/**
 * A key/value pair within a json object.
 * "key":value
 */
typedef struct JSONPair {
    char* key;         /**< The pair's key. **/
    JSONElement value; /**< The pair's value. **/
} JSONPair;

/*~ Interface ~*/

/*=============================================================================
    JSONObject {}
=============================================================================*/

// -- Constructor --
JSONObject o_emptyJSONObject(void);

// -- Destructor --
void o_destroyJSONObject(JSONObject* json);

// -- To String --
char* o_JSONObjectToString(JSONObject json);

// -- Parser --
JSONObject o_parseJSONObject(char* string);

// -- Check --
bool o_has(JSONObject json, char* key);
bool o_isJSONObject(JSONObject json, char* key);
bool o_isJSONArray(JSONObject json, char* key);
bool o_isBoolean(JSONObject json, char* key);
bool o_isInt(JSONObject json, char* key);
bool o_isDouble(JSONObject json, char* key);
bool o_isString(JSONObject json, char* key);
bool o_isNull(JSONObject json, char* key);

// -- Accessors --
JSONObject  o_getJSONObject(JSONObject json, char* key);
JSONArray   o_getJSONArray(JSONObject json, char* key);
bool        o_getBoolean(JSONObject json, char* key);
long        o_getInt(JSONObject json, char* key);
long double o_getDouble(JSONObject json, char* key);
char*       o_getString(JSONObject json, char* key);

JSONObject  o_optJSONObject(JSONObject json, char* key, JSONObject dflt);
JSONArray   o_optJSONArray(JSONObject json, char* key, JSONArray dflt);
bool        o_optBoolean(JSONObject json, char* key, bool dflt);
long        o_optInt(JSONObject json, char* key, long dflt);
long double o_optDouble(JSONObject json, char* key, long double dflt);
char*       o_optString(JSONObject json, char* key, char* dflt);

// -- Mutators --
void o_setJSONObject(JSONObject* json, char* key, JSONObject set);
void o_setJSONArray(JSONObject* json, char* key, JSONArray set);
void o_setBoolean(JSONObject* json, char* key, bool set);
void o_setInt(JSONObject* json, char* key, long set);
void o_setDouble(JSONObject* json, char* key, long double set);
void o_setString(JSONObject* json, char* key, char* set);
void o_setNull(JSONObject* json, char* key);
void o_remove(JSONObject* json, char* key);

/*=============================================================================
    JSONArray []
=============================================================================*/

// -- Constructor --
JSONArray a_emptyJSONArray(void);

// -- Destructor --
void a_destroyJSONArray(JSONArray* json);

// -- To String --
char* a_JSONArrayToString(JSONArray json);

// -- Parser --
JSONArray a_parseJSONArray(char* string);

// -- Check --
bool a_isJSONObject(JSONArray json, int index);
bool a_isJSONArray(JSONArray json, int index);
bool a_isString(JSONArray json, int index);
bool a_isInt(JSONArray json, int index);
bool a_isDouble(JSONArray json, int index);
bool a_isBoolean(JSONArray json, int index);
bool a_isNull(JSONArray json, int index);

// -- Accessors --
JSONObject  a_getJSONObject(JSONArray json, int index);
JSONArray   a_getJSONArray(JSONArray json, int index);
bool        a_getBoolean(JSONArray json, int index);
long        a_getInt(JSONArray json, int index);
long double a_getDouble(JSONArray json, int index);
char*       a_getString(JSONArray json, int index);

JSONArray   a_optJSONArray(JSONArray json, int index, JSONArray dflt);
JSONArray   a_optJSONArray(JSONArray json, int index, JSONArray dflt);
bool        a_optBoolean(JSONArray json, int index, bool dflt);
long        a_optInt(JSONArray json, int index, long dflt);
long double a_optDouble(JSONArray json, int index, long double dflt);
char*       a_optString(JSONArray json, int index, char* dflt);

// -- Mutators --
void a_setJSONObject(JSONArray* json, int index, JSONObject set);
void a_setJSONArray(JSONArray* json, int index, JSONArray set);
void a_setBoolean(JSONArray* json, int index, bool set);
void a_setInt(JSONArray* json, int index, long set);
void a_setDouble(JSONArray* json, int index, long double set);
void a_setString(JSONArray* json, int index, char* set);
void a_setNull(JSONArray* json, int index);
void a_remove(JSONArray* json, int index);

/*~ Implementation ~*/

// -- Helper functions --
static char*       libjson_emptyString(int size);
static char*       libjson_extendString(char* str, int additionalSize);
static char*       libjson_extractString(char* str);
static char*       libjson_JSONElementToString(JSONElement element);
static char*       libjson_JSONPairToString(JSONPair pair);
static char*       libjson_extractRaw(char* str, char open, char close);
static char*       libjson_strcpy(char* str);
static bool        libjson_isdigit(char c);
static bool        libjson_isspace(char c);
static bool        libjson_strcmp(char* s1, char* s2);
static long double libjson_floor(long double d);
static int         libjson_strlen(char* str);
static JSONElement libjson_emptyJSONElement(void);
static JSONElement o_getJSONElement(JSONObject json, char* key);
static JSONElement a_getJSONElement(JSONArray json, int index);
static void        o_setJSONElement(JSONObject* json, char* key, JSONElement set);
static void        a_setJSONElement(JSONArray* json, int index, JSONElement set);
static void        libjson_destroyJSONElement(JSONElement* element);
static void        libjson_destroyJSONPair(JSONPair* pair);
static void        libjson_deallocate(void** p);
#define libjson_dealloc(p) libjson_deallocate((void**)&p)

/*=============================================================================
    JSONObject {}
=============================================================================*/

// -- Constructor --
/**
 * Create an empty json object.
 * 
 * @return An empty json object.
 */
JSONObject o_emptyJSONObject(void) {
    JSONObject empty;

    empty.numberOfElements = 0;
    empty.elements = NULL;

    return empty;
}

// -- Destructor --
/**
 * Free all heap memory used by a json object.
 * 
 * @param json The object to deallocate.
 */
void o_destroyJSONObject(JSONObject* json) {
    for(int i=0; i<json->numberOfElements; i++) {
        libjson_destroyJSONPair(&json->elements[i]);
    }
    libjson_dealloc(json->elements);
    json->numberOfElements = 0;
}

// -- To String --
/**
 * Convert a json object to a string.
 * @warning Return value should be freed when no longer needed.
 * 
 * @param json The object to convert to string.
 * @return A string representation of the object.
 */
char* o_JSONObjectToString(JSONObject json) {
    char* str = libjson_emptyString(1 + (json.numberOfElements == 0));
    str[0] = '{';

    if(json.numberOfElements == 0) {
        str[1] = '}';
    }

    for(int i=0; i<json.numberOfElements; i++) {
        char* pair = libjson_JSONPairToString(json.elements[i]);
        char* temp = libjson_extendString(str, libjson_strlen(pair)+1);
        if(!temp) {
            fprintf(stderr, "Ran out of memory in JSONObjectToString");
         libjson_dealloc(pair);
         libjson_dealloc(str);
            return NULL;
        }
        str = temp;
        sprintf(str, "%s%s%s", str, pair, (i<json.numberOfElements-1?",":"}"));
        libjson_dealloc(pair);
        str = temp;
    }

    return str;
}

// -- Parser --
/**
 * Parse a string into a JSONObject.
 * @warning The @p str must be valid json.
 * 
 * @param str The json to parse.
 * @return The JSONObject representation of the parsed string.
 */
JSONObject o_parseJSONObject(char* str) {
    bool firstBrace = true;
    JSONObject o = o_emptyJSONObject();
    char* key = NULL;
    bool onValue = false;
    int len = libjson_strlen(str);

    for(int i=0; i<len; i++) {
        char c = str[i];

        if(libjson_isspace(c)) {
            continue;
        }

        if(c == '{') {
            if(firstBrace) {
                firstBrace = false;
            } else {
                char* child = libjson_extractRaw(str+i, '{', '}');
                o_setJSONObject(&o, key, o_parseJSONObject(child));
                i+=libjson_strlen(child)-1;
                libjson_dealloc(child);
                libjson_dealloc(key);
                onValue = false;
            }
        } else if(c == '}') {
            // should be closing brace, and can be ignored.
            libjson_dealloc(key);
            break;
        } else if(c == '\"') {
            char* s = libjson_extractString(str+i);
            i+=libjson_strlen(s)+1;
            
            if(onValue) {
                o_setString(&o, key, s);
                libjson_dealloc(s);
                libjson_dealloc(key);
                onValue = false;
            } else {
                key = s;
            }
        } else if(c == '[') {
            char* child = libjson_extractRaw(str+i, '[', ']');
            o_setJSONArray(&o, key, a_parseJSONArray(child));
            i+=libjson_strlen(child)-1;
            libjson_dealloc(child);
            libjson_dealloc(key);
            onValue = false;
        } else if(c == 'n') {
            o_setNull(&o, key);
            libjson_dealloc(key);
            onValue = false;
            i+=3;
        } else if(c == 't' || c == 'f') {
            o_setBoolean(&o, key, c == 't');
            libjson_dealloc(key);
            onValue = false;
            i+=3+(c != 't');
        } else if(c == ':') {
            onValue = true;
        } else if(c == ',') {
            //assert(!onValue)
        } else if(libjson_isdigit(c) || c == '-') {
            char tmp[128] = {0};
            bool hadPoint = false;
            int start = i;
            long double num = 0;

            for(int j=0; j+start<len; j++) {
                char d = str[start+j];

                if(d != '.' && !libjson_isdigit(d) && d != '-') {
                    break;
                }

                if(d == '.' && !hadPoint) {
                    hadPoint = true;
                    tmp[j] = d;
                } else if(d != '.') {
                    if(!(d == '-' && j != 0)) {
                        tmp[j] = d;
                    }
                }
                i++;
            }
            sscanf(tmp, "%Lf", &num);
            o_setDouble(&o, key, num);

            libjson_dealloc(key);
            onValue = false;
        }
    }
    return o;
}

// -- Check --
/**
 * Check if a json object has a value for a given key.
 * 
 * @param json The object to check for the key in.
 * @param key  The key to check the object for.
 * @return True if the key is present. False otherwise.
 */
bool o_has(JSONObject json, char* key) {
    bool has = false;
    for(int i=0; i<json.numberOfElements; i++) {
        JSONPair temp = json.elements[i];
        if(libjson_strcmp(key, temp.key)) {
            has = true;
            break;
        }
    }
    return has;
}

/**
 * Check if the value for this key is a json object.
 * 
 * @param json The object to check the value in.
 * @param key  The key the value is paired with.
 * @return If the value is an object, true. Otherwise, false.
 */
bool o_isJSONObject(JSONObject json, char* key) {
    return o_getJSONElement(json, key).type == object;
}

/**
 * Check if the value for this key is a json array.
 * 
 * @param json The object to check the value in.
 * @param key  The key the value is paired with.
 * @return If the value is an array, true. Otherwise, false.
 */
bool o_isJSONArray(JSONObject json, char* key) {
    return o_getJSONElement(json, key).type == array;
}

/**
 * Check if the value for this key is a boolean.
 * 
 * @param json The object to check the value in.
 * @param key  The key the value is paired with.
 * @return If the value is a boolean, true. Otherwise, false.
 */
bool o_isBoolean(JSONObject json, char* key) {
    return o_getJSONElement(json, key).type == boolean;
}

/**
 * Check if the value for this key is an integer.
 * 
 * @param json The object to check the value in.
 * @param key  The key the value is paired with.
 * @return If the value is an integer, true. Otherwise, false.
 */
bool o_isInt(JSONObject json, char* key) {
    JSONElement element = o_getJSONElement(json, key);
    return element.type == number && element.number == libjson_floor(element.number);
}

/**
 * Check if the value for this key is a double.
 * 
 * @param json The object to check the value in.
 * @param key  The key the value is paired with.
 * @return If the value is a double, true. Otherwise, false.
 */
bool o_isDouble(JSONObject json, char* key) {
    return o_getJSONElement(json, key).type == number;
}

/**
 * Check if the value for this key is a string.
 * 
 * @param json The object to check the value in.
 * @param key  The key the value is paired with.
 * @return If the value is a string, true. Otherwise, false.
 */
bool o_isString(JSONObject json, char* key) {
    return o_getJSONElement(json, key).type == string;
}

/**
 * Check if the value for this key is null.
 * 
 * @param json The object to check the value in.
 * @param key  The key the value is paired with.
 * @return If the value is null or if the key isn't present, true. Otherwise, false.
 */
bool o_isNull(JSONObject json, char* key) {
    return o_getJSONElement(json, key).type == null;
}

// -- Accessors --
/**
 * Get a json object from a json object by it's key.
 * 
 * @param json The object to get an object from.
 * @param key  The key the object is paired with.
 * @return The object, or a json null if the key isn't present.
 */
JSONObject o_getJSONObject(JSONObject json, char* key) {
    return o_getJSONElement(json, key).object;
}

/**
 * Get a json array from a json object by it's key.
 * 
 * @param json The object to get an array from.
 * @param key  The key the array is paired with.
 * @return The array, or a json null if the key isn't present.
 */
JSONArray o_getJSONArray(JSONObject json, char* key) {
    return o_getJSONElement(json, key).array;
}

/**
 * Get a boolean from a json object by it's key.
 * 
 * @param json The object to get a boolean from.
 * @param key  The key the boolean is paired with.
 * @return The boolean, or a json null if the key isn't present.
 */
bool o_getBoolean(JSONObject json, char* key){
    return o_getJSONElement(json, key).boolean;
}

/**
 * Get an integer from a json object by it's key.
 * 
 * @param json The object to get an integer from.
 * @param key  The key the integer is paired with.
 * @return The integer, or a json null if the key isn't present.
 */
long o_getInt(JSONObject json, char* key) {
    return (long)o_getJSONElement(json, key).number;
}

/**
 * Get a double from a json object by it's key.
 * 
 * @param json The object to get a double from.
 * @param key  The key the double is paired with.
 * @return The double, or a json null if the key isn't present.
 */
long double o_getDouble(JSONObject json, char* key) {
    return o_getJSONElement(json, key).number;
}

/**
 * Get a string from a json object by it's key.
 * 
 * @param json The object to get a string from.
 * @param key  The key the string is paired with.
 * @return The string, or a json null if the key isn't present.
 */
char* o_getString(JSONObject json, char* key) {
    return o_getJSONElement(json, key).string;
}

/**
 * Get a json object from a json object by it's key.
 * 
 * @param json The object to get an object from.
 * @param key  The key the object is paired with.
 * @param dflt The default object to return if the key isn't present.
 * @return The object, or @p dflt if the key isn't present.
 */
JSONObject o_optJSONObject(JSONObject json, char* key, JSONObject dflt) {
    JSONElement element = o_getJSONElement(json, key);
    if(element.type == null) {
        return dflt;
    }
    return element.object;
}

/**
 * Get a json array from a json object by it's key.
 * 
 * @param json The object to get an array from.
 * @param key  The key the array is paired with.
 * @param dflt The default array to return if the key isn't present.
 * @return The array, or @p dflt if the key isn't present.
 */
JSONArray o_optJSONArray(JSONObject json, char* key, JSONArray dflt) {
    JSONElement element = o_getJSONElement(json, key);
    if(element.type == null) {
        return dflt;
    }
    return element.array;
}

/**
 * Get a boolean from a json object by it's key.
 * 
 * @param json The object to get a boolean from.
 * @param key  The key the boolean is paired with.
 * @param dflt The default boolean to return if the key isn't present.
 * @return The boolean, or @p dflt if the key isn't present.
 */
bool o_optBoolean(JSONObject json, char* key, bool dflt) {
    JSONElement element = o_getJSONElement(json, key);
    if(element.type == null) {
        return dflt;
    }
    return element.boolean;
}

/**
 * Get an integer from a json object by it's key.
 * 
 * @param json The object to get an integer from.
 * @param key  The key the integer is paired with.
 * @param dflt The default integer to return if the key isn't present.
 * @return The integer, or @p dflt if the key isn't present.
 */
long o_optInt(JSONObject json, char* key, long dflt) {
    JSONElement element = o_getJSONElement(json, key);
    if(element.type == null) {
        return dflt;
    }
    return (long)element.number;
}

/**
 * Get a double from a json object by it's key.
 * 
 * @param json The object to get a double from.
 * @param key  The key the double is paired with.
 * @param dflt The default double to return if the key isn't present.
 * @return The double, or @p dflt if the key isn't present.
 */
long double o_optDouble(JSONObject json, char* key, long double dflt) {
    JSONElement element = o_getJSONElement(json, key);
    if(element.type == null) {
        return dflt;
    }
    return element.number;
}

/**
 * Get a string from a json object by it's key.
 * 
 * @param json The string to get a boolean from.
 * @param key  The key the string is paired with.
 * @param dflt The default string to return if the key isn't present.
 * @return The string, or @p dflt if the key isn't present.
 */
char* o_optString(JSONObject json, char* key, char* dflt) {
    JSONElement element = o_getJSONElement(json, key);
    if(element.type == null) {
        return dflt;
    }
    return element.string;
}

// -- Mutators --
/**
 * Set a json object for a key in a json object.
 * 
 * @param json The object to set the object in.
 * @param key  The key the object is paired with.
 * @param set  The object to set.
 */
void o_setJSONObject(JSONObject* json, char* key, JSONObject set) {
    JSONElement element = libjson_emptyJSONElement();
    element.type = object;
    element.object = set;
    o_setJSONElement(json, key, element);
}

/**
 * Set a json array for a key in a json object.
 * 
 * @param json The object to set the array in.
 * @param key  The key the array is paired with.
 * @param set  The array to set.
 */
void o_setJSONArray(JSONObject* json, char* key, JSONArray set) {
    JSONElement element = libjson_emptyJSONElement();
    element.type = array;
    element.array = set;
    o_setJSONElement(json, key, element);
}

/**
 * Set a boolean for a key in a json object.
 * 
 * @param json The object to set the boolean in.
 * @param key  The key the boolean is paired with.
 * @param set  The boolean to set.
 */
void o_setBoolean(JSONObject* json, char* key, bool set) {
    JSONElement element = libjson_emptyJSONElement();
    element.type = boolean;
    element.boolean = set;
    o_setJSONElement(json, key, element);
}

/**
 * Set an integer for a key in a json object.
 * 
 * @param json The object to set the integer in.
 * @param key  The key the integer is paired with.
 * @param set  The integer to set.
 */
void o_setInt(JSONObject* json, char* key, long set) {
    JSONElement element = libjson_emptyJSONElement();
    element.type = number;
    element.number = (long double)set;
    o_setJSONElement(json, key, element);
}

/**
 * Set a double for a key in a json object.
 * 
 * @param json The object to set the double in.
 * @param key  The key the double is paired with.
 * @param set  The double to set.
 */
void o_setDouble(JSONObject* json, char* key, long double set) {
    JSONElement element = libjson_emptyJSONElement();
    element.type = number;
    element.number = set;
    o_setJSONElement(json, key, element);
}

/**
 * Set a string for a key in a json object.
 * 
 * @param json The object to set the string in.
 * @param key  The key the string is paired with.
 * @param set  The string to set.
 */
void o_setString(JSONObject* json, char* key, char* set) {
    JSONElement element = libjson_emptyJSONElement();
    element.type = string;
    element.string = libjson_strcpy(set);
    o_setJSONElement(json, key, element);
}

/**
 * Set a null for a key in a json object.
 * 
 * @param json The object to set the null in.
 * @param key  The key the null is paired with.
 */
void o_setNull(JSONObject* json, char* key) {
    o_setJSONElement(json, key, libjson_emptyJSONElement());
}

/**
 * Remove a value from a json object by it's key.
 * 
 * @param json The json object to remove a value from.
 * @param key  The key the value to be removed is paired with.
 */
void o_remove(JSONObject* json, char* key) {
    int index = 0;
    bool exists = false;
    for(int i=0; i<json->numberOfElements; i++) {
        JSONPair temp = json->elements[i];
        if(libjson_strcmp(key, temp.key)) {
            index = i;
            exists = true;
            libjson_destroyJSONPair(&json->elements[i]);
            break;
        }
    }
    if(exists) {
        for(int i=index; i<json->numberOfElements-1; i++) {
            json->elements[i] = json->elements[i+1];
        }

        json->numberOfElements--;
        json->elements = realloc(json->elements, sizeof(JSONPair)*json->numberOfElements);
    }
}

/*=============================================================================
    JSONArray []
=============================================================================*/

// -- Constructor --
/**
 * Create an empty json array.
 * 
 * @return An empty json array.
 */
JSONArray a_emptyJSONArray(void) {
    JSONArray json;

    json.numberOfElements = 0;
    json.elements = NULL;

    return json;
}

// -- Destructor --
/**
 * Free all heap memory used by a json array.
 * 
 * @param json The array to deallocate.
 */
void a_destroyJSONArray(JSONArray* json) {
    for(int i=0; i<json->numberOfElements; i++) {
        libjson_destroyJSONElement(&json->elements[i]);
    }
    libjson_dealloc(json->elements);
    json->numberOfElements = 0;
}

// -- To String --
/**
 * Convert a json array to a string.
 * @warning Return value should be freed when no longer needed.
 * 
 * @param json The array to convert to string.
 * @return A string representation of the array.
 */
char* a_JSONArrayToString(JSONArray json) {
    char* str = libjson_emptyString(1 + (json.numberOfElements == 0));
    str[0] = '[';

    if(json.numberOfElements == 0) {
        str[1] = ']';
    }

    for(int i=0; i<json.numberOfElements; i++) {
        char* elem = libjson_JSONElementToString(json.elements[i]);
        char* temp = libjson_extendString(str, libjson_strlen(elem)+1);
        if(!temp) {
            fprintf(stderr, "Ran out of memory in JSONArrayToString");
            libjson_dealloc(elem);
            libjson_dealloc(str);
            return NULL;
        }
        str = temp;
        sprintf(str, "%s%s%s", str, elem, (i<json.numberOfElements-1?",":"]"));
        libjson_dealloc(elem);
    }

    return str;
}

// -- Parser --
/**
 * Parse a string into a JSONArray.
 * @warning The @p str must be valid json.
 * 
 * @param str The json to parse.
 * @return The JSONArray representation of the parsed string.
 */
JSONArray a_parseJSONArray(char* str) {
    bool firstBrace = true;
    JSONArray a = a_emptyJSONArray();
    int len = libjson_strlen(str);

    for(int i=0; i<len; i++) {
        char c = str[i];

        if(libjson_isspace(c)) {
            continue;
        } else if(c == '[') {
            if(firstBrace) {
                firstBrace = false;
                continue;
            } else {
                char* child = libjson_extractRaw(str+i, '[', ']');
                a_setJSONArray(&a, a.numberOfElements, a_parseJSONArray(child));
                i+=libjson_strlen(child)-1;
                libjson_dealloc(child);
            }
        } else if(c == ']') {
            // should be closing brace, and can be ignored.
            break;
        } else if(c == '\"') {
            char* s = libjson_extractString(str+i);
            a_setString(&a, a.numberOfElements, s);
            i+=libjson_strlen(s)+1;
            libjson_dealloc(s);
        } else if(c == '{') {
            char* child = libjson_extractRaw(str+i, '{', '}');
            a_setJSONObject(&a, a.numberOfElements, o_parseJSONObject(child));
            i+=libjson_strlen(child)-1;
            libjson_dealloc(child);
        } else if(c == 'n') {
            a_setNull(&a, a.numberOfElements);
            i+=3;
        } else if(c == 't' || c == 'f') {
            a_setBoolean(&a, a.numberOfElements, c == 't');
            i+=3+(c != 't');
        } else if(c == ',') {
            //safe to ignore?
        } else if(libjson_isdigit(c) || c == '-') {
            char tmp[128] = {0};
            bool hadPoint = false;
            int start = i;
            long double num = 0;

            for(int j=0; j+start<len; j++) {
                char d = str[start+j];

                if(d != '.' && !libjson_isdigit(d) && d != '-') {
                    break;
                }

                if(d == '.' && !hadPoint) {
                    hadPoint = true;
                    tmp[j] = d;
                } else if(d != '.') {
                    if(!(d == '-' && j != 0)) {
                        tmp[j] = d;
                    }
                }
                i++;
            }
            sscanf(tmp, "%Lf", &num);
            a_setDouble(&a, a.numberOfElements, num);
        }
    }
    return a;
}

// -- Check --
/**
 * Check if the value at this index is a json object.
 * 
 * @param json  The array to check the value in.
 * @param index The index the value is located at.
 * @return If the value is an object, true. Otherwise, false.
 */
bool a_isJSONObject(JSONArray json, int index) {
    return a_getJSONElement(json, index).type == object;
}

/**
 * Check if the value at this index is a json array.
 * 
 * @param json  The array to check the value in.
 * @param index The index the value is located at.
 * @return If the value is an array, true. Otherwise, false.
 */
bool a_isJSONArray(JSONArray json, int index) {
    return a_getJSONElement(json, index).type == array;
}

/**
 * Check if the value at this index is a boolean.
 * 
 * @param json  The array to check the value in.
 * @param index The index the value is located at.
 * @return If the value is a boolean, true. Otherwise, false.
 */
bool a_isBoolean(JSONArray json, int index) {
    return a_getJSONElement(json, index).type == boolean;
}

/**
 * Check if the value at this index is an integer.
 * 
 * @param json  The array to check the value in.
 * @param index The index the value is located at.
 * @return If the value is an integer, true. Otherwise, false.
 */
bool a_isInt(JSONArray json, int index) {
    JSONElement element = a_getJSONElement(json, index);
    return element.type == number && element.number == libjson_floor(element.number);
}

/**
 * Check if the value at this index is a double.
 * 
 * @param json  The array to check the value in.
 * @param index The index the value is located at.
 * @return If the value is a double, true. Otherwise, false.
 */
bool a_isDouble(JSONArray json, int index) {
    return a_getJSONElement(json, index).type == number;
}

/**
 * Check if the value at this index is a string.
 * 
 * @param json  The array to check the value in.
 * @param index The index the value is located at.
 * @return If the value is a string, true. Otherwise, false.
 */
bool a_isString(JSONArray json, int index) {
    return a_getJSONElement(json, index).type == string;
}

/**
 * Check if the value at this index is null.
 * 
 * @param json  The array to check the value in.
 * @param index The index the value is located at.
 * @return If the value is null or if the index is out of bounds, true. Otherwise, false.
 */
bool a_isNull(JSONArray json, int index) {
    return a_getJSONElement(json, index).type == null;
}

// -- Accessors --
/**
 * Get an object from a json array at an index.
 * 
 * @param json  The array to get an object from.
 * @param index The index the object is located at.
 * @return The object, or a json null if the index is not in bounds.
 */
JSONObject a_getJSONObject(JSONArray json, int index) {
    return a_getJSONElement(json, index).object;
}

/**
 * Get an array from a json array at an index.
 * 
 * @param json  The array to get an array from.
 * @param index The index the array is located at.
 * @return The array, or a json null if the index is not in bounds.
 */
JSONArray a_getJSONArray(JSONArray json, int index) {
    return a_getJSONElement(json, index).array;
}

/**
 * Get a boolean from a json array at an index.
 * 
 * @param json  The array to get a boolean from.
 * @param index The index the boolean is located at.
 * @return The boolean, or a json null if the index is not in bounds.
 */
bool a_getBoolean(JSONArray json, int index) {
    return a_getJSONElement(json, index).boolean;
}

/**
 * Get an integer from a json array at an index.
 * 
 * @param json  The array to get an integer from.
 * @param index The index the integer is located at.
 * @return The integer, or a json null if the index is not in bounds.
 */
long a_getInt(JSONArray json, int index) {
    return (long)a_getJSONElement(json, index).number;
}

/**
 * Get a double from a json array at an index.
 * 
 * @param json  The array to get a double from.
 * @param index The index the double is located at.
 * @return The double, or a json null if the index is not in bounds.
 */
long double a_getDouble(JSONArray json, int index) {
    return a_getJSONElement(json, index).number;
}

/**
 * Get a string from a json array at an index.
 * 
 * @param json  The array to get a string from.
 * @param index The index the string is located at.
 * @return The string, or a json null if the index is not in bounds.
 */
char* a_getString(JSONArray json, int index) {
    return a_getJSONElement(json, index).string;
}

/**
 * Get a json object from a json array at an index.
 * 
 * @param json  The array to get an object from.
 * @param index The index the object is located at.
 * @param dflt  The default object to return if the index is not in bounds.
 * @return The object, or @p dflt if the index is not in bounds.
 */
JSONObject a_optJSONObject(JSONArray json, int index, JSONObject dflt) {
    JSONElement element = a_getJSONElement(json, index);
    if(element.type == null) {
        return dflt;
    }
    return element.object;
}

/**
 * Get a json array from a json array at an index.
 * 
 * @param json  The array to get an array from.
 * @param index The index the array is located at.
 * @param dflt  The default array to return if the index is not in bounds.
 * @return The array, or @p dflt if the index is not in bounds.
 */
JSONArray a_optJSONArray(JSONArray json, int index, JSONArray dflt) {
    JSONElement element = a_getJSONElement(json, index);
    if(element.type == null) {
        return dflt;
    }
    return element.array;
}

/**
 * Get a boolean from a json array at an index.
 * 
 * @param json  The array to get a boolean from.
 * @param index The index the boolean is located at.
 * @param dflt  The default boolean to return if the index is not in bounds.
 * @return The boolean, or @p dflt if the index is not in bounds.
 */
bool a_optBoolean(JSONArray json, int index, bool dflt) {
    JSONElement element = a_getJSONElement(json, index);
    if(element.type == null) {
        return dflt;
    }
    return element.boolean;
}

/**
 * Get an integer from a json array at an index.
 * 
 * @param json  The array to get an integer from.
 * @param index The index the integer is located at.
 * @param dflt  The default integer to return if the index is not in bounds.
 * @return The integer, or @p dflt if the index is not in bounds.
 */
long a_optInt(JSONArray json, int index, long dflt) {
    JSONElement element = a_getJSONElement(json, index);
    if(element.type == null) {
        return dflt;
    }
    return (long)element.number;
}

/**
 * Get a double from a json array at an index.
 * 
 * @param json  The array to get a double from.
 * @param index The index the double is located at.
 * @param dflt  The default double to return if the index is not in bounds.
 * @return The double, or @p dflt if the index is not in bounds.
 */
long double a_optDouble(JSONArray json, int index, long double dflt) {
    JSONElement element = a_getJSONElement(json, index);
    if(element.type == null) {
        return dflt;
    }
    return element.number;
}

/**
 * Get a string from a json array at an index.
 * 
 * @param json  The string to get an array from.
 * @param index The index the string is located at.
 * @param dflt  The default string to return if the index is not in bounds.
 * @return The string, or @p dflt if the index is not in bounds.
 */
char* a_optString(JSONArray json, int index, char* dflt) {
    JSONElement element = a_getJSONElement(json, index);
    if(element.type == null) {
        return dflt;
    }
    return element.string;
}

// -- Mutators --
/**
 * Add a json object at the end of a json array.
 * 
 * @param json The array to add the object to.
 * @param index The index to add the value at.
 * @param set  The object to add.
 */
void a_setJSONObject(JSONArray* json, int index, JSONObject set) {
    JSONElement element = libjson_emptyJSONElement();
    element.type = object;
    element.object = set;
    a_setJSONElement(json, index, element);
}

/**
 * Add a json array at the end of a json array.
 * 
 * @param json The array to add the array to.
 * @param index The index to add the value at.
 * @param set  The array to add.
 */
void a_setJSONArray(JSONArray* json, int index, JSONArray set) {
    JSONElement element = libjson_emptyJSONElement();
    element.type = array;
    element.array = set;
    a_setJSONElement(json, index, element);
}

/**
 * Add a boolean at the end of a json array.
 * 
 * @param json The array to add the boolean to.
 * @param index The index to add the value at.
 * @param set  The boolean to add.
 */
void a_setBoolean(JSONArray* json, int index, bool set) {
    JSONElement element = libjson_emptyJSONElement();
    element.type = boolean;
    element.boolean = set;
    a_setJSONElement(json, index, element);
}

/**
 * Add an integer at the end of a json array.
 * 
 * @param json The array to add the integer to.
 * @param index The index to add the value at.
 * @param set  The integer to add.
 */
void a_setInt(JSONArray* json, int index, long set) {
    JSONElement element = libjson_emptyJSONElement();
    element.type = number;
    element.number = (long double)set;
    a_setJSONElement(json, index, element);
}

/**
 * Add a double at the end of a json array.
 * 
 * @param json The array to add the double to.
 * @param index The index to add the value at.
 * @param set  The double to add.
 */
void a_setDouble(JSONArray* json, int index, long double set) {
    JSONElement element = libjson_emptyJSONElement();
    element.type = number;
    element.number = set;
    a_setJSONElement(json, index, element);
}

/**
 * Add a string at the end of a json array.
 * 
 * @param json The array to add the string to.
 * @param index The index to add the value at.
 * @param set  The string to add.
 */
void a_setString(JSONArray* json, int index, char* set) {
    JSONElement element = libjson_emptyJSONElement();
    element.type = string;
    element.string = libjson_strcpy(set);
    a_setJSONElement(json, index, element);
}

/**
 * Add a null at the end of a json array.
 * 
 * @param json The array to add the null to.
 * @param index The index to add the value at.
 */
void a_setNull(JSONArray* json, int index) {
    JSONElement element = libjson_emptyJSONElement();
    a_setJSONElement(json, index, element);
}

/**
 * Remove a value from a json array by it's index.
 * 
 * @param json  The json array to remove a value from.
 * @param index The index the value to be removed is located at.
 */
void a_remove(JSONArray* json, int index) {
    for(int i=index; i<json->numberOfElements-1; i++) {
        json->elements[i] = json->elements[i+1];
    }

    json->numberOfElements--;
    json->elements = realloc(json->elements, sizeof(JSONElement)*json->numberOfElements);
}

// -- Helper functions --

/**
 * Create an empty, or null, json value.
 * 
 * @return An empty json value.
 */
static JSONElement libjson_emptyJSONElement(void) {
    JSONElement empty;

    empty.type = null;
    empty.object = o_emptyJSONObject();
    empty.array = a_emptyJSONArray();
    empty.boolean = false;
    empty.number = 0;
    empty.string = NULL;

    return empty;
}

/**
 * Free all heap memory used by a json value.
 * 
 * @param element The value to deallocate.
 */
static void libjson_destroyJSONElement(JSONElement* element) {
    if(element->type == object) {
        o_destroyJSONObject(&element->object);
    } else if(element->type == array) {
        a_destroyJSONArray(&element->array);
    } else if(element->type == string) {
        libjson_dealloc(element->string);
    }
    element->type = null;
}

/**
 * Allocate more memory space at the end of a string.
 * @note Appended memory is initialized to null bytes.
 * @warning Return value should be freed when no longer needed.
 * 
 * @param str            The original string to append space after.
 * @param additionalSize The number of additioal bytes to allocate.
 * 
 * @return The reallocated string, or NULL if it fails.
 */
static char* libjson_extendString(char* str, int additionalSize) {
    int len = libjson_strlen(str);
    int size = len + additionalSize + 1;

    char* extended = realloc(str, size);

    if(extended) {
        for(int i=len; i<size; i++) {
            extended[i] = '\0';
        }
    }
    return extended;
}

/**
 * Allocate memory for use by a string.
 * @note Memory is initialized to null bytes.
 * @warning Return value should be freed when no longer needed.
 * 
 * @param size The number of characters in the string.
 * 
 * @return The allocated string, or NULL if it fails.
 */
static char* libjson_emptyString(int size) {
    size++;
    char* memory = malloc(size+1);

    if(memory) {
        for(int i=0; i<=size; i++) {
            memory[i] = '\0';
        }
    }
    return memory;
}

/**
 * Copy the string enclosed by quotation marks from the beginning of @p str.
 * @note The extracted string may contain quotation marks as \".
 * @warning The first character of @p str must be ", and there must eventually be an unescaped ".
 * @warning Return value should be freed when no longer needed.
 * 
 * @param str The string to extract a json string from.
 * @return The json string with no enclosing quotation marks.
 */
static char* libjson_extractString(char* str) {
    int len = libjson_strlen(str);
    int escapes = 0;
    int end = 0;

    for(int i=0; i<len; i++) {
        char c = str[i];

        if(c == '\\') {
            escapes++;
        }

        if(c == '\"' && i > 0 && escapes % 2 == 0) {
            end = i;
            break;
        }

        if(c != '\\') {
            escapes = 0;
        }
    }

    char* s = libjson_emptyString(end-1);
    for(int i=1; i<end; i++) {
        s[i-1] = str[i];
    }
    s[end] = '\0';

    return s;
}

/**
 * Get a token from a string beginning with a character, and ending with another.
 * This is used for returning a string containing a json object or array, using 
 * @p open = { and @p close = } or @p open = [ and @p close = ] respectively.
 * @note Characters within strings (enclosed by quotations) aren't used for tokenizing.
 * @warning The first character of @p str must be @p open, and there must eventually be an @p close which is not eclosed in quotation marks.
 * @warning Return value should be freed when no longer needed.
 * 
 * @param str   The string to get the token from.
 * @param open  The character to begin tokenizing with.
 * @param close The character to end tokenizing with.
 * @return A string beginning with @p open, and ending with the first occurence of @p close in @p str.
 */
static char* libjson_extractRaw(char* str, char open, char close) {
    int depth = 0;
    int len = libjson_strlen(str);
    int end = 0;

    for(int i=0; i<len; i++) {
        char c = str[i];

        if(c == open) {
            depth++;
        } else if(c == close) {
            depth--;
            if(depth == 0) {
                end = i;
                break;
            }
        } else if(c == '\"') {
            char* e = libjson_extractString(str+i);
            i+=libjson_strlen(e)+1;
            libjson_dealloc(e);
        }
    }

    char* token = libjson_emptyString(end+1);
    for(int i=0; i<=end; i++) {
        token[i] = str[i];
    }
    token[end+1] = '\0';

    return token;
}

/**
 * Convert a json value to a string.
 * @warning Return value should be freed when no longer needed.
 * 
 * @param element The value to convert to string.
 * @return A string representation of the value.
 */
static char* libjson_JSONElementToString(JSONElement element) {
    char* str = NULL;
    char tmp[128] = {0};

    switch(element.type) {
        case object:
            str = o_JSONObjectToString(element.object);
            break;
        case array:
            str = a_JSONArrayToString(element.array);
            break;
        case boolean:
            if(element.boolean) {
                str = libjson_strcpy("true");
            } else {
                str = libjson_strcpy("false");
            }
            break;
        case number:
            sprintf(tmp, "%Lf", element.number);
            int lastNonZero = 0;
            int decimal = 0;
            int len = libjson_strlen(tmp);

            for(int i=0; i<len; i++) {
                if(tmp[i] != '0') {
                    lastNonZero = i;
                    
                    if(tmp[i] == '.') {
                        decimal = i;
                    }
                }
            }

            if(decimal) {
                if(lastNonZero == decimal) {
                    tmp[decimal] = '\0';
                } else {
                    tmp[lastNonZero+1] = '\0';
                }
            }
            str = libjson_strcpy(tmp);
            break;
        case string:
            str = libjson_emptyString(libjson_strlen(element.string)+2);
            sprintf(str, "\"%s\"", element.string);
            break;
        case null:
            str = libjson_strcpy("null");
            break;
    }
    return str;
}

/**
 * Free all heap memory used by a json key/value pair.
 * 
 * @param pair The key/value pair to deallocate.
 */
static void libjson_destroyJSONPair(JSONPair* pair) {
    libjson_dealloc(pair->key);
    libjson_destroyJSONElement(&pair->value);
}

/**
 * Get a value from a json object by it's key.
 * 
 * @param json The object to get a value from.
 * @param key  The key the value is paired with.
 * @return The value, or a json null if the key isn't present.
 */
static JSONElement o_getJSONElement(JSONObject json, char* key) {
    JSONElement element = libjson_emptyJSONElement();
    for(int i=0; i<json.numberOfElements; i++) {
        JSONPair temp = json.elements[i];
        if(libjson_strcmp(key, temp.key)) {
            element = temp.value;
            break;
        }
    }
    return element;
}

/**
 * Set a value for a key in a json object. If the key already exists, the old data will be overwritten.
 * 
 * @param json The object to set the value in.
 * @param key  The key the value is paired with.
 * @param set  The value to set.
 */
static void o_setJSONElement(JSONObject* json, char* key, JSONElement set) {
    o_remove(json, key);

    JSONPair* tmp = realloc(json->elements, sizeof(JSONPair)*(json->numberOfElements + 1));

    if(!tmp) {
        fprintf(stderr, "Ran out of memory in setJSONElement");
    } else {
        json->elements = tmp;

        JSONPair pair;
        pair.value = set;
        pair.key = libjson_strcpy(key);

        json->elements[json->numberOfElements] = pair;
        json->numberOfElements++;
    }
}

/**
 * Convert a key/value pair to a string.
 * @warning Return value should be freed when no longer needed.
 * 
 * @param pair The key/value pair to convert to string.
 * @return A string representation of the key/value pair.
 */
static char* libjson_JSONPairToString(JSONPair pair) {
    char* value = libjson_JSONElementToString(pair.value);
    char* str = libjson_emptyString(libjson_strlen(value)+3+libjson_strlen(pair.key));
    sprintf(str, "\"%s\":%s", pair.key, value);
    libjson_dealloc(value);
    return str;
}

/**
 * Get a value from a json array at an index.
 * 
 * @param json  The array to get a value from.
 * @param index The index the value is located at.
 * @return The value, or a json null if the index is not in bounds.
 */
static JSONElement a_getJSONElement(JSONArray json, int index) {
    if(index < 0 || index >= json.numberOfElements) {
        return libjson_emptyJSONElement();
    }
    return json.elements[index];
}

/**
 * Add a value at an index to a json array. This will push other elements later into the array.
 * If the @p index is less than or equal to 0, the item will be put at the start of the array.
 * If the @p index is greater than or equal to the length of the array, the item will be put at
 * the end of the array.
 * 
 * @param json  The array to add the value to.
 * @param index The index to add the value at.
 * @param set   The value to add.
 */
static void a_setJSONElement(JSONArray* json, int index, JSONElement set) {
    if(index < 0) {
        index = 0;
    } else if(index > json->numberOfElements) {
        index = json->numberOfElements;
    }
    JSONElement* tmp = realloc(json->elements, sizeof(JSONElement)*(json->numberOfElements + 1));

    if(!tmp) {
        fprintf(stderr, "Ran out of memory in addJSONElement");
    } else {
        for(int i=json->numberOfElements; i>index; i--) {
            json->elements[i] = json->elements[i-1];
        }

        json->numberOfElements++;
        json->elements = tmp;
        json->elements[index] = set;
    }
}

/**
 * Free a pointer, and set it to NULL.
 * 
 * @param p A pointer to the pointer to deallocate.
 */
static void libjson_deallocate(void** p) {
    if(p) {
        free(*p);
        *p = NULL;
    }
}

/**
 * Round a double down, truncating any decimal points off.
 * 
 * @param d The double to floor.
 * @return The floored double.
 */
static long double libjson_floor(long double d) {
    return (long double)(long)d;
}

/**
 * Check if a character is a digit. (0-9)
 * 
 * @param c The character to check.
 * @return If the character is a digit, true. Otherwise, false.
 */
static bool libjson_isdigit(char c) {
    return c >= '0' && c <= '9';
}

/**
 * Check if a character is whitespace.
 * 
 * @param c The character to check.
 * @return If the character is whitespace, true. Otherwise, false. 
 */
static bool libjson_isspace(char c) {
    return c == ' ' 
        || c == '\t'
        || c == '\n' 
        || c == '\r'
        || c == '\f'
        || c == '\v'; 
}

/**
 * Copy the contents of a string to another string.
 * 
 * @param str The string to copy.
 * @return The copied string.
 */
static char* libjson_strcpy(char* str) {
    if(!str) {
        return NULL;
    }

    int len = libjson_strlen(str);
    char* cpy = libjson_emptyString(len);

    for(int i=0; i<len; i++) {
        cpy[i] = str[i];
    }
    cpy[len] = '\0';

    return cpy;
}

/**
 * Compare that two strings are equal.
 * 
 * @param s1 The first string to compare.
 * @param s2 The second string to compare.
 * @return If the strings are identical and not null, true. Otherwise, false.
 */
static bool libjson_strcmp(char* s1, char* s2) {
    int i = 0;

    if(!s1 || !s2) {
        return false;
    }

    while(s1[i] != '\0' && s2[i] != '\0') {
        if(s1[i] != s2[i]) {
            return false;
        }
        i++;
    }
    return s1[i] == s2[i]; // == '\0'
}

/**
 * Get the number of characters in a null terminated string.
 * 
 * @param str The string to get the number of characters of.
 * @return The number of characters in the string.
 */
static int libjson_strlen(char* str) {
    int len = 0;

    if(str) {
        while(str[len] != '\0') {
            len++;
        }
    }

    return len;
}

#ifdef __cplusplus
}
#endif

#endif//__LIB_JSON_H__
