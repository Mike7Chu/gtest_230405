// 17_Mocking5.cpp
#include <iostream>

struct Packet { };

class PacketStream {
public:
    void AppendPacket(Packet* newPacket)
    {
        std::cout << "Append Packet" << std::endl;
    }

    const Packet* GetPacket(size_t packetNumber) const
    {
        std::cout << "GetPacket" << std::endl;
        return nullptr;
    }
};

class MyPacketStream {
public:
    void AppendPacket(Packet* newPacket)
    {
        std::cout << "MyPacketStream Append Packet" << std::endl;
    }

    const Packet* GetPacket(size_t packetNumber) const
    {
        std::cout << "MyPacketStream GetPacket" << std::endl;
        return nullptr;
    }
};

class PacketReader {
public:
    // 암묵적 인터페이스
    // => Policy Based Design(단위 전략)
    template <typename Stream>
    void ReadPacket(Stream* stream, size_t packetNumber)
    {
        // ...
        stream->AppendPacket(nullptr);
        stream->GetPacket(packetNumber);
        // ...
    }
};

#include <gmock/gmock.h>

// 단위 전략에서도 행위 기반 검증을 수행할 수 있습니다.
class MockPacketStream {
public:
    // void AppendPacket(Packet* newPacket)
    MOCK_METHOD(void, AppendPacket, (Packet * newPacket));

    // const Packet* GetPacket(size_t packetNumber)
    MOCK_METHOD(const Packet*, GetPacket, (size_t packetNumber), (const));
};

TEST(PacketReaderTest, Sample)
{
    // 제품 코드가 사용하는 방식
    // PacketStream stream;
    // PacketReader reader;
    // reader.ReadPacket(&stream, 42);

    MockPacketStream mock;
    PacketReader reader;

    EXPECT_CALL(mock, AppendPacket(nullptr));
    EXPECT_CALL(mock, GetPacket(42));

    reader.ReadPacket(&mock, 42);
}