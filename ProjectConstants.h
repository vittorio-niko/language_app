#ifndef PROJECTCONSTANTS_H
#define PROJECTCONSTANTS_H
#include <QString>
#include <QSize>
#include <QMargins>

namespace Titles {
    inline const QString mainWindowTitle = "Duolingo clone";
    inline const QString submissionDialogTitle = "Confirm Submission";
    inline const QString complexityDialogTitle = "Complexity";
    inline const QString warningTitle = "Warning";
}

namespace Texts {
    inline const QString confirmSubmission = "Are you sure you want to finish and send the results?";
    inline const QString sendResults = "Send results...";
    inline const QString startCourse = "Start...";
    inline const QString ok = "Ok";
    inline const QString cancel = "Cancel";
    inline const QString returnToTheMainPage = "To the main page";
    inline const QString chooseComplexity = "Choose complexity: ";
    inline const QString easyLevel = "Easy";
    inline const QString easyLevelDescription = "<small>Help buttons available, more listening attempts</small>";
    inline const QString hardLevel = "Hard";
    inline const QString hardLevelDescription = "<small>Only hardcore</small>";
    inline const QString chooseAnOption = "Please, choose an option";
}

namespace Paths {
    inline const QString mainWindowIconPath = ":/images/duo_logo.png";
    inline const QString leftArrowIconPath = ":/images/left_arrow.png";
    inline const QString rightArrowIconPath = ":/images/right_arrow.png";
    inline const QString courseIntroDuoPath = ":/images/joyful_duo.png";
    inline const QString badResultImagePath = ":/images/crying_duo.png";
    inline const QString mediumResultImagePath = ":/images/sad_duo.png";
    inline const QString goodResultImagePath = ":/images/happy_duo.png";
}

namespace Formats {
    inline const QString timeFormat = "hh:mm:ss";
}

namespace Proportions {
    inline const QSize switcherSize = QSize(50, 50);
    inline const QSize switcherIconSize = QSize(40, 40);
    inline const QSize helpButtonSize = QSize(80, 30);
    inline const QSize stdImageSize = QSize(200, 200);
    inline const QSize enlargedImageSize = QSize(300, 300);
    inline const QSize submitCourseDialogSize = QSize(200, 130);
    inline const QSize complexityDialogSize = QSize(200, 130);
    inline const QSize mainWindowMinSize = QSize(400, 400);
    inline const QSize mainWindowSize = QSize(680, 550);
    inline constexpr int sectionListWidth = 160;
    inline const QMargins taskContentMargins = QMargins(10, 20, 10, 10);
}

namespace Time {
    inline constexpr int helpInfoDelay = 200;
    inline constexpr int countdownTimerInterval = 1000;
}

namespace Styles {
    inline const QString switcherStyle = R"(
                                          QToolButton {
                                              background-color: #F5F5F5;
                                              border: 1px solid #D1D1D1;
                                              border-radius: 7px;
                                              padding: 5px;
                                          }

                                          QToolButton:hover {
                                              background-color: #E0E0E0;
                                          }

                                          QToolButton:pressed {
                                              background-color: #D1D1D1;
                                          }

                                          QToolButton:checked {
                                              background-color: #CCCCCC;
                                          }
    )";
    inline const QString playerStyle = R"(
                                        AudioPlayerWidget {
                                            background-color: #f8f8f8;
                                            border-radius: 12px;
                                            padding: 12px;
                                            border: 1px solid #e0e0e0;
                                        }

                                        QPushButton {
                                            background-color: #4CAF50;
                                            border: none;
                                            color: white;
                                            padding: 8px 16px;
                                            border-radius: 6px;
                                            font-weight: bold;
                                            min-width: 60px;
                                        }

                                        QPushButton:hover {
                                            background-color: #45a049;
                                        }

                                        QPushButton:pressed {
                                            background-color: #3d8b40;
                                        }

                                        QPushButton:disabled {
                                            background-color: #eaeaea;
                                            color: #a0a0a0;
                                        }

                                        QSlider::groove:horizontal {
                                            height: 8px;
                                            background: #e0e0e0;
                                            border-radius: 4px;
                                        }

                                        QSlider::sub-page:horizontal {
                                            background: #4CAF50;
                                            border-radius: 4px;
                                        }

                                        QSlider::handle:horizontal {
                                            background: #4CAF50;
                                            width: 14px;
                                            height: 14px;
                                            margin: -3px 0;
                                            border-radius: 7px;
                                            border: 2px solid white;
                                        }

                                        QSlider::handle:horizontal:hover {
                                            background: #45a049;
                                        }

                                        QLabel {
                                            color: #555;
                                            font-family: 'Segoe UI', Arial, sans-serif;
                                            font-size: 11px;
                                            min-width: 40px;
                                            text-align: center;
                                        }

                                        QLabel#playsLeftLabel {
                                            color: #777;
                                            font-style: italic;
                                            font-size: 10px;
                                            padding-top: 5px;
                                        }

                                        QSlider::groove:horizontal:hover {
                                            background: #d0d0d0;
                                        }
    )";
    inline const QString helpButtonStyle = R"(
                                            QToolButton {
                                                background-color: #e8f5e9;
                                                border: 1px solid #c8e6c9;
                                                color: #2e7d32;
                                                border-radius: 6px;
                                                padding: 4px 8px;
                                                font-size: 11px;
                                                font-weight: 500;
                                            }

                                            QToolButton:hover {
                                                background-color: #dcedc8;
                                                border-color: #a5d6a7;
                                            }

                                            QToolButton:pressed {
                                                background-color: #c8e6c9;
                                                color: #1b5e20;
                                            }

                                            QToolTip {
                                                background-color: #e8f5e9;
                                                color: #2e7d32;
                                                border: 1px solid #c8e6c9;
                                                border-radius: 6px;
                                                padding: 4px 8px;
                                                font-size: 11px;
                                                font-weight: 500;
                                                font-family: 'Segoe UI', Arial, sans-serif;
                                            }
    )";

    inline const QString groupStyle = R"(
                                        QGroupBox {
                                            border: 1px solid #e0e0e0;
                                            border-radius: 8px;
                                            margin-top: 8px;
                                            padding: 12px;
                                            background-color: white;
                                        }

                                        QGroupBox::title {
                                            subcontrol-origin: padding;
                                            subcontrol-position: top left;
                                            padding: 0 6px;
                                            margin-left: 10px;
                                            margin-top: 0px;
                                            color: #5a5a5a;
                                            font-size: 30px;
                                            font-weight: 500;
                                            background-color: white;
                                            position: relative;
                                            top: -8px;
                                        }
    )";
    inline const QString labelStyle = R"(
                                        QLabel {
                                            font-family: 'Segoe UI', 'Open Sans', sans-serif;
                                            font-size: 14px;
                                            font-weight: 450;
                                            color: #424242;
                                            letter-spacing: 0.3px;
                                            line-height: 1.4;
                                        }
    )";
    inline const QString blockHeaderStyle = R"(
                                        QLabel {
                                            font-family: 'Segoe UI', 'Open Sans', sans-serif;
                                            font-size: 19px;
                                            font-weight: 500;
                                            color: #424242;
                                            margin-top: 0px;
                                            margin-bottom: 0px;
                                            padding: 0px;
                                        }
    )";
    inline const QString mainHeaderStyle = R"(
                                        QLabel {
                                            font-family: 'Segoe UI', 'Open Sans', sans-serif;
                                            font-size: 27px;
                                            font-weight: 500;
                                            color: #424242;
                                            margin-top: 0px;
                                            margin-bottom: 0px;
                                            padding: 0px;
                                        }
    )";
    inline const QString radioButtonStyle = R"(
                                            QRadioButton {
                                                font-size: 14px;
                                                color: #333333;
                                                spacing: 8px;
                                                padding: 4px 8px;
                                                border: none;
                                                background-color: transparent;
                                            }

                                            QRadioButton::indicator {
                                                width: 16px;
                                                height: 16px;
                                                margin-left: 2px;
                                                margin-right: 6px;
                                                border-radius: 8px;
                                                border: 2px solid #CCCCCC;
                                                background-color: white;
                                                alignment: alignVCenter;
                                            }

                                            QRadioButton::indicator:checked {
                                                background-color: #58CC02;
                                                border: 2px solid #58CC02;
                                            }
    )";
    inline const QString lineEditStyle = R"(
                                        QLineEdit {
                                            background-color: #FAFAFA;
                                            border: 1.2px solid #DADCE0;
                                            border-radius: 6px;
                                            padding: 4px 8px;
                                            font-size: 13px;
                                            color: #202124;
                                            font-family: 'Segoe UI', 'Helvetica Neue', sans-serif;
                                            selection-background-color: #BEE3A7;
                                            min-height: 24px;
                                        }

                                        QLineEdit:focus {
                                            border: 1.5px solid #34A853;
                                            background-color: #FFFFFF;
                                        }
    )";
    inline const QString listWidgetStyle = R"(
                                            QListWidget {
                                                background-color: #ffffff;
                                                border: 1px solid #e0e0e0;
                                                border-radius: 10px;
                                                padding: 4px;
                                                outline: 0;
                                                font-family: 'Segoe UI', Arial, sans-serif;
                                            }

                                            QListWidget::item {
                                                background-color: transparent;
                                                color: #4a4a4a;
                                                border-radius: 6px;
                                                padding: 8px 12px;
                                                margin: 1px 0;
                                                font-size: 14px;
                                                border: none;
                                                min-height: 28px;
                                            }

                                            QListWidget::item:hover {
                                                background-color: #f0f7f0;
                                            }

                                            QListWidget::item:selected {
                                                background-color: #e0f0e0;  /* Мягкий зеленый */
                                                color: #2a5c2a;
                                                font-weight: 500;
                                            }

                                            QListWidget::item:selected:hover {
                                                background-color: #d0e8d0;
                                            }

                                            QScrollBar:vertical {
                                                border: none;
                                                background: #f5f5f5;
                                                width: 6px;
                                                margin: 0px;
                                                border-radius: 3px;
                                            }

                                            QScrollBar::handle:vertical {
                                                background: #c0d0c0;
                                                min-height: 20px;
                                                border-radius: 3px;
                                            }

                                            QScrollBar::add-line:vertical,
                                            QScrollBar::sub-line:vertical {
                                                height: 0px;
                                                background: none;
                                            }

                                            QScrollBar::add-page:vertical,
                                            QScrollBar::sub-page:vertical {
                                                background: none;
                                            }
    )";
    inline const QString timerStyle = "font-size: 14px; color: #d32f2f; font-weight: bold;";
    inline const QString submitButtonStyle = R"(
                                            QPushButton {
                                                background-color: #5cdb5c;
                                                color: white;
                                                border: none;
                                                border-radius: 12px;
                                                padding: 6px 16px;
                                                font-weight: bold;
                                                font-size: 14px;
                                                min-width: 100px;
                                            }

                                            QPushButton:pressed {
                                                background-color: #4acf4a;
                                            }
    )";
    inline const QString imageFrameStyle = R"(
                                            QLabel {
                                                border: 1px solid #E0E0E0;
                                                border-radius: 8px;
                                                background-color: transparent;
                                            }
    )";
    inline const QString courseSectionStyle = R"(
                                            CourseSection {
                                                border: 2px solid #E0E0E0;
                                                border-radius: 16px;
                                                background-color: #FAFAFA;
                                            }

                                            QLabel {
                                                font-size: 18px;
                                                font-weight: bold;
                                            }

                                            QPushButton {
                                                background-color: #58CC02;
                                                color: white;
                                                font-size: 16px;
                                                font-weight: bold;
                                                border: none;
                                                border-radius: 12px;
                                                padding: 8px 16px;
                                            }

                                            QPushButton:hover {
                                                background-color: #45a700;
                                            }

                                            QProgressBar {
                                                background-color: #E0E0E0;
                                                border: none;
                                                border-radius: 10px;
                                                height: 20px;
                                                text-align: center;
                                                font-size: 14px;
                                                font-weight: bold;
                                                color: #333333;
                                            }

                                            QProgressBar::chunk {
                                                background-color: #58CC02;
                                                border-radius: 10px;
                                            }
    )";
    inline const QString dialogButtonStyle = R"(
                                            QPushButton {
                                                background-color: #58CC02;
                                                color: white;
                                                font-size: 16px;
                                                font-weight: bold;
                                                border: none;
                                                border-radius: 12px;
                                                padding: 8px 16px;
                                            }
    )";
    inline const QString returnButtonStyle = R"(
                                            QPushButton {
                                                background-color: #5cdb5c;
                                                color: white;
                                                border: none;
                                                border-radius: 12px;
                                                padding: 6px 16px;
                                                font-weight: bold;
                                                font-size: 14px;
                                                min-width: 100px;
                                            }

                                            QPushButton:pressed {
                                                background-color: #4acf4a;
                                            }
    )";
}

#endif // PROJECTCONSTANTS_H
