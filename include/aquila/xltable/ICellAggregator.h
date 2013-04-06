#pragma once
/**
 *=============================================================================
 * 2011/03/28
 * $Id: ICellAggregator.h 104 2011-08-15 09:47:48Z whirlwind $
 * Агрегатор ячеек XlTable
 *=============================================================================
 */

#include "aquila/xltable/ICell.h"
#include "aquila/xltable/XltException.h"

namespace aquila {
	namespace xltable {

		class ICellAggregator : public IReferenceCounted {
		public:
			virtual ~ICellAggregator(void) { }

			/**
			 * Получить количество ячеек
			 *
			 * Возвращает количество агрегированных ячеек.
			 */
			virtual unsigned int getCellCount()=0;

			/**
			 * Получить ячейку по индексу
			 *
			 * Возвращает экземпляр ячейки с указанным индексом.
			 * Выбрасывает исключение, производное от
			 * XltException, если ячейка с таким индексом
			 * отсутствует или не проинициализирована.
			 */
			virtual ICell* getCell(unsigned int index)=0;

			/**
			 * Добавить ячейку вещественного типа
			 */
			virtual unsigned int addFloat(double value)=0;

			/**
			 * Добавить ячейку булева типа
			 */
			virtual unsigned int addBoolean(bool value)=0;

			/**
			 * Добавить ячейку строкового типа
			 */
			virtual unsigned int addString(const char* lpstr, int size)=0;

			/**
			 * Добавить ячейку целочисленного типа
			 */
			virtual unsigned int addInteger(int value)=0;

			/**
			 * Добавить ячейку типа ошибка
			 */
			virtual unsigned int addError()=0;

			/**
			 * Добавить пустую ячейку
			 */
			virtual unsigned int addBlank()=0;

			/**
			 * Добавить пропуск
			 */
			virtual unsigned int addSkip()=0;

		};

	} // end namespace xltable
} // end namespace aquila