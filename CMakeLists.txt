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

function(MODULES)
    include("${PROJECT_SOURCE_DIR}/modules/modules.cmake")

    foreach (M ${KERNEL_MODULES})
        FILE(GLOB MODULE_${M}_SRC "${PROJECT_SOURCE_DIR}/modules/${M}/*.c" "${PROJECT_SOURCE_DIR}/modules/${M}/*.h")
        add_executable(module_${M} ${MODULE_${M}_SRC})
        add_custom_command(TARGET module_${M} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy "module_${M}" "isodir/boot/modules/module_${M}")
        set_target_properties(module_${M} PROPERTIES LINK_FLAGS "-T${PROJECT_SOURCE_DIR}/modules/layout.ld -r")
    endforeach ()
endfunction()

PROFILE("${ARCH}")

set(CMAKE_VERBOSE_MAKEFILE on)

# generic sources
FILE(GLOB SOURCE_FILES ${PROJECT_SOURCE_DIR}/kernel/*.c ${PROJECT_SOURCE_DIR}/kernel/*.h)

link_libraries(gcc)

include_directories(${PROJECT_SOURCE_DIR}/kernel/arch/${ARCH})
include_directories(${PROJECT_SOURCE_DIR}/kernel)

add_executable(SJOS ${ARCH_SRC} ${SOURCE_FILES})

#flags
set(CMAKE_C_FLAGS "${ARCH_C_FLAGS} -ffreestanding -nostdlib -fbuiltin -Wall -Wextra -nostartfiles")
set(CMAKE_ASM_NASM_FLAGS "${ARCH_ASM_FLAGS}")
set_target_properties(SJOS PROPERTIES LINK_FLAGS "-T${LINKER_LAYOUT}")

# coping kernel to boot dir
add_custom_command(TARGET SJOS POST_BUILD COMMAND ${CMAKE_COMMAND} -E make_directory isodir)
add_custom_command(TARGET SJOS POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different ${PROJECT_SOURCE_DIR}/kernel/grub.cfg isodir/boot/grub/grub.cfg)
add_custom_command(TARGET SJOS POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different SJOS isodir/boot/SJOS)

#bochs settings
add_custom_command(TARGET SJOS POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different ${PROJECT_SOURCE_DIR}/kernel/bochsrc .)

#iso
add_custom_command(TARGET SJOS POST_BUILD COMMAND grub-mkrescue -o sjos.iso isodir)

MODULES()