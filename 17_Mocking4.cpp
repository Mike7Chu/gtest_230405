// 17_Mocking4.cpp
#include <iostream>

struct Packet { };

class IPacketStream {
public:
    virtual ~IPacketStream() { }

    virtual void AppendPacket(Packet* newPacket) = 0;
    virtual const Packet* GetPacket(size_t packetNumber) const = 0;
};

class PacketStream : public IPacketStream {
public:
    void AppendPacket(Packet* newPacket) override
    {
        std::cout << "Append Packet" << std::endl;
    }

    const Packet* GetPacket(size_t packetNumber) const override
    {
        std::cout << "GetPacket" << std::endl;
        return nullptr;
    }
};

class PacketReader {
public:
    void ReadPacket(IPacketStream* stream, size_t packetNumber)
    {
        // ...
        stream->AppendPacket(nullptr);
        stream->GetPacket(packetNumber);
        // ...
    }
};
//----
#include <gmock/gmock.h>

class MockPacketStream : public IPacketStream {
public:
    //  virtual void AppendPacket(Packet* newPacket) = 0;
    //  virtual const Packet* GetPacket(size_t packetNumber) const = 0;
    MOCK_METHOD(void, AppendPacket, (Packet * newPacket), (override));
    MOCK_METHOD(const Packet*, GetPacket, (size_t packetNumber), (const, override));
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