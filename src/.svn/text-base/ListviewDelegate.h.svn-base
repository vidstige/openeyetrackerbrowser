#ifndef LISTVIEWDELEGATE_H
#define LISTVIEWDELEGATE_H

/*
   Copyright 2011 Tobii Technology AB

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
*/


#include <QtGui>

class ListviewDelegate : public QStyledItemDelegate {
public:
    ListviewDelegate();
    virtual ~ListviewDelegate();

    enum datarole {headerTextRole = Qt::UserRole + 100,
                   subHeaderTextrole = Qt::UserRole + 101,
                   IconRole = Qt::UserRole + 102,
                   ProductIdRole = Qt::UserRole + 103,
                  };

    void paint(QPainter *painter, const QStyleOptionViewItem &option,
               const QModelIndex &index) const;

    QSize sizeHint(const QStyleOptionViewItem &option,
                   const QModelIndex &index ) const;

};




#endif // LISTVIEWDELEGATE_H
