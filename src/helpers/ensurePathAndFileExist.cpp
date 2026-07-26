
#include "helpers/ensurePathAndFileExist.h"

#include <QFile>
#include <QDebug>
#include <QDir>
#include <QFileInfo>

/*
 * Ensures that a file and its parent directory path exist
 *
 * If the file does not exist:
 * - Missing directories are created
 * - The file is created
 * - Initial contents are written into the file
 *
 * Existing files are left unchanged
 */
void helpers::ensurePathAndFileExist(
    const QString& path,
    const QString& initialContents,
    bool& ok
) {

    QFile file(path);

    if (!file.exists()) {

        QFileInfo fileInfo(path);

        // Create directory path
        QDir dir;
        if (!dir.mkpath(fileInfo.path())) {
            qDebug() << "Failed to create directory:" << fileInfo.path();
            ok = false;
            return;
        };

        // Create empty file
        if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            qDebug() << "Failed to create file:" << file.errorString();
            ok = false;
            return;
        };

        // Write starting value
        QTextStream out(&file);
        out << initialContents;

        // Close file
        file.close();

    };

    ok = true;

};
