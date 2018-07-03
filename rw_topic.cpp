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

#include "rw_alias.h"
#include "rw_category.h"
#include "rw_topic.h"
#include "rw_partition.h"
#include <QXmlStreamWriter>
#include <QMetaEnum>
#include <QModelIndex>
#include <QDebug>

#include "rw_contents_item.h"   // TODO - remove this?

static int topic_id = 1;
static QString g_default_name = "no-name";

RWTopic::RWTopic(RWCategory *item, RWContentsItem *parent) :
    RWContentsItem(item, parent),
    category(item),
    p_key_column(-1)
{
}

/**
 * @brief RWTopic::canBeGenerated
 * @return true if a model index has been set on the modelValueForName
 */
bool RWTopic::canBeGenerated() const
{
    // Don't check children, since only the name is needed in a topic.
    return p_name.modelColumn() >= 0;
    //return p_name.modelColumn() >= 0 && RWBaseItem::canBeGenerated();
}

void RWTopic::writeToContents(QXmlStreamWriter *writer, const QModelIndex &index)
{
    // Don't put topics into the file if they don't match the filter
    if (keyColumn() < 0 || index.sibling(index.row(), keyColumn()).data().toString() == keyValue())
    {
        writeStartToContents(writer, index);
        writer->writeEndElement();  // </topic>
    }
}


void RWTopic::writeStartToContents(QXmlStreamWriter *writer, const QModelIndex &index)
{
    writer->writeStartElement("topic");
    {
        writer->writeAttribute("topic_id", QString("topic_%1").arg(topic_id++));
        if (!category->id().isEmpty()) writer->writeAttribute("category_id", category->id());
        QString public_name = p_name.valueString(index);
        if (public_name.isEmpty()) public_name = g_default_name;
        writer->writeAttribute("public_name", public_name);
        QString prefix = p_prefix.valueString(index);
        if (!prefix.isEmpty()) writer->writeAttribute("prefix", prefix);
        QString suffix = p_suffix.valueString(index);
        if (!suffix.isEmpty()) writer->writeAttribute("suffix", suffix);
        if (isRevealed()) writer->writeAttribute("is_revealed", "true");

        // Add alias snippets as the first entry within the topic,
        // but only generate aliases for those entries that have a non-empty string.
        // This allows a user to specify several different aliases in the GUI each using a different set of attributes,
        // and then use a different CSV column for each particular alias.
        foreach (RWAlias *alias, aliases)
        {
            alias->writeToContents(writer, index);
        }

        // Children in the following order:
        //   X x 'alias'
        //   X x 'section'
        //   X x 'tag_assign'
        //   X x connection / dconnection
        //   X x 'topic'
        writeChildrenToContents(writer, index);

        // Relevant export tag on every topic
        writeExportTag(writer);

        // No actual TEXT for this element (only children)
        //if (!text().valueString(index).isEmpty()) writer->writeCharacters(text().valueString(index));
    }
}


void RWTopic::setDefaultName(const QString &name)
{
    g_default_name = name;
}
