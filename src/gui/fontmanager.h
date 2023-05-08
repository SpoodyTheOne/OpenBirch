#ifndef FONTMANAGER_H
#define FONTMANAGER_H

#include <QFont>
#include <QFontDatabase>
#include <iostream>

class FontManager
{
public:
    static inline QFont MathFont() {

        std::cout << QFontDatabase::applicationFontFamilies(MathFontIdx).at(0).toStdString() << std::endl;

        return QFont(QFontDatabase::applicationFontFamilies(MathFontIdx).at(0), 12);
    }

    static inline int MathFontIdx;
};

#endif // FONTMANAGER_H
