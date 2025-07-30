#include <QApplication>
#include "MainWindow.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    MainWindow window("C:/Users/expo0/Qt_projects/language_app/data/courses_db.db");
    window.show();
    return app.exec();
}
