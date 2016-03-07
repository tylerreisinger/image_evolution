set(SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/gui/MainWindow.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/gui/MutateDialog.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/gui/GuiBridge.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/gui/InitialSettingsDialog.cpp

    ${CMAKE_CURRENT_SOURCE_DIR}/EvolutionDriver.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/EvolutionStatistics.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ImageEvolver.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Image.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/MipmapCollection.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Mutator.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Population.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/State.cpp

    ${CMAKE_CURRENT_SOURCE_DIR}/ImageSse.cpp
    PARENT_SCOPE)
