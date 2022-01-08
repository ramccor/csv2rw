[![ko-fi](https://img.shields.io/badge/Ko--Fi-farling-success)](https://ko-fi.com/farling)
[![patreon](https://img.shields.io/badge/Patreon-amusingtime-success)](https://patreon.com/amusingtime)
[![paypal](https://img.shields.io/badge/Paypal-farling-success)](https://paypal.me/farling)
![GitHub License](https://img.shields.io/github/license/farling42/csv2rw)
![Latest Release Download Count](https://img.shields.io/github/downloads/farling42/csv2rw/latest/RWimporter.exe)

Hello RW Community,

I have been quietly working on a generic CSV import tool which )hopefully) requires no programming knowledge for the user.

There are several steps to using the tool:

0. Download the latest installer from https://github.com/farling42/csv2rw/releases

1. Prepare data from RealmWorks

1.1 Within RealmWorks, make a copy of each "predefined" category into which you want to import your CSV data. If you have your own categories already defined, then you don't need to do this step.

(Go to the "Manage" tab, select "Categories", choose the topic/article category which you want to use, select the tool icon and select "Create duplicate of category".)

1.2 Create a structure only export of the realm.

(Go to the "Share" tab, select "Manage Exports"; in the new window select the "Export Realm Structure Only" tab, type something into the "Name" box, prese the "Save Changes" button, then press the "Full Export" button to generate the RWstructure file.)

2. Use the tool

2.1 Start up the CSV Import tool.

2.2 Press the "Load CSV" button and choose the file containing your CSV data.

2.3 Press the "Load Structure" button and choose the file containing the RealmWorks structure-only export file.

2.4 Select the required category type in the drop down menu below the "Load Structure" button to choose the category that you want your CSV data to be imported into. (This should be the "copy" that you made of the predefined category/article structure.)

2.5 Drag each of the CSV column names from the left panel to the corresponding place in the category in the right panel.

2.5.1 If the snippet should be revealed, then select the first radio box on the line (the circle). If the snippet should be marked as GM-only, then select the second radio box on the line.

2.5.2 If you want to remove a field from the category panel, then just right-click the field to remove it.

2.5.3 If you want a field to contain the same text in all occurrences of the topic/article, then you can add text directly into the field, or choose a particular tag from the drop-down list (instead of dragging one of the CSV column names across).

2.6 If you want all your topics/articles to be imported as children of another topic; then tick "Add Parent", choose a category for the parent, and enter a name for it (optionally with a prefix and suffix for the parent too). If you want to group entries under separate children, you can choose a particular CSV column to use for each group (e.g. you can group your spells with each school of spells under a different parent).

2.6.1 If you want a heirarchy created, then you can create multiple parents, choosing different CSV columns to fill in the title of the parent topics.

2.7 When you have all the fields defined, press the "GENERATE" button at the bottom-right of the window to generate the export file.

3 Import into RealmWorks

3.1 Import the generated file into your realm.

(Go to the "Share" tab, select "Import", click on the box next to "File to Import" and select the rwexport file generated by the CSV tool. Then press the "Import" button.)

---

NOTES

It is no longer mandatory to make a copy of a predefined category, however if a copy is made (or a user defined category is used), then the additional greyed-out placeholder text will be displayed within this tool.

The first line of the CSV file is assumed to have the field names in it.

The bottom panel of the window shows the contents of the CSV file, so you can double-check that you are choosing the correct field.

For the domain selection parts of a topic, you can drag the CSV field name directly onto the drop-down marker in the right panel; or if you want the plain text then you can drop it into the "annotation" part of the window.

Note that if the value does not exist in the tags available from RealmWorks, then no value will be put into the RWexport file.

A field from the CSV panel can be dragged to more than one place in the topic/article panel if you want the same data in more than one place (usually used to set both the tag selector and the annotation field for the same item).
