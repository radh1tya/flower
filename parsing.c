#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>
#include "parsing.h"

MarkdownElement detect_md(char *line) {
    MarkdownElement element;
    if (line[0] == '#') {
        int count = 0;
        while (line[count] == '#') {
            count++;
        }
        element.type = count;
        element.content = strdup(line + count + 2);
    } else if (strstr(line, "**")) {
      char *startbold = strstr(line, "**");
      char *endbold = strstr(startbold + 2, "**");
      if ( startbold && endbold ) {
	*startbold = '\0';
	*endbold = '\0';

	size_t before_bold_len = strlen(line);
	size_t bold_len = strlen(startbold + 2);
	size_t after_bold_len = strlen(endbold + 2);
	
      element.type = BOLD;
      element.content = malloc(before_bold_len + bold_len + after_bold_len + 14);
      if(element.content) {
	snprintf(element.content, before_bold_len + bold_len + after_bold_len + 14, "%s<b>%s</b>%s", line, startbold + 2, endbold + 2);
      }
    }
    }
    else {
        element.type = PARAGRAPH;
        element.content = strdup(line);
    }
    return element;
}

void include_style() {
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
	}
	else if (element.type == PARAGRAPH) {
            fprintf(fw, "<p>%s</p>\n", element.content);
        }
        free(element.content);
    }
    fprintf(fw, "</body>\n</html>\n");
}
