#include <QApplication>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QMessageBox>
#include <algorithm>
#include <vector>

class Texts : public QWidget {
private:
    QVBoxLayout *layout{new QVBoxLayout(this)};
    QLabel *label{new QLabel("Placeholder text...", this)};
    QLineEdit *lineEdit{new QLineEdit(this)};
    QPushButton *submitBtn{new QPushButton("Submit", this)};
    QPushButton *reverseBtn{new QPushButton("Reverse", this)};
    QPushButton *clearBtn{new QPushButton("Clear", this)};

    [[nodiscard]] bool _isEmpty() const noexcept {
        return lineEdit->text().isEmpty();
    }

    static void _setLabelText(QLabel& lbl, const QString& text) noexcept {
        lbl.setText(text);
    }
public:
    void clear() const noexcept {
        lineEdit->clear();
        _setLabelText(*label, "Placeholder text...");
    }

    void reverse() const noexcept {
        QString text = lineEdit->text();
        std::reverse(text.begin(), text.end());
        _setLabelText(*label, text);
    }

    explicit Texts(QWidget *parent = nullptr) : QWidget(parent) {
        setLayout(layout);

        layout->addWidget(label);
        layout->addWidget(lineEdit);
        layout->addWidget(submitBtn);
        layout->addWidget(reverseBtn);
        layout->addWidget(clearBtn);

        connect(submitBtn, &QPushButton::clicked, this, [this] {
            if (_isEmpty()) {
                QMessageBox::warning(this, "ERROR", "QLineEdit empty.");
            } else {
                _setLabelText(*label, lineEdit->text());
            }
        });

        connect(reverseBtn, &QPushButton::clicked, this, [this] {
            if (_isEmpty()) {
                QMessageBox::warning(this, "ERROR", "QLineEdit empty.");
            } else {
                reverse();
            }
        });

        connect(clearBtn, &QPushButton::clicked, this, [this] {
            clear();
        });
    }
};

class Program : public QWidget {
private:
    QVBoxLayout *vLayout{new QVBoxLayout(this)};
    QHBoxLayout *hLayout{new QHBoxLayout()};
    Texts *text1{new Texts(this)};
    Texts *text2{new Texts(this)};
    Texts *text3{new Texts(this)};

    std::vector<Texts*> texts{};

    QPushButton *clearAllBtn{new QPushButton("Clear All", this)};
    QPushButton *reverseAllBtn{new QPushButton("Reverse All", this)};
public:
    explicit Program(QWidget *parent = nullptr) : QWidget(parent) {
        setLayout(vLayout);
        vLayout->addLayout(hLayout);

        hLayout->addWidget(text1);
        hLayout->addWidget(text2);
        hLayout->addWidget(text3);

        vLayout->addWidget(clearAllBtn);
        vLayout->addWidget(reverseAllBtn);

        texts.push_back(text1);
        texts.push_back(text2);
        texts.push_back(text3);

        connect(clearAllBtn, &QPushButton::clicked, this, [this] {
            for (const auto& t : texts) {
                t->clear();
            }
        });

        connect(reverseAllBtn, &QPushButton::clicked, this, [this] {
            for (const auto& t : texts) {
                t->reverse();
            }
        });
    }
};

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    Program program;

    program.resize(200, 155);
    program.show();

    return QApplication::exec();
}
