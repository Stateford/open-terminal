#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define MAX 1024
#define TERMINAL "urxvt"
#define ACTIVE_WINDOW_COMMAND "xprop -root 32x '\t$0' _NET_ACTIVE_WINDOW | cut -f 2"

void getFocusedWindowId(char* const path, int size);
void getPath(const char* const path, char* const dest, int size);
void parsePath(const char* const path, char* const dest, int size);

void getFocusedWindowId(char* const path, int size) {
    FILE *file = NULL;
    file = popen(ACTIVE_WINDOW_COMMAND, "r");

    if(file == NULL) {
        printf("ERROR");
        exit(1);
    }

    /* Read the output a line at a time - output it. */
      while (fgets(path, size, file) != NULL) {
      }

      for(unsigned int i = 0; i < strlen(path); i++) {
          if(path[i] == '\n') {
              path[i] = '\0';
          }
      }

      /* close */
      pclose(file);
}

void getPath(const char* const command, char* const dest, int size) {
    FILE *file = NULL;
    file = popen(command, "r");

    if(file==NULL) {
        printf("ERROR");
        exit(1);
    }

    while(fgets(dest, size, file) != NULL) {}

    for(unsigned int i = 0; i < strlen(dest); i++) {
        if(dest[i] == '\n') {
            dest[i] = '\0';
        }
    }
    
    pclose(file);
}

void parsePath(const char* const path, char* const dest, int size) {
    int startCopying = 0;
    int copyPosition = 0;
    for(unsigned int i = 0; i < strlen(path); i++) {
        if(startCopying) {
            if(path[i] == ' ')
                continue;

            if(path[i] == '"') {
                dest[copyPosition] = '\0';
                break;
            }

            dest[copyPosition] = path[i];
            copyPosition++;
        }
        else if(path[i] == ':') {
            startCopying = 1;
        }
    }
}

int main() {
    char wd[MAX];
    getcwd(wd, MAX);

    char windowId[MAX];

    getFocusedWindowId(windowId, sizeof(windowId) - 1);

    char command[MAX];
    snprintf(command, sizeof(command) -1, "xprop -id %s _NET_WM_NAME", windowId);

    printf("%s", command);

    char path[MAX];
    getPath(command, path, sizeof(path) - 1);

    char finalPath[MAX];
    parsePath(path, finalPath, sizeof(finalPath));
    char finalCommand[MAX];
    snprintf(finalCommand, sizeof(finalCommand), "i3-sensible-terminal -cd %s", finalPath);

    system(finalCommand);

    return 0;
}
