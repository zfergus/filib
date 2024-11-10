################################################################################
# See comments and discussions here:
# http://stackoverflow.com/questions/5088460/flags-to-enable-thorough-and-verbose-g-warnings
################################################################################

if(TARGET filib::warnings)
  return()
endif()

set(FILIB_WARNING_FLAGS
    -Wall
    -Wextra
    -pedantic
    -Wunused
    -Wno-long-long
    -Wpointer-arith
    -Wformat=2
    -Wuninitialized
    -Wcast-qual
    -Wmissing-noreturn
    -Wmissing-format-attribute
    -Wredundant-decls
    -Werror=implicit
    -Werror=nonnull
    -Werror=init-self
    -Werror=main
    -Werror=missing-braces
    -Werror=sequence-point
    -Werror=return-type
    -Werror=trigraphs
    -Werror=array-bounds
    -Werror=write-strings
    -Werror=address
    -Werror=int-to-pointer-cast
    -Werror=pointer-to-int-cast
    -Wno-unused-variable
    -Wunused-but-set-variable
    -Wno-unused-parameter
    -Wshadow
    -Wstack-protector
    -Wswitch
    -Wswitch-unreachable
    -Wcast-align
    -Wdisabled-optimization
    -Winvalid-pch
    -Wpacked
    -Wno-padded
    -Wstrict-overflow
    -Wstrict-overflow=2
    -Wlogical-op
    -Wno-sign-compare
    -Wnull-dereference
    -fdelete-null-pointer-checks
    -Wduplicated-cond
    -Wmisleading-indentation
    -fno-omit-frame-pointer
    -fno-optimize-sibling-calls
)

# Flags above don't make sense for MSVC
if(MSVC)
  set(FILIB_WARNING_FLAGS)
endif()

include(CheckCCompilerFlag)

add_library(filib_warnings INTERFACE)
add_library(filib::warnings ALIAS filib_warnings)

foreach(FLAG IN ITEMS ${FILIB_WARNING_FLAGS})
  string(REPLACE "=" "-" FLAG_VAR "${FLAG}")
  if(NOT DEFINED IS_SUPPORTED_${FLAG_VAR})
    check_c_compiler_flag("${FLAG}" IS_SUPPORTED_${FLAG_VAR})
  endif()
  if(IS_SUPPORTED_${FLAG_VAR})
    target_compile_options(filib_warnings INTERFACE ${FLAG})
  endif()
endforeach()
