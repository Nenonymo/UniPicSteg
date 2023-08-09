#include "keyShaping.h"

template <typename T>
void printKey(T data)
{
    printf("Alpha=%d, len=%d, seed=[%.5f;%.5f;%.5f;%.5f;%.5f;%.5f]\n",
        data.alpha, data.len, data.seed[0], data.seed[1], data.seed[2],
        data.seed[3], data.seed[4], data.seed[5]);
    printf("size of the key: %ld {%ld, %ld, %ld}\n", sizeof(T), sizeof(data.alpha), sizeof(data.len), sizeof(data.seed[0]));
}
template void printKey<const KeyData&>(const KeyData& data);
template void printKey<KeyData&>(KeyData& data);

std::string serialize(const KeyData& data)
{
    std::string binary((char*)&data, sizeof(KeyData));
    return base64_encode((const unsigned char*)binary.data(), binary.size());
}

KeyData deserialize(const std::string& str)
{
    std::string binary = base64_decode(str);
    KeyData output;
    std::memcpy(&output, binary.data(), sizeof(KeyData));
    return output;
}

