#pragma once
/**
 *=============================================================================
 * 2011/03/28
 * $Id: DataStream.h 104 2011-08-15 09:47:48Z whirlwind $
 * Реализация объекта доступа к потока данных. Данный класс не реализует
 * механизм выделения памяти, а только соответствующие методы доступа.
 * Реализуйте специфический механизм формирования буфера данных в наследниках.
 *=============================================================================
 */

#include "aquila/core/auto_grab.h"
#include "aquila/core/IDataBuffer.h"
#include "aquila/xltable/IDataStream.h"

using namespace aquila::core;

namespace aquila {
	namespace xltable {

		class DataStream : public IDataStream {
		public:

			DataStream(IDataBuffer* data) :
				dataBuffer(data), offset(0)
			{
				buffer = dataBuffer->getPointer();
				length = dataBuffer->getSize();
			}

			DataStream(LPBYTE streamData, unsigned int size) :
				offset(0)
			{
				buffer = streamData;
				length = size;
			}

			virtual ~DataStream(void) {

			}

			inline unsigned int getLength() {
				return length;
			}

			inline unsigned int getOffset() {
				return offset;
			}

			inline BYTE readByte() {
				if ( offset >= length ) {
					return 0;
				}
				BYTE v = buffer[offset];
				offset += sizeof(BYTE);
				return v;
			}

			inline WORD readWord() {
				if ( offset >= length ) {
					return 0;
				}
				WORD v = *((WORD*)(buffer + offset));
				offset += sizeof(WORD);
				return v;
			}

			inline DWORD readDword() {
				if ( offset >= length ) {
					return 0;
				}
				DWORD v = *((DWORD*)(buffer + offset));
				offset += sizeof(DWORD);
				return v;
			}

			inline const char* readString(size_t size) {
				if ( offset >= length ) {
					return "";
				}
				const char* lpstr = (const char*)(buffer + offset);
				offset += size;
				return lpstr;
			}

			inline double readFloat() {
				if ( offset >= length ) {
					return 0;
				}
				double v = *((double*)(buffer + offset));
				offset += 8;
				return v;
			}

		private:
			unsigned int length;
			unsigned int offset;
			LPBYTE	buffer;
			auto_grab<IDataBuffer> dataBuffer;
		};

	} // end namespace xltable
} // end namespace aquila