#ifndef RW_TOPIC_WIDGET_H
#define RW_TOPIC_WIDGET_H

/*
RWImporter
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

#include <QFrame>

class RWAlias;
class RWStructureItem;
class RWCategory;
class RWContentsItem;
class RWFacet;
class RWPartition;
class RWSection;
class RWSnippet;
class RWTopic;
class QAbstractItemModel;
class QActionGroup;
class QComboBox;
class QBoxLayout;
class QHBoxLayout;
class QMenu;
class QPushButton;

class RWTopicWidget : public QFrame
{
    Q_OBJECT
    QWidget *add_section(QList<int> sections, QAbstractItemModel *columns, RWSection *section);
    QWidget *add_snippet(QAbstractItemModel *columns, RWSnippet *snippet);

public:
    explicit RWTopicWidget(RWTopic *topic, QAbstractItemModel *columns, bool include_sections = true, QWidget *parent = nullptr);
    RWTopic *topic() const { return p_topic; }
signals:

public slots:

private slots:
    void add_name();
    void remove_name(QHBoxLayout *row, RWAlias *alias);
    void show_key();

private:
    QAbstractItemModel *p_columns;
    RWTopic *p_topic;
    QWidget *p_first_section;
    QPushButton *p_key;
    void add_rwalias(RWAlias *alias);
    void set_key_tooltip();
    QWidget *create_section_options(RWSection *Item);
    QWidget *create_snippet_options(RWContentsItem *Item);
    template<typename T>
    QActionGroup *create_enum_actions(const QString &section_name, T current_value, QMenu *menu, QMap<QString,QString> &rename);
    void add_name_attributes(QBoxLayout *layout, RWAlias *alias);
};

#endif // RW_TOPIC_WIDGET_H
