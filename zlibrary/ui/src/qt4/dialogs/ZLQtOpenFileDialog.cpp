/*
 * Copyright (C) 2010 Geometer Plus <contact@geometerplus.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
 * 02110-1301, USA.
 */

//#include <QtGui/QFileDialog>

#include <QDir>
#include <QDebug>
#include <QInputDialog>
#include <QVBoxLayout>
#include <QList>
#include <QPushButton>
#include <QMessageBox>
#include "ZLQtOpenFileDialog.h"

ZLQtOpenFileDialog::ZLQtOpenFileDialog(const std::string &title, const std::string &directoryPath, const std::string &filePath, const Filter &filter)
: directory(), file()
{
}

ZLQtOpenFileDialog::~ZLQtOpenFileDialog() {
	//delete myDialog;
}

bool ZLQtOpenFileDialog::runInternal() {
    QString path("/");
    int i = 1;
    for(;;)
    {
        QDir dir(path);
        QFileInfoList list = dir.entryInfoList(QDir::AllEntries, QDir::Name);

        if(list.count() == 0)
        {
            qDebug() << "return true, dir=" << directory << ", file=" << file;
            return true;
        }
        
        QString text = path + "\n\n";
        for(int j = i - 8; j < list.count(); j++)
        {
            if(j < 0)
            {
                j = 0;
            }
            QFileInfo fi = list.at(j);
            if(i == j)
            {
                text += "-> ";
            }
            else
            {
                text += "     ";
            }
            if(j == 0)
            {
                text += "..... cancel";
            }
            else
            {
                text += fi.fileName();
            }
            text += "\n";
        }
        
        int val = QMessageBox::question(NULL, "Open book",
                                    text,
                                    "^",
                                    "v",
                                    "Select", 0, 2);
       if(val == 0 && i > 0)
       {
           i--;
       }
       if(val == 1 && i + 1 < list.count())
       {
           i++;
       }
       if(val == 2)
       {
           if(i == 0)
           {
               return false;    // cancel
           }
           QFileInfo fi = list.at(i);
           file = fi.fileName();
           directory = path;
           if(path.length() > 1)
           {
               path += "/";
           }
           path += file;
           i = 1;
       }
    }
}

std::string ZLQtOpenFileDialog::filePath() const {
    qDebug() << "file=" << file;
    QString res = directory + "/" + file;
	return (const char*)res.toUtf8();
}

std::string ZLQtOpenFileDialog::directoryPath() const {
    qDebug() << "directory=" << directory;
	return (const char*)directory.toUtf8();
}

void ZLQtOpenFileDialog::setPosition(int x, int y) {
	
}

void ZLQtOpenFileDialog::setSize(int width, int height) {
	
}

int ZLQtOpenFileDialog::x() const {
	
}

int ZLQtOpenFileDialog::y() const {
	
}

int ZLQtOpenFileDialog::width() const {
	
}

int ZLQtOpenFileDialog::height() const {
	
}
