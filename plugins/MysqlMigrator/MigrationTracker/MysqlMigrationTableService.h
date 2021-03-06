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
#ifndef MIGRATIONTRACKER_MYSQLMIGRATIONTABLESERVICE_H
#define MIGRATIONTRACKER_MYSQLMIGRATIONTABLESERVICE_H

#include "MigrationTracker/BaseMigrationTrackerService.h"
#include "MysqlMigrator/MysqlMigrator.h"

namespace MigrationTracker {

class MYSQLMIGRATOR_DLL_EXPORT MysqlMigrationTableService : public MigrationTracker::BaseMigrationTrackerService
{
public:
    MysqlMigrationTableService();

    bool canRevertStrucuturalChangesUsingTransactions() const;
    bool wasMigrationExecuted(const QString &migrationName
                              , const CommandExecution::CommandExecutionContext &context) const;
    QStringList migrationList(const CommandExecution::CommandExecutionContext &context) const;

    bool addMigration(const QString &migrationName, const CommandExecution::CommandExecutionContext &context) const;
    bool removeMigration(const QString &migrationName, const CommandExecution::CommandExecutionContext &context) const;

    bool ensureVersionTable(const MigrationExecution::MigrationExecutionContext &context) const;
};

} // namespace MigrationTracker

#endif // MYSQLMIGRATIONTABLESERVICE_H
