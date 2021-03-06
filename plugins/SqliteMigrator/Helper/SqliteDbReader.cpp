/****************************************************************************
**
** Copyright (C) 2013, HicknHack Software
** All rights reserved.
** Contact: http://www.hicknhack-software.com/contact
**
** This file is part of the QSqlMigrator
**
** GNU Lesser General Public License Usage
** This file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3.0 as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL3 included in the
** packaging of this file.  Please review the following information to
** ensure the GNU General Public License version 3.0 requirements will be
** met: http://www.gnu.org/copyleft/gpl.html.
**
****************************************************************************/
#include "SqliteMigrator/Helper/SqliteDbReader.h"

#include "Structure/Table.h"

#include <QDebug>
#include <QSqlError>
#include <QSqlQuery>

using namespace Structure;

namespace Helper {

SqliteDbReader::SqliteDbReader()
{
}

Table SqliteDbReader::getTableDefinition(const QString &tableName
                                         ,const CommandExecution::CommandExecutionContext &context) const
{
    Table table = Table(tableName);
    QString queryString = QString("PRAGMA table_info(%1)").arg(tableName);
    QSqlQuery query = context.database().exec(queryString);
    QSqlError error = query.lastError();
    if (error.isValid()) {
        ::qDebug() << Q_FUNC_INFO << error.text();
    } else {
        while (query.next()) {
            QString name = query.value(1).toString();
            QString type = query.value(2).toString();
            bool notNull = query.value(3).toBool();
            QString defaultValue = query.value(4).toString();
            bool primaryKey = query.value(5).toBool();

            Column::Attributes attr = Column::None;
            if (notNull) {
                attr |= Column::NotNullable;
            }
            if (primaryKey) {
                attr |= Column::Primary;
            }

            Column col = Column(name, type, attr);
            if (!defaultValue.isEmpty()) {
                col.setDefault(defaultValue);
            }
            table.add(col);
        }
    }
    return table;
}

} // namespace Helper
