#pragma once

#include <vector>
#include <string>
#include <stdint.h>
#include <memory>
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#ifndef _WIN32
#include <arpa/inet.h>
#else
#include <winsock2.h>
#include <ws2tcpip.h>
#endif

class BinaryWriter
{

public:
	BinaryWriter(uint32_t defaultBufferSize = 1024*1024);

	template<class T> 
	void writeData(const T *t, uint64_t len = 0);

	void writeU8(uint8_t data);
	void writeU16(uint16_t data);
	void writeU32(uint32_t data);
	void writeS8(int8_t data);
	void writeS16(int16_t data);
	void writeS32(int32_t data);
	void writeFloat(float data);
	void writeString(const std::string &str);
	void writeVec2(const glm::vec2 &v);
	void writeVec3(const glm::vec3 &v);
	void writeVec4(const glm::vec4 &v);
	void writeQuat(const glm::quat &q);
	void writeMat3(const glm::mat3 &m);
	void writeMat4(const glm::mat4 &m);

	void saveToFile(const std::string &file);

private:
	std::vector<uint8_t> m_buffer;
};

class BinaryReader
{

public:
	BinaryReader(const std::string &file);
	BinaryReader(std::vector<uint8_t> &buffer);

	template <class T>
	T readData(uint32_t len = 0);

	uint8_t     readU8();
	uint16_t    readU16();
	uint32_t    readU32();
	int8_t      readS8();
	int16_t     readS16();
	int32_t     readS32();
	float       readFloat();
	std::string readString();
	glm::vec2   readVec2();
	glm::vec3   readVec3();
	glm::vec4   readVec4();
	glm::quat   readQuat();
	glm::mat3   readMat3();
	glm::mat4   readMat4();

private:
	std::vector<uint8_t> m_buffer;
	uint64_t m_bufferOffset;
};
