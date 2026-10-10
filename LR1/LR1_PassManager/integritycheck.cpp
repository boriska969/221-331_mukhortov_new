#include "integritycheck.h"

#include <QCryptographicHash>
#include <QDebug>

#ifdef Q_OS_WIN
#include <windows.h>
#include <cstring>

typedef quint64 QWORD;
#endif

static const char REFERENCE_HASH_SLOT[] =
    "LR1TEXTHASH:0000000000000000000000000000000000000000000=";
static const int REFERENCE_HASH_MARKER_LEN = 12;
static const int REFERENCE_HASH_LEN = 44;

static QByteArray referenceHashBase64()
{
    return QByteArray(REFERENCE_HASH_SLOT + REFERENCE_HASH_MARKER_LEN, REFERENCE_HASH_LEN);
}

namespace IntegrityCheck {

QByteArray calculateTextSegmentHash()
{
#ifdef Q_OS_WIN
    QWORD imageBase = (QWORD)GetModuleHandle(NULL);

    PIMAGE_DOS_HEADER dosHeader = reinterpret_cast<PIMAGE_DOS_HEADER>(imageBase);
    PIMAGE_NT_HEADERS peHeader = reinterpret_cast<PIMAGE_NT_HEADERS>(
        imageBase + dosHeader->e_lfanew);

    // Берём VirtualSize именно секции .text из таблицы секций, а не
    // агрегированный OptionalHeader.SizeOfCode — эти поля не обязаны
    // совпадать, и расхождение ломает сверку хешей на ровном месте.
    PIMAGE_SECTION_HEADER sectionHeader = IMAGE_FIRST_SECTION(peHeader);
    QWORD baseOfCode = 0;
    QWORD textSize = 0;
    for (WORD i = 0; i < peHeader->FileHeader.NumberOfSections; ++i) {
        if (memcmp(sectionHeader[i].Name, ".text", 5) == 0) {
            baseOfCode = sectionHeader[i].VirtualAddress;
            textSize = sectionHeader[i].Misc.VirtualSize;
            break;
        }
    }
    QWORD textBase = imageBase + baseOfCode;

    QByteArray textSegmentContents = QByteArray(
        reinterpret_cast<const char*>(textBase), static_cast<int>(textSize));
    QByteArray hash = QCryptographicHash::hash(
        textSegmentContents, QCryptographicHash::Sha256);
    QByteArray hashBase64 = hash.toBase64();

    qDebug() << "textBase =" << Qt::hex << textBase;
    qDebug() << "textSize =" << textSize;
    qDebug() << "calculatedTextHashBase64 =" << hashBase64;

    return hashBase64;
#else
    return {};
#endif
}

bool verify()
{
#ifdef Q_OS_WIN
    QByteArray current = calculateTextSegmentHash();
    QByteArray reference = referenceHashBase64();

    bool ok = (current == reference);
    qDebug() << "IntegrityCheck result =" << ok;
    return ok;
#else
    return true;
#endif
}

}
