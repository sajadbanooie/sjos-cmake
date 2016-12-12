cmake_minimum_required(VERSION 3.6)
project(SJOS)

ENABLE_LANGUAGE(ASM_NASM)
ENABLE_LANGUAGE(C)
set(CMAKE_C_STANDARD 11)

set(ARCH "i386")

function(PROFILE ARCH)
    FILE(GLOB ARCH_SRC "${PROJECT_SOURCE_DIR}/kernel/arch/${ARCH}/*.c" "${PROJECT_SOURCE_DIR}/kernel/arch/${ARCH}/*.asm" "${PROJECT_SOURCE_DIR}/kernel/arch/${ARCH}/*.h")

    include("${PROJECT_SOURCE_DIR}/kernel/arch/${ARCH}/flags.cmake")

    set(ARCH_SRC ${ARCH_SRC} PARENT_SCOPE)

    set(LINKER_LAYOUT "${PROJECT_SOURCE_DIR}/kernel/arch/${ARCH}/layout.ld" PARENT_SCOPE)

    set(ARCH_C_FLAGS ${ARCH_C_FLAGS} PARENT_SCOPE)
    set(ARCH_ASM_FLAGS ${ARCH_ASM_FLAGS} PARENT_SCOPE)

    # setting toolchains
    SET(CMAKE_AR "${GCC_AR}" PARENT_SCOPE)
    SET(CMAKE_LINKER "${GCC_LD}" PARENT_SCOPE)
    SET(CMAKE_NM "${GCC_NM}" PARENT_SCOPE)
    SET(CMAKE_OBJDUMP "${GCC_OBJDUMP}" PARENT_SCOPE)
    SET(CMAKE_RANLIB "${GCC_RANLIB}" PARENT_SCOPE)
    SET(CMAKE_CXX_COMPILER "${GPP}" PARENT_SCOPE)
    SET(CMAKE_C_COMPILER "${GCC}" PARENT_SCOPE)
endfunction()

PROFILE("${ARCH}")

set(CMAKE_VERBOSE_MAKEFILE on)

#flags
set(CMAKE_C_FLAGS "${ARCH_C_FLAGS} -ffreestanding -nostdlib -fbuiltin -Wall -Wextra -nostartfiles -T${LINKER_LAYOUT}")
set(CMAKE_ASM_NASM_FLAGS "${ARCH_ASM_FLAGS}")

# generic sources
FILE(GLOB SOURCE_FILES ${PROJECT_SOURCE_DIR}/kernel/*.c ${PROJECT_SOURCE_DIR}/kernel/*.h)

link_libraries(gcc)

include_directories(${PROJECT_SOURCE_DIR}/kernel/arch/${ARCH})
include_directories(${PROJECT_SOURCE_DIR}/kernel)

add_executable(SJOS ${ARCH_SRC} ${SOURCE_FILES})

# coping kernel to boot dir
add_custom_command(TARGET SJOS POST_BUILD COMMAND ${CMAKE_COMMAND} -E make_directory isodir)
add_custom_command(TARGET SJOS POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${PROJECT_SOURCE_DIR}/kernel/grub.cfg isodir/boot/grub/grub.cfg)
add_custom_command(TARGET SJOS POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy SJOS isodir/boot/SJOS)

#bochs settings
add_custom_command(TARGET SJOS POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${PROJECT_SOURCE_DIR}/kernel/bochsrc .)

#iso
add_custom_command(TARGET SJOS POST_BUILD COMMAND grub-mkrescue -o sjos.iso isodir)
