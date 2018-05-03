find_package(Git)

function(get_git_last_commit_infos GIT_SHA1 GIT_SHA1_ABBR GIT_DATE_YEAR GIT_DATE_MONTH GIT_DATE_DAY GIT_DESC)
    # the commit's SHA1, and whether the building workspace was dirty or not
    execute_process(COMMAND
            "${GIT_EXECUTABLE}" describe --match=NeVeRmAtCh --always --dirty
            WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}"
            OUTPUT_VARIABLE GIT_SHA1_ABBRloc
            ERROR_QUIET OUTPUT_STRIP_TRAILING_WHITESPACE)
    set(${GIT_SHA1_ABBR} "${GIT_SHA1_ABBRloc}" PARENT_SCOPE)

    # the commit's SHA1, and whether the building workspace was dirty or not
    execute_process(COMMAND
            "${GIT_EXECUTABLE}" describe --match=NeVeRmAtCh --always --abbrev=40 --dirty
            WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}"
            OUTPUT_VARIABLE GIT_SHA1loc
            ERROR_QUIET OUTPUT_STRIP_TRAILING_WHITESPACE)
    set(${GIT_SHA1} "${GIT_SHA1loc}" PARENT_SCOPE)

    # the date of the commit
    execute_process(COMMAND
            "${GIT_EXECUTABLE}" log -1 --format=%ad --date=format:'%Y'
            WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}"
            OUTPUT_VARIABLE GIT_DATE_YEARloc
            ERROR_QUIET OUTPUT_STRIP_TRAILING_WHITESPACE)
    string(SUBSTRING ${GIT_DATE_YEARloc} 1 4 GIT_DATE_YEARloc)
    set(${GIT_DATE_YEAR} "${GIT_DATE_YEARloc}" PARENT_SCOPE)

    execute_process(COMMAND
            "${GIT_EXECUTABLE}" log -1 --format=%ad --date=format:'%m'
            WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}"
            OUTPUT_VARIABLE GIT_DATE_MONTHloc
            ERROR_QUIET OUTPUT_STRIP_TRAILING_WHITESPACE)
    string(SUBSTRING ${GIT_DATE_MONTHloc} 1 2 GIT_DATE_MONTHloc)
    set(${GIT_DATE_MONTH} "${GIT_DATE_MONTHloc}" PARENT_SCOPE)

    execute_process(COMMAND
            "${GIT_EXECUTABLE}" log -1 --format=%ad --date=format:'%d'
            WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}"
            OUTPUT_VARIABLE GIT_DATE_DAYloc
            ERROR_QUIET OUTPUT_STRIP_TRAILING_WHITESPACE)
    string(SUBSTRING ${GIT_DATE_DAYloc} 1 2 GIT_DATE_DAYloc)
    set(${GIT_DATE_DAY} "${GIT_DATE_DAYloc}" PARENT_SCOPE)

    # the subject of the commit
    execute_process(COMMAND
            "${GIT_EXECUTABLE}" log -1 --format=%s
            WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}"
            OUTPUT_VARIABLE GIT_COMMIT_SUBJECTloc
            ERROR_QUIET OUTPUT_STRIP_TRAILING_WHITESPACE)
    set(${GIT_DESC} "${GIT_COMMIT_SUBJECTloc}" PARENT_SCOPE)
endfunction()