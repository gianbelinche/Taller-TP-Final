/********************************************************************************
** Form generated from reading UI file 'characterselection.ui'
**
** Created by: Qt User Interface Compiler version 5.9.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHARACTERSELECTION_H
#define UI_CHARACTERSELECTION_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CharacterSelection
{
public:
    QComboBox *comboBox;
    QComboBox *comboBox_2;
    QLabel *label;
    QLabel *label_2;

    void setupUi(QWidget *CharacterSelection)
    {
        if (CharacterSelection->objectName().isEmpty())
            CharacterSelection->setObjectName(QStringLiteral("CharacterSelection"));
        CharacterSelection->resize(640, 480);
        CharacterSelection->setMinimumSize(QSize(640, 480));
        CharacterSelection->setMaximumSize(QSize(640, 480));
        CharacterSelection->setStyleSheet(QStringLiteral("background-image: url(:/new/prefix1/background.png);"));
        comboBox = new QComboBox(CharacterSelection);
        comboBox->setObjectName(QStringLiteral("comboBox"));
        comboBox->setGeometry(QRect(80, 190, 91, 25));
        comboBox_2 = new QComboBox(CharacterSelection);
        comboBox_2->setObjectName(QStringLiteral("comboBox_2"));
        comboBox_2->setGeometry(QRect(80, 280, 91, 25));
        label = new QLabel(CharacterSelection);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(190, 276, 71, 31));
        label->setStyleSheet(QStringLiteral("background-color: transparent;"));
        label_2 = new QLabel(CharacterSelection);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(190, 180, 71, 41));
        label_2->setStyleSheet(QStringLiteral("background-color: transparent;"));

        retranslateUi(CharacterSelection);

        QMetaObject::connectSlotsByName(CharacterSelection);
    } // setupUi

    void retranslateUi(QWidget *CharacterSelection)
    {
        CharacterSelection->setWindowTitle(QApplication::translate("CharacterSelection", "Form", Q_NULLPTR));
        comboBox->clear();
        comboBox->insertItems(0, QStringList()
         << QApplication::translate("CharacterSelection", "Humano", Q_NULLPTR)
         << QApplication::translate("CharacterSelection", "Elfo", Q_NULLPTR)
         << QApplication::translate("CharacterSelection", "Enano", Q_NULLPTR)
         << QApplication::translate("CharacterSelection", "Gnomo", Q_NULLPTR)
        );
        comboBox_2->clear();
        comboBox_2->insertItems(0, QStringList()
         << QApplication::translate("CharacterSelection", "Guerrero", Q_NULLPTR)
         << QApplication::translate("CharacterSelection", "Mago", Q_NULLPTR)
         << QApplication::translate("CharacterSelection", "Cl\303\251rigo", Q_NULLPTR)
         << QApplication::translate("CharacterSelection", "Paladin", Q_NULLPTR)
        );
        label->setText(QApplication::translate("CharacterSelection", "Clase", Q_NULLPTR));
        label_2->setText(QApplication::translate("CharacterSelection", "Raza", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class CharacterSelection: public Ui_CharacterSelection {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHARACTERSELECTION_H
