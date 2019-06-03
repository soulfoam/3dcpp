#include <iostream>
#include <fstream>
#include <cstring>
#include "io.hpp"

static inline float 
htonf(float val) 
{
    uint32_t rep;
    memcpy(&rep, &val, sizeof(rep));
    rep = htonl(rep);
    memcpy(&val, &rep, sizeof(rep));
    return val;
}

static inline float 
ntohf(float val) 
{
    uint32_t rep;
    memcpy(&rep, &val, sizeof(rep));
    rep = ntohl(rep);
    memcpy(&val, &rep, sizeof(rep));
    return val;
}

BinaryWriter::BinaryWriter(uint32_t defaultBufferSize)
{
	m_buffer.reserve(defaultBufferSize);
}

template<class T>
void BinaryWriter::writeData(const T *t, uint64_t len)
{
	if (len == 0) len = sizeof(T);
	const char *buffer = reinterpret_cast<const char*>(t);
	m_buffer.insert(m_buffer.end(), buffer, buffer + len);
}

void 
BinaryWriter::writeU8(uint8_t data)
{
	writeData(&data);
}

void 
BinaryWriter::writeU16(uint16_t data)
{
	data = htons(data);
	writeData(&data);
}

void 
BinaryWriter::writeU32(uint32_t data)
{
	data = htonl(data);
	writeData(&data);
}

void 
BinaryWriter::writeS8(int8_t data)
{
	writeData(&data);
}

void 
BinaryWriter::writeS16(int16_t data)
{
	data = htons(data);
	writeData(&data);
}

void 
BinaryWriter::writeS32(int32_t data)
{
	data = htonl(data);
	writeData(&data);
}

void 
BinaryWriter::writeFloat(float data)
{
	data = htonf(data);
	writeData(&data);
}

void 
BinaryWriter::writeString(const std::string &str)
{
	writeU32(str.size());
	writeData(str.c_str(), str.size());
}

void 
BinaryWriter::writeVec2(const glm::vec2 &v)
{
	writeFloat(v.x);
	writeFloat(v.y);
}

void 
BinaryWriter::writeVec3(const glm::vec3 &v)
{
	writeFloat(v.x);
	writeFloat(v.y);
	writeFloat(v.z);
}

void 
BinaryWriter::writeVec4(const glm::vec4 &v)
{
	writeFloat(v.x);
	writeFloat(v.y);
	writeFloat(v.z);
	writeFloat(v.w);
}

void 
BinaryWriter::writeQuat(const glm::quat &q)
{
	writeFloat(q.x);
	writeFloat(q.y);
	writeFloat(q.z);
	writeFloat(q.w);
}

void 
BinaryWriter::writeMat3(const glm::mat3 &m)
{
	for (int col = 0; col < 4; col++)
	{
		for (int row = 0; row < 4; row++)
		{
			writeFloat(m[col][row]);
		}
	}
}

void 
BinaryWriter::writeMat4(const glm::mat4 &m)
{
	for (int col = 0; col < 4; col++)
	{
		for (int row = 0; row < 4; row++)
		{
			writeFloat(m[col][row]);
		}
	}
}

void 
BinaryWriter::saveToFile(const std::string &file)
{
	std::ofstream out(file, std::ios::out | std::ios::binary);
	out.write(reinterpret_cast<char*>(&m_buffer[0]), m_buffer.size());
}

BinaryReader::BinaryReader(const std::string &file)
	:	
	m_bufferOffset(0)
{
	std::ifstream in(file, std::ios::binary | std::ios::ate);
	auto size = in.tellg();

	m_buffer.reserve(size);

	in.seekg(0, std::ios::beg);
	in.read(reinterpret_cast<char*>(&m_buffer[0]), size);
	
}

BinaryReader::BinaryReader(std::vector<uint8_t> &buffer)
	:
	m_bufferOffset(0)
{	
	m_buffer = std::move(buffer);
}

template <class T>
T BinaryReader::readData(uint32_t len)
{
	if (len == 0) len = sizeof(T);	

	T ret;

	if ((m_bufferOffset + len) > m_buffer.capacity())
	{
		std::cout << "BinaryReader is out of data. (Read: " << m_bufferOffset << ")" << std::endl;
		return ret;
	}

	std::memcpy(&ret, &m_buffer[0] + m_bufferOffset, len);
	m_bufferOffset += len;

	return ret;
}

uint8_t
BinaryReader::readU8()
{
	return readData<uint8_t>();		
}

uint16_t
BinaryReader::readU16()
{
	uint16_t data = readData<uint16_t>();	
	return ntohs(data);
}

uint32_t
BinaryReader::readU32()
{
	uint32_t data = readData<uint32_t>();	
	return ntohl(data);
}

int8_t
BinaryReader::readS8()
{
	return readData<int8_t>();		
}

int16_t
BinaryReader::readS16()
{
	int16_t data = readData<int16_t>();	
	return ntohs(data);
}

int32_t
BinaryReader::readS32()
{
	int32_t data = readData<int32_t>();	
	return ntohl(data);
}

float
BinaryReader::readFloat()
{
	float data = readData<float>();	
	return ntohf(data);
}

std::string
BinaryReader::readString()
{
	uint32_t size = readU32();
	std::string ret(&m_buffer[0] + m_bufferOffset, &m_buffer[0] + m_bufferOffset + size);
	m_bufferOffset += size;
	return ret;
}

glm::vec2 
BinaryReader::readVec2()
{
	float x = readFloat();
	float y = readFloat();
	return glm::vec2(x, y);
}

glm::vec3
BinaryReader::readVec3()
{
	float x = readFloat();
	float y = readFloat();
	float z = readFloat();
	return glm::vec3(x, y, z);
}

glm::vec4
BinaryReader::readVec4()
{
	float x = readFloat();
	float y = readFloat();
	float z = readFloat();
	float w = readFloat();
	return glm::vec4(x, y, z, w);
}

glm::quat
BinaryReader::readQuat()
{
	float x = readFloat();
	float y = readFloat();
	float z = readFloat();
	float w = readFloat();
	return glm::quat(x, y, z, w);
}

glm::mat3
BinaryReader::readMat3()
{
	glm::mat3 m;
	for (int row = 0; row < 3; row++)
	{
		for (int col = 0; col < 3; col++)
		{
			m[col][row] = readFloat();
		}
	}

	return m;
}

glm::mat4
BinaryReader::readMat4()
{
	glm::mat4 m;
	for (int col = 0; col < 4; col++)
	{
		for (int row = 0; row < 4; row++)
		{
			m[col][row] = readFloat();
		}
	}

	return m;
}
