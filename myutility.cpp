#include "myutility.h"

QSize utl::CalculateScreenCenter(QSize mainScreen, QSize currentScreen) {

    return QSize((mainScreen.width()-currentScreen.width()) / 2,
                 (mainScreen.height()-currentScreen.height()) / 2);
}
