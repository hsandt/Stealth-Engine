function(add_copy_command target folder_to_copy)
    # Scan through resource folder for updated files and copy if none existing or changed
    # http://qrikko.blogspot.fr/2016/05/cmake-and-how-to-copy-resources-during.html
    file (GLOB_RECURSE source_paths "${PROJECT_SOURCE_DIR}/${folder_to_copy}/*.*")
    foreach(source_path ${source_paths})
        get_filename_component(filename ${source_path} NAME)
        get_filename_component(dir ${source_path} DIRECTORY)
        get_filename_component(dirname ${dir} NAME)

        # DEBUG
        message(STATUS "(${source_path}) filename: ${filename}, dir: ${dir}, dirname: ${dirname}")

        set (target_path "")

        while(NOT ${dirname} STREQUAL resources)
            get_filename_component(path_component ${dir} NAME)
            set (target_path "${path_component}/${target_path}")
            get_filename_component(dir ${dir} DIRECTORY)
            get_filename_component(dirname ${dir} NAME)
            # DEBUG
            message(STATUS "(${dirname}) target_path: ${target_path}, path_component: ${path_component}, dir: ${dir}, dirname: ${dirname}")
        endwhile()

        set(target_path "${CMAKE_BINARY_DIR}/bin/resources/${target_path}${filename}")
        message(STATUS "target_path: ${target_path}")

        # Add POST_BUILD command to copy resource file
        # http://stackoverflow.com/questions/13429656/cmake-how-to-copy-contents-of-a-directory-into-build-directory-after-make
        add_custom_command(
                TARGET ${target} POST_BUILD COMMAND
                ${CMAKE_COMMAND} -E copy_if_different
                ${source_path}
                ${target_path}
                COMMENT "Moving updated resource-file '${filename}'"
        )
    endforeach()
endfunction()

