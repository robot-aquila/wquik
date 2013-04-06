#pragma once
/**
 *=============================================================================
 * 2011/03/28
 * $Id$
 * Интерфейс ячейки XlTable
 *=============================================================================
 */

#include "aquila/core/IReferenceCounted.h"
#include <string>

using namespace std;
using namespace aquila::core;

namespace aquila {
	namespace xltable {

		class ICell : public IReferenceCounted {
		public:
			virtual ~ICell(void){}

			/**
			 * Проверка типа
			 *
			 * Возвращает true, если ячейка типа float
			 */
			virtual bool isFloat()=0;

			/**
			 * Проверка типа
			 *
			 * Возвращает true, если ячейка булева типа
			 */
			virtual bool isBoolean()=0;

			/**
			 * Проверка типа
			 *
			 * Возвращает true, если ячейка строкового типа
			 */
			virtual bool isString()=0;

			/**
			 * Проверка типа
			 *
			 * Возвращает true, если ячейка целочисленного типа
			 */
			virtual bool isInteger()=0;

			/**
			 * Проверка типа
			 *
			 * Возвращает true, если ячейка типа ошибка
			 */
			virtual bool isError()=0;

			/**
			 * Проверка типа
			 *
			 * Возвращает true, если пустая ячейка
			 */
			virtual bool isBlank()=0;

			/**
			 * Проверка типа
			 *
			 * Возвращает true, если значение ячейки неизменно (пропуск)
			 */
			virtual bool isSkip()=0;

			/**
			 * Получить в виде вещественного числа
			 *
			 * Возвращает значение ячейки типа float
			 * или 0.0, для ячеек другого типа.
			 */
			virtual double asFloat()=0;

			/**
			 * Получить в виде булева значения
			 *
			 * Для ячеек булева типа возвращает значение ячейки.
			 * Для ячеек другого типа всегда возвращает false.
			 */
			virtual bool asBoolean()=0;

			/**
			 * Получить в виде строки
			 *
			 * Для ячеек строкового типа возвращает значение ячейки.
			 * Для ячеек других типов всегда возвращает пустую строку.
			 */
			virtual string asString()=0;

			/**
			 * Получить в виде целого
			 *
			 * Для ячеек целочисленного типа возвращает значение ячейки.
			 * Для ячеек других типов всегда возвращает 0.
			 */
			virtual int asInteger()=0;

		};

	} // end namespace xltable
} // end namespace aquila