define_property(TARGET PROPERTY LINK_LIBRARIES_ALL
        BRIEF_DOCS "List of all targets, linked to this one"
        FULL_DOCS "List of all targets, linked to this one"
        )

# Compute list of all target links (direct and indirect) for given library
# Result is stored in LINK_LIBRARIES_ALL target property.
function(compute_links lib)
    if(${lib}_IN_PROGRESS)
        message(FATAL_ERROR "Circular dependency for library '${lib}'")
    endif()
    # Immediately return if output property is already set.
    get_property(complete TARGET ${lib} PROPERTY LINK_LIBRARIES_ALL SET)
    if(completed)
        return()
    endif()
    # Initialize output property.
    set_property(TARGET ${lib} PROPERTY LINK_LIBRARIES_ALL "")

    set(${lib}_IN_PROGRESS 1) # Prevent recursion for the same lib

    get_target_property(links ${lib} LINK_LIBRARIES)

    if(NOT links)
        return() # Do not iterate over `-NOTFOUND` value in case of absence of the property.
    endif()

    # For each direct link append it and its links
    foreach(link ${links})
        set_property(TARGET ${lib} APPEND PROPERTY
                LINK_LIBRARIES_ALL ${link} ${link_links_all}
                )
    endforeach(link ${links})
    # Remove duplicates
    get_target_property(links_all ${lib} LINK_LIBRARIES_ALL)
    list(REMOVE_DUPLICATES links_all)
    set_property(TARGET ${lib} PROPERTY LINK_LIBRARIES_ALL ${links_all})
endfunction()

function(include_target_dependency_in_target_package dependencyTarget packageTarget)
    compute_links(${dependencyTarget})
    get_target_property(DEPLIBS ${dependencyTarget} LINK_LIBRARIES_ALL)
    foreach(LIB ${DEPLIBS})
        if(EXISTS ${LIB})
            get_filename_component(VARREALPATH ${LIB} REALPATH)
            get_filename_component(VAROUT ${VARREALPATH} NAME)
            message("Found depency of ${dependencyTarget}: ${VAROUT} (${LIB}). Including as a package copy target of ${packageTarget}.")
            add_custom_command(TARGET ${packageTarget} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different ${LIB} "$<TARGET_FILE_DIR:${packageTarget}>/lib/${VAROUT}")
        endif()
    endforeach()
endfunction()