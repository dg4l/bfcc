#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include "bytearray/bytearray.h"

enum TOKS{
    BF_DP_INC = '>',
    BF_DP_DEC = '<',
    BF_INC = '+',
    BF_DEC = '-',
    BF_PUTC = '.',
    BF_GETC = ',',
    BF_LOOP_OPEN = '[',
    BF_LOOP_CLOSING = ']'
};

int main(int argc, char** argv){
    if (argc < 2){
        printf("error: no file input\n");
        return -1;
    }
    ByteArray* file = file_to_byte_array(argv[1]);
    fprintf(stdout, "#include <stdio.h>\n#include <stdint.h>\n#include <stdlib.h>\n\n");
    fprintf(stdout, "int main(void){\n");
    fprintf(stdout, "    uint8_t* dp = malloc(50000);\n");
    for (size_t i = 0; i < file->bufsize; ++i){
        switch(file->buf[i]){
            case BF_DP_INC:
                fprintf(stdout, "    ++dp;");
                break;
            case BF_DP_DEC:
                fprintf(stdout, "    --dp;");
                break;
            case BF_INC:
                fprintf(stdout, "    ++(*dp);");
                break;
            case BF_DEC:
                fprintf(stdout, "    --(*dp);");
                break;
            case BF_PUTC:
                fprintf(stdout,"    fprintf(stdout, \"%%c\", *dp);");
                break;
            case BF_GETC:
                fprintf(stdout, "    *dp = getchar();");
                break;
            case BF_LOOP_OPEN:
                fprintf(stdout, "    while(*dp){");
                break;
            case BF_LOOP_CLOSING:
                fprintf(stdout, "    }");
                break;
        }
    }
    printf("\n");
    fprintf(stdout, "}\n");
    cleanup_bytearray(&file);
}
