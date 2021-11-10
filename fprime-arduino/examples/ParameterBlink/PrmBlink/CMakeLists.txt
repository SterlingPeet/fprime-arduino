####
# F prime CMakeLists.txt:
#
# SOURCE_FILES: combined list of source and autocoding files
# MOD_DEPS: (optional) module dependencies
#
####
set(SOURCE_FILES
    "${CMAKE_CURRENT_LIST_DIR}/PrmBlinkComponentAi.xml"
    "${CMAKE_CURRENT_LIST_DIR}/PrmBlinkComponent.cpp"
)


# Uncomment and add any modules that this component depends on, else
# they might not be available when cmake tries to build this component.

set(MOD_DEPS
    Fw/Cmd
)

register_fprime_module()


