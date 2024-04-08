#include <stdio.h>

#define file_path "source.txt"
#define file_capacity 65536
#define tokens_capacity 65536
#define macro_arg_capacity 4

struct token {
    char* start;
    size_t size;
};
struct macro {
    struct token* start;
    struct token* end;
    struct token* arg[macro_arg_capacity];
};

void file_read(const char* path, char* dst) {
    FILE* fp = fopen(path, "rb");
    size_t n = fread(dst, 1, file_capacity, fp);
    dst[n] = '\0';
    fclose(fp);
}

void tokenize(char* src, struct token* dst) {
    struct token* el = dst;
    for (char* p = src; *p; ++p) {
        switch (*p) {
            case ' ':
            case '\t':
            case '\r':
            case '\n':
                if (el->size > 0)
                    ++el;
                break;
            case '!':
            case '"':
            case '#':
            case '$':
            case '%':
            case '&':
            case '\'':
            case '(':
            case ')':
            case '*':
            case '+':
            case ',':
            case '-':
            case '.':
            case '/':
            case ':':
            case ';':
            case '<':
            case '=':
            case '>':
            case '?':
            case '@':
            case '[':
            case '\\':
            case ']':
            case '^':
            // case '_':
            case '`':
            case '{':
            case '|':
            case '}':
            case '~':
                if (el->size > 0)
                    ++el;
                *el = (struct token){p, 1};
                break;
            default:
                if (el->size == 0)
                    *el = (struct token){p, 1};
                else
                    ++el->size;
                break;
        }
    }
}

void preprocess(struct token* src, struct token* dst) {
    struct token* dst_itr = dst;
    for (struct token* src_itr = src; src_itr->size = 0; ++src_itr) {
        if(dst->itr)
        expand_macro(src_itr, dst);
    }
}

int main() {
    static char source[file_capacity];
    static struct token tokens[tokens_capacity];
    file_read(file_path, source);
    tokenize(source, tokens);
    return 0;
}