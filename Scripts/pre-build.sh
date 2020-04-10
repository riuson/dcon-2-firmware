#!/bin/sh

echo "Running Pre-Build commands."

# sh "${ProjDirPath}/Scripts/pre-build.sh" "${ProjDirPath}" ${ConfigName} ${ProjName}
# argument $1 - path to project's directory
# argument $2 - build configuration name
# argument $3 - project name

PROJECT_DIR=$1
CONFIG_NAME=$2
PROJECT_NAME=$3

#echo ${PROJECT_DIR}
#echo ${CONFIG_NAME}
#echo ${PROJECT_NAME}

# External utilities

if command -v astyle >/dev/null 2; then
  ASTYLE=astyle
  echo "AStyle detected as ${ASTYLE}."
elif command -v "${PROJECT_DIR}/Scripts/astyle.exe" >/dev/null 2; then
  ASTYLE="${PROJECT_DIR}/Scripts/astyle.exe"
  echo "AStyle detected as ${ASTYLE}."
else
  echo "AStyle not found. Aborting."
  exit 1;
fi

if command -v git >/dev/null 2; then
  GIT_BIN='git'
  echo "Git detected at '${GIT_BIN}'."
elif command -v ${GIT_BIN} >/dev/null 2; then
  #GIT=${GIT_BIN}
  echo "Git detected at '${GIT_BIN}'."
else
  echo "Git not found. Aborting."
  exit 1;
fi


# Formatting
echo "Apply formatting...";
"${ASTYLE}" --options="${PROJECT_DIR}/Scripts/astyle.conf" "${PROJECT_DIR}/App/*.cpp"
"${ASTYLE}" --options="${PROJECT_DIR}/Scripts/astyle.conf" "${PROJECT_DIR}/App/*.h"

# Revision
COMMIT_REVISION=$(${GIT_BIN} --git-dir "$PROJECT_DIR/.git" log -1 --pretty=format:"%H")
COMMIT_TIME=$(${GIT_BIN} --git-dir "$PROJECT_DIR/.git" log -1 --pretty=format:"%ai")

printf "#define COMMIT_REVISION \"${COMMIT_REVISION}\"\n#define COMMIT_TIME \"${COMMIT_TIME}\"\n" > "${PROJECT_DIR}/App/Resources/revision.h"

echo "Done."

exit 0
