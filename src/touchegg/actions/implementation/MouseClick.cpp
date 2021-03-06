/**
 * @file /src/touchegg/actions/implementation/MouseClick.cpp
 *
 * This file is part of Touchégg.
 *
 * Touchégg is free software: you can redistribute it and/or modify it under the
 * terms of the GNU General Public License  as  published by  the  Free Software
 * Foundation,  either version 2 of the License,  or (at your option)  any later
 * version.
 *
 * Touchégg is distributed in the hope that it will be useful,  but  WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
 * A PARTICULAR PURPOSE.  See the  GNU General Public License  for more details.
 *
 * You should have received a copy of the  GNU General Public License along with
 * Touchégg. If not, see <http://www.gnu.org/licenses/>.
 *
 * @author José Expósito <jose.exposito89@gmail.com> (C) 2011 - 2012
 * @class  MouseClick
 */
#include "MouseClick.h"

// ****************************************************************************************************************** //
// **********                                  CONSTRUCTORS AND DESTRUCTOR                                 ********** //
// ****************************************************************************************************************** //

MouseClick::MouseClick(const QString &settings, const QString &timing, Window window)
    : Action(settings, timing, window)
{
    this->button = 1;
    this->times = 1;

    QStringList mainStrl = settings.split(":");
    for (int i = 0; i < mainStrl.length(); i++) {
        QStringList strl = ((QString)mainStrl.at(i)).split("=");
        if (strl.length() == 2 && strl.at(0) == "BUTTON") {
            bool ok = false;
            int aux = strl.at(1).toInt(&ok);

            if (ok && aux >= 1 && aux <= 9)
                this->button = aux;
            else
                qWarning() << "Error reading MOUSE_CLICK settings, using the default settings";
        } else if (strl.length() == 2 && strl.at(0) == "TIMES") {
            bool ok = false;
            int aux = strl.at(1).toInt(&ok);

            if (ok && aux >= 1 && aux <= 5)
                this->times = aux;
            else
                qWarning() << "Error reading MOUSE_CLICK settings, using the default settings";
        } else
            qWarning() << "Error reading MOUSE_CLICK settings, using the default settings";
    }
}


// ****************************************************************************************************************** //
// **********                                        PUBLIC METHODS                                        ********** //
// ****************************************************************************************************************** //

void MouseClick::executeStart(const QHash<QString, QVariant>& /*attrs*/) {
    if (at_start) {
        mouseClick();
    }
}

void MouseClick::executeUpdate(const QHash<QString, QVariant>& /*attrs*/) {}

void MouseClick::executeFinish(const QHash<QString, QVariant>& /*attrs*/)
{
    if (!at_start) {
        mouseClick();
    }
}

void MouseClick::mouseClick() {
    for (int i = 0; i < this->times; i++) {
        XTestFakeButtonEvent(QX11Info::display(), this->button, true, 0);
        XTestFakeButtonEvent(QX11Info::display(), this->button, false, 0);
    }
    XFlush(QX11Info::display());
}
