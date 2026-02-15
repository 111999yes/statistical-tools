#include <QApplication>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    QWidget window;
    window.setFixedSize(400, 300);
    window.setWindowTitle("統計工具 - Qt 版");

    QVBoxLayout *layout = new QVBoxLayout(&window);
    QPushButton *button = new QPushButton("開始計算統計數據");
    layout->addWidget(button);

    window.show();
    return app.exec();
}