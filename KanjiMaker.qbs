import qbs

QtGuiApplication {
    consoleApplication: false
    cpp.cxxLanguageVersion: "c++11"
    Depends {name: "Qt.widgets"}

    files: [
        "*.cpp",
        "*.h",
        "**/*.cpp",
        "**/*.h",
    ]

    Group {     // Properties for the produced executable
        fileTagsFilter: product.type
        qbs.install: true
    }
}
