#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>

#define MAX 1024
#define ACTIVE_WINDOW_COMMAND "xprop -root 32x '\t$0' _NET_ACTIVE_WINDOW | cut -f 2"

bool getFocusedWindowId(char* const path, int size);
bool getPath(const char* const path, char* const dest, int size);
bool parsePath(const char* const path, char* const dest, int size);

bool getFocusedWindowId(char* const path, int size) {
    FILE *file = NULL;
    file = popen(ACTIVE_WINDOW_COMMAND, "r");

    if(file == NULL)
        return false;

    /* Read the output a line at a time - output it. */
      while (fgets(path, size, file) != NULL) {}

      for(unsigned int i = 0; i < strlen(path); i++) {
          if(path[i] == '\n') {
              path[i] = '\0';
          }
      }
      if(strlen(path) == 0)
          return false;

      /* close */
      const int result = pclose(file);
      return true;
}

bool getPath(const char* const command, char* const dest, int size) {
    FILE *file = NULL;
    file = popen(command, "r");

    if(file==NULL)
        return false;

    while(fgets(dest, size, file) != NULL) {}

    for(unsigned int i = 0; i < strlen(dest); i++) {
        if(dest[i] == '\n') {
            dest[i] = '\0';
        }
    }
    if(strlen(dest) == 0)
        return false;
    
    const int result = pclose(file);

    return true;
}

bool parsePath(const char* const path, char* const dest, int size) {
    int startCopying = false;
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
            startCopying = true;
        }
    }

    if(!startCopying || strlen(dest) == 0)
        return false;

    return true;
}

int main() {
    char wd[MAX];
    getcwd(wd, MAX);

    char windowId[MAX];

    bool result = getFocusedWindowId(windowId, sizeof(windowId) - 1);
    if(!result)
        goto failure;

    char command[MAX];
    snprintf(command, sizeof(command) -1, "xprop -id %s _NET_WM_NAME", windowId);


    char path[MAX];
    result = getPath(command, path, sizeof(path) - 1);
    if(!result)
        goto failure;

    char finalPath[MAX];
    parsePath(path, finalPath, sizeof(finalPath));
    char finalCommand[MAX];
    snprintf(finalCommand, sizeof(finalCommand), "i3-sensible-terminal -cd %s", finalPath);

    system(finalCommand);
    return 0;

failure:
    system("i3-sensible-terminal");

    return 0;
}
