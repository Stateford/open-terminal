PROJECT_NAME=open-terminal
COMPILER=clang
SOURCE_FILES=src/main.c

all: release

release:
	${COMPILER} -Os ${SOURCE_FILES} -o ${PROJECT_NAME}
.PHONY: release

debug:
	${COMPILER} ${SOURCE_FILES} -o ${PROJECT_NAME}
.PHONY: debug

run: debug
	./${PROJECT_NAME}

clean:
	rm ${PROJECT_NAME}

.PHONY: clean
