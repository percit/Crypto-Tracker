qt_add_executable(hello_world
    main.cpp
    DataEntryModel.cpp
    ../qml/qml.qrc
)

target_link_libraries(hello_world PRIVATE
    Qt::Quick
)
