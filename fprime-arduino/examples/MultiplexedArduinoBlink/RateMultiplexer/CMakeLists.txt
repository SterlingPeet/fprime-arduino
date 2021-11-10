set(SOURCE_FILES
	"${CMAKE_CURRENT_LIST_DIR}/RateGroupSerializableAi.xml"
	"${CMAKE_CURRENT_LIST_DIR}/ComponentSerializableAi.xml"
	"${CMAKE_CURRENT_LIST_DIR}/ChangeTimerPortAi.xml"
	"${CMAKE_CURRENT_LIST_DIR}/RateMultiplexerComponentAi.xml"
	"${CMAKE_CURRENT_LIST_DIR}/RateMultiplexerComponentImpl.cpp"
)
register_fprime_module()


set(UT_SOURCE_FILES
  "${CMAKE_CURRENT_LIST_DIR}/test/ut/main.cpp"
  "${CMAKE_CURRENT_LIST_DIR}/test/ut/Tester.cpp"
  "${CMAKE_CURRENT_LIST_DIR}/test/ut/TesterBase.cpp"
  "${CMAKE_CURRENT_LIST_DIR}/test/ut/GTestBase.cpp"
)
register_fprime_ut()