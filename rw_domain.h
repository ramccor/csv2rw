#ifndef RW_DOMAIN_H
#define RW_DOMAIN_H

/*
CSV2RW
Copyright (C) 2017 Martin Smith

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program. If not, see <http://www.gnu.org/licenses/>.
*/

#include "rw_structure_item.h"

class QXmlStreamWriter;

typedef RWStructureItem DomainTag;

class RWDomain : public RWStructureItem
{
    Q_OBJECT
public:
    RWDomain(QXmlStreamReader *stream, QObject *parent = 0);
    static RWDomain *getDomainById(const QString &domain_id);
    static RWDomain *getDomainByName(const QString &domain_id);
    QStringList tagNames() const;
    QString tagId(const QString &tag_name) const;
};

#endif // RW_DOMAIN_H
