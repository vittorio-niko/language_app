#include "ResultPage.h"

ResultPage::ResultPage(const QString& courseName, int coursePercent,
                       QWidget *parent): QWidget(parent) {
    QVBoxLayout *resultPageLayout = new QVBoxLayout(this);

    QLabel *courseNameHeader = new QLabel(courseName, this);
    courseNameHeader->setAlignment(Qt::AlignCenter);
    courseNameHeader->setStyleSheet(Styles::mainHeaderStyle);
    resultPageLayout->addWidget(courseNameHeader);

    QString resultString = "Your result: " + QString::number(coursePercent) + "%";
    QLabel *resultLabel = new QLabel(resultString, this);
    resultLabel->setStyleSheet(Styles::mainHeaderStyle);
    resultPageLayout->addWidget(resultLabel, 0, Qt::AlignCenter);

    if (0 <= coursePercent && coursePercent <= 100) {
        if (coursePercent <= 30) {
            ImageLabel *resultImage = new ImageLabel(Paths::badResultImagePath,
                                                     Proportions::enlargedImageSize,
                                                     this);
            resultPageLayout->addWidget(resultImage, 0, Qt::AlignCenter);
        } else if (31 <= coursePercent && coursePercent <= 69) {
            ImageLabel *resultImage = new ImageLabel(Paths::mediumResultImagePath,
                                                     Proportions::enlargedImageSize,
                                                     this);
            resultPageLayout->addWidget(resultImage, 0, Qt::AlignCenter);
        } else if (70 <= coursePercent) {
            ImageLabel *resultImage = new ImageLabel(Paths::goodResultImagePath,
                                                     Proportions::enlargedImageSize,
                                                     this);
            resultPageLayout->addWidget(resultImage, 0, Qt::AlignCenter);
        }
    }

    returnButton = new QPushButton(Texts::returnToTheMainPage, this);
    returnButton->setStyleSheet(Styles::returnButtonStyle);
    connect(returnButton, &QPushButton::clicked, this, [=](){
        emit returnRequired();
    });
    resultPageLayout->addWidget(returnButton, 0, Qt::AlignCenter);

    setLayout(resultPageLayout);
}
