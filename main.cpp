#include <QApplication>
#include <QPushButton>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QPushButton btn("Qt is working!");
    btn.resize(300,100);
    btn.show();

    return app.exec();
}