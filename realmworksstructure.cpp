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

#include "realmworksstructure.h"
#include <QXmlStreamReader>
#include <QDebug>
#include <QAbstractItemModel>
#include <QProgressBar>
#include <QProgressDialog>
#include <QCoreApplication>
#include <QSortFilterProxyModel>

#define SHOW_XML

RealmWorksStructure::RealmWorksStructure()
{

}

static void dump_tree(int indent, RWBaseItem *parent)
{
    QString indentation(indent, QChar(QChar::Space));

    qDebug().noquote().nospace() << indentation << *parent;
    QList<RWBaseItem*> child_items = parent->childItems<RWBaseItem*>();
    foreach (RWBaseItem *child, child_items)
    {
        dump_tree(indent +3, child);
    }
}

/**
 * @brief RealmWorksStructure::loadFile
 * @param file
 */
void RealmWorksStructure::loadFile(QIODevice *device)
{
    QXmlStreamReader reader;
    reader.setDevice(device);

    // Move to the start of the first element
    if (reader.readNextStartElement())
    {
        export_element = read_element(&reader, 0);
    }

    if (reader.hasError())
    {
        qWarning() << "Failed to parse XML in structure file: line" <<
                      reader.lineNumber() << ", column" <<
                      reader.columnNumber() << "error:" <<
                      reader.errorString();
        return;
    }
    qWarning() << "Structure file loaded successfully";
    //dump_tree (0, export_element);

    // Now find the partitions and domains in the structure
    RWBaseItem *main_structure = export_element->findChild<RWStructure*>(QString(), Qt::FindDirectChildrenOnly);
    categories = main_structure->childItems<RWCategory*>();
    domains = main_structure->childItems<RWDomain*>();
    //qDebug() << "File has" << categories.count() << "categories and" << domains.count() << "domains";
}

RWBaseItem *RealmWorksStructure::read_element(QXmlStreamReader *reader, RWBaseItem *parent)
{
    RWBaseItem *element = 0;
    if (reader->name().startsWith("structure"))
        element = new RWStructure(reader, parent);
    else if (reader->name().startsWith("category"))
        element = new RWCategory(reader, parent);
    else if (reader->name().startsWith("domain"))
        element = new RWDomain(reader, parent);
    else if (reader->name().startsWith("facet"))
        element = new RWFacet(reader, parent);
    else if (reader->name().startsWith("partition"))
        element = new RWPartition(reader, parent);
    else if (reader->name().startsWith("text_override"))
        element = new RWBaseItem(reader, parent, /*ignore_for_contents*/ true);
    else if (reader->name().startsWith("export") ||
             reader->name().startsWith("tag") ||
             reader->name().startsWith("definition") ||
             reader->name().startsWith("details") ||
             reader->name().startsWith("requirements") ||
             reader->name().startsWith("legal") ||
             reader->name().startsWith("content_summary") ||
             //reader->name().startsWith("text_override") ||
             reader->name().startsWith("contents") ||
             reader->name().startsWith("description") ||
             reader->name().startsWith("credits") ||
             reader->name().startsWith("summary") ||
             reader->name().startsWith("purpose") )
        element = new RWBaseItem(reader, parent);
    else
    {
        qWarning() << "read_element: unknown element type:" << reader->name();
        element = new RWBaseItem(reader, parent);
    }

    // Now read the rest of this element
    while (!reader->atEnd())
    {
        switch (reader->readNext())
        {
        case QXmlStreamReader::StartElement:
            read_element(reader, element);
            break;

        case QXmlStreamReader::EndElement:
            element->setStructureText(element->structureText().trimmed());
            // Maybe some post-processing?
            element->postLoad();
            return element;

        case QXmlStreamReader::Characters:
            // Add the characters to the end of the text for this element.
            element->setStructureText(element->structureText().append(reader->text()));
            break;

        case QXmlStreamReader::Comment:
        case QXmlStreamReader::EntityReference:
        case QXmlStreamReader::ProcessingInstruction:
        case QXmlStreamReader::NoToken:
        case QXmlStreamReader::Invalid:
        case QXmlStreamReader::StartDocument:
        case QXmlStreamReader::EndDocument:
        case QXmlStreamReader::DTD:
            // Skip everything else
            break;
        }
    }

    // Maybe some post-processing?
    element->postLoad();

    return element;
}

/**
 * @brief RealmWorksStructure::writeExportFile
 * @param file
 * @param category
 * @param model
 */

void RealmWorksStructure::writeExportFile(QIODevice *device, RWCategory *category, QAbstractItemModel *model,
                                          RWCategory *parent_category)
{
    QProgressDialog progress;
    progress.setModal(true);
    progress.setWindowTitle("Progress");
    progress.setLabelText("Generating topics/articles...");
    progress.setCancelButton(0);  // hide cancel button
#if 0
    // All I want is "%v of %m", but the bar displays differently!
    QProgressBar *bar = new QProgressBar;
    bar->setFormat("%v of %m");
    bar->setAlignment(Qt::AlignCenter);
    bar->setMinimumWidth(100);
    progress.setBar(bar);
#endif
    progress.show();

    QXmlStreamWriter *writer = new QXmlStreamWriter(device);
    // Write out the basics to the file.
    writer->setAutoFormatting(true);
    writer->writeStartDocument();
    writer->writeStartElement("export");
    {
        writer->writeDefaultNamespace(export_element->namespaceUri());
        writer->writeNamespace("http://www.w3.org/2001/XMLSchema-instance", "xsi");
        // Write out some specific attributes.
        writer->writeAttribute("format_version", export_element->attributes().value("format_version").toString());
        writer->writeAttribute("game_system_id", export_element->attributes().value("game_system_id").toString());
        writer->writeAttribute("is_structure_only", "false");

        RWStructure *main_structure = export_element->findChild<RWStructure*>(QString(), Qt::FindDirectChildrenOnly);

        // Write out the correct project definition
        writer->writeStartElement("definition");
        {
            // Replace details with our own details
            writer->writeStartElement("details");
            {
                writer->writeAttribute("name", "Test Import");
                writer->writeAttribute("import_tag_id", "Tag_1");

                writer->writeTextElement("summary", "Imported");
                writer->writeTextElement("requirements", "None");
                writer->writeTextElement("credits", "Imported");
                writer->writeTextElement("legal", "Imported");
            }
            writer->writeEndElement();  // details

            writer->writeStartElement("content_summary");
            {
                writer->writeAttribute("max_domain_count", QString::number(domains.count()));
                writer->writeAttribute("max_category_count", QString::number(categories.count()));
                writer->writeAttribute("plot_count", "0");
                writer->writeAttribute("topic_count", QString::number(model->rowCount()));
            }
            writer->writeEndElement();  // content_summary
        }
        writer->writeEndElement();  // definition

        // Write out the loaded structure
        main_structure->writeToStructure(writer);

        // Process the CSV to write out the entire RWEXPORT file.
        writer->writeStartElement("contents");

        // EITHER a possible a single parent
        // OR one parent per unique entry in the identified column
        if (parent_category == 0 || parent_category->namefield().modelColumn() < 0)
        {
            if (parent_category)
            {
                parent_category->writeStartToContents(writer, model->index(0,0));    // TODO - iterate across unique values in the column
            }
            int maxrow = model->rowCount();
            progress.setMaximum(maxrow);
            for (int row = 0 ; row < maxrow ; row++)
            {
                progress.setValue(row);
                qApp->processEvents();  // for progress dialog
                category->writeToContents(writer, model->index(row, 0));
            }
            if (parent_category)
            {
                writer->writeEndElement();  // topic
            }
        }
        else
        {
            // Get list of unique entries in the parent column
            QSet<QString> parent_names;
            QMap<QString,int> parent_row;
            int parent_column = parent_category->namefield().modelColumn();
            for (int row=0; row<model->columnCount(); row++)
            {
                QString name = model->index(row, parent_column).data().toString();
                if (name.isEmpty()) name = "<no name>";
                if (!parent_names.contains(name))
                {
                    parent_names.insert(name);
                    parent_row.insert(name, row);
                }
            }
            qDebug() << "Unique Parents =" << parent_names;

            progress.setMaximum(model->rowCount());
            int count = 0;
            QSortFilterProxyModel proxy;
            proxy.setSourceModel(model);
            proxy.setFilterKeyColumn(parent_column);

            foreach (const QString &parent_name, parent_names)
            {
                parent_category->writeStartToContents(writer, model->index(parent_row.value(parent_name),0));    // TODO - iterate across unique values in the column

                // Find the rows which match the parent's name
                proxy.setFilterFixedString(parent_name);

                int maxrow = proxy.rowCount();
                for (int row = 0 ; row < maxrow ; row++)
                {
                    progress.setValue(count++);
                    qApp->processEvents();  // for progress dialog
                    category->writeToContents(writer, proxy.index(row, 0));
                }
                writer->writeEndElement();  // topic
            }
        }
        writer->writeEndElement(); // contents
    }
    writer->writeEndElement(); // export

    writer->writeEndDocument();
    delete writer;
}
