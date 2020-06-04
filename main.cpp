#include <QCoreApplication>
#include <QXmlStreamReader>
#include <QDebug>
#include <QFile>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    {
        QString StdInChI;
        QString StdInChIKey;
        QString FixedHInChI;
        QString FixedHInChIKey;
        QString Struct2D;
        QString SdfIdtoCanonicalId;
        QString RgroupsAtoms;
        QString RGroupsAtomIds;
        QString amino = "arginine";
        int num1 = 1 ;
        int num2 = 73;

        QFile file("t.xml");
        if(!file.open(QFile::ReadOnly | QFile::Text)){
            qDebug() << "Cannot read file" << file.errorString();
            exit(0);
        }

        QXmlStreamReader xmlReader;
        xmlReader.setDevice(&file);


        QString previousElement;
        while(!xmlReader.atEnd())
        {
            xmlReader.readNext();

            if (!xmlReader.isStartElement()) {
                continue;
            }

            QString text = xmlReader.name().toString();
            if ((text == QStringLiteral("StdInChI")))
            {
                StdInChI = xmlReader.readElementText();
            }
            if ((text == QStringLiteral("StdInChIKey")))
            {
                StdInChIKey = xmlReader.readElementText();
            }
            if ((text == QStringLiteral("FixedHInChI")))
            {
                FixedHInChI = xmlReader.readElementText();
            }
            if ((text == QStringLiteral("FixedHInChIKey")))
            {
                FixedHInChIKey = xmlReader.readElementText();
            }
            if ((text == QStringLiteral("Struct2D")))
            {
                Struct2D = xmlReader.readElementText();
                //int start_position = Struct2D.indexOf("&#xA                    2D&#xA&#xA ");
                //int end_position = start_position + 35;
                //Struct2D.remove(start_position, end_position);
                Struct2D.replace("&#xA","\n");
            }
            if ((text == QStringLiteral("SdfIdtoCanonicalId")))
            {
                SdfIdtoCanonicalId = xmlReader.readElementText();
            }
            if ((text == QStringLiteral("RgroupsAtoms")))
            {
                RgroupsAtoms = xmlReader.readElementText();
            }
            if ((text == QStringLiteral("RGroupsAtomIds")))
            {
                RGroupsAtomIds = xmlReader.readElementText();
                QString aminoacid = amino + QString::number(num1);
                QString id = QString::number(num2);
                QString result = "QString " + aminoacid + " = INSERT INTO MonomerDetails(id, MonomerNameId, StdInChI, StdInChIKey,"
                                 " FixedHInChI, FixedHInChIKey, Structure, SdfIdtoCanonicalId,"
                                 " RgroupsAtoms, RGroupsAtomIds)"
                                 " VALUES (" + id + ", 15, '" + StdInChI + "', '" + StdInChIKey + "', '" + FixedHInChI + "', '" + FixedHInChIKey + "', '" + Struct2D + "', '" + SdfIdtoCanonicalId + "', '" + RgroupsAtoms + "', '" + RGroupsAtomIds + "');pol";
                qDebug() << result << endl;
                num1++;
                num2++;
            }
        }

        if (xmlReader.hasError()) {

        }
    }

    return 0;
}

