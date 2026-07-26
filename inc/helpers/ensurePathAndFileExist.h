
#pragma once

class QString;

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

namespace helpers {

    void ensurePathAndFileExist(
        const QString& path,
        const QString& initialContents,
        bool& ok
    );

};
