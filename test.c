#include "libjson.h"
#include <string.h>

int main(int argc, char** argv) {
    char* raw = NULL;
    char buf[1024] = {0};

    FILE* fp = stdin;

    if(argc > 1) {
        if(argc > 2) {
            printf("Usage: ./libjsontest filename.json\n");
            return 1;
        }
        if(!(fp = fopen(argv[1], "r"))) {
            printf("Failed to open %s\n", argv[1]);
            return 1;
        }
    }
    
    while(fgets(buf, 1023, fp)) {
        raw = libjson_extendString(raw, strlen(buf));
        strcat(raw, buf);
    }
    if(argc == 2) {
        fclose(fp);
    }
    
    JSONObject json = o_parseJSONObject(raw);
    free(raw);

    char* string = o_JSONObjectToString(json);

    o_destroyJSONObject(&json);

    printf("%s", string);
    free(string);

    return 0;
}
