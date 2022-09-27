CMAKE_MINIMUM_REQUIRED(VERSION 3.24)
if (NOT ogre-next-deps_FOUND)
    INCLUDE(FetchContent)
    FetchContent_Declare(ogre-next-deps GIT_REPOSITORY "https://github.com/OGRECave/ogre-next-deps.git")
    FetchContent_GetProperties(ogre-next-deps)
    if (NOT ogre-next-deps_POPULATED)
        SET(FETCHCONTENT_QUIET NO)
        FetchContent_Populate(ogre-next-deps)
        SET(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
        ADD_SUBDIRECTORY(${ogre-next-deps_SOURCE_DIR} ${ogre-next-deps_BINARY_DIR})
        SET(ogre-next-deps_FOUND TRUE)
    endif()
endif()