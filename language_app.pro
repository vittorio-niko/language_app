QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

DEFINES += PROJECT_PATH=\\\"$$PWD/\\\"

SOURCES += \
    AudioPlayerWidget.cpp \
    Block.cpp \
    ComplexityDialog.cpp \
    Course.cpp \
    CourseSection.cpp \
    GrammarBlock.cpp \
    HelpButton.cpp \
    ImageLabel.cpp \
    ListeningBlock.cpp \
    MainPage.cpp \
    MainWindow.cpp \
    OpenQuestion.cpp \
    OptionQuestion.cpp \
    Question.cpp \
    ReadingBlock.cpp \
    ResultPage.cpp \
    StyledLabel.cpp \
    SubmitCourseDialog.cpp \
    Switcher.cpp \
    Task.cpp \
    TrueFalseQuestion.cpp \
    main.cpp

HEADERS += \
    AudioPlayerWidget.h \
    Block.h \
    BlockType.h \
    Complexity.h \
    ComplexityDialog.h \
    Course.h \
    CourseBlockTypes.h \
    CourseSection.h \
    GrammarBlock.h \
    HelpButton.h \
    ImageLabel.h \
    ListeningBlock.h \
    MainBlockInfo.h \
    MainCourseInfo.h \
    MainPage.h \
    MainWindow.h \
    OpenQuestion.h \
    OptionQuestion.h \
    ProjectConstants.h \
    Question.h \
    QuestionType.h \
    ReadingBlock.h \
    ResultPage.h \
    StyledLabel.h \
    SubmitCourseDialog.h \
    Switcher.h \
    Task.h \
    TrueFalseQuestion.h

FORMS +=
QT       += multimedia
QT += sql
# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc
