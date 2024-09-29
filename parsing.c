#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>
#include "parsing.h"

MarkdownElement do_bold(char **current) {
    MarkdownElement element;
    element.content = malloc(256);
    char *output = element.content;

    *current += 2;
    output += sprintf(output, "<b>");
    
    while (strncmp(*current, "**", 2) != 0 && **current != '\0') {
        *output++ = **current;
        (*current)++;
    }
    
    if (strncmp(*current, "**", 2) == 0) {
        *current += 2;
        output += sprintf(output, "</b>");
    }

    *output = '\0';
    element.type = BOLD;
    return element;
}

MarkdownElement do_italic(char **current) {
    MarkdownElement element;
    element.content = malloc(256);
    char *output = element.content;

    (*current)++;
    output += sprintf(output, "<i>");

    while (**current != '_' && **current != '\0') {
        *output++ = **current;
        (*current)++;
    }

    if (**current == '_') {
        (*current)++;
        output += sprintf(output, "</i>");
    }

    *output = '\0';
    element.type = ITALIC;
    return element;
}

MarkdownElement detect_md(char *line) {
    MarkdownElement element;
    element.type = PARAGRAPH;
    element.content = malloc(strlen(line) * 10);
    
    if (line[0] == '#') {
        int count = 0;
        while (line[count] == '#') {
            count++;
        }
        element.type = count;
        snprintf(element.content, strlen(line), "%s", line + count + 1);
        return element;
    }
    
    char *current = line;
    char *output = element.content;

    while (*current != '\0') {
        if (strncmp(current, "**", 2) == 0) {
            MarkdownElement boldElement = do_bold(&current);
            strcpy(output, boldElement.content);
            output += strlen(boldElement.content);
            free(boldElement.content);
        }
        else if (*current == '>') {
            current++;
            output += sprintf(output, "<blockquote>");
            while (*current != '\0' && *current != '\n') {
                if (strncmp(current, "**", 2) == 0) {
                    MarkdownElement boldElement = do_bold(&current);
                    strcpy(output, boldElement.content);
                    output += strlen(boldElement.content);
                    free(boldElement.content);
                }
                else if (*current == '_') {
                    MarkdownElement italicElement = do_italic(&current);
                    strcpy(output, italicElement.content);
                    output += strlen(italicElement.content);
                    free(italicElement.content);
                }
                else {
                    *output++ = *current++;
                }
            }
            output += sprintf(output, "</blockquote>");
        }
        else if (*current == '_') {
            MarkdownElement italicElement = do_italic(&current);
            strcpy(output, italicElement.content);
            output += strlen(italicElement.content);
            free(italicElement.content);
        }
        else {
            *output++ = *current++;
        }
    }
    *output = '\0';

    return element;
}
void include_style(void) {
    DIR *dr_css = opendir("themes");

    if (dr_css == NULL) {
        fprintf(stderr, "404: Gak bisa buka direktori themes\n");
        return;
    }

    int style_found = 0;
    struct dirent *dir_css;
    while ((dir_css = readdir(dr_css)) != NULL) {
        if (strcmp(dir_css->d_name, "style.css") == 0) {
            style_found = 1;
            char src_path[256];
            snprintf(src_path, sizeof(src_path), "themes/%s", dir_css->d_name);

            FILE *src = fopen(src_path, "r");
            if (src == NULL) {
                fprintf(stderr, "404: Gak bisa buka %s\n", src_path);
                closedir(dr_css);
                return;
            }

            FILE *dest = fopen("public/style.css", "w");
            if (dest == NULL) {
                fprintf(stderr, "Galat membuat public/style.css\n");
                fclose(src);
                closedir(dr_css);
                return;
            }

            char buffer[1024];
            size_t bytes;
            while ((bytes = fread(buffer, 1, sizeof(buffer), src)) > 0) {
                fwrite(buffer, 1, bytes, dest);
            }
            fclose(src);
            fclose(dest);
            break;
        }
    }

    if (!style_found) {
        fprintf(stderr, "404: style.css tidak ditemukan di themes\n");
    }

    closedir(dr_css);
}

void parsing(FILE *file, FILE *fw) {
    fprintf(fw, "<html>\n<head>\n<link rel=\"stylesheet\" href=\"style.css\">\n</head>\n");
    fprintf(fw, "<body>\n");

    char line[256];
    while (fgets(line, sizeof(line), file)) {
        line[strcspn(line, "\n")] = 0;
        MarkdownElement element = detect_md(line);
        if (element.type >= 1 && element.type <= 6) {
            fprintf(fw, "<h%d>%s</h%d>\n", element.type, element.content, element.type);
        } else if (element.type == BOLD) {
            fprintf(fw, "%s\n", element.content);
        } else if (element.type == ITALIC) {
            fprintf(fw, "%s\n", element.content);
        } else if (element.type == BLOCKQUOTE) {
            fprintf(fw, "%s\n", element.content);
        } else if (element.type == PARAGRAPH) {
            fprintf(fw, "<p>%s</p>\n", element.content);
        }
        free(element.content);
    }
    fprintf(fw, "</body>\n</html>\n");
}
