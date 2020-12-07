#pragma once

namespace Access {

enum{
    None = 0x00,
    Read = 0x01,
    Write = 0x02,
};
using access_t = unsigned char;

}
