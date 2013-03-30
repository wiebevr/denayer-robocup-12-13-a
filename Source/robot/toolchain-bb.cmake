set(CMAKE_SYSTEM_NAME Linux)
set(CMAKE_SYSTEM_VERSION 1)
set(CMAKE_SYSTEM_PROCESSOR armv7-a)

# -mcpu
set(PIXFC_ARM_TARGET_PROCESSOR cortex-a8)

# -march
set(PIXFC_ARM_TARGET_ARCH armv7-a)

# The cross compiler, make sure it is in PATH.
set(CMAKE_C_COMPILER  ${ROBOT_SOURCE_DIR}/env/arm-2011.03/arm-none-linux-gnueabi/bin/gcc)
set(CMAKE_CXX_COMPILER  ${ROBOT_SOURCE_DIR}/env/arm-2011.03/arm-none-linux-gnueabi/bin/g++)

set(CMAKE_FIND_ROOT_PATH ${ROBOT_SOURCE_DIR}/env/fs )
