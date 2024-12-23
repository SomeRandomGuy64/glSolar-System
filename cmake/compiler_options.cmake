# Function to set compiler flags
function(set_compiler_flags target)
    # Common compiler warnings and standards
    if(MSVC)
        target_compile_options(${target} PRIVATE 
            /W4     # Enable high-level warnings
            /WX     # Treat warnings as errors
        )
    else()
        target_compile_options(${target} PRIVATE 
            -Wall   # Enable all warnings
            -Werror # Treat warnings as errors
        )
    endif()
endfunction()