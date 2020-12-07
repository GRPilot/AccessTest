#include "platform.h"

namespace p {

QString encode(const QString &text) {
    return QCryptographicHash::hash(
                text.toStdString().c_str(),
                QCryptographicHash::Md5
           ).toHex();
}

}
